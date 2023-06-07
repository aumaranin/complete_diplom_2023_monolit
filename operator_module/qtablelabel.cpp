#include "qtablelabel.h"

QTableLabel::QTableLabel()
{

}

void QTableLabel::mouseDoubleClickEvent(QMouseEvent *e)
{
    emit camSelected(idConf);
}
