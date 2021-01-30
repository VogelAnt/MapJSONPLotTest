#include "mainwindow.h"
#include "mainwidget.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWidget tw;
  tw.show();
  return a.exec();
}
