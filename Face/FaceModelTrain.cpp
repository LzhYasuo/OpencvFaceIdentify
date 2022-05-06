#include "FaceModelTrain.h"
#include <QFile>
#include <QDebug>
#include <iostream>

//#include <opencv2\core.hpp>
#include <opencv2/face.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
//#include "../Inc/face/face.hpp"
//#include "../Inc/face/facerec.hpp"

const QString trainInfoPath = "F:/QTpro/Work/build-OpencvFaceIdentify-Desktop_Qt_5_9_8_MinGW_32bit-Debug/debug/Train/Train.txt";
const QString PCAPath = "F:/QTpro/Work/build-OpencvFaceIdentify-Desktop_Qt_5_9_8_MinGW_32bit-Debug/debug/Train/myFacePCA.xml";
const QString FisherPath = "F:/QTpro/Work/build-OpencvFaceIdentify-Desktop_Qt_5_9_8_MinGW_32bit-Debug/debug/Train/myFaceFisher.xml";
const QString LBPHPath = "F:/QTpro/Work/build-OpencvFaceIdentify-Desktop_Qt_5_9_8_MinGW_32bit-Debug/debug/Train/myFaceLBPH.xml";
const QString FaceCountPath = "F:/QTpro/Work/build-OpencvFaceIdentify-Desktop_Qt_5_9_8_MinGW_32bit-Debug/debug/Train/TrainCount.txt";

FaceModelTrain::FaceModelTrain(QObject *parent)
{

}

FaceModelTrain::~FaceModelTrain()
{

}

bool FaceModelTrain::ReadFaceCount(int& a,int& b)
{
    QFile FaceCountFile(FaceCountPath);
    const bool isOpen = FaceCountFile.open(QFile::ReadOnly | QFile::Text);
    if(!isOpen)
    {
        return false;
    }
    QString allStr = FaceCountFile.readAll();
    QStringList msg = allStr.split(":");
    a = msg.at(0).toInt();
    b = msg.at(1).toInt();
    return true;
}

bool FaceModelTrain::WriteFaceCount(int a, int b)
{
    const QString writeStr = QString::number(a) + ":" + QString::number(b);
    QFile FaceCountFile(FaceCountPath);
    const bool isOpen = FaceCountFile.open(QFile::ReadOnly | QFile::Text);
    if(!isOpen)
    {
        return false;
    }
    FaceCountFile.write(writeStr.toStdString().data());
    return true;
}

void FaceModelTrain::WriteTarinInfo(QStringList list)
{
    QFile file(trainInfoPath);
    bool isOpen = file.open(QFile::ReadWrite | QFile::Text);
    if(!isOpen)
    {
        //打开文件失败
        return;
    }
    for(auto &i : list)
    {

        int length = sizeof(i.toStdString().data());
        if(file.write(i.toStdString().data(),length) == length)
            file.waitForBytesWritten(1000);
    }

    //写入成功后决定是否要开始训练
}

void FaceModelTrain::Train(int pCount,int nCount)
{
    const QString TrainCountWrite = QString::number(pCount) + ":" + QString::number(nCount);
    QFile fileCount(FaceCountPath);
    bool isOpen = fileCount.open(QFile::WriteOnly | QFile::Text);
    if(!isOpen)
    {
        return;
    }

    bool isWrite = fileCount.write(TrainCountWrite.toStdString().data());
    if(!isWrite)
    {
        return;
    }

    std::vector<cv::Mat> imageVec;
    std::vector<int> labelVec;

    QFile file(trainInfoPath);
    isOpen = file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(isOpen)
    {
        QString line;
        QTextStream in(&file);  //用文件构造流
        line = in.readLine();//读取一行放到字符串里
        while(!line.isNull())//字符串有内容
        {
            QStringList msg = line.split(";");
            imageVec.push_back(cv::imread(msg.at(0).toStdString(),CV_LOAD_IMAGE_GRAYSCALE));
            labelVec.push_back(msg.at(1).toInt());
            line=in.readLine();//循环读取下行
        }
    }
    if(imageVec.size() != labelVec.size())
    {
        return;
    }
    const unsigned int imageCount = imageVec.size();
    if(imageCount <= 0)
    {
        return;
    }

    cv::Ptr<cv::face::BasicFaceRecognizer> model = cv::face::EigenFaceRecognizer::create();
    model->train(imageVec, labelVec);
    qDebug() << PCAPath;
    model->save(PCAPath.toStdString());//保存路径可自己设置，但注意用“\\”

    cv::Ptr<cv::face::BasicFaceRecognizer> model1 = cv::face::FisherFaceRecognizer::create();
    model1->train(imageVec, labelVec);
    qDebug() << FisherPath;
    model1->save(FisherPath.toStdString());

    cv::Ptr<cv::face::LBPHFaceRecognizer> model2 = cv::face::LBPHFaceRecognizer::create();
    model2->train(imageVec, labelVec);
    qDebug() << LBPHPath;
    model2->save(LBPHPath.toStdString());

    emit TrainFinish(nCount);

}

void FaceModelTrain::Init()
{

}
