#include "PieChartWidget.h"
#include "ui_PieChartWidget.h"

#include <QPainter>

PieChartWidget::PieChartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PieChartWidget)
{
    ui->setupUi(this);
}

PieChartWidget::~PieChartWidget()
{
    delete ui;
}

void PieChartWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRectF size = QRectF(100, 100, 300, 300);
    painter.setBrush(Qt::red);
    painter.drawPie(size, 0, 90*16);
    painter.setBrush(Qt::blue);
    painter.drawPie(size, 90*16, 160*16);
    painter.setBrush(Qt::green);
    painter.drawPie(size, 160*16, 270*16);
}
