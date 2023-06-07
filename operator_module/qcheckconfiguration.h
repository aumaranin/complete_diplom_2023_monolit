#ifndef QCHECKCONFIGURATION_H
#define QCHECKCONFIGURATION_H

#include <QCheckBox>

class QCheckConfiguration : public QCheckBox
{
public:
    int idConf;
    virtual void mouseDoubleClickEvent( QMouseEvent * e );
    QCheckConfiguration();

signals:

};

#endif // QCHECKCONFIGURATION_H
