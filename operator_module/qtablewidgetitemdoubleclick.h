#ifndef QTABLEWIDGETITEMDOUBLECLICK_H
#define QTABLEWIDGETITEMDOUBLECLICK_H

#include <QTableWidgetItem>

class QTableWidgetItemDoubleClick : public QTableWidgetItem
{
    Q_OBJECT
public:
    QTableWidgetItemDoubleClick();
    int idConf;
    virtual void mouseDoubleClickEvent( QMouseEvent * e );
signals:
    void camSelected(int id);
};

#endif // QTABLEWIDGETITEMDOUBLECLICK_H
