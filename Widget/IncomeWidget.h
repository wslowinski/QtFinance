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
    void setDesign();

private slots:
    void add();
    void edit();
    void remove();

private:
    Ui::IncomeWidget *ui;

    IncomeModel* m_incomeModel;
};

#endif
