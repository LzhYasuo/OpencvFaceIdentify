#include "FilterAction.h"
#include <QFile>
#include <QDebug>
#include "pub/PubFunction.h"

const QString FaceCascadePath = "F:/QTpro/Work/build-OpencvFaceIdentify-Desktop_Qt_5_9_8_MinGW_32bit-Debug/debug/Face/haarcascade_frontalface_alt.xml";
const QString FaceModelPath = "F:/QTpro/Work/build-OpencvFaceIdentify-Desktop_Qt_5_9_8_MinGW_32bit-Debug/debug/Train/myFacePCA.xml";;
const QString TrainInfoPath = "F:/QTpro/Work/build-OpencvFaceIdentify-Desktop_Qt_5_9_8_MinGW_32bit-Debug/debug/Train/Train.txt";
const QString PaintInfoPath = "F:/QTpro/Work/build-OpencvFaceIdentify-Desktop_Qt_5_9_8_MinGW_32bit-Debug/debug/JPG/";

FilterAction::FilterAction(QObject* parent)
    :QObject (parent)
{
//    cv::CascadeClassifier cascade;
//    cascade.load(FaceCascadePath.toStdString());
//    cv:: cascade;
    qDebug() << FaceCascadePath;
    _cascade.load(FaceCascadePath.toStdString());
    _modelPCA =  cv::face::EigenFaceRecognizer::create();
    _modelPCA->read(FaceModelPath.toStdString());
}

FilterAction::~FilterAction()
{

}

cv::Mat FilterAction::GetMat()
{
    if(_inputMat.empty())
        _inputMat = cv::Mat();
    return _inputMat;
}

void FilterAction::SetMat(cv::Mat mat, cv::Mat mat1)
{
    if(mat.empty())
        return;
    _inputMat = mat.clone();
    _inputMat1 = mat.clone();
}

int FilterAction::VoiceAction()
{
    int PCANum = -1;
    if(!_inputMat.empty())
    {
        cv::resize(_inputMat,_inputMat,cv::Size(300,250));
        cv::Mat matGary;
        cv::cvtColor(_inputMat,matGary,cv::COLOR_BGR2GRAY);
        std::vector<cv::Rect> faceVec;
        _cascade.detectMultiScale(matGary,faceVec,1.1,3,0 | CV_HAAR_DO_ROUGH_SEARCH);
        if(faceVec.size() == 1)
        {
            cv::Rect faceInfo = faceVec.at(0);
            cv::Mat trainMat = matGary(faceInfo);
            cv::resize(trainMat,trainMat,cv::Size(92,112));
            int numPCA = _modelPCA->predict(trainMat);
            qDebug() <<numPCA;
            if(_isSeleteCount == 0)
            {
                _isSelete = numPCA;
                _isSeleteCount++;
            }
            else if(_isSeleteCount >= 0 && _isSeleteCount <= 9)
            {
                if(_isSelete == numPCA)
                {
                    _isSeleteCount++;
                }
                else
                {
                    _isSeleteCount = 0;
                }
            }
            else if(_isSeleteCount == 10)
            {
                _isSeleteCount = 0;
                PCANum =_isSelete;
            }
            cv::rectangle(_inputMat,faceInfo.tl(),faceInfo.br(),cv::Scalar(255,0,255),2);
        }
    }
    return PCANum;
}

bool FilterAction::WritePaintAction(int pCountNum,int nCountNum)
{
    const QString paintPath = PaintInfoPath + QString::number(pCountNum) + ".jpg";
    const QString writePath = paintPath + ";" + QString::number(nCountNum);
    qDebug() << PaintInfoPath;
    if(!_inputMat.empty())
    {
        cv::Mat matGary;
        cv::resize(_inputMat,_inputMat,cv::Size(300,250));
        cv::cvtColor(_inputMat,matGary,cv::COLOR_BGR2GRAY);
        std::vector<cv::Rect> faceVec;
        _cascade.detectMultiScale(matGary, faceVec, 1.1, 3, 0 | CV_HAAR_DO_ROUGH_SEARCH);
        if(faceVec.size() == 1)
        {
            cv::Rect faceInfo = faceVec.at(0);
            //只有一张脸的情况
            cv::Mat faceMat = matGary(faceInfo);
            if(faceMat.cols <= 0 || faceMat.rows <= 0)
                return false;
            cv::resize(faceMat,faceMat,cv::Size(92,112));
            const bool isWrite = cv::imwrite(paintPath.toStdString(),faceMat);
            cv::rectangle(_inputMat,faceInfo.tl(),faceInfo.br(),cv::Scalar(0,255,0),2);
            if(!isWrite)
            {
                return false;
            }
            QFile file(TrainInfoPath);
            const bool isOpen = file.open(QFile::ReadWrite | QFile::Text | QFile::Append);
            if(!isOpen)
            {
                return false;
            }
            file.write(writePath.toStdString().data());
            file.write("\n");
            file.flush();
            file.close();
        }
    }
    return true;
}
