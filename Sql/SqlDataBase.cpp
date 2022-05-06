#include "SqlDataBase.h"
#include <QFile>
#include <QSqlQuery>
#include <QVariantList>
#include <qDebug>

const QString DataBaseFilePath = "F:/QTpro/Work/build-OpencvFaceIdentify-Desktop_Qt_5_9_8_MinGW_32bit-Debug/debug/DB/FaceData.db";

SqlDataBase::SqlDataBase(QObject* parent)
    :QObject (parent)
{

}

SqlDataBase::~SqlDataBase()
{

}

SqlDataBase *SqlDataBase::Get()
{
    static SqlDataBase cx;
    return &cx;
}

bool SqlDataBase::Open()
{
    bool isOpen = false;
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        _db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        _db = QSqlDatabase::addDatabase("QSQLITE");
    }
    isOpen = OpenDataBase();
    return isOpen;
}

bool SqlDataBase::InsertFaceInfo(QVariantList valueList)
{
    _db.setDatabaseName(DataBaseFilePath);
    if(!_db.open())
        return false;

    const QString name = valueList.at(0).toString();
    const int id = valueList.at(1).toInt();
    const QString insertStr = QString("insert into FaceInfo values(%2,'%1')").arg(id).arg(name);
    QSqlQuery query(_db);
    bool isExec = query.exec(insertStr);
    if(!isExec)
    {
        return false;
    }

    _db.close();
    return true;
}

bool SqlDataBase::InsertFaceClock(QVariantList valueList)
{
    _db.setDatabaseName(DataBaseFilePath);
    if(!_db.open())
        return false;

    const QString name = valueList.at(0).toString();
    const int id = valueList.at(1).toInt();
    const QString dateTime = valueList.at(2).toString();
    const QString insertStr = QString("insert into FaceDataBase values(%1,'%2',Datetime('%3'))").arg(id).arg(name).arg(dateTime);
    qDebug() << insertStr;
    QSqlQuery query(_db);
    bool isExec = query.exec(insertStr);
    if(isExec)
    {
        return false;
    }

    _db.close();
    return true;
}

bool SqlDataBase::GetFaceInfoAllData(QList<QStringList>& List)
{
    _db.setDatabaseName(DataBaseFilePath);
    if(!_db.open())
        return false;
    const QString SelectStr = QString("select * from FaceInfo");
    QSqlQuery query(_db);
    const bool isSelect = query.exec(SelectStr);
    if(!isSelect)
        return false;
    while(query.next())
    {
        QStringList sqlList;
        for(int i = 0; i <= 1; i++)
        {
            sqlList.push_back(query.value(i).toString());
        }
        List.push_back(sqlList);
    }
    _db.close();
    return true;
}

bool SqlDataBase::GetFaceClockAllData(QList<QStringList> & List)
{
    _db.setDatabaseName(DataBaseFilePath);
    if(!_db.open())
        return false;
    const QString SelectStr = QString("select * from FaceDataBase");
    QSqlQuery query(_db);
    const bool isSelect = query.exec(SelectStr);
    if(!isSelect)
        return false;
    while(query.next())
    {
        QStringList sqlList;
        for(int i = 0; i <= 2; i++)
        {
            sqlList.push_back(query.value(i).toString());
        }
        List.push_back(sqlList);
    }
    _db.close();
    return true;
}

bool SqlDataBase::GetClockData(QList<QStringList>& List, QString name, QString id, QString DateTime1, QString DateTime2)
{
    _db.setDatabaseName(DataBaseFilePath);
    if(!_db.open())
        return false;
    if(name.isEmpty() && id.isEmpty() && DateTime1.isEmpty() && DateTime2.isEmpty())
        return false;
    if(!name.isEmpty() && id.isEmpty() && DateTime1.isEmpty() && DateTime2.isEmpty())
    {
        const QString selectStr = QString("select * from FaceDataBase where name = '%1'").arg(name);
        bool isSelect = GetValue(List,selectStr);
        if(!isSelect)
            return false;
    }
    else if(name.isEmpty() && !id.isEmpty() && DateTime1.isEmpty() && DateTime2.isEmpty())
    {
        const QString selectStr = QString("select * from FaceDataBase where id = %1").arg(id);
        bool isSelect = GetValue(List,selectStr);
        if(!isSelect)
            return false;
    }
    else if(name.isEmpty() && id.isEmpty() && !DateTime1.isEmpty() && !DateTime2.isEmpty())
    {
        const QString selectStr = QString("select * from FaceDataBase where ClockTime >= Datetime('%1') and ClockTime <= Datetime('%2')").arg(DateTime1).arg(DateTime2);
        bool isSelect = GetValue(List,selectStr);
        if(!isSelect)
            return false;
    }
    else if(!name.isEmpty() && id.isEmpty() && !DateTime1.isEmpty() && !DateTime2.isEmpty())
    {
        const QString selectStr = QString("select * from FaceDataBase where name = '%1' and ClockTime >= Datetime('%2') and ClockTime <= Datetime('%3')").arg(name).arg(DateTime1).arg(DateTime2);
        bool isSelect = GetValue(List,selectStr);
        if(!isSelect)
            return false;
    }
    else if(name.isEmpty() && !id.isEmpty() && !DateTime1.isEmpty() && !DateTime2.isEmpty())
    {
        const QString selectStr = QString("select * from FaceDataBase where id = %1 and ClockTime >= Datetime('%2') and ClockTime <= Datetime('%3')").arg(id).arg(DateTime1).arg(DateTime2);
        bool isSelect = GetValue(List,selectStr);
        if(!isSelect)
            return false;
    }
    else if(name.isEmpty() && id.isEmpty() && !DateTime1.isEmpty() && !DateTime2.isEmpty())
    {
        const QString selectStr = QString("select * from FaceDataBase where name = '%1' and id = %2 and ClockTime >= Datetime('%3') and ClockTime <= Datetime('%4')")
                                            .arg(name).arg(id).arg(DateTime1).arg(DateTime2);
        bool isSelect = GetValue(List,selectStr);
        if(!isSelect)
            return false;
    }
    _db.close();
    return true;
}

