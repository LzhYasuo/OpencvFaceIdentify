#include <QLabel>
#include <QPushButton>
#include <QTime>
#include <QHBoxLayout>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include "../Filter/Filter.h"
#include "../Task/TaskCamera.h"
#include "../Face/FaceModelTrain.h"
#include "../Sql/SqlDataBase.h"

#include "MainWindow.h"
#include "OpenCVGLWidget.h"
#include "RoundWidget.h"
#include "AdminWidget.h"
#include "AddFaceWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : GuiBaseWidget(parent)
{
    QFile* countFile = new QFile();
    countFile->setFileName("CountFile.txt");
    bool isOpen = countFile->open(QFile::ReadWrite | QFile::Text);
    if(isOpen)
    {
//        QMessageBox::information(this,"标题","训练文件打开失败,将只提供打开功能");
//        return;
    }

    qRegisterMetaType<cv::Mat>("cv::Mat");
    this->setObjectName("MainWindow");
    this->setStyleSheet("#MainWindow{background-color:rgb(30,30,30);}");

    FaceModelTrain* trainObj = new FaceModelTrain();
    int pCount = 0;
    int nCount = 0;
    trainObj->ReadFaceCount(pCount,nCount);
    taskCamera = new TaskCamera(pCount,nCount);
    taskCamera->Open();
    taskCamera->start();

    this->Init();

    const bool isDbOpen = SqlDataBase::Get()->Open();
    if(!isDbOpen)
    {
        qDebug() << "数据库打开失败";
    }

    this->connect(taskCamera,&TaskCamera::PaintWriteFinish,trainObj,&FaceModelTrain::Train);
    this->connect(trainObj,&FaceModelTrain::TrainFinish,this,[=](int id)
    {
        QPushButton* btnTrain = this->findChild<QPushButton*>("btnTrain");
        btnTrain->setEnabled(true);

        QVariantList list = QVariantList() << _faceName << id;
        SqlDataBase::Get()->InsertFaceInfo(list);
    });
    this->connect(taskCamera,&TaskCamera::VoiceIdentify,this,[=](int id){
        if(id == -1)
        {
            QLabel* lblName = this->findChild<QLabel*>("lblNameValue");
            QLabel* lblID = this->findChild<QLabel*>("lblIdValue");
            QLabel* lblState = this->findChild<QLabel*>("lblStateValue");
            lblName->setText("");
            lblID->setText("");
            lblState->setText("");
            return;
        }
        QLabel* lblState = this->findChild<QLabel*>("lblStateValue");
        QLabel* lblName = this->findChild<QLabel*>("lblNameValue");
        QLabel* lblID = this->findChild<QLabel*>("lblIdValue");
        QDateTime current_time = QDateTime::currentDateTime();
        QString currentTime = current_time.toString("yyyy-MM-dd hh:mm:ss");
        bool isClock = false;
        if(_preClock == id)
        {
            qDebug() << "重复签到";
            isClock = true;
        }
        QString name;
        bool isSelect = SqlDataBase::Get()->GetInfoData(name,"",QString::number(id));
        if(!isSelect)
        {
            //
        }
        lblName->setText(name);
        lblID->setText(QString::number(id));
        if(isClock)
        {
            lblState->setText("重复打卡!");
        }
        else
        {
            lblState->setText("打卡成功!");
            QVariantList list = QVariantList() << name << id << currentTime;
            isSelect = SqlDataBase::Get()->InsertFaceClock(list);
            if(!isSelect)
            {
                //
            }
        }

        _preClock = id;
    });

    startTimer(1000);
}

MainWindow::~MainWindow()
{

}

