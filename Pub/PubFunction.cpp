#include "PubFunction.h"
#include <QApplication>

//返回程序当前所在路径
QString PubFunction::appPath()
{
    //如果定义在Android下面
#ifdef Q_OS_ANDROID
    return QString("/sdcard/Android/%1").arg(appName());
#else
    return qApp->applicationDirPath();
#endif
}
