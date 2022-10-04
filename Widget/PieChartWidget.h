#ifndef PIECHARTWIDGET_H
#define PIECHARTWIDGET_H

#include <QWidget>

namespace Ui {
class PieChartWidget;
}

class PieChartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PieChartWidget(QWidget *parent = nullptr, std::vector<double> percentages = {});
    ~PieChartWidget();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::PieChartWidget *ui;
    std::vector<double> m_percentages;
    double getPie(double percentage);
};

#endif