QWidget *MainWindow::CamearWidgetInit()
{
    QWidget* mWidget = new QWidget();
    QHBoxLayout* mLayout = Get_HLayout();
    RoundWidget* roundWidget2 = new RoundWidget();
    roundWidget2->setFixedSize(600,600);
    roundWidget2->setStyleSheet("background-color:rgb(170,255,255);");
    QHBoxLayout* roundLayout2 = Get_HLayout();
    RoundWidget* roundWidget1 = new RoundWidget();
    roundWidget1->setFixedSize(588,588);
    roundWidget1->setStyleSheet("background-color:rgb(30,30,30);");
    QHBoxLayout* roundLayout1 = Get_HLayout();
    RoundWidget* roundWidget = new RoundWidget();
    roundWidget->setFixedSize(470,470);
    roundWidget->setStyleSheet("background-color:rgb(170,255,255);");
    QHBoxLayout* roundLayout = Get_HLayout();
    OpenCVGLWidget* glWidget = new OpenCVGLWidget();
    glWidget->setFixedSize(460,460);
    roundLayout->addWidget(glWidget);
    roundWidget->setLayout(roundLayout);
    roundLayout1->addWidget(roundWidget);
    roundWidget1->setLayout(roundLayout1);
    roundLayout2->addWidget(roundWidget1);
    roundWidget2->setLayout(roundLayout2);
    mLayout->addWidget(roundWidget2);
    mWidget->setLayout(mLayout);

    this->connect(taskCamera,&TaskCamera::UpdateMat,glWidget,&OpenCVGLWidget::ShowImg);

    return mWidget;
}

