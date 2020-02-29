#ifndef SENSORDISPLAYRK_H
#define SENSORDISPLAYRK_H

#include <QMainWindow>
#include "sensor.h"

#include <QFile>
#include <QStringList>
#include <QDebug>
#include <iostream>
#include <QTextStream>
#include <QFileDevice>
#include <algorithm>
#include <QHash>

#include <QDir>
#include <QTime>
#include <QDateTime>
#include <QTimer>
#include <QLCDNumber>
#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui { class SensorDisplayRK; }
QT_END_NAMESPACE

class SensorDisplayRK : public QMainWindow
{
    Q_OBJECT


public:
    SensorDisplayRK(QWidget *parent = nullptr);
    ~SensorDisplayRK();
//    void delay();

public slots:
//    void delay();
//    QString getLatestFileInDir(QString &sFileDirectory);
//    QStringList getSensorData(QString &SensoReqN,QString &filePath);
    qint8 sensorDataRequest();

private slots:


private:
    Ui::SensorDisplayRK *ui;
    QTimer *timer;

};
#endif // SENSORDISPLAYRK_H
