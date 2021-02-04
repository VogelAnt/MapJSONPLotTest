#include "routewidget.h"

RouteWidget::RouteWidget() {
  m_routeOptionlist << "Route from coordinate"
                    << "Route from Adress";
  SetupGeneralLayout();
  connect(m_comboBox, &QComboBox::currentTextChanged, this,
          &RouteWidget::on_ComboBoxSwitched);
}

void RouteWidget::SetupGeneralLayout() {
  m_vLayout = new QVBoxLayout(this);
  m_hComboboxlayout = new QHBoxLayout();
  m_comboBox = new QComboBox(this);
  m_comboBox->addItems(m_routeOptionlist);
  m_hComboboxlayout->addWidget(m_comboBox, 1);
  m_hComboboxlayout->addSpacing(2);
  m_vLayout->addLayout(m_hComboboxlayout);
  m_gridLayout = new QGridLayout();
  m_fromLabel = new QLabel("From: ", this);
  m_gridLayout->addWidget(m_fromLabel, 0, 0);
  SetupLatLonLayout();
  SetupAdressLayout();
  m_hButtonlayout = new QHBoxLayout();
  m_findRoutebutton = new QPushButton("Find Route", this);
  m_clearButton = new QPushButton("Clear", this);
  m_hButtonlayout->addWidget(m_findRoutebutton);
  m_hButtonlayout->addWidget(m_clearButton);
  m_vLayout->addLayout(m_hButtonlayout);
}

void RouteWidget::SetupLatLonLayout() {
  // Lat Lon Layout
  m_toLabel = new QLabel("To: ", this);
  m_fromLatlabel = new QLabel("Lat", this);
  m_fromLatedit = new QLineEdit("", this);
  m_fromLonlabel = new QLabel("Lon", this);
  m_fromLonedit = new QLineEdit("", this);
  m_toLatlabel = new QLabel("Lat", this);
  m_toLatedit = new QLineEdit("", this);
  m_toLonlabel = new QLabel("Lon", this);
  m_toLonedit = new QLineEdit("", this);
  ChangeToLatLonLayout();
}

void RouteWidget::ChangeToLatLonLayout() {
  RemoveAdressLayout();
  m_gridLayout->addWidget(m_fromLatlabel, 1, 0);
  m_gridLayout->addWidget(m_fromLatedit, 1, 1);
  m_gridLayout->addWidget(m_fromLonlabel, 2, 0);
  m_gridLayout->addWidget(m_fromLonedit, 2, 1);
  m_gridLayout->addWidget(m_toLabel, 3, 0);
  m_gridLayout->addWidget(m_toLatlabel, 4, 0);
  m_gridLayout->addWidget(m_toLatedit, 4, 1);
  m_gridLayout->addWidget(m_toLonlabel, 5, 0);
  m_gridLayout->addWidget(m_toLonedit, 5, 1);
}

void RouteWidget::SetupAdressLayout() {
  // Address Layout
  m_fromStreetlabel = new QLabel("Street: ", this);
  m_fromCitylabel = new QLabel("City: ", this);
  m_fromCountrylabel = new QLabel("Country: ", this);
  m_toStreetlabel = new QLabel("Street: ", this);
  m_toCitylabel = new QLabel("City: ", this);
  m_fromCountrylabel = new QLabel("Country: ", this);
}

void RouteWidget::ChangeToAdressLayout() {
  RemoveLatLonLayout();
  m_gridLayout->addWidget(m_fromStreetlabel, 1, 0);
  m_gridLayout->addWidget(m_toStreetedit, 1, 1);
  m_gridLayout->addWidget(m_fromCitylabel, 2, 0);
  m_gridLayout->addWidget(m_toCityedit, 2, 1);
  m_gridLayout->addWidget(m_fromCountrylabel, 3, 0);
  m_gridLayout->addWidget(m_fromCountryedit, 3, 1);
  m_gridLayout->addWidget(m_toLabel, 4, 0);
  m_gridLayout->addWidget(m_toStreetlabel, 5, 0);
  m_gridLayout->addWidget(m_toStreetedit, 5, 1);
  m_gridLayout->addWidget(m_toCitylabel, 6, 0);
  m_gridLayout->addWidget(m_toCityedit, 6, 1);
  m_gridLayout->addWidget(m_toCountrylabel, 7, 0);
  m_gridLayout->addWidget(m_toCountryedit, 7, 1);
}

void RouteWidget::ClearLineEdits() {
  // copy from other projects
}

void RouteWidget::on_ComboBoxSwitched() {
  if (m_comboBox->currentText() == "Route from coordinate") {
    ChangeToLatLonLayout();
  } else if (m_comboBox->currentText() == "Route from Adress") {
    ChangeToAdressLayout();
  }
}

void RouteWidget::RemoveLatLonLayout() { ClearLineEdits(); }

void RouteWidget::RemoveAdressLayout() { ClearLineEdits(); }

RouteWidget::~RouteWidget() {
  delete m_vLayout;
  delete m_gridLayout;
}
