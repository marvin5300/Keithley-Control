#include "rs232.h"
#include <sstream>
#include <iostream>
#include <QDebug>
//#include <iomanip>
#include <QThread>

RS232::RS232(QString _portName, quint32  _baudRate,
             char _terminator,
             QSerialPort::FlowControl _flowControl,
             QSerialPort::StopBits _stopBits,
             QSerialPort::DataBits _dataBits,
             QSerialPort::Parity _parity, QObject *parent) :
    QObject(parent)
{
    portName = _portName;
    baudRate = _baudRate;
    terminator = _terminator;
    flowControl = _flowControl;
    dataBits = _dataBits;
    stopBits = _stopBits;
    parity = _parity;
}

void RS232::makeConnection() {
    // this function gets called with a signal from client-thread

    if (!serialPort.isNull()) {
        serialPort.clear();
    }
    serialPort = new QSerialPort(portName);
    serialPort->setBaudRate(baudRate);
    serialPort->setStopBits(stopBits);
    serialPort->setFlowControl(flowControl);
    serialPort->setDataBits(dataBits);
    serialPort->setParity(parity);
    if (!serialPort->open(QIODevice::ReadWrite)) {
        qDebug() << (QObject::tr("Failed to open port %1, error: %2\ntrying again in %3 seconds\n")
            .arg(portName)
            .arg(serialPort->errorString())
            .arg(timeout/1000));
        serialPort.clear();
        QThread::usleep(timeout);
        //emit serialRestart(portName, baudRate);
        emit connectionStatus(false);
        this->deleteLater();
        return;
    }
    connect(serialPort, &QSerialPort::readyRead, this, &RS232::onReadyRead);
    serialPort->clear(QSerialPort::AllDirections);
}

void RS232::onReadyRead() {
    // this function gets called when the serial port emits readyRead signal
    QByteArray temp = serialPort->readAll();
    for (int i=0; i<temp.size(); i++) {
        buffer+=temp.data()[i];
    }
    //if (buffer.empty()){
        //std::cout << "\nread: " << std::flush;
    //    emit receivedMessage("received: ");
    //}
    //std::cout << temp.toStdString();
    //emit receivedMessage(QString::fromStdString(temp.toStdString()));
    while (scanMessage(buffer)) {};
}

bool RS232::scanMessage(std::string& buffer){
    // Reads the buffer and returns true if a complete message is found.
    // If so: removes it from the buffer and starts the processing of this message.
    std::string message = "";
    for (std::string::size_type  i = 0; i < buffer.size(); i++){
        if (buffer[i]==terminator){
            buffer.erase(0, message.size()+1);
            if (!message.empty()){
                emit receivedMessage(QString::fromStdString(message));
                qDebug() << "received: " << QString::fromStdString(message);
                processMessage(message);
                return true;
            }
        }
        message += buffer[i];
    }
    return false;
}

void RS232::processMessage(std::string& message){

// here comes all the fun stuff to do with parsing messages from the device
}

void RS232::sendScpiCommand(QString command){
    if (serialPort.isNull()) {
        return;
    }
    //std::cout << "\nsend:" << (command.toStdString()+terminator) << std::endl;
    //emit receivedMessage(QString(command + terminator + "\n"));
    qDebug() << "send: " << QString(command+""+terminator);
    serialPort->write((command.toStdString()+""+terminator).c_str(), command.length()+1);
}

void RS232::closeConnection(){
    closeSerialPort();
    this->deleteLater();
}

void RS232::closeSerialPort(){
    if (!serialPort.isNull()){
        serialPort->close();
        serialPort.clear();
    }
}
