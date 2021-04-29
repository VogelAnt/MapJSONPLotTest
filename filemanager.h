#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <iostream>

#include <QObject>
#include <QFile>
#include <QDir>
#include <QVariantMap>
#include <QVector>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>

class FileManager : QObject {
  Q_OBJECT
public:
  FileManager();
  void SaveLocations(QVector<QPair<QString, QString>> latLonvec);
  QVector<QPair<QString, QString>> LoadLocations(QString fileName);

signals:
  void SendLatLonVec(QVector<QPair<QString, QString>> latLonVec);

private:
  void InitialSetup();
  QDir m_locationsDir;
  QString m_locationsDirpath =
      "home/tony/Documents/MapJSONPlotTest/LocationFiles";
};

#endif // FILEMANAGER_H
