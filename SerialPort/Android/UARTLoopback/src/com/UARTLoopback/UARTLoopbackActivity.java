package com.UARTLoopback;

import java.io.UnsupportedEncodingException;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class UARTLoopbackActivity extends Activity {
    private Button     m_btnOpen	=  	null;   //打开按钮
    private Button     m_btnClose  =  	null;   //关闭按钮
    private Button     m_btnSend   =	null;   //发送按钮
    private TextView 	m_ReadBytes =	null;
    private EditText   m_txtSend   =  	null;   //发送文本
    private EditText   m_txtRecv   =  	null;   //接收文本
    private String     m_sRecv     =  	"";  	//接收到的文本
    private long 		m_nRecv     =  	0;		//接收到的字节数
    private com.UARTLoopback.FT311UARTInterface m_Comm = null;  //串口
    private com.UARTLoopback.FT311UARTInterface.EventPlugPull m_EventPlugPull = new com.UARTLoopback.FT311UARTInterface.EventPlugPull(){
        public void onEvent(int nPlugPull)
        {//拔出事件处理函数
            Toast.makeText(UARTLoopbackActivity.this,"拔出",Toast.LENGTH_LONG).show();
        }
    };
    private com.UARTLoopback.FT311UARTInterface.EventDataReceived m_EventDataReceived = new com.UARTLoopback.FT311UARTInterface.EventDataReceived(){
        public void onEvent(byte[] data,int nBytes)
        {//接收到串口数据，就调用此函数
        	try
        	{
        		m_nRecv	+=	nBytes;
        		m_sRecv +=	new String(data, 0, nBytes, "UTF-8");
        	}
        	catch (UnsupportedEncodingException ex)
        	{        		
        	}
            m_Handler.sendEmptyMessage(1);  //更新界面显示
        }
    };
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);        
        m_Comm      =   new com.UARTLoopback.FT311UARTInterface(this); //串口
        m_Comm.setEventDataReceived(m_EventDataReceived);
        m_Comm.setEventPlugPull(m_EventPlugPull);
        m_txtSend   =   (EditText) findViewById(R.id.txtSend);
        m_ReadBytes	=	(TextView) findViewById(R.id.ReadBytes);
        m_txtRecv   =   (EditText) findViewById(R.id.txtRecv);
        m_btnOpen   =   (Button) findViewById(R.id.btnOpen);
        m_btnOpen.setOnClickListener(new Button.OnClickListener()
            {
                @Override
                public void onClick(View view)
                {
                    if(m_Comm.open(9600,'N',8,1,0))
                    {//成功打开串口
                        m_txtRecv.setText(m_sRecv="");
                    }
                    else if(m_Comm.isExist())
                    {//打开串口失败，可能是权限不够，申请权限
                        m_Comm.requestPermission();
                    }
                    else
                    {
                        m_txtRecv.setText("请连接 USB 转串口");
                    }
                    enableControls();
                }
            }
        );
        m_btnSend  = (Button) findViewById(R.id.btnSend);
        m_btnSend.setOnClickListener(new Button.OnClickListener()
              {
                  @Override
                  public void onClick(View view)
                  {
                      if(m_Comm.isOpen())
                      {
                          byte[] data = m_txtSend.getText().toString().getBytes();
                          m_Comm.write(data,data.length);
                      }
                  }
              }
        );
        m_btnClose = (Button) findViewById(R.id.btnClose);
        m_btnClose.setOnClickListener(new Button.OnClickListener()
            {
                @Override
                public void onClick(View view)
                {
                    m_Comm.close();
                    enableControls();
                }
            }
        );
        enableControls();
    }
    private void enableControls()
    {
        boolean bOpen = m_Comm.isOpen();
        m_btnOpen.setEnabled(!bOpen);
        m_btnSend.setEnabled(bOpen);
        m_btnClose.setEnabled(bOpen);
    }
    private Handler m_Handler = new Handler()
    {
        @Override
        public void handleMessage(Message msg)
        {
            switch (msg.what)
            {
            case 1:
                m_txtRecv.setText(m_sRecv);
                m_ReadBytes.setText(String.valueOf(m_nRecv));
                break;
            }
            super.handleMessage(msg);
        }
    };
    @Override
    protected void onDestroy()
    {
        m_Comm.close();
        super.onDestroy();
    }
}
