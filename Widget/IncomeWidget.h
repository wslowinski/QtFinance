#ifndef INCOMEWIDGET_H
#define INCOMEWIDGET_H

#include <QWidget>

namespace Ui {
class IncomeWidget;
}

class IncomeModel;

class IncomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IncomeWidget(QWidget *parent = nullptr);
    ~IncomeWidget();

    void setModel(IncomeModel* model);
    int getCurrentID();

private slots:
    void add();
    void edit();
    void remove();
    void setting();
    void filter(int index);

private:
    Ui::IncomeWidget *ui;
    IncomeModel* m_incomeModel;

    void init();
};

#endif
