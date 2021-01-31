#include "mapmarker.h"

MarkerModel::MarkerModel(QObject *parent) : QAbstractListModel(parent) {
  connect(this, &QAbstractListModel::rowsInserted, this,
          &MarkerModel::pathChanged);
  connect(this, &QAbstractListModel::rowsRemoved, this,
          &MarkerModel::pathChanged);
  connect(this, &QAbstractListModel::dataChanged, this,
          &MarkerModel::pathChanged);
  connect(this, &QAbstractListModel::modelReset, this,
          &MarkerModel::pathChanged);
  connect(this, &QAbstractListModel::rowsMoved, this,
          &MarkerModel::pathChanged);
}

void MarkerModel::addMarker(const QGeoCoordinate &coordinate, float elevation,
                            QDateTime dateTime) {
  QPair<double, double> latLonpair;
  latLonpair.first = coordinate.latitude();
  latLonpair.second = coordinate.longitude();
  gpxCoordinate item;
  item.latlon = coordinate;
  item.ele = elevation;
  item.time = dateTime;
  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  m_coordinates.append(item);
  endInsertRows();
  std::cout << "LAT: " << coordinate.latitude()
            << " LON: " << coordinate.longitude() << std::endl;
  m_LatLonVector.append(latLonpair);
  emit AddLatLonPairToUI(coordinate.latitude(), coordinate.longitude());
  //  std::cout << "COORDINATES : " << coordinate.toString().toStdString() <<
  //  "\n"
  //            << "ELEVATION : " << QString::number(elevation).toStdString()
  //            << "\n"
  //            << "DATE TIME : " << dateTime.toString().toStdString() <<
  //            std::endl;
  // TODO: from here write a function to compute the distance between two points
  // TODO: think how you can use that in conjunction with the section function
  // TODO: how do you add text to the map ?
  // TODO: in the beginning: there should be an option to start from a fixed
  // point and go from there
  // TODO: or do the setting of way points free flow
}

void MarkerModel::changeMarkerPosition(int markerindex,
                                       const QGeoCoordinate &coordinate,
                                       float elevation, QDateTime dateTime) {
  emit ChangeCoordinateWidget(markerindex, coordinate.latitude(),
                              coordinate.longitude());
}

int MarkerModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid()) {
    return 0;
  }
  return m_coordinates.count();
}

// TODO: read the doc of QAbstractItemModel
bool MarkerModel::removeRows(int row, int count, const QModelIndex &parent) {
  std::cout << "Now in removeRows" << std::endl;
  if (row + count > m_coordinates.count() || row < 0)
    return false;
  beginRemoveRows(parent, row, row + count - 1);
  for (int i = 0; i < count; ++i)
    m_coordinates.removeAt(row + i);
  endRemoveRows();
  return true;
}

bool MarkerModel::removeRow(int row, const QModelIndex &parent) {
  return removeRows(row, 1, parent);
}

QVariant MarkerModel::data(const QModelIndex &index, int role) const {
  if (index.row() < 0 || index.row() >= m_coordinates.count())
    return QVariant();
  if (role == Qt::DisplayRole)
    return QVariant::fromValue(index.row());
  else if (role == MarkerModel::positionRole) {
    return QVariant::fromValue(m_coordinates[index.row()].latlon);
  }
  return QVariant();
}

QHash<int, QByteArray> MarkerModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[positionRole] = "positionRole";
  return roles;
}

QVariantList MarkerModel::path() const {
  QVariantList path;
  for (const gpxCoordinate &coord : m_coordinates) {
    path << QVariant::fromValue(coord.latlon);
  }
  return path;
}

double MarkerModel::HaversineDistanceInKm(double lat_1, double lat_2,
                                          double lon_1, double lon_2) {
  // Compute distance between longitude and latitude
  double dLat = (lat_2 - lat_1) * M_PI / 180.0;
  double dLon = (lon_2 - lon_1) * M_PI / 180.0;

  // convert to radians
  lat_1 *= M_PI / 180.0;
  lat_2 *= M_PI / 180.0;
  double a =
      pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat_1) * cos(lat_2);
  double earthRadius = 6371;
  double c = 2 * asin(sqrt(a));
  return earthRadius * c;
}

void MarkerModel::SetSingleScenario(bool status) {
  m_singleScenario = status;
  std::cout << "Single scenario status is "
            << QString::number(status).toStdString() << std::endl;
}

void MarkerModel::SetDrawScenario(bool status) {
  m_drawScenario = status;
  std::cout << "Draw Scenario Status is "
            << QString::number(status).toStdString() << std::endl;
}

void MarkerModel::removeFirstMarker() { emit RMMarkerOne(); }

double MarkerModel::HaversineDistanceInMeters(double lat_1, double lat_2,
                                              double lon_1, double lon_2) {
  // Compute distance between longitude and latitude
  double dLat = (lat_2 - lat_1) * M_PI / 180.0;
  double dLon = (lon_2 - lon_1) * M_PI / 180.0;

  // convert to radians
  lat_1 *= M_PI / 180.0;
  lat_2 *= M_PI / 180.0;
  double a =
      pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat_1) * cos(lat_2);
  double earthRadius = 6371;
  double c = 2 * asin(sqrt(a));
  return earthRadius * c * 1000;
}
