#include "filemanager.h"

FileManager::FileManager() { InitialSetup(); }

void FileManager::InitialSetup() {}

void FileManager::SaveLocations() {
  QVector<QPair<QString, QString>> markerVector;
  QPair<QString, QString> latlonPair1;
  latlonPair1.first = "46";
  latlonPair1.second = "47";
  markerVector.append(latlonPair1);
  QPair<QString, QString> latlonPair2;
  latlonPair2.first = "44";
  latlonPair2.second = "45";
  markerVector.append(latlonPair2);
  QJsonObject root_obj;
  QJsonObject markers_obj;
  //  QJsonArray latlon_array;
  QJsonArray latlon_array;

  for (auto it : markerVector) {
    latlon_array << it.first << it.second;
  }
  markers_obj.insert("LatlON", latlon_array);
  root_obj.insert("Markers", markers_obj);
  QJsonDocument locationDoc(root_obj);
  QString json_string = locationDoc.toJson();
  QFile testFile;
  QString fileName(QDir::currentPath() + "LatLonSave1");
  testFile.setFileName(fileName);
  if (!testFile.open(QIODevice::WriteOnly)) {
    std::cout << "Failed to open File" << std::endl;
  }
  testFile.write(json_string.toLocal8Bit());
  testFile.close();
  std::cout << "Saved file at " << fileName.toStdString() << std::endl;
}
