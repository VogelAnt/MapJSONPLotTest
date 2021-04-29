#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include "mapmarker.h"
#include "coordinatewidget.h"
#include "filemanager.h"

#include <iostream>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
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
  void on_SendLatLonVector(QVector<QPair<QString, QString>> latLonvec);

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
  void SetupMenuBar();
  void LoadMarkersIntoUI();
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
  MapMarker *markerModel = nullptr;
  QMenuBar *m_menuBar = nullptr;
  QMenu *m_fileMenu = nullptr;
  QAction *m_saveAction = nullptr;
  QAction *m_loadAction = nullptr;
  FileManager m_fileManager;
  int m_markerIndex = 1;
  QVector<QPair<QString, QString>> m_latlonVector;

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
  void on_SaveActionTriggered();
  void on_LoadActionTriggered();
};

#endif // TESTWIDGET_H
