#include "PieChartWidget.h"
#include "ui_PieChartWidget.h"

#include <QPainter>

PieChartWidget::PieChartWidget(QWidget *parent, std::vector<double> percentages) :
    QWidget(parent),
    ui(new Ui::PieChartWidget),
    m_percentages(percentages)
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
    painter.setPen(Qt::black);
    painter.setFont(QFont("Times", 14));
    QRectF size = QRectF(100, 100, 300, 300);
    m_percentages = {0, 33.5, 7, 9, 13, 11.5, 20, 0, 3, 2, 1};

    std::vector<QString> categoriesName = {"Beauty", "Bills", "Drugstore", "Fashion", "Free Time",
                      "Groceries", "Health", "Home appliances", "Restaurants",
                      "Transport", "No Category"};

    std::vector<Qt::GlobalColor> colors = {Qt::black, Qt::blue, Qt::cyan, Qt::green, Qt::magenta, Qt::red,
                                          Qt::yellow, Qt::white, Qt::darkYellow, Qt::lightGray, Qt::darkCyan};

    const int rate = 27; int y = 100; double sum = 0;
    for (unsigned int i = 0; i < m_percentages.size(); ++i)
    {
        painter.setBrush(colors.at(i));
        painter.drawPie(size, sum, getPie(m_percentages.at(i)));
        sum += getPie(m_percentages.at(i));
        painter.drawEllipse(420, y - 10, 10, 10);
        painter.drawText(440, y, categoriesName.at(i));
        painter.drawText(590, y, QString::number(m_percentages.at(i)) + " %");
        y += rate;
    }
}

double PieChartWidget::getPie(double percentage)
{
    return 16 * percentage * 360 / 100;
}
