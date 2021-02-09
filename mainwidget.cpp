#include "mainwidget.h"

MainWidget::MainWidget() {
  SetupScenarioMap();
  SetupGeneralLayout();
  connect(m_scenarioCombobox, &QComboBox::currentTextChanged, this,
          &MainWidget::on_ScenarioChanged);
  connect(m_scenarioCombobox, &QComboBox::currentTextChanged, this,
          &MainWidget::on_textSwitched);
  connect(m_scenarioCombobox, &QComboBox::currentTextChanged, this,
          &MainWidget::on_scenarioTypechanged);
  connect(markerModel, &MarkerModel::AddLatLonPairToUI, this,
          &MainWidget::on_AddLatLonPairToUI);
  connect(markerModel, &MarkerModel::ChangeCoordinateWidget, this,
          &MainWidget::on_ChangeCoordinateWidget);
  connect(markerModel, &MarkerModel::RMMarkerOne, this,
          &MainWidget::on_RMFirstMarker);
  connect(m_addCoordinatebutton, &QPushButton::clicked, this,
          &MainWidget::on_AddCoordinateButtonclicked);
  SetupHLayout(m_addMarkerlayout, Qt::AlignLeft);
  SetupVLayout(m_coordinateLayout, Qt::AlignTop);
}

void MainWidget::on_AddLatLonPairToUI(double lat, double lon) {
  CoordinateWidget *coordinateWidget =
      new CoordinateWidget(this, m_markerIndex, lat, lon);
  connect(coordinateWidget->m_removeCoordinatebutton, &QPushButton::clicked,
          this, &MainWidget::on_RemoveCoordinateWidget);
  m_coordinateLayout->addWidget(coordinateWidget);
  ++m_markerIndex;
}

void MainWidget::SetupGeneralLayout() {
  this->setMinimumSize(800, 500);
  m_hLayout = new QHBoxLayout(this);
  //  m_w1 = new QWidget(this);
  m_w2 = new QWidget(this);
  //  m_w1->setStyleSheet("background-color : red");
  m_w2->setStyleSheet("background-color : blue");
  //  m_hLayout->addWidget(m_w1, 1);
  SetupCoordinateLayout();
  SetupQuickLayout();
  m_hLayout->addLayout(m_coordinateLayout, 1);
  m_hLayout->addLayout(m_vLayout, 1);
  m_hLayout->addWidget(m_w2, 1);
}

void MainWidget::SetupScenarioMap() {
  m_scenarioMap["Single Static Scenario"] = m_singleScenarioselected;
  m_scenarioMap["Multi Static Scenario"] = m_multiScenarioselected;
  m_scenarioMap["Draw Scenario"] = m_drawScenarioselected;
  m_scenarioMap["Custom Dynamic Scenario"] = m_customScenarioselected;
}

void MainWidget::SetupQuickLayout() {
  m_vLayout = new QVBoxLayout();
  m_scenarioCombobox = new QComboBox(this);
  m_scenarioSelectionlist << "Single Static Scenario"
                          << "Multi Static Scenario"
                          << "Draw Scenario"
                          << "Custom Dynamic Scenario"
                          << "GeoCode Scenario";
  m_scenarioCombobox->addItems(m_scenarioSelectionlist);
  markerModel = new MarkerModel();
  qWidget = new QQuickWidget(this);
  qWidget->rootContext()->setContextProperty("markerModel", markerModel);
  qWidget->setSource(QUrl("qrc:/test.qml"));
  qWidget->setFocus();
  qWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
  m_vLayout->addWidget(m_scenarioCombobox, 1);
  m_vLayout->addWidget(qWidget, 1);
}

void MainWidget::on_textSwitched() {
  emit markerModel->comboBoxSelectionChanged();
  QString dropBoxtext = m_scenarioCombobox->currentText();
  if (dropBoxtext == "Single Static Scenario") {
    markerModel->SetDrawScenario(false);
    markerModel->SetSingleScenario(true);
    return;
  } else if (dropBoxtext == "Draw Scenario") {
    markerModel->SetSingleScenario(false);
    markerModel->SetDrawScenario(true);
    return;
  } else {
    markerModel->SetSingleScenario(false);
    markerModel->SetDrawScenario(false);
  }
  std::cout << "Emitted the marker model selection changed " << std::endl;
}

void MainWidget::SetupCoordinateLayout() {
  m_coordinateLayout = new QVBoxLayout();
  m_addMarkerlayout = new QHBoxLayout();
  m_latLabel = new QLabel("Lat ", this);
  m_latEdit = new QLineEdit(this);
  m_lonLabel = new QLabel("Lon", this);
  m_lonEdit = new QLineEdit(this);
  m_addCoordinatebutton = new QPushButton("+", this);
  m_addMarkerlayout->addWidget(m_latLabel);
  m_addMarkerlayout->addWidget(m_latEdit);
  m_addMarkerlayout->addWidget(m_lonLabel);
  m_addMarkerlayout->addWidget(m_lonEdit);
  m_addMarkerlayout->addWidget(m_addCoordinatebutton);
  // TODO: fix the proportions
  m_coordinateLayout->addLayout(m_addMarkerlayout);
}

