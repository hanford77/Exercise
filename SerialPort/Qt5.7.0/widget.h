#pragma once

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();    
private slots:    
    void slotReadData();
    void on_btnOpenCom_clicked();
    void on_btnCloseCom_clicked();
    void on_btnSend_clicked();
private:
    void enableControls();
private:
    Ui::Widget* ui;
    QSerialPort*m_port;     //串口对象
    QByteArray  m_dataCom;  //从串口读取到的数据
};
