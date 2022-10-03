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
    explicit PieChartWidget(QWidget *parent = nullptr);
    ~PieChartWidget();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::PieChartWidget *ui;
};

#endif
