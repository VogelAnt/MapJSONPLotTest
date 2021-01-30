#ifndef COORDINATEWIDGET_H
#define COORDINATEWIDGET_H

#include <QObject>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QPushButton>

class CoordinateWidget : public QWidget {
  Q_OBJECT
public:
  CoordinateWidget(QWidget *parent, int index, double lat, double lon);
  ~CoordinateWidget();
  void SetLat(double lat);
  void SetLon(double lon);
  void SetLabelText();

private:
  void SetupHLayout(QHBoxLayout *hlayout, Qt::Alignment alignment);
  void SetupLayout();
  int m_coordinateIndex = 1;
  QHBoxLayout *m_coordinateLayout = nullptr;
  QPushButton *m_removeCoordinatebutton = nullptr;
  QLabel *m_coordinateLabel = nullptr;
  double m_lat;
  double m_lon;
};

#endif // COORDINATEWIDGET_H
