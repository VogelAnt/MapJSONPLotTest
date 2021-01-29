#include "testwidget.h"

TestWidget::TestWidget() {
  SetupScenarioMap();
  SetupGeneralLayout();
  connect(m_scenarioCombobox, &QComboBox::currentTextChanged, this,
          &TestWidget::on_ScenarioChanged);
  connect(m_scenarioCombobox, &QComboBox::currentTextChanged, this,
          &TestWidget::on_textSwitched);
}

void TestWidget::SetupGeneralLayout() {
  m_hLayout = new QHBoxLayout(this);
  m_w1 = new QWidget(this);
  m_w2 = new QWidget(this);
  m_w1->setStyleSheet("background-color : red");
  m_w2->setStyleSheet("background-color : blue");
  m_hLayout->addWidget(m_w1, 1);
  SetupQuickLayout();
  m_hLayout->addLayout(m_vLayout, 1);
  m_hLayout->addWidget(m_w2, 1);
}

void TestWidget::SetupScenarioMap() {
  m_scenarioMap["Single Static Scenario"] = m_singleScenarioselected;
  m_scenarioMap["Multi Static Scenario"] = m_multiScenarioselected;
  m_scenarioMap["Draw Scenario"] = m_drawScenarioselected;
  m_scenarioMap["Custom Dynamic Scenario"] = m_customScenarioselected;
}

void TestWidget::SetupQuickLayout() {
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
  m_vLayout->addWidget(m_scenarioCombobox, 1);
  m_vLayout->addWidget(qWidget, 1);
}

void TestWidget::on_AddLatLonPair(double lat, double lon) {
  QHBoxLayout *latlonLayout = new QHBoxLayout();
  QLabel *latLabel = new QLabel("Latitude: ", this);
  QLabel *lonLabel = new QLabel("Longitude: ", this);
  QLineEdit *latEdit = new QLineEdit(QString::number(lat), this);
  QLineEdit *lonEdit = new QLineEdit(QString::number(lon), this);

  latlonLayout->addWidget(latLabel, 1);
  latlonLayout->addWidget(latEdit, 1);
  latlonLayout->addWidget(lonLabel, 1);
  latlonLayout->addWidget(lonEdit, 1);
  m_vLayout->addLayout(latlonLayout);
}

void TestWidget::on_textSwitched() {
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

void TestWidget::on_ScenarioChanged() {
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

TestWidget::~TestWidget() {
  // for each Label and LineEdit
  delete m_hLayout;
}

void TestWidget::on_MapClicked() {
  std::cout << "CLICKED ON MAP " << std::endl;
}
