#include "filemanager.h"

FileManager::FileManager() { InitialSetup(); }

void FileManager::InitialSetup() {}

// TODO: Add FileName from FileDialog
void FileManager::SaveLocations(QVector<QPair<QString, QString>> latLonvec) {
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

QVector<QPair<QString, QString>> FileManager::LoadLocations(QString fileName) {
  QVector<QPair<QString, QString>> latLonvector;
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
  // root obj needed
  QJsonObject root_obj = json_doc.object();
  QVariantMap root_map = root_obj.toVariantMap();

  QVariantMap stats = root_map["LatLonPair"].toMap();

  // rename inv to LatLonList
  QVariantList lat_lon_list = root_map["LatLonPair"].toList();

  if (lat_lon_list.isEmpty()) {
    qDebug() << "The lat lon list is empty";
  }
  for (int i; i < lat_lon_list.count(); ++i) {
    QVariantMap var_latlon_map = lat_lon_list.at(i).toMap();
    for (auto it : var_latlon_map.keys()) {
      QStringList latlon_values = var_latlon_map.value(it).toStringList();
      QPair<QString, QString> latlonPair;
      latlonPair.first = it;
      latlonPair.second = var_latlon_map.value(it).toString();
      latLonvector.push_back(latlonPair);
    }
  }
  if (latLonvector.isEmpty()) {
    qDebug() << "Vector is empty !!!";
  }
  return latLonvector;
}
