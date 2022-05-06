#ifndef _SQL_DATABASE_H_
#define _SQL_DATABASE_H_

#include <QObject>
#include <QSqlDatabase>

class SqlDataBase : public QObject
{
    Q_OBJECT
public:
    static SqlDataBase* Get();
    bool Open();
    bool InsertFaceInfo(QVariantList valueList);
    bool InsertFaceClock(QVariantList valueList);

    bool GetFaceInfoAllData(QList<QStringList>&);
    bool GetFaceClockAllData(QList<QStringList>&);
    bool GetClockData(QList<QStringList>&,QString name = "",QString id = "",QString DateTime1 = "",QString DateTime2 = "");
    bool GetInfoData(QList<QStringList>&,QString name = "",QString id = "");
    bool GetInfoData(QString&,QString name = "",QString id = "");
private:
    bool GetValue(QList<QStringList>&, QString selectStr);
    bool OpenDataBase();
    bool CreateDataBaseFile();
    SqlDataBase(QObject* parent = nullptr);
    ~SqlDataBase();
private:
    QSqlDatabase _db;
};

#endif //_SQL_DATABASE_H_
