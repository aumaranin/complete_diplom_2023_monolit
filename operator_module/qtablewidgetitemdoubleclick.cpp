#include "qtablewidgetitemdoubleclick.h"

QTableWidgetItemDoubleClick::QTableWidgetItemDoubleClick()
{

}

void QTableWidgetItemDoubleClick::mouseDoubleClickEvent(QMouseEvent *e)
{
    emit camSelected(idConf);
}
