#ifndef QTABLELABEL_H
#define QTABLELABEL_H

#include <QLabel>

class QTableLabel : public QLabel
{
    Q_OBJECT
public:
    QTableLabel();
    int idConf;
    virtual void mouseDoubleClickEvent( QMouseEvent * e );
signals:
    void camSelected(int id);
};

#endif // QTABLELABEL_H