void MainWindow::Init()
{
    const QString leftLabelStyle = "color:rgb(230,230,230);"
                                   "font : 16pt ""楷体""; ";
    const QString topLabelStyle = "color:rgb(230,230,230);"
                                  "font: 25pt ""楷体"";";
    const QString buttonStyle = "QPushButton{"
                                "border:1px solid rgb(230,230,230);"
                                "font : 20pt ""楷体"";"
                                "color: rgb(230,230,230);"
                                "}"
                                "QPushButton:hover{"
                                "background-color:rgb(170,255,255);"
                                "color:rgb(30,30,30);"
                                "}";

    QVBoxLayout* mLayout = Get_VLayout(10);

    QWidget* topWidget = new QWidget();
    topWidget->setStyleSheet("border:3px solid rgb(170,255,255);");
    QHBoxLayout* topLayout = Get_HLayout();

    QLabel* lblTopTitle = Get_Label("人脸识别考勤打卡系统",0,0,topLabelStyle);
    lblTopTitle->setAlignment(Qt::AlignCenter);
    topLayout->addWidget(lblTopTitle);
    topWidget->setLayout(topLayout);

    QHBoxLayout* bodyLayout = Get_HLayout(20);
    QWidget* leftWidget = new QWidget();
    leftWidget->setFixedWidth(300);
    leftWidget->setObjectName("leftWidget");
    leftWidget->setStyleSheet("#leftWidget{border:3px solid rgb(170,255,255);}");
    QVBoxLayout* leftLayout = Get_VLayout(0,30,30,10,10);

    QWidget* dateWidget = new QWidget();
    dateWidget->setObjectName("dateWidget");
    dateWidget->setStyleSheet("#dateWidget{"
                              "border-top:1px solid rgb(230,230,230);"
                              "border-bottom:1px solid rgb(230,230,230);}");
    QHBoxLayout* dateLayout = Get_HLayout();
    QLabel* lblDateText = Get_Label("日期:",55,0,leftLabelStyle);
    lblDateText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QLabel* lbldateValue = Get_Label("xx,xx,xx",0,0,leftLabelStyle);
    lbldateValue->setText(QDateTime::currentDateTime().toString("yyyy/MM/dd dddd"));
    lbldateValue->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    dateLayout->addWidget(lblDateText);
    dateLayout->addWidget(lbldateValue);
    dateWidget->setLayout(dateLayout);

    QWidget* timeWidget = new QWidget();
    timeWidget->setObjectName("timeWidget");
    timeWidget->setStyleSheet("#timeWidget{border-bottom:1px solid rgb(230,230,230);}");
    QHBoxLayout* timeLayout = Get_HLayout();
    QLabel* lblTimeText = Get_Label("时间:",55,0,leftLabelStyle);
    lblTimeText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QLabel* lblTimeValue = Get_Label("xx,xx,xx",0,0,leftLabelStyle);
    lblTimeValue->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    timeLayout->addWidget(lblTimeText);
    timeLayout->addWidget(lblTimeValue);
    timeWidget->setLayout(timeLayout);

    QWidget* nameWidget = new QWidget();
    nameWidget->setObjectName("nameWidget");
    nameWidget->setStyleSheet("#nameWidget{border-bottom:1px solid rgb(230,230,230);}");
    QHBoxLayout* nameLayout = Get_HLayout();
    QLabel* lblNameText = Get_Label("姓名:",55,0,leftLabelStyle);
    lblNameText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QLabel* lblNameValue = Get_Label("xxx",0,0,leftLabelStyle);
    lblNameValue->setObjectName("lblNameValue");
    lblNameValue->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    nameLayout->addWidget(lblNameText);
    nameLayout->addWidget(lblNameValue);
    nameWidget->setLayout(nameLayout);

    QWidget* idWidget = new QWidget();
    idWidget->setObjectName("idWidget");
    idWidget->setStyleSheet("#idWidget{border-bottom:1px solid rgb(230,230,230);}");
    QHBoxLayout* idLayout = Get_HLayout();
    QLabel* lblIdText = Get_Label("序号:",55,0,leftLabelStyle);
    lblIdText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QLabel* lblIdValue = Get_Label("03",0,0,leftLabelStyle);
    lblIdValue->setObjectName("lblIdValue");
    lblIdValue->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    idLayout->addWidget(lblIdText);
    idLayout->addWidget(lblIdValue);
    idWidget->setLayout(idLayout);

    QWidget* stateWidget = new QWidget();
    stateWidget->setObjectName("stateWidget");
    stateWidget->setStyleSheet("#stateWidget{border-bottom:1px solid rgb(230,230,230);}");
    QHBoxLayout* stateLayout = Get_HLayout();
    QLabel* lblStateText = Get_Label("状态:",55,0,leftLabelStyle);
    lblStateText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QLabel* lblStateValue = Get_Label("打卡成功!",0,0,leftLabelStyle);
    lblStateValue->setObjectName("lblStateValue");
    lblStateValue->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    stateLayout->addWidget(lblStateText);
    stateLayout->addWidget(lblStateValue);
    stateWidget->setLayout(stateLayout);

    leftLayout->addWidget(dateWidget);
    leftLayout->addWidget(timeWidget);
    leftLayout->addWidget(nameWidget);
    leftLayout->addWidget(idWidget);
    leftLayout->addWidget(stateWidget);
    leftWidget->setLayout(leftLayout);

    QWidget* cameraWidget = CamearWidgetInit();

    bodyLayout->addWidget(leftWidget);
    bodyLayout->addWidget(cameraWidget);

    QWidget* bottomWidget = new QWidget();
    bottomWidget->setObjectName("bottomWidget");
    bottomWidget->setStyleSheet("#bottomWidget{border:3px solid rgb(170,255,255);};");
    QHBoxLayout* bottomLayout = Get_HLayout();
    QPushButton* btnTrain = Get_Button("训练",100,35,buttonStyle);
    btnTrain->setObjectName("btnTrain");
    QPushButton* btnAmdin = Get_Button("管理员",100,35,buttonStyle);
    bottomLayout->addWidget(btnTrain);
    bottomLayout->addWidget(btnAmdin);
    bottomLayout->addStretch();
    bottomWidget->setLayout(bottomLayout);

    mLayout->addWidget(topWidget);
    mLayout->addLayout(bodyLayout);
    mLayout->addWidget(bottomWidget);
    this->setLayout(mLayout);

    this->connect(this,&MainWindow::UpdateTime,this,[=](){
        lblTimeValue->setText(QTime::currentTime().toString());
        QStringList ms = lblTimeValue->text().split(":");
        bool isChange = true;
        for(auto& i : ms)
        {
            if(i != "00")
            {
                isChange = false;
            }
        }
        if(isChange)
        {
            lbldateValue->setText(QDateTime::currentDateTime().toString("yyyy/MM/dd dddd"));
        }
    });
    this->connect(btnAmdin,&QPushButton::clicked,this,[=](){
        AdminWidget* mWidget = new AdminWidget();
        mWidget->exec();
    });
    this->connect(btnTrain,&QPushButton::clicked,this,[=]()
    {
        QString faceName = "";
        AddFaceWidget* face = new AddFaceWidget();
        int i = face->exec();
        if(i == 0)
        {
            faceName = face->GetStr();
        }
        if(!faceName.isEmpty())
        {
            btnTrain->setEnabled(false);
            taskCamera->SetTrain();
        }

    });
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    taskCamera->Close();
}

void MainWindow::timerEvent(QTimerEvent *e)
{
    emit UpdateTime();
}
