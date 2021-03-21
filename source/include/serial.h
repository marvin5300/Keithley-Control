#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QSerialPort>
#include <string>
#include <QPointer>

/**
* Serial interface (UART) class that uses QSerialPort.
* This class only knows basic serial communication. 
*/
class Serial : public QObject
{
    Q_OBJECT
public:
    explicit Serial(QString _portName, quint32 _baudRate = 9600,
                   char _terminator = 0x0a,
                   QSerialPort::FlowControl _flowControl = QSerialPort::NoFlowControl,
                   QSerialPort::StopBits _stopBits = QSerialPort::OneStop,
                   QSerialPort::DataBits _dataBits = QSerialPort::Data8,
                   QSerialPort::Parity _parity = QSerialPort::NoParity,
                   QObject *parent = nullptr);

signals:
    void receivedMessage(QString message);
    void connectionStatus(bool connected);

public slots:
    void onReadyRead();
    void makeConnection();
    void sendScpiCommand(QString command);
    void closeConnection();

private slots:
    bool scanMessage(std::string& buffer);

private:
    QPointer<QSerialPort> serialPort;
    void closeSerialPort();
    QString portName;
    std::string buffer = "";
    quint32 baudRate; // usually 9600
    char terminator; // usually <LF> "linefeed" in ascii
    QSerialPort::FlowControl flowControl; // usually NoFlowControl
    QSerialPort::StopBits stopBits; // usually OneStop
    QSerialPort::DataBits dataBits; // usually Data8 (8 Bits)
    QSerialPort::Parity parity; // usually NoParity
    unsigned int timeout = 5000; // s
    void processMessage(std::string& message);
};

#endif // SERIAL_H
