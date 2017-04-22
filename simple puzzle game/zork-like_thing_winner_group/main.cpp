#include "mainwindow.h"
#include <QApplication>

template <typename T>
void showWindow() {
  static T w;
  w.setWindowTitle("Zork-like thing");
  w.show();
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // MainWindow w;
   // w.setWindowTitle("Zork-like thing");
    //w.setAttribute(Qt::WA_QuitOnClose,true);
   // w.show();
    showWindow<MainWindow>();
    //a.setQuitOnLastWindowClosed(true);
    //a.connect( &a,SIGNAL(lastWindowClosed()),&a,SLOT(quit()));
    return a.exec();
}

