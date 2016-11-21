//User must modify the below package with their package name
package com.UARTLoopback;

import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.hardware.usb.UsbAccessory;
import android.hardware.usb.UsbManager;
import android.os.ParcelFileDescriptor;

/******************************************************************************\
 用于串口通讯
\******************************************************************************/
public class FT311UARTInterface
{
    private static final String     ACTION_USB_PERMISSION   =   "com.UARTLoopback.USB_PERMISSION";
    private UsbManager              m_UsbManager            =   null;
    private PendingIntent           m_PermissionIntent      =   null;   //用于请求权限
    private boolean                 m_bPermissionRequest    =   false;  //是否已经请求操作 USB 的权限了
    private ParcelFileDescriptor    m_FileDescriptor        =   null;   //USB 附件文件描述符
    private FileInputStream         m_InputStream           =   null;   //用于读USB 附件
    private FileOutputStream        m_OutputStream          =   null;   //用于写USB 附件

    private byte[]                  m_Buffer                =   null;   //输入缓冲区
    private int                     m_nBufferSize           =   1024;   //输入缓冲区大小
    private int                     m_nBufferW              =   0;      //输入缓冲区写的位置
    private int                     m_nBufferR              =   0;      //输入缓冲区读的位置
    private Lock                    m_Lock                  =   new ReentrantLock();
    private EventDataReceived       m_EventDataReceived     =   null;   //读取到数据事件
    private EventPlugPull           m_EventPlugPull         =   null;   //插拔事件
    private boolean                 m_bConfig               =   true;   //需要配置

