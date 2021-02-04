#ifndef ROUTEWIDGET_H
#define ROUTEWIDGET_H

#include <QGridLayout>
#include <QVBoxLayout>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QStringList>

class RouteWidget : public QWidget {
  Q_OBJECT
public:
  RouteWidget();
  ~RouteWidget();
  QPushButton *m_clearButton = nullptr;
  QPushButton *m_findRoutebutton = nullptr;

private:
  void SetupGeneralLayout();
  void SetupLatLonLayout();
  void SetupAdressLayout();
  void ClearLineEdits();
  void ChangeToLatLonLayout();
  void ChangeToAdressLayout();
  void RemoveLatLonLayout();
  void RemoveAdressLayout();

  // General Layout
  QVBoxLayout *m_vLayout = nullptr;
  QHBoxLayout *m_hButtonlayout = nullptr;
  QHBoxLayout *m_hComboboxlayout = nullptr;
  QGridLayout *m_gridLayout = nullptr;
  QComboBox *m_comboBox = nullptr;
  QLabel *m_fromLabel = nullptr;
  QLabel *m_toLabel = nullptr;

  // Lat Lon Layout
  QLabel *m_fromLatlabel = nullptr;
  QLabel *m_fromLonlabel = nullptr;
  QLabel *m_toLatlabel = nullptr;
  QLabel *m_toLonlabel = nullptr;
  QLineEdit *m_fromLatedit = nullptr;
  QLineEdit *m_fromLonedit = nullptr;
  QLineEdit *m_toLatedit = nullptr;
  QLineEdit *m_toLonedit = nullptr;

  // Adress Layout
  QLabel *m_fromStreetlabel = nullptr;
  QLabel *m_fromCitylabel = nullptr;
  QLabel *m_fromCountrylabel = nullptr;
  QLabel *m_toStreetlabel = nullptr;
  QLabel *m_toCitylabel = nullptr;
  QLabel *m_toCountrylabel = nullptr;
  QLineEdit *m_fromStreetedit = nullptr;
  QLineEdit *m_fromCityedit = nullptr;
  QLineEdit *m_fromCountryedit = nullptr;
  QLineEdit *m_toStreetedit = nullptr;
  QLineEdit *m_toCityedit = nullptr;
  QLineEdit *m_toCountryedit = nullptr;
  QStringList m_routeOptionlist;
private slots:
  void on_ComboBoxSwitched();
};

#endif // ROUTEWIDGET_H
