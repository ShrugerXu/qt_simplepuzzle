#include "stage.h"
#include "item.h"
#include <QtWidgets>
Stage::Stage(QWidget *parent)   : QLabel(parent)
{
    setAcceptDrops(true);
    initialize();
}

void Stage::initialize(){
        keyIcon = new QLabel(this);
        keyIcon->setPixmap(QPixmap(":/images/images/key.png"));
        keyIcon->move(430, 100);
        keyIcon->setVisible(false);
        keyIcon->setObjectName(QStringLiteral("A key"));
        keyIcon->setAttribute(Qt::WA_DeleteOnClose);
        doorkeyIcon = new QLabel(this);
        doorkeyIcon->setPixmap(QPixmap(":/images/images/doorkey.png"));
        doorkeyIcon->move(400, 200);
        doorkeyIcon->setVisible(false);
        doorkeyIcon->setObjectName(QStringLiteral("A doorkey"));
        doorkeyIcon->setAttribute(Qt::WA_DeleteOnClose);
        noteIcon = new QLabel(this);
        noteIcon->setPixmap(QPixmap(":/images/images/note.png"));
        noteIcon->move(180, 220);
        noteIcon->setVisible(false);
        noteIcon->setObjectName(QStringLiteral("A note"));
        noteIcon->setAttribute(Qt::WA_DeleteOnClose);
        trophyIcon = new QLabel(this);
        trophyIcon->setPixmap(QPixmap(":/images/images/trophy.png"));
        trophyIcon->move(400, 200);
        trophyIcon->setVisible(false);
        trophyIcon->setObjectName(QStringLiteral("A trophy"));
        trophyIcon->setAttribute(Qt::WA_DeleteOnClose);
}

void Stage::showItem(QString itemName){
    if(itemName=="A key")keyIcon->show();
    else if(itemName=="A doorkey")doorkeyIcon->show();
    else if(itemName=="A note")noteIcon->show();
    else if(itemName=="A trophy")trophyIcon->show();
}

void Stage::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void Stage::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void Stage::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;
        QPixmap *key= new QPixmap(":/images/images/key.png");
        QPixmap *doorkey= new QPixmap(":/images/images/doorkey.png");
        QPixmap *note= new QPixmap(":/images/images/note.png");
        QPixmap *trophy= new QPixmap(":/images/images/trophy.png");
        if(pixmap.toImage()==key->toImage()){
            keyIcon = new QLabel(this);
            keyIcon->setObjectName(QStringLiteral("A key"));
            keyIcon->setPixmap(pixmap);
            keyIcon->move(event->pos() - offset);
            keyIcon->show();
            keyIcon->setAttribute(Qt::WA_DeleteOnClose);
            emit dropNew("A key");
        }
        else if(pixmap.toImage()==doorkey->toImage()){
            doorkeyIcon = new QLabel(this);
            doorkeyIcon->setObjectName(QStringLiteral("A doorkey"));
            doorkeyIcon->setPixmap(pixmap);
            doorkeyIcon->move(event->pos() - offset);
            doorkeyIcon->show();
            doorkeyIcon->setAttribute(Qt::WA_DeleteOnClose);
            emit dropNew("A doorkey");
        }
        else if(pixmap.toImage()==note->toImage()){
            noteIcon = new QLabel(this);
            noteIcon->setObjectName(QStringLiteral("A note"));
            noteIcon->setPixmap(pixmap);
            noteIcon->move(event->pos() - offset);
            noteIcon->show();
            noteIcon->setAttribute(Qt::WA_DeleteOnClose);
            emit dropNew("A note");
        }
        else if(pixmap.toImage()==trophy->toImage()){
            trophyIcon = new QLabel(this);
            trophyIcon->setObjectName(QStringLiteral("A trophy"));
            trophyIcon->setPixmap(pixmap);
            trophyIcon->move(event->pos() - offset);
            trophyIcon->show();
            trophyIcon->setAttribute(Qt::WA_DeleteOnClose);
            emit dropNew("A trophy");
        }
        key->~QPixmap();
        doorkey->~QPixmap();
        note->~QPixmap();
        trophy->~QPixmap();
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

//! [1]
void Stage::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;
    QPixmap pixmap = *child->pixmap();
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos());
//! [1]
//! [2]
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);
//! [2]
//! [3]
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());
//! [3]
    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();
    child->setPixmap(tempPixmap);
    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    } else {
        child->show();
        child->setPixmap(pixmap);
    }
}


