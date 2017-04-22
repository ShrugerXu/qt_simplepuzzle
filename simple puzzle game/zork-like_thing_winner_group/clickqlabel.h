#ifndef CLICKQLABLE
#define CLICKQLABLE
#include <QLabel>
#include <QWidget>
/**
  *QLable with click event
  * */
 class ClickQLabel:public QLabel{
     Q_OBJECT
public:
     explicit ClickQLabel(QWidget *parent =0);
     ClickQLabel(const QString &text, QWidget *parent=0);

signals:
     void clicked();
protected:
     void mouseReleaseEvent(QMouseEvent *);
     void enterEvent(QEvent *);
     void leaveEvent(QEvent *);
public slots:
};
#endif // CLICKQLABLE

