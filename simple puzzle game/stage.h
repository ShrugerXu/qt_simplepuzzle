#ifndef STAGE_H
#define STAGE_H
#include <QLabel>
#include <QPixmap>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class Stage : public QLabel
{
Q_OBJECT
public:
    Stage(QWidget *parent = 0);
    void form();
     QLabel *keyIcon;
     QLabel *doorkeyIcon;
     QLabel *noteIcon;
     QLabel *trophyIcon;
     //QPixmap *test;
    // QLabel *newIcon;
protected:
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
public:
    void initialize();
    void showItem(QString itemName);
signals:
    dropNew(QString);
};



#endif // STAGE_H
