using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using System.Runtime.InteropServices;	//DllImport

namespace SerialPort
{
    public partial class frmMain : Form
    {
        [StructLayout(LayoutKind.Sequential,Pack=4)]
        public struct OVERLAPPED
        {
            public IntPtr Internal;
            public IntPtr InternalHigh;
            public UInt32 Offset;
            public UInt32 OffsetHigh;
            public IntPtr hEvent; 
        }
        [DllImport("kernel32.dll", SetLastError = true, CallingConvention = CallingConvention.Winapi)]
        private static extern UInt32 WriteFile(IntPtr hFile, byte[] lpBuffer, UInt32 nNumberOfBytesToWrite, ref UInt32 lpNumberOfBytesWritten, ref OVERLAPPED lpOverlapped);
        
        protected System.IO.Ports.SerialPort m_sp = new System.IO.Ports.SerialPort();
        protected OVERLAPPED    m_ov;
        protected Object        m_Lock      =   new Object();
        protected const int     m_nMaxRecv  =   8192;
        protected byte[]        m_dataRecv  =   new byte[m_nMaxRecv];//接收到的数据
        protected int           m_nRecv     =   0;  //接收到的字节数
        protected bool          m_bDirty    =   false;

        public frmMain()
        {            
            InitializeComponent();
        }
        /***************************************************************\
        从字符串里提取整数
        s   [in]    字符串
        返回：提取出来的整数，-1 表示错误
        \***************************************************************/
        static int GetIntInStr(string s)
        {
            bool	bOK     =	false; 	//是否发现了数字
            int		n		=	0;
            int     nLenS   =   s.Length;
            char    c		=	'\0';
            for(int i = 0;i < nLenS;++i)
            {
                c   =   s[i];
                if(c >= '0' && c <= '9')
                {
                    bOK	=	true;
                    n   =   n * 10 + (c - '0');
                }
            }
            if(!bOK)
            {
                n	=	-1;//没有数字，返回 -1
            }
            return n;
        }
        //获得串口句柄，供 Win32 API 使用
        static IntPtr GetCommHandle(System.IO.Ports.SerialPort sp)
        {
            IntPtr hComm = IntPtr.Zero;
            if (sp != null)
            {
                object stream = typeof(System.IO.Ports.SerialPort).GetField("internalSerialStream", System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance).GetValue(sp);
                var handle = (Microsoft.Win32.SafeHandles.SafeFileHandle)stream.GetType().GetField("_handle", System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance).GetValue(stream);
                hComm = handle.DangerousGetHandle();
            }
            return hComm;
        }
        private void frmMain_Load(object sender, EventArgs e)
        {
            cboCOM.Items.Clear();
            string[] arrPort = System.IO.Ports.SerialPort.GetPortNames();
            if(arrPort.Length > 0)
            {                
                IEnumerable<string> query = arrPort.OrderBy(s => GetIntInStr(s));
                bool bFirst = true;
                foreach(string s in query)
                {
                    if (s.StartsWith("COM"))
                    {                        
                        if (bFirst)
                        {
                            cboCOM.Text = s.Substring(3);
                            bFirst = false;
                        }
                        cboCOM.Items.Add(s.Substring(3));
                    }
                }
            }
            cboBaud.Text = "9600";
            cboParity.SelectedIndex = 0;
            cboData.SelectedItem = "8";
            cboStop.SelectedItem = "1";
            m_sp.ReceivedBytesThreshold = 1;
            m_sp.DataReceived+=new System.IO.Ports.SerialDataReceivedEventHandler(m_sp_DataReceived);
            EnableControls();
        }
        private void frmMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            try
            {
                if (m_sp.IsOpen)
                {//关闭串口
                    m_sp.Close();
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        private void EnableControls()
        {
            bool bOpen = m_sp.IsOpen;
            cboCOM.Enabled = !bOpen;
            cboBaud.Enabled = !bOpen;
            cboParity.Enabled = !bOpen;
            cboData.Enabled = !bOpen;
            cboStop.Enabled = !bOpen;
            chkXON.Enabled = !bOpen;
            chkRTS.Enabled = !bOpen;
            btnOpen.Enabled = !bOpen;
            btnClose.Enabled = bOpen;
            txtSend.ReadOnly = !bOpen;
            btnWriteSync.Enabled = bOpen;
            btnWriteAsync.Enabled = bOpen;
        }
        private void btnOpen_Click(object sender, EventArgs e)
        {
            m_nRecv = 0;
            txtRecv.Text = "";
            try
            {
                if (m_sp.IsOpen)
                {//关闭串口
                    m_sp.Close();
                }
                m_sp.PortName = "COM" + cboCOM.Text;        //COM 口
                m_sp.BaudRate = int.Parse(cboBaud.Text);    //波特率
                switch (cboParity.Text[0])
                {//校验法
                    case 'N': m_sp.Parity = System.IO.Ports.Parity.None; break;
                    case 'O': m_sp.Parity = System.IO.Ports.Parity.Odd; break;
                    case 'E': m_sp.Parity = System.IO.Ports.Parity.Even; break;
                    case 'M': m_sp.Parity = System.IO.Ports.Parity.Mark; break;
                    case 'S': m_sp.Parity = System.IO.Ports.Parity.Space; break;
                }
                m_sp.DataBits = int.Parse(cboData.Text);    //数据位
                switch (cboStop.Text)
                {//停止位
                    case "1": m_sp.StopBits = System.IO.Ports.StopBits.One; break;
                    case "2": m_sp.StopBits = System.IO.Ports.StopBits.Two; break;
                    case "1.5": m_sp.StopBits = System.IO.Ports.StopBits.OnePointFive; break;
                }
                //流控制
                int nFlow = 0;
                if (chkXON.Checked)
                {//软件流控制
                    nFlow |= 1;
                }
                if (chkRTS.Checked)
                {//硬件流控制
                    nFlow |= 2;
                }
                switch (nFlow)
                {
                    case 0: m_sp.Handshake = System.IO.Ports.Handshake.None; break;
                    case 1: m_sp.Handshake = System.IO.Ports.Handshake.XOnXOff; break;
                    case 2: m_sp.Handshake = System.IO.Ports.Handshake.RequestToSend; break;
                    case 3: m_sp.Handshake = System.IO.Ports.Handshake.RequestToSendXOnXOff; break;
                }
                m_sp.Open();
                m_sp.DtrEnable = true;
                if((nFlow & 2) == 0)
                {//未使用 RTS 硬件流控制时，才能设置 RTS 的信号
                    m_sp.RtsEnable = true;
                }                
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);                
            }
            EnableControls();
        }
        private void btnClose_Click(object sender, EventArgs e)
        {
            try
            {
                if (m_sp.IsOpen)
                {//关闭串口
                    m_sp.Close();
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            EnableControls();
        }
        private void btnWriteSync_Click(object sender, EventArgs e)
        {//同步写
            m_sp.Encoding = System.Text.Encoding.Default;               
            m_sp.Write(txtSend.Text);
        }        
        private void btnWriteAsync_Click(object sender, EventArgs e)
        {//异步写
            byte[] byt = System.Text.Encoding.Default.GetBytes(txtSend.Text);
            if(byt!=null && byt.Length > 0)
            {
                IntPtr hComm = GetCommHandle(m_sp);
                UInt32 w = 0;
                m_ov.hEvent = IntPtr.Zero;
                m_ov.Internal = IntPtr.Zero;
                m_ov.InternalHigh = IntPtr.Zero;
                m_ov.Offset = 0;
                m_ov.OffsetHigh = 0;
                UInt32 nRet = WriteFile(hComm, byt, (UInt32)byt.Length, ref w, ref m_ov);
            }
        }
        void m_sp_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {//接收串口数据
            int nRead = m_sp.BytesToRead;
            if (nRead > 0)
            {
                byte[] dataRead = new byte[nRead];
                nRead   =   m_sp.Read(dataRead, 0, nRead);
                if (nRead > 0)
                {//把读取到的数据 dataRead 填入 m_dataRecv。填不下的话，舍弃前面的数据
                    lock (m_Lock)
                    {
                        if(nRead >= m_nMaxRecv)
                        {
                            Array.Copy(dataRead, nRead - m_nMaxRecv, m_dataRecv, 0, m_nRecv = m_nMaxRecv);
                        }
                        else if (m_nRecv + nRead > m_nMaxRecv)
                        {
                            Array.Copy(m_dataRecv, m_nRecv + nRead - m_nMaxRecv, m_dataRecv, 0, m_nMaxRecv - nRead);
                            Array.Copy(dataRead, 0, m_dataRecv, m_nMaxRecv - nRead, nRead);
                            m_nRecv = m_nMaxRecv;
                        }
                        else
                        {
                            Array.Copy(dataRead, 0, m_dataRecv, m_nRecv,nRead);
                            m_nRecv += nRead;
                        }
                        m_bDirty    =   true;
                    }
                }
            }
        }
        private void timer1_Tick(object sender, EventArgs e)
        {//更新界面显示
            if (m_bDirty)
            {
                string sText = null;
                lock (m_Lock)
                {
                    sText = System.Text.Encoding.Default.GetString(m_dataRecv, 0, m_nRecv);
                    m_bDirty = false;
                }
                txtRecv.Text = sText;
                txtRecv.SelectionStart = sText.Length;
                txtRecv.ScrollToCaret();
            }
        }
    }
}