bool SqlDataBase::GetInfoData(QList<QStringList>& List, QString name, QString id)
{
    _db.setDatabaseName(DataBaseFilePath);
    if(!_db.open())
        return false;
    if(name.isEmpty() && id.isEmpty())
        return false;
    else if(!name.isEmpty() && id.isEmpty())
    {
        QSqlQuery query(_db);
        const QString selectStr = QString("select * from FaceInfo where name = '%1'").arg(name);
        bool isSelect = query.exec(selectStr);
        if(!isSelect)
            return false;
        while (query.next())
        {
            QStringList sqlList;
            for(int i = 0; i <= 1; i++)
            {
                sqlList.push_back(query.value(i).toString());
            }
            List.push_back(sqlList);
        }
    }
    else if(name.isEmpty() && !id.isEmpty())
    {
        QSqlQuery query(_db);
        const QString selectStr = QString("select * from FaceInfo where id = %1").arg(id);
        bool isSelect = query.exec(selectStr);
        if(!isSelect)
            return false;
        while (query.next())
        {
            QStringList sqlList;
            for(int i = 0; i <= 1; i++)
            {
                sqlList.push_back(query.value(i).toString());
            }
            List.push_back(sqlList);
        }
    }
    _db.close();
    return true;
}

bool SqlDataBase::GetInfoData(QString& Str, QString name, QString id)
{
    _db.setDatabaseName(DataBaseFilePath);
    if(!_db.open())
        return false;
    if(name.isEmpty() && id.isEmpty())
        return false;
    else if(!name.isEmpty() && id.isEmpty())
    {
        QSqlQuery query(_db);
        const QString selectStr = QString("select id from FaceInfo where name = '%1'").arg(name);
        bool isSelect = query.exec(selectStr);
        if(!isSelect)
            return false;
        while (query.next())
        {
            Str = query.value(0).toString();
        }
    }
    else if(name.isEmpty() && !id.isEmpty())
    {
        QSqlQuery query(_db);
        const QString selectStr = QString("select name from FaceInfo where id = %1").arg(id);
        bool isSelect = query.exec(selectStr);
        if(!isSelect)
            return false;
        while (query.next())
        {
            Str = query.value(0).toString();
        }
    }
    _db.close();
    return true;
}

bool SqlDataBase::GetValue(QList<QStringList>& List, QString selectStr)
{
    QSqlQuery query(_db);
    const bool isSelect = query.exec(selectStr);
    if(!isSelect)
        return false;
    while(query.next())
    {
        QStringList sqlList;
        for(int i = 0; i <= 2; i++)
        {
            sqlList.push_back(query.value(i).toString());
        }
        List.push_back(sqlList);
    }
    return true;
}

bool SqlDataBase::OpenDataBase()
{
    QFile file(DataBaseFilePath);
    const bool isExists = file.exists();
    if(!isExists)
    {
        const bool isCreate = CreateDataBaseFile();
        return isCreate;
    }
    const bool isOpen = file.open(QFile::ReadWrite);
    if(!isOpen)
    {
        return false;
    }
    _db.setDatabaseName(DataBaseFilePath);
    const bool isDBOpen = _db.open();
    if(!isDBOpen)
    {
        return false;
    }
    _db.close();
    file.close();
    return true;
}

bool SqlDataBase::CreateDataBaseFile()
{
    QFile file(DataBaseFilePath);
    const bool isOpen = file.open(QFile::WriteOnly);
    if(!isOpen)
        return false;
    _db.setDatabaseName(DataBaseFilePath);
    if(!_db.open())
    {
        return false;
    }
    QSqlQuery query;
    const QString cFaceClock = "create table FaceDataBase(id int,name varchar,ClockTime datetime)";
    const QString cFaceInfo = "create table FaceInfo(id int primary key,name varchar)";
    bool isExec = query.exec(cFaceClock);
    isExec = query.exec(cFaceInfo);

    _db.close();
    file.close();
    return true;
}
