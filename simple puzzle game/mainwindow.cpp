#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Room.h"
#include <iostream>
#include <string>
#include "stage.h"

#include <QtWidgets>
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::initialize(){
    ui->screen->setPixmap(QPixmap(":/recipe/recipe/room1.jpg"));
    createRooms();
    displayStage("Room:a");
    ui->text->setPlainText("hello");
    QObject::connect(ui->equipment,SIGNAL(newLabel(QPixmap)),this,SLOT(taken(QPixmap)));
    QObject::connect(ui->screen,SIGNAL(dropNew(QString)),this,SLOT(got(QString)));
    QObject::connect(ui->tryWindow,SIGNAL(newLabel(QPixmap)),this,SLOT(taken(QPixmap)));
    QObject::connect(ui->tryWindow,SIGNAL(newLabel(QPixmap)),this,SLOT(identify(QPixmap)));
    QObject::connect(ui->label_2,SIGNAL(clicked()),this,SLOT(explain()));
}

void MainWindow::taken(QPixmap pixmap){
    QPixmap *key= new QPixmap(":/images/images/key.png");
    QPixmap *doorkey= new QPixmap(":/images/images/doorkey.png");
    QPixmap *note= new QPixmap(":/images/images/note.png");
    QPixmap *trophy= new QPixmap(":/images/images/trophy.png");
    //ui->text->setPlainText("hi");
    int get=-1;
    if(pixmap.toImage()==key->toImage()){
        get=currentRoom->isItemInRoom("A key");
        if(get>=0){
            ui->text->setPlainText("You take a key");
        }
    }
    if(pixmap.toImage()==doorkey->toImage()){
        get=currentRoom->isItemInRoom("A doorkey");
        if(get>=0){
            ui->text->setPlainText("You take a doorkey");
        }
    }
    if(pixmap.toImage()==note->toImage()){
        get=currentRoom->isItemInRoom("A note");
        if(get>=0){
            ui->text->setPlainText("You take a note");
        }
    }
    if(pixmap.toImage()==trophy->toImage()){
        get=currentRoom->isItemInRoom("A trophy");
        if(get>=0){
            ui->text->setPlainText("You take a trophy");
        }
    }
    key->~QPixmap();
    doorkey->~QPixmap();
    note->~QPixmap();
    trophy->~QPixmap();
}

void MainWindow::identify(QPixmap pixmap){

    this->image= pixmap.toImage();

}

void MainWindow::explain(){
     ui->text->setPlainText("You can put an item in the window below."
                            " \n\t By clicking \"Try\",you may trigger event in curent room. "
                            "\n\t By clicking \"Info\",you can get more detailed infomation about current item.  ");
}

QImage MainWindow::getImage(){
    return this->image;
}

void MainWindow::got(QString itemName){
    ui->text->setPlainText("ouch");
    string stdItemName=itemName.toStdString();
    int judge=currentRoom->isItemInRoom(stdItemName);
    if(judge<0){
        currentRoom->addItem(new Item(stdItemName,1,10));
    }

}

QString MainWindow::whichRoom(QString o){
    if(o=="Room:a")return ":/recipe/recipe/room1.jpg";
    else if(o=="Room:b")return ":/recipe/recipe/room2.jpg";
    else if(o=="Room:c")return ":/recipe/recipe/room3.jpg";
    else if(o=="Room:d")return ":/recipe/recipe/room4.jpg";
    else if(o=="Room:e")return ":/recipe/recipe/room5.jpg";
    else if(o=="Room:f")return ":/recipe/recipe/room6.jpg";
    else if(o=="Room:g")return ":/recipe/recipe/room7.jpg";
    else if(o=="Room:h")return ":/recipe/recipe/room8.jpg";
    else if(o=="Room:i")return ":/recipe/recipe/room9.jpg";
    else return "";
}

void MainWindow::clearStage(){
    if(ui->screen->findChild<QLabel *>("A key")){
 ui->screen->keyIcon->hide();
    }
    if(ui->screen->findChild<QLabel *>("A doorkey")){
ui->screen->doorkeyIcon->hide();
    }
    if(ui->screen->findChild<QLabel *>("A note")){
 ui->screen->noteIcon->hide();
    }
    if(ui->screen->findChild<QLabel *>("A trophy")){
 ui->screen->trophyIcon->hide();
    }
}

void MainWindow::displayStage(QString o){
    QString room=o.at(5);
    if(room=="a")tem=a;
        else if(room=="b")tem=b;
        else if(room=="c")tem=c;
        else if(room=="d")tem=d;
        else if(room=="e")tem=e;
        else if(room=="f")tem=f;
        else if(room=="g")tem=g;
        else if(room=="h")tem=h;
        else if(room=="i")tem=i;
    if(tem->itemSize()>0){
        int size=tem->itemSize();
        for(int x=0;x<size;x++){
            QString dItem=QString::fromStdString(tem->displayItem(x));
            if(ui->screen->findChild<QLabel *>(dItem)){
            ui->screen->showItem(dItem);
            }
        }
    }
}