    public interface EventDataReceived
    {
        void onEvent(byte[] data,int nBytes);   //读取到串口数据
    }
    public interface EventPlugPull
    {
        void onEvent(int nPlugPull);    //nPlugPull 0-拔出  1-插入(未实现)
    }
    private static void Thread_sleep(long ms)
    {
        try
        {
            Thread.sleep(ms);
        } catch (InterruptedException ex)
        {
        }
    }
    private static int FileInputStream_read(FileInputStream s, byte[] data, int nBytes)
    {
        if (s != null && data != null && nBytes > 0)
        {
            try
            {
                return s.read(data, 0, nBytes);
            }
            catch (IOException e)
            {
            }
        }
        return 0;
    }
    private static void FileInputStream_close(FileInputStream s)
    {
        if (s != null)
        {
            try
            {
                s.close();
            } catch (IOException e)
            {
            }
        }
    }
    private static void FileOutputStream_write(FileOutputStream s, byte[] data, int nBytes)
    {
        if (s != null && data != null && nBytes > 0)
        {
            try
            {
                s.write(data, 0, nBytes);
            } catch (IOException e)
            {
            }
        }
    }
    private static void FileOutputStream_close(FileOutputStream s)
    {
        if (s != null)
        {
            try
            {
                s.close();
            } catch (IOException e)
            {
            }
        }
    }
    private static void ParcelFileDescriptor_close(ParcelFileDescriptor s)
    {
        if (s != null)
        {
            try
            {
                s.close();
            } catch (IOException e)
            {
            }
        }
    }
    //构造函数
    public FT311UARTInterface(Context context)
    {
        super();
        m_Buffer = new byte[m_nBufferSize];
        m_InputStream = null;
        m_OutputStream = null;
        m_UsbManager = (UsbManager) context.getSystemService(Context.USB_SERVICE);
        m_PermissionIntent = PendingIntent.getBroadcast(context, 0, new Intent(ACTION_USB_PERMISSION), 0);
        {//注册需要接收的广播
            IntentFilter filter = new IntentFilter(ACTION_USB_PERMISSION);  //申请权限
            filter.addAction(UsbManager.ACTION_USB_ACCESSORY_DETACHED);     //拔出
            context.registerReceiver(m_UsbReceiver, filter);                //注册
        }
    }
    /**************************************************************************\
    配置串口
    baud        [in]    波特率 [300,921600]
    parity      [in]    校验法 0: none, 1: odd, 2: even, 3: mark, 4: space
    dataBits    [in]    数据位 7 或 8
    stopBits    [in]    停止位 1 或 2
    flow        [in]    流控制 0:none, 1: RTS/CTS
    注意：从插入到拔出，只能配置一次
    \**************************************************************************/
    private void config(int baud, char parity, int dataBits, int stopBits, int flow)
    {
        byte[] data = new byte[8];
        //波特率
        if(baud < 300)
        {
            baud    =   300;
        }
        else if(baud > 921600)
        {
            baud    =   921600;
        }
        data[0] = (byte) baud;
        data[1] = (byte) (baud >> 8);
        data[2] = (byte) (baud >> 16);
        data[3] = (byte) (baud >> 24);
        //校验法
        switch (parity)
        {
        case 0:
        case 'n':
        case 'N':
            parity = 0;
            break;
        case 1:
        case 'o':
        case 'O':
            parity = 1;
            break;
        case 2:
        case 'e':
        case 'E':
            parity = 2;
            break;
        case 3:
        case 'm':
        case 'M':
            parity = 3;
            break;
        case 4:
        case 's':
        case 'S':
            parity = 4;
            break;
        default:
            parity = 0;
            break;
        }
        data[6] = (byte) parity;
        //数据位
        if(dataBits < 7)
        {
            dataBits = 7;
        }
        else if(dataBits > 8)
        {
            dataBits = 8;
        }
        data[4] = (byte) dataBits;
        //停止位
        if(stopBits < 1)
        {
            stopBits = 1;
        }
        else if(stopBits > 2)
        {
            stopBits = 2;
        }
        data[5] = (byte) stopBits;
        //流控制
        if(flow < 0)
        {
            flow    =   0;
        }
        else if(flow > 1)
        {
            flow    =   1;
        }
        data[7] = (byte) flow;
        //发送数据
        FileOutputStream_write(m_OutputStream,data,data.length);
    }
    //写数据
    public void write(byte[] buffer, int nBytes)
    {
        if (buffer != null && nBytes > 0)
        {
            if(nBytes == 64)
            {//不知道为什么，64 字节要分两次写
                byte[] data =   new byte[1];
                data[0]     =   buffer[63];
                FileOutputStream_write(m_OutputStream, buffer, 63);
                FileOutputStream_write(m_OutputStream, data,1);
            }
            else
            {
                FileOutputStream_write(m_OutputStream, buffer, nBytes);
            }
        }
    }
    //读数据
    public int read(byte[] buffer, int nBytes)
    {
        m_Lock.lock();
        int nBufferByte =   m_nBufferW - m_nBufferR;
        if(nBufferByte < 0)
        {
            nBufferByte += m_nBufferSize;
        }
        if(buffer != null && nBytes > 0 && nBufferByte > 0)
        {
            if (nBytes > nBufferByte)
            {
                nBytes = nBufferByte;
            }
            for (int i = 0; i < nBytes; ++i)
            {
                buffer[i] = m_Buffer[m_nBufferR];
                if(++m_nBufferR >= m_nBufferSize)
                {
                    m_nBufferR  =   0;
                }
            }
        }
        else
        {
            nBytes = 0;
        }
        m_Lock.unlock();
        return nBytes;
    }
    //设置数据接收事件处理器
    public void setEventDataReceived(EventDataReceived e)
    {
        m_Lock.lock();
        m_EventDataReceived     =   e;
        m_Lock.unlock();
    }
    //设置插拔事件处理器
    public void setEventPlugPull(EventPlugPull e)
    {
        m_Lock.lock();
        m_EventPlugPull     =   e;
        m_Lock.unlock();
    }
    //设置缓冲区大小
    public void setBufferSize(int nSize)
    {
        m_Lock.lock();
        if(nSize > 0)
        {
            if(nSize > m_nBufferSize)
            {//重新分配内存
                m_Buffer    =   new byte[nSize];
            }
            m_nBufferSize   =   nSize;  //输入缓冲区大小
            m_nBufferW      =   0;      //输入缓冲区写的位置
            m_nBufferR      =   0;      //输入缓冲区读的位置
        }
        m_Lock.unlock();
    }
    //获取缓冲区内的字节数
    public int BytesInBuffer()
    {
        m_Lock.lock();
        int nBufferByte =   m_nBufferW - m_nBufferR;
        if(nBufferByte < 0)
        {
            nBufferByte    +=   m_nBufferSize;
        }
        m_Lock.unlock();
        return nBufferByte;
    }
    //清空缓冲区
    public void empty()
    {
        m_Lock.lock();
        m_nBufferW  =   0;  //输入缓冲区写的位置
        m_nBufferR  =   0;  //输入缓冲区读的位置
        m_Lock.unlock();
    }
    //是否已经连接
    public boolean isExist()
    {
        return FindAccessory() != null;
    }
    //是否已经打开
    public boolean isOpen()
    {
        return m_ThreadRead != null;
    }
    //检查 USB 附件是否已经有了权限
    public boolean hasPermission()
    {
        UsbAccessory acc = FindAccessory();
        return acc != null && m_UsbManager.hasPermission(acc);
    }
    //请求权限
    public void requestPermission()
    {
        UsbAccessory acc = FindAccessory();
        if(acc != null && !m_UsbManager.hasPermission(acc))
        {
            synchronized (m_UsbReceiver)
            {
                if(!m_bPermissionRequest)
                {
                    m_UsbManager.requestPermission(acc, m_PermissionIntent);
                    m_bPermissionRequest = true;
                }
            }
        }
    }
    //查找 USB 附件
    private UsbAccessory FindAccessory()
    {
        UsbAccessory[]  Accessory   =   m_UsbManager.getAccessoryList();
        if(Accessory != null)
        {
            String ManufacturerString   =   "mManufacturer=FTDI";
            String ModelString1         =   "mModel=FTDIUARTDemo";
            String ModelString2         =   "mModel=Android Accessory FT312D";
            String VersionString        =   "mVersion=1.0";
            String sAccessory;

            for(UsbAccessory acc : Accessory)
            {
                if (acc != null)
                {
                    sAccessory  =   acc.toString();
                    if (sAccessory.indexOf(ManufacturerString) >= 0
                    && (sAccessory.indexOf(ModelString1) >= 0 || sAccessory.indexOf(ModelString2) >= 0)
                    && sAccessory.indexOf(VersionString) >= 0)
                    {
                        return acc;
                    }
                }
            }
        }
        return null;
    }
    //打开串口
    public boolean open(int baud, char parity, int dataBits, int stopBits, int flow)
    {
        close();
        m_nBufferR  =   0;
        m_nBufferW  =   0;
        UsbAccessory acc = FindAccessory();
        if(acc != null && m_UsbManager.hasPermission(acc) && OpenAccessory(acc))
        {
            if(m_bConfig)
            {//需要配置
                config(baud, parity, dataBits, stopBits, flow);
                m_bConfig   =   false;
            }
            return true;
        }
        return false;
    }
    //关闭
    public void close()
    {
        if(m_ThreadRead != null)
        {
            m_ThreadRead.m_bExit    =   true;   //目前没有更好的退出方法
            m_ThreadRead            =   null;
        }
        FileInputStream_close(m_InputStream);
        FileOutputStream_close(m_OutputStream);
        ParcelFileDescriptor_close(m_FileDescriptor);
        m_InputStream = null;
        m_OutputStream = null;
        m_FileDescriptor = null;
    }
    //打开 USB 附件
    private boolean OpenAccessory(UsbAccessory accessory)
    {
        m_FileDescriptor = m_UsbManager.openAccessory(accessory);
        if (m_FileDescriptor != null)
        {
            FileDescriptor fd = m_FileDescriptor.getFileDescriptor();
            m_InputStream = new FileInputStream(fd);
            m_OutputStream = new FileOutputStream(fd);
            if (m_InputStream != null && m_OutputStream != null)
            {
                m_ThreadRead = new ThreadRead();
                m_ThreadRead.start();
                return true;
            }
        }
        close();
        return false;
    }
    //广播接收器
    private final BroadcastReceiver m_UsbReceiver = new BroadcastReceiver()
    {
        @Override
        public void onReceive(Context context, Intent intent)
        {
            String action = intent.getAction();
            if (ACTION_USB_PERMISSION.equals(action))
            {//代码 m_UsbManager.requestPermission 请求权限时
                synchronized (this)
                {
                    if(intent.getBooleanExtra(UsbManager.EXTRA_PERMISSION_GRANTED, false))
                    {
                        //UsbAccessory acc = (UsbAccessory) intent.getParcelableExtra(UsbManager.EXTRA_ACCESSORY);
                        //OpenAccessory(acc);
                    }
                    m_bPermissionRequest = false;
                }
            }
            else if (UsbManager.ACTION_USB_ACCESSORY_DETACHED.equals(action))
            {//拔出 USB 转串口设备
                m_Lock.lock();
                EventPlugPull ePlugPull =   m_EventPlugPull;
                m_Lock.unlock();
                if(ePlugPull != null)
                {
                    ePlugPull.onEvent(0);
                }
                close();
                m_bConfig   =   true;   //下次 open 时，发送配置
            }
        }
    };
    ThreadRead m_ThreadRead =   null;   //读取数据的线程
    //读取数据的线程
    private class ThreadRead extends Thread
    {
        public boolean m_bExit = false;
        ThreadRead()
        {
            //setPriority(Thread.MAX_PRIORITY);   //调整线程优先级别
        }
        public void run()
        {
            byte[]  data    =   new byte[1024];
            int     nRead   =   0;
            int     i       =   0;
            for(;;)
            {
                if(m_bExit)
                {
                    break;
                }
                nRead   =   FileInputStream_read(m_InputStream,data,data.length);   //这个函数阻塞，没有好办法退出线程
                if(nRead > 0)
                {
                    if(m_bExit)
                    {
                        break;
                    }
                    m_Lock.lock();
                    EventDataReceived eDataReceived =   m_EventDataReceived;
                    m_Lock.unlock();
                    if(eDataReceived != null)
                    {
                        eDataReceived.onEvent(data,nRead);
                    }
                    else
                    {
                        m_Lock.lock();
                        for( i = 0; i < nRead; ++i)
                        {
                            m_Buffer[m_nBufferW]    =   data[i];
                            if(++m_nBufferW >= m_nBufferSize)
                            {
                                m_nBufferW  =   0;
                            }
                        }
                        m_Lock.unlock();
                    }
                }
                else
                {
                    Thread_sleep(10);
                }
            }
        }
    }
}