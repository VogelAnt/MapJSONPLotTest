#ifndef TESTWIDGET_H
#define TESTWIDGET_H
#include "mapmarker.h"

#include <iostream>
#include <QObject>
#include <QWidget>
#include <QObject>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtQuickWidgets/QtQuickWidgets>
#include <QtQuickWidgets/QQuickWidget>
#include <QtQuick>
#include <QComboBox>

class TestWidget : public QWidget {
  Q_PROPERTY(bool SingleStaticScenario READ GetSingleScenarioStatus NOTIFY
                 SendSingleAndDrawStatus)
public:
  TestWidget();
  ~TestWidget();
  Q_INVOKABLE bool GetSingleScenarioStatus() {
    return m_scenarioMap["Single Static Scenario"];
  }
  Q_INVOKABLE bool GetMultiScenarioStatus() {
    return m_scenarioMap["Multi Static Scenario"];
  }
  Q_INVOKABLE bool GetDrawScenarioStatus() {
    return m_scenarioMap["Draw Scenario"];
  }
  Q_INVOKABLE bool GetCustomScenarioStatus() {
    return m_scenarioMap["Custom Dynamic Scenario"];
  }
  QObject *m_item = nullptr;
signals:
  // TODO: unused delete
  void SendSingleAndDrawStatus(bool singleScenariostatus,
                               bool drawScenariostatus);

public slots:
  void on_MapClicked();

private:
  void SetupGeneralLayout();
  void SetupQuickLayout();
  void SetupScenarioMap();
  QHBoxLayout *m_hLayout = nullptr;
  QVBoxLayout *m_vLayout = nullptr;
  QComboBox *m_scenarioCombobox = nullptr;
  QWidget *m_w1 = nullptr;
  QQuickWidget *qWidget = nullptr;
  QWidget *m_w2 = nullptr;
  QStringList m_scenarioSelectionlist;
  bool m_singleScenarioselected;
  bool m_multiScenarioselected;
  bool m_drawScenarioselected;
  bool m_customScenarioselected;

  QHBoxLayout *m_addMarkerlayout = nullptr;
  QVBoxLayout *markerCoordlayout = nullptr;

  QMap<QString, bool> m_scenarioMap;
  MarkerModel *markerModel = nullptr;
  int m_markerIndex = 1;
private slots:
  // TODO: Add to Trajectory Editor
  /**
   * @brief on_AddLatLonPair
   * For a multi static scenario add the lat lon line edits
   * @param lat
   * @param lon
   */
  void on_AddLatLonPair(double lat, double lon);
  /**
   * @brief on_ScenarioChanged
   * When the scenario has been changed
   */
  // TODO: Add to Trajectory Editor
  void on_ScenarioChanged();
  void on_textSwitched();
};

#endif // TESTWIDGET_H
