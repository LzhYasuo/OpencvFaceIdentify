#ifndef _GUI_BASE_WIDGET_H_
#define _GUI_BASE_WIDGET_H_

#include <QWidget>

class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QComboBox;
class GuiBaseWidget : public QWidget
{
    Q_OBJECT
public:
    GuiBaseWidget(QWidget* parent = nullptr);
    ~GuiBaseWidget();

protected:
    //布局
    //Spaceing 空间之间的间距 | left 左边距 | right 右边距 | top 上边距 | bottom 下边距
    QHBoxLayout* Get_HLayout(int Spaceing = 0,int left = 0,int right = 0,int top = 0,int bottom = 0);
    QVBoxLayout* Get_VLayout(int Spaceing = 0,int left = 0,int right = 0,int top = 0,int bottom = 0);

    //按钮
    //text 名称 | width 宽度 | height 长度 | Style 样式表 | Icon 图标 | IconWidth 图标宽度 | IconHeight 图标长度
    QPushButton* Get_Button(QString text = "",int width = 0,int height = 0,QString Style = "");
    QPushButton* Get_IconButton(QString text = "",QString Icon = "",int width = 0,int height = 0,int IconSize = 0,int Iconheight = 0,QString Style = "");

    //标签
    //text 名称 | width 宽度 | height 长度 | Style 样式表 | pix 图片
    QLabel* Get_Label(QString text = "",int width = 0,int height = 0,QString Style = "");
    QLabel* Get_PixLabel(QString pix = "",int width = 0,int height = 0,QString Style = "");

    QComboBox* Get_ComboBox(QStringList List = QStringList(),int width = 0,int height = 0);
};

#endif //_GUI_BASE_WIDGET_H_
