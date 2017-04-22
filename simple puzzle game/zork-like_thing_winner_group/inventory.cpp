#include "inventory.h"
#include <QtWidgets>
Inventory::Inventory(QWidget *parent): QWidget(parent)
{
 setAcceptDrops(true);
trig=true;
}

void Inventory::clear()
{
    pieceLocations.clear();
    piecePixmaps.clear();
    pieceRects.clear();
    highlightedRect = QRect();
    inPlace = 0;
    update();
}

void Inventory::trigger(){
    trig= !trig;
}

bool Inventory::getTrigger(){
    return trig;
}

void Inventory::setTrigger(){
    trig=true;
}

void Inventory::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")){
        trigger();
        event->accept();
    }
    else
        event->ignore();
}

void Inventory::dragLeaveEvent(QDragLeaveEvent *event)
{
    QRect updateRect = highlightedRect;
    highlightedRect = QRect();
    update(updateRect);
    trigger();
    event->accept();
}

void Inventory::dragMoveEvent(QDragMoveEvent *event)
{
    QRect updateRect = highlightedRect.united(targetSquare(event->pos()));
    if (event->mimeData()->hasFormat("application/x-dnditemdata")
        && findPiece(targetSquare(event->pos())) == -1) {
        highlightedRect = targetSquare(event->pos());
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        highlightedRect = QRect();
        event->ignore();
    }
    update(updateRect);
}

void Inventory::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")
        && findPiece(targetSquare(event->pos())) == -1) {
        QByteArray pieceData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream stream(&pieceData, QIODevice::ReadOnly);
        QRect square = targetSquare(event->pos());
        QPixmap pixmap;
        QPoint location;
        stream >> pixmap >> location;
        if(getTrigger()==true){
            setTrigger();
        }
        else{
            emit newLabel(pixmap);
            setTrigger();
        }
        pieceLocations.append(location);
        piecePixmaps.append(pixmap);
        pieceRects.append(square);
        highlightedRect = QRect();
        update(square);
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else {
        highlightedRect = QRect();
        event->ignore();
    }
}

int Inventory::findPiece(const QRect &pieceRect) const
{
    for (int i = 0; i < pieceRects.size(); ++i) {
        if (pieceRect == pieceRects[i])
            return i;
    }
    return -1;
}

void Inventory::mousePressEvent(QMouseEvent *event)
{
    QRect square = targetSquare(event->pos());
    int found = findPiece(square);
    if (found == -1)
        return;
    QPoint location = pieceLocations[found];
    QPixmap pixmap = piecePixmaps[found];
    pieceLocations.removeAt(found);
    piecePixmaps.removeAt(found);
    pieceRects.removeAt(found);
    if (location == QPoint(square.x()/pieceSize(), square.y()/pieceSize()))
        inPlace--;
    update(square);
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << location;
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(event->pos() - square.topLeft());
    drag->setPixmap(pixmap);
    if (drag->start(Qt::MoveAction) == 0) {
        pieceLocations.insert(found, location);
        piecePixmaps.insert(found, pixmap);
        pieceRects.insert(found, square);
        update(targetSquare(event->pos()));
        if (location == QPoint(square.x()/pieceSize(), square.y()/pieceSize()))
            inPlace++;
    }
}

void Inventory::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.fillRect(event->rect(), Qt::white);
    if (highlightedRect.isValid()) {
        painter.setBrush(QColor("#ffcccc"));
        painter.setPen(Qt::NoPen);
        painter.drawRect(highlightedRect.adjusted(0, 0, -1, -1));
    }
    for (int i = 0; i < pieceRects.size(); ++i) {
        painter.drawPixmap(pieceRects[i], piecePixmaps[i]);
    }
    painter.end();
}

const QRect Inventory::targetSquare(const QPoint &position) const
{
    return QRect(position.x()/pieceSize() * pieceSize(), position.y()/pieceSize() * pieceSize(), pieceSize(), pieceSize());
}

int Inventory::pieceSize() const
{
   // return m_ImageSize / 5;
    return 81;
}

int Inventory::imageSize() const
{
   // return m_ImageSize;
    return 729;
}