void MainWidget::on_ScenarioChanged() {
  QString currentScenarioselection = m_scenarioCombobox->currentText();
  for (auto mapKey : m_scenarioMap.keys()) {
    m_scenarioMap[mapKey] = false;
  }
  m_scenarioMap[currentScenarioselection] = true;
  if (GetSingleScenarioStatus()) {
    std::cout << "Single SCenario selected" << std::endl;
  }
  if (GetMultiScenarioStatus()) {
    std::cout << "Multi SCenario selected" << std::endl;
  }
  if (GetDrawScenarioStatus()) {
    std::cout << "Draw SCenario selected" << std::endl;
  }
  if (GetCustomScenarioStatus()) {
    std::cout << "Custom SCenario selected" << std::endl;
  }
  //  emit SendSingleAndDrawStatus(GetSingleScenarioStatus(),
  //                               GetDrawScenarioStatus());
}

MainWidget::~MainWidget() {
  // for each Label and LineEdit
  delete m_hLayout;
}

void MainWidget::on_MapClicked() {
  std::cout << "CLICKED ON MAP " << std::endl;
}

void MainWidget::SetupVLayout(QVBoxLayout *vlayout, Qt::Alignment alignment) {
  vlayout->setSpacing(0);
  vlayout->setMargin(0);
  vlayout->setAlignment(alignment);
  vlayout->setContentsMargins(0, 0, 0, 0);
}

void MainWidget::SetupHLayout(QHBoxLayout *hlayout, Qt::Alignment alignment) {
  hlayout->setSpacing(0);
  hlayout->setMargin(0);
  hlayout->setAlignment(alignment);
  hlayout->setContentsMargins(0, 0, 0, 0);
}

void MainWidget::on_scenarioTypechanged() {
  m_markerIndex = 1;
  clearCoordinatelayout();
}

void MainWidget::clearCoordinatelayout() {
  QList<CoordinateWidget *> CoordinateWidgetList =
      this->findChildren<CoordinateWidget *>();
  foreach (CoordinateWidget *coordinateWidget, CoordinateWidgetList) {
    delete coordinateWidget;
  }
}

void MainWidget::on_ChangeCoordinateWidget(int idx, double lat, double lon) {
  QList<CoordinateWidget *> CoordinateWidgetList =
      this->findChildren<CoordinateWidget *>();
  foreach (CoordinateWidget *coordinateWidget, CoordinateWidgetList) {
    if (coordinateWidget->GetCoordinateIndex() == idx) {
      coordinateWidget->SetLat(lat);
      coordinateWidget->SetLon(lon);
    }
  }
}

void MainWidget::on_RMFirstMarker() {
  std::cout << "RMing MARKER" << std::endl;
  QList<CoordinateWidget *> CoordinateWidgetList =
      this->findChildren<CoordinateWidget *>();
  foreach (CoordinateWidget *coordinateWidget, CoordinateWidgetList) {
    if (coordinateWidget->GetCoordinateIndex() == 1) {
      delete coordinateWidget;
    }
  }
  ResetMarkerIndex();
}

void MainWidget::ResetMarkerIndex() {
  m_markerIndex = 1;
  QList<CoordinateWidget *> CoordinateWidgetList =
      this->findChildren<CoordinateWidget *>();
  foreach (CoordinateWidget *coordinateWidget, CoordinateWidgetList) {
    coordinateWidget->SetCoordinateIndex(m_markerIndex);
    ++m_markerIndex;
    std::cout << "SET COORDINATE INDEX TO "
              << coordinateWidget->GetCoordinateIndex() << std::endl;
  }
}

void MainWidget::on_RemoveCoordinateWidget() {
  CoordinateWidget *cordWidg = qobject_cast<CoordinateWidget *>(
      qobject_cast<QPushButton *>(sender())->parent());
  std::cout << "Removed Coordinate Widget of index "
            << cordWidg->GetCoordinateIndex() << std::endl;
  markerModel->removeMarkerFromUI(cordWidg->GetCoordinateIndex());
  delete qobject_cast<QPushButton *>(sender())->parent();
  ResetMarkerIndex();
}

void MainWidget::on_AddCoordinateButtonclicked() {
  std::cout << "Adding Coordinate at " << m_latEdit->text().toDouble() << " : "
            << m_lonEdit->text().toDouble() << std::endl;
  // TODO: convert to GeoCoordinate
  emit markerModel->addMarkerAtCoordinate(QGeoCoordinate(
      m_latEdit->text().toDouble(), m_lonEdit->text().toDouble(), 0));
}
