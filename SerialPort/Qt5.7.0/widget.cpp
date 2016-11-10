#include "widget.h"
#include "ui_widget.h"
#include <map>

/******************************************************************************\
从字符串里提取整数
s   [in]    字符串
返回：提取出来的整数，-1 表示错误
\******************************************************************************/
int GetIntInStr(const QString&s)
{
    bool    bOK     =   false;
    int     n       =   0;
    int     nLenS   =   s.length(); //字符串长度
    ushort  c       =   0;
    for(int i = 0;i < nLenS;++i)
    {
        c   =   s[i].unicode();
        if(c >= '0' && c <= '9')
        {
            bOK =   true;
            n   =   n * 10 + (c - '0');
        }
    }
    if(!bOK)
    {
        n   =   -1;
    }
    return n;
}

Widget::Widget(QWidget *parent)
:QWidget(parent)
,ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_port = new QSerialPort();
    {//获取串口信息，填入下拉列表框内
        std::map<int,QString>   mapPort;
        {//填充 mapPort
            QString sPort;
            int     nPort;
            foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
            {
                sPort   =   info.portName();
                nPort   =   GetIntInStr(sPort);
                if(nPort >= 0)
                {
                    mapPort[nPort]  =   sPort;
                }
            }
        }
        {//填充 cboPort
            ui->cboPort->clear();
            for(std::map<int,QString>::iterator it = mapPort.begin();it != mapPort.end();++it)
            {
                ui->cboPort->addItem(it->second);
            }
        }
    }
    connect(m_port,SIGNAL(readyRead()),this,SLOT(slotReadData()));
    enableControls();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotReadData()
{    
    QByteArray  data;
    const int   nMax    =   64 * 1024;
    for(;;)
    {
        data    =   m_port->readAll();
        if(data.isEmpty())
        {
            break;
        }
        m_dataCom.append(data);
        if(m_dataCom.size() > nMax)
        {
            m_dataCom   =   m_dataCom.right(nMax);
        }
    }
    ui->txtRecv->setText(m_dataCom);
    ui->txtRecv->moveCursor(QTextCursor::End);
}

void Widget::on_btnOpenCom_clicked()
{
    if(!m_port->isOpen())
    {
        m_dataCom.clear();
        m_port->setPortName(ui->cboPort->currentText());
        m_port->setBaudRate(ui->cboBaud->currentText().toInt());
        m_port->setParity(QSerialPort::NoParity);
        m_port->setDataBits(QSerialPort::Data8);
        m_port->setStopBits(QSerialPort::OneStop);
        bool    bRTS    =   false;  //流控制是否为硬件
        switch(ui->cboFlow->currentIndex())
        {
        case 1://硬件 RTS/CTS
            bRTS    =   true;
            m_port->setFlowControl(QSerialPort::HardwareControl);
            break;
        case 2://软件
            m_port->setFlowControl(QSerialPort::SoftwareControl);
            break;
        default://无
            m_port->setFlowControl(QSerialPort::NoFlowControl);
            break;
        }
        if(m_port->open(QIODevice::ReadWrite))
        {            
            if(!bRTS)
            {//流控制为硬件时，会自动管理 RTS 的状态
             //流控制不为硬件时，需要设置 RTS、DTR 为高电平，保证对方能顺利的发送数据过来
                m_port->setRequestToSend(true);
                m_port->setDataTerminalReady(true);
            }
            enableControls();
        }
    }
}

void Widget::on_btnCloseCom_clicked()
{
    if(m_port->isOpen())
    {
        m_port->close();
        enableControls();
    }
}

void Widget::on_btnSend_clicked()
{
    QByteArray  data    =   ui->txtSend->toPlainText().toUtf8();
    if(!data.isEmpty())
    {
        m_port->write(data);
        m_port->waitForBytesWritten(5000);
    }
}

void Widget::enableControls()
{
    bool bOpen  =   m_port->isOpen();
    ui->cboPort->setEnabled(!bOpen);
    ui->cboBaud->setEnabled(!bOpen);
    ui->cboFlow->setEnabled(!bOpen);
    ui->btnOpenCom->setEnabled(!bOpen);
    ui->btnCloseCom->setEnabled(bOpen);
    ui->btnSend->setEnabled(bOpen);
}
