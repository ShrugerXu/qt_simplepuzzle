#include "clickqlabel.h"
#include <QMouseEvent>
#include <QPalette>

ClickQLabel::ClickQLabel(QWidget *parent):
    QLabel(parent)
{
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::darkGreen);
    setPalette(pa);
}

ClickQLabel::ClickQLabel(const QString &text,QWidget *parent):
    QLabel(parent)
{
    setText(text);
}

void ClickQLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
        emit clicked();
}

void ClickQLabel::enterEvent(QEvent *){
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::blue);
    setPalette(pa);
}

void ClickQLabel::leaveEvent(QEvent *){
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::darkGreen);
    setPalette(pa);
}
