#ifndef INCOMEDIALOG_H
#define INCOMEDIALOG_H

#include "Class/Income.h"
#include "Class/Currencies.h"

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
    void setting();
    void download();
    void filter(int index);

private:
    Ui::IncomeDialog *ui;
    Income& m_income;
    QStringList m_list;
    Currencies::Rates m_rates;

    void init();
};

#endif
