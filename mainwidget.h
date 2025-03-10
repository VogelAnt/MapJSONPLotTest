#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include "mapmarker.h"
#include "coordinatewidget.h"

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
#include <QPushButton>

class MainWidget : public QWidget {
  Q_PROPERTY(bool SingleStaticScenario READ GetSingleScenarioStatus NOTIFY
                 SendSingleAndDrawStatus)
public:
  MainWidget();
  ~MainWidget();
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

public slots:
  void on_MapClicked();
  void on_AddLatLonPairToUI(double lat, double lon);
  void on_scenarioTypechanged();
  void on_ChangeCoordinateWidget(int idx, double lat, double lon);
  void on_RMFirstMarker();

private:
  void SetupVLayout(QVBoxLayout *vlayout, Qt::Alignment alignment);
  void SetupHLayout(QHBoxLayout *hlayout, Qt::Alignment alignment);
  void SetupCoordinateLayout();
  void SetupGeneralLayout();
  void SetupQuickLayout();
  void SetupScenarioMap();
  void AddToCoordinateLayout();
  void clearCoordinatelayout();
  void SetupHorizontalLayout();
  void SetupVerticalLayout();
  void ResetMarkerIndex();
  // Map Widget layout
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

  // coordinate layout
  QHBoxLayout *m_addMarkerlayout = nullptr;
  QVBoxLayout *m_coordinateLayout = nullptr;
  QLabel *m_latLabel = nullptr;
  QLineEdit *m_latEdit = nullptr;
  QLabel *m_lonLabel = nullptr;
  QLineEdit *m_lonEdit = nullptr;
  QPushButton *m_addCoordinatebutton = nullptr;
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
  void on_RemoveCoordinateWidget();
  void on_AddCoordinateButtonclicked();
};

#endif // TESTWIDGET_H
