#ifndef INVENTORY_H
#define INVENTORY_H
#include <QList>
#include <QPixmap>
#include <QPoint>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
class QMouseEvent;
QT_END_NAMESPACE

class Inventory : public QWidget
{
   Q_OBJECT


public:
    explicit Inventory(QWidget *parent = 0);
    void clear();

    int pieceSize() const;
    int imageSize() const;
    void trigger();
    bool getTrigger();
    void setTrigger();
protected:
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
private:
    int findPiece(const QRect &pieceRect) const;
    const QRect targetSquare(const QPoint &position) const;
    bool trig;
    QList<QPixmap> piecePixmaps;
    QList<QRect> pieceRects;
    QList<QPoint> pieceLocations;
    QRect highlightedRect;
    int inPlace;
    int m_ImageSize;
signals:
    newLabel(QPixmap);
};

#endif // INVENTORY_H
