#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <src/measurementparameter.h>
#include <QObject>
#include <QPointer>
#include <QFile>
#include <QMap>

class FileHandler : public QObject
{
    Q_OBJECT
public:
    explicit FileHandler(QObject *parent = nullptr);
    const QString getFilePath();
    const QString getFileName();

signals:
    void openedFileName(const QString filename);

public slots:
    void setOutputAutomatic(bool autoOutput);
    void setOutputFile(QString fileName);
    void onNewMeasurementStarted();
    void onFinishedMeasurement();
    void onReceivingValues(QString devicename, QList<MeasurementValue> values, quint64 number);
    void writeLine(QString line);
    void writeBufferToFile(bool endOfMeasurement);

private:
    void correct_columns();
    void createAutomaticOutputFile();
    QString placeholder = "n/a";
    QPointer<QFile> outputFile;
    bool _autoOutput = false;
    quint64 lastWrittenLine = 0;
    QStringList fileHeaderStrings = {"time"};
    QMap<quint64, QStringList> valueLineListMap;
    quint64 bufferedLines = 100;
};

#endif // FILEHANDLER_H
