#ifndef MAPMARKER_H
#define MAPMARKER_H

#include <iostream>
#include <cmath>
#include <QObject>
#include <QAbstractListModel>
#include <QGeoCoordinate>
#include <QDebug>
#include <QDate>

/**
 * @brief The gpxCoordinate struct
 * Embodies the position information of the respective point
 */
struct gpxCoordinate {
  QGeoCoordinate latlon;
  float ele;
  QDateTime time;
};

/**
 * @brief The MarkerModel class
 */
class MarkerModel : public QAbstractListModel {
  Q_OBJECT
  Q_PROPERTY(QVariantList path READ path NOTIFY pathChanged)

public:
  enum MarkerRoles { positionRole = Qt::UserRole, pathRole };
  MarkerModel(QObject *parent = nullptr);
  Q_INVOKABLE void addMarker(const QGeoCoordinate &coordinate,
                             float elevation = 0,
                             QDateTime dateTime = QDateTime::currentDateTime());
  Q_INVOKABLE int getMarkerCount() { return m_markerCount; }
  Q_INVOKABLE void increaseMarkerCount() { ++m_markerCount; }
  Q_INVOKABLE void decreaseMarkerCount() { --m_markerCount; }
  Q_INVOKABLE bool getSingleScenarioStatus() { return m_singleScenario; }
  Q_INVOKABLE bool getDrawScenarioStatus() { return m_drawScenario; }
  Q_INVOKABLE int resetMarkerCount() {
    m_markerCount = 0;
    return m_markerCount;
  }
  Q_INVOKABLE void
  changeMarkerPosition(int index, const QGeoCoordinate &coordinate,
                       float elevation = 0,
                       QDateTime dateTime = QDateTime::currentDateTime());
  //  void addMarker(const QGeoCoordinate &coordinate);
  Q_INVOKABLE void removeFirstMarker();
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  bool removeRows(int row, int count,
                  const QModelIndex &parent = QModelIndex()) override;
  bool removeRow(int row, const QModelIndex &parent = QModelIndex());
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;
  QVariantList path() const;
  double HaversineDistanceInKm(double lat_1, double lat_2, double lon_1,
                               double lon_2);
  double HaversineDistanceInMeters(double lat_1, double lat_2, double lon_1,
                                   double lon_2);
  void SetSingleScenario(bool status);
  void SetDrawScenario(bool status);
  void AddLatLonLabel(int markerCount, double lat, double lon);
signals:
  void pathChanged();
  void comboBoxSelectionChanged();
  void AddLatLonPairToUI(double lat, double lon);
  void ChangeCoordinateWidget(int idx, double lat, double lon);
  void RMMarkerOne();

private:
  bool m_singleScenario = true;
  bool m_drawScenario = false;
  QVector<QPair<double, double>> m_LatLonVector;
  QVector<gpxCoordinate> m_coordinates;
  int m_markerCount = 0;
};
#endif // MARKERMODEL_H
