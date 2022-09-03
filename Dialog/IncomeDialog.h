#ifndef INCOMEDIALOG_H
#define INCOMEDIALOG_H

#include "Class/Income.h"

#include <QDialog>

namespace Ui {
class IncomeDialog;
}

class IncomeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IncomeDialog(Income& income, QWidget *parent = nullptr);
    ~IncomeDialog();

private slots:
    void accept();
    void reject();

private:
    Ui::IncomeDialog *ui;
    Income& m_income;

    void init();
};

#endif
