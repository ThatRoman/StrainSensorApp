#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>

class sensor : public QObject
{
    Q_OBJECT
public:
    explicit sensor(QObject *parent = nullptr);


    int sensorN = 0;
    double sensorReading = 0.00;
    double sensorTemperature = 0.0;


signals:

};

#endif // SENSOR_H
