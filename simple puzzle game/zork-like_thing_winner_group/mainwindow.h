#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <iostream>
#include <string>
#include "Room.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    string go(string direction);
    QString whichRoom(QString o);
    void displayStage(QString o);
    void clearStage();
private slots:

    void on_N_clicked();

    void on_W_clicked();

    void on_E_clicked();

    void on_S_clicked();

    void taken(QPixmap pixmap);

    void got(QString itemName);

    void identify(QPixmap pixmap);

    void explain();

    QImage getImage();

    void on_tryItem_clicked();

    void on_getInfo_clicked();

private:
    Ui::MainWindow *ui;
    void initialize();
    Room *currentRoom;
    void createRooms();
    Room *a, *b, *c, *d, *e, *f, *g, *h, *i,*tem;
    QImage image;
};

#endif // MAINWINDOW_H
