#include "sensordisplayrk.h"
#include "ui_sensordisplayrk.h"


SensorDisplayRK::SensorDisplayRK(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SensorDisplayRK){
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(sensorDataRequest()));
    timer->start(1000);

}

SensorDisplayRK::~SensorDisplayRK(){
    delete ui;
}

void delay(int delayMsec) // Function used for delays
{
    QTime dieTime= QTime::currentTime().addMSecs(delayMsec);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

QString getLatestFileInDir (QString &sFileDirectory){ // function searches specified Directory for CSV files
    if(QDir(sFileDirectory).entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() == 0)
    {
        qWarning() << "Directory is empty";
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Sensor data error");
        msgBox.setInformativeText("Data files are not found. Check files and restart the app");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return "Error";
    }
    QDir directory(sFileDirectory); // starting from the end and returns QString with the latest filename
    // Take all files in LatestFileDirectory directory, reverse order
    // and combine first element with LatestFileDirectory into a string
    QStringList fileList = directory.entryList(QStringList() << "*.csv" << "*.CSV", QDir::Files, QDir::Reversed);
    if (fileList.isEmpty()) {
        qWarning() << "Error! Please check if you specified correct path to *.CSV files and it is not empty";
        return "Error";
    }
    QString filePath = sFileDirectory + fileList[0];
    //    qInfo() << "Returning full file path - " << filePath;
    return filePath;
}

QHash<qint16,QStringList> getSensorData (QHash<qint16,QStringList> &SensorList,QString &filePath){


    QFile file(filePath);// Open a *.csv file to read using file path from above

    if (!file.open(QIODevice::ReadOnly)) { // Check if there are any errors with openning the file
        qDebug() << file.errorString();
    }
            qInfo() << QTime::currentTime() <<"Using file:" << filePath;
    while (!file.atEnd()){// open and loop through file line by line till the end of file
        QString lineLoop =  file.readLine();
        // split sensorN and readings for a line and read current sensorN (',' - is a separator)
        QStringList data = lineLoop.split(',').replaceInStrings("\r\n","");
        //include try/catch here for false data
        if (data[0].toInt()<5000 || data[0].toInt()>5500 ){qInfo() << "Found error in sensor number. Skipping line: " << lineLoop;}
        // For each line in the file update reading,temp & timestamp as .insert method will update and not append if exist
        qint16 CurrentSensorN = data[0].toInt();
//        qInfo() << "Currently updating line: " << SensorList;
        SensorList.insert(CurrentSensorN,{data[1],data[2],data[3]});
    }
    file.close();
    qInfo() << "Returning following list of sensors: " << SensorList.keys();
    qInfo() << "***********************Done. File is closed***********************";
    return  SensorList;
}

qint8 SensorDisplayRK::sensorDataRequest()
{
    qInfo() << "Starting application... reading sensor data";
    QHash<qint16,QStringList> SensorList;

    while(true){
        // Specify file Directory eg. "D:/Qt/Projects/QtClockToSensor/"
        QString sFileDirectory = "D:/Qt/Projects/StrainSensorApp/SensorDataFolder/";
        QString filePath = getLatestFileInDir(sFileDirectory);
        if (filePath=="Error"){
            QCoreApplication::exit();
            return 1;}
        QHash<qint16,QStringList> Output = getSensorData(SensorList, filePath);
        // create a string from has value with number 5026 - check if there is such key in hash
        if (!Output.contains(5026)){
            qWarning() << "Output is out of range refer to sensorDataRequest()";
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText("sensorDataRequest() error");
            msgBox.setInformativeText("Reqested sensor is not in function output hash");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
            QCoreApplication::exit();
        }
        QStringList OutputString5026 = Output.value(5026);
        qInfo() << OutputString5026;
        ui->groupBox5000->setTitle("5000 (T " + QString::number(OutputString5026[1].toDouble(), 'f', 1) + "C)");
        ui->lcdNumber5000->display(OutputString5026[0].toDouble());
        // set delay(mSec) not to overload system
        delay(500);

    }
    qInfo() << "Thank you for using the app. Have a good day!";
    return 1;
}



int main()
{

    return 0;
}