void MainWindow::on_N_clicked()
{
    QString o=QString::fromStdString(go("north"));
    QString pic=whichRoom(o);
    if(pic!=""){
        if(currentRoom->checkRoomLicense()==true){
            clearStage();
            ui->screen->setPixmap(QPixmap(pic));
            displayStage(o);
            ui->text->setPlainText(o);
        }
        else {ui->text->setPlainText("Room locked.");
        go("south");
        }
    }
}


void MainWindow::on_W_clicked()
{
    QString o=QString::fromStdString(go("west"));
    QString pic=whichRoom(o);
    if(pic!=""){
        if(currentRoom->checkRoomLicense()==true){
            clearStage();
            ui->screen->setPixmap(QPixmap(pic));
            displayStage(o);
            ui->text->setPlainText(o);
        }
        else {ui->text->setPlainText("Room locked.");
            go("east");
        }
    }
}

void MainWindow::on_E_clicked()
{
    QString o=QString::fromStdString(go("east"));
    QString pic=whichRoom(o);
    if(pic!=""){
        if(currentRoom->checkRoomLicense()==true){
            clearStage();
            ui->screen->setPixmap(QPixmap(pic));
            displayStage(o);
            ui->text->setPlainText(o);
        }
        else {ui->text->setPlainText("Room locked.");
            go("west");
        }
    }
}

void MainWindow::on_S_clicked()
{
    QString o=QString::fromStdString(go("south"));
    QString pic=whichRoom(o);
    if(pic!=""){
        if(currentRoom->checkRoomLicense()==true){
            clearStage();
            ui->screen->setPixmap(QPixmap(pic));
            displayStage(o);
            ui->text->setPlainText(o);
        }
        else {ui->text->setPlainText("Room locked.");
            go("north");
        }
    }
}

void MainWindow::createRooms()  {
    a = new Room("Room:a",1);
        a->addItem(new Item("A note", 1, 11));
    b = new Room("Room:b",0);
        b->addItem(new Item("A trophy", 1, 11));
    c = new Room("Room:c",1);
    d = new Room("Room:d",0);
    e = new Room("Room:e",1);
        e->addItem(new Item("A doorkey", 1, 11));
    f = new Room("Room:f",1);
    g = new Room("Room:g",1);
    h = new Room("Room:h",1);
        h->addItem(new Item("A key", 1, 11));
    i = new Room("Room:i",1);       
//             (N, E, S, W)
    a->setExits(f, b, d, c);
    b->setExits(NULL, NULL, NULL, a);
    c->setExits(NULL, a, NULL, NULL);
    d->setExits(a, e, NULL, i);
    e->setExits(NULL, NULL, NULL, d);
    f->setExits(NULL, g, a, h);
    g->setExits(NULL, NULL, NULL, f);
    h->setExits(NULL, f, NULL, NULL);
    i->setExits(NULL, d, NULL, NULL);
        currentRoom = a;
}

string MainWindow::go(string direction) {
    //Make the direction lowercase
    //Move to the next room
    Room* nextRoom = currentRoom->nextRoom(direction);
    if (nextRoom == NULL)
        return("You are trying to walk through a wall.");
    else
    {
        currentRoom = nextRoom;
        return currentRoom->longDescription();
    }
}

void MainWindow::on_tryItem_clicked()
{
    QPixmap *key= new QPixmap(":/images/images/key.png");
    QPixmap *doorkey= new QPixmap(":/images/images/doorkey.png");
    QPixmap *note= new QPixmap(":/images/images/note.png");
    QPixmap *trophy= new QPixmap(":/images/images/trophy.png");
    if(this->getImage()==key->toImage()){
        if(currentRoom==a){
            ui->text->setPlainText("The room to the south has been unlocked");
            d->openRoomLicense();
        }
       else ui->text->setPlainText("Nothing happened");
    }
    if(this->getImage()==doorkey->toImage()){
           if(currentRoom==a){
               ui->text->setPlainText("The room to the east has been unlocked");
               b->openRoomLicense();
           }
       else ui->text->setPlainText("Nothing happened");

    }
    if(this->getImage()==note->toImage()){
        ui->text->setPlainText("Nothing happened");
    }
    if(this->getImage()==trophy->toImage()){
        ui->text->setPlainText("Nothing happened");
    }
    key->~QPixmap();
    doorkey->~QPixmap();
    note->~QPixmap();
    trophy->~QPixmap();
}

void MainWindow::on_getInfo_clicked()
{
    QPixmap *key= new QPixmap(":/images/images/key.png");
    QPixmap *doorkey= new QPixmap(":/images/images/doorkey.png");
    QPixmap *note= new QPixmap(":/images/images/note.png");
    QPixmap *trophy= new QPixmap(":/images/images/trophy.png");
    if(this->getImage()==key->toImage()){
        ui->text->setPlainText("a beatiful key");
    }
    if(this->getImage()==doorkey->toImage()){
        ui->text->setPlainText("a beatiful doorkey");
    }
    if(this->getImage()==note->toImage()){
        ui->text->setPlainText("Welcome, try to find a way to the east room.");
    }
    if(this->getImage()==trophy->toImage()){
        ui->text->setPlainText("Congraduations! You have finished the puzzle! This beautiful gold trophy is for you!");
    }
    key->~QPixmap();
    doorkey->~QPixmap();
    note->~QPixmap();
    trophy->~QPixmap();
}
