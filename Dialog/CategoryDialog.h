#ifndef CATEGORYDIALOG_H
#define CATEGORYDIALOG_H

#include <QDialog>

class Category;

namespace Ui {
class CategoryDialog;
}

class CategoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CategoryDialog(Category& category, QWidget *parent = nullptr);
    ~CategoryDialog();

private slots:
    void accept();
    void reject();


private:
    Ui::CategoryDialog *ui;

    Category& category_;
};

#endif // CATEGORYDIALOG_H
