#ifndef FACEMODELTRAIN_H_
#define FACEMODELTRAIN_H_

#include <QObject>

class FaceModelTrain : public QObject
{
    Q_OBJECT
public:
    FaceModelTrain(QObject* parent = nullptr);
    ~FaceModelTrain();

    //
    bool ReadFaceCount(int&,int&);
    bool WriteFaceCount(int,int);
    //写入训练信息
    void WriteTarinInfo(QStringList);
    //训练
    void Train(int,int);
    void Init();

signals:
    void TrainFinish(int);
private:
};

#endif //FACEMODELTRAIN_H_
