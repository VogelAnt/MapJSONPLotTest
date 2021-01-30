#include "coordinatewidget.h"

CoordinateWidget::CoordinateWidget(QWidget *parent, int index, double lat,
                                   double lon) {
  m_coordinateIndex = index;
  m_lat = lat;
  m_lon = lon;
  SetupLayout();
  SetupHLayout(m_coordinateLayout, Qt::AlignLeft);
}

CoordinateWidget::~CoordinateWidget() { delete m_coordinateLayout; }

void CoordinateWidget::SetupLayout() {
  m_coordinateLayout = new QHBoxLayout(this);
  m_removeCoordinatebutton = new QPushButton("-", this);
  m_coordinateLabel =
      new QLabel("Coordinate #" + QString::number(m_coordinateIndex) + " Lat " +
                     QString::number(m_lat) + " Lon " + QString::number(m_lon),
                 this);
  m_coordinateLayout->addWidget(m_removeCoordinatebutton);
  m_coordinateLayout->addWidget(m_coordinateLabel);
  // TODO: make the layout here tighter and align left
}

void CoordinateWidget::SetupHLayout(QHBoxLayout *hlayout,
                                    Qt::Alignment alignment) {
  hlayout->setSpacing(0);
  hlayout->setMargin(0);
  hlayout->setAlignment(alignment);
  hlayout->setContentsMargins(0, 0, 0, 0);
}

void CoordinateWidget::SetLabelText() {
  m_coordinateLabel->setText(
      "Coordinate #" + QString::number(m_coordinateIndex) + " Lat " +
      QString::number(m_lat) + " Lon " + QString::number(m_lon));
}

void CoordinateWidget::SetLat(double lat) {
  m_lat = lat;
  SetLabelText();
}

void CoordinateWidget::SetLon(double lon) {
  m_lon = lon;
  SetLabelText();
}
