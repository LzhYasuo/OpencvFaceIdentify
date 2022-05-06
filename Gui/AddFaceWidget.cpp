#include "AddFaceWidget.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

AddFaceWidget::AddFaceWidget(QWidget *parent)
    :QDialog (parent)
{
    this->Init();
    this->setFixedSize(200,130);
}

AddFaceWidget::~AddFaceWidget()
{

}

void AddFaceWidget::Init()
{
    const QString widgetStyle = "background-color:rgb(30,30,30);";
    const QString LineEditStyle = "font : 15pt ""楷体"";"
                                  "color :rgb(230,230,230);";
    const QString lblStyle = "font : 15pt ""楷体"";"
                             "color : rgb(230,230,230); ";
    const QString buttonStyle = "font : 15pt ""楷体"";"
                                "color :rgb(230,230,230);"
                                "border:1px solid rgb(230,230,230); ";
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QWidget* AddWidget = new QWidget();
    AddWidget->setObjectName("AddWidget");
    AddWidget->setStyleSheet(widgetStyle);
    QVBoxLayout* AddLayout = new QVBoxLayout();
    AddLayout->setSpacing(0);
    AddLayout->setContentsMargins(0,0,0,0);

    QLabel* lblAddFaceText = new QLabel("请输出你需要添加的人脸名称：");
    lblAddFaceText->setFixedHeight(35);
    lblAddFaceText->setStyleSheet(lblStyle);

    QLineEdit* AddFaceedit = new QLineEdit();
    AddFaceedit->setFixedHeight(35);
    AddFaceedit->setStyleSheet(LineEditStyle);

    QHBoxLayout* ButtonLayout = new QHBoxLayout();
    ButtonLayout->setSpacing(0);
    ButtonLayout->setContentsMargins(0,0,0,0);
    QPushButton* btn_sure = new QPushButton("确认");
    btn_sure->setFixedHeight(35);
    btn_sure->setStyleSheet(buttonStyle);
    QPushButton* btn_exit = new QPushButton("取消");
    btn_exit->setFixedHeight(35);
    btn_exit->setStyleSheet(buttonStyle);
    ButtonLayout->addWidget(btn_sure);
    ButtonLayout->addWidget(btn_exit);

    AddLayout->addWidget(lblAddFaceText);
    AddLayout->addWidget(AddFaceedit);
    AddLayout->addLayout(ButtonLayout);
    AddWidget->setLayout(AddLayout);
    mLayout->addWidget(AddWidget);

    this->connect(btn_sure,&QPushButton::clicked,this,[=](){
        _Str = AddFaceedit->text();
        this->done(0);
    });
    this->connect(btn_exit,&QPushButton::clicked,this,[=](){
        this->done(1);
    });

    this->setLayout(mLayout);
}

QString AddFaceWidget::GetStr() const
{
    return _Str;
}
