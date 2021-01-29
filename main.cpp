#include "mainwindow.h"
#include "testwidget.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  TestWidget tw;
  tw.show();
  return a.exec();
}
