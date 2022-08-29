#include "Style.h"

void Style::setTableViewStyle(QTableView* tableVIew)
{
    tableVIew->setSelectionMode(QAbstractItemView::SingleSelection);
    tableVIew->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableVIew->setTextElideMode(Qt::ElideRight);
    QHeaderView* headerView = tableVIew->horizontalHeader();
    headerView->setVisible(true);
    tableVIew->resizeColumnsToContents();
    tableVIew->setCurrentIndex(tableVIew->model()->index(0, 0));
    tableVIew->show();
}
