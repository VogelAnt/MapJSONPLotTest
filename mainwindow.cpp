#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  QWidget *centralWidget = new QWidget(this);
  QHBoxLayout *hLayout = new QHBoxLayout(centralWidget);
  m_qWidget = new QQuickWidget(centralWidget);
  m_qWidget->setSource(QUrl::fromLocalFile("qrc:///Map.qml"));
  m_qWidget->show();
  hLayout->addWidget(m_qWidget);
}

MainWindow::~MainWindow() { delete ui; }
