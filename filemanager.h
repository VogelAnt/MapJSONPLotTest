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
  /**
   * @brief SetupFileStructure
   * Create the directories and basic for scenarios and users
   */
  void SaveLocations(QVector<QPair<QString, QString>> latLonvec);
  void LoadLocations(QString fileName);
signals:
  void SendLatLonVec(QVector<QPair<QString, QString>> latLonVec);

private:
  void InitialSetup();
  QDir m_locationsDir;
  QString m_locationsDirpath =
      "home/tony/Documents/MapJSONPlotTest/LocationFiles";
};

#endif // FILEMANAGER_H
