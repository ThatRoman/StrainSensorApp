#include "sensordisplayrk.h"

#include <QApplication>

QHash<qint16,QStringList> SensorList;

//QHash<qint16,QStringList> initializeSensorListWithDefaults(){ // to update when reading through the file

//    for (qint16 i=5000; i < 5005; i ++){ // change i < 5005  to number of sensor needed
//        SensorList.insert(i,{"","",""});
//    }
//    qInfo() << SensorList;

//    return SensorList;
//}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    initializeSensorListWithDefaults();

    SensorDisplayRK w;
    w.show();
    return a.exec();
}
