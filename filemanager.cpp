#include "filemanager.h"

FileManager::FileManager() { InitialSetup(); }

void FileManager::InitialSetup() {}

void FileManager::SaveLocations(QVector<QPair<QString, QString>> latLonvec) {
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

  for (auto it : latLonvec) {
    QJsonObject latLon;
    latLon[it.first] = it.second;
    latlon_array << latLon;
  }
  root_obj.insert("LatLonPair", latlon_array);
  //  .insert("Markers", markers_obj);
  QJsonDocument locationDoc(root_obj);
  QString json_string = locationDoc.toJson();
  QFile testFile;
  QString fileName(QDir::currentPath() + "LatLonSave1.json");
  testFile.setFileName(fileName);
  if (!testFile.open(QIODevice::WriteOnly)) {
    std::cout << "Failed to open File" << std::endl;
  }
  testFile.write(json_string.toLocal8Bit());
  testFile.close();
  std::cout << "Saved file at " << fileName.toStdString() << std::endl;
}

void FileManager::LoadLocations(QString fileName) {
  QFile file_obj(fileName);
  if (!file_obj.open(QIODevice::ReadOnly)) {
    std::cout << "Failed to open file: " << fileName.toStdString() << std::endl;
    exit(1);
  }
  QTextStream file_text(&file_obj);
  QString json_string;
  json_string = file_text.readAll();
  file_obj.close();
  QByteArray json_bytes = json_string.toLocal8Bit();
  auto json_doc = QJsonDocument::fromJson(json_bytes);
  if (json_doc.isNull()) {
    std::cout << "Failed to create json doc from: " << json_bytes.toStdString()
              << std::endl;
    exit(2);
  }
  std::cout << "Printing JSON doc " << json_doc.toJson().toStdString()
            << std::endl;
  if (!json_doc.isObject()) {
    std::cout << "json doc is not object." << std::endl;
    exit(3);
  }
  QJsonObject root_obj = json_doc.object();
  QVariantMap root_map = root_obj.toVariantMap();
  QVariantList latlonVariantlist = root_map["LatLonPair"].toList();
  if (latlonVariantlist.isEmpty()) {
    std::cout << "The inventory array is empty";
  }
  // TODO: take this user list and use it as
  for (int i = 0; i < latlonVariantlist.count(); ++i) {
    QString userName = latlonVariantlist.at(i).toString();
    std::cout << userName.toStdString() << std::endl;
    //    userList.append(userName);
  }
}
