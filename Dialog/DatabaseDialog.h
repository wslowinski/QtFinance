#ifndef DATABASEDIALOG_H
#define DATABASEDIALOG_H

#include <QDialog>

namespace Ui {
class DatabaseDialog;
}

class DatabaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DatabaseDialog(QString path = "/home/vladyslav/Database/budget.db", QWidget *parent = nullptr);
    ~DatabaseDialog();

private slots:
    void accept();
    void reject();
    void open();

private:
    Ui::DatabaseDialog *ui;
    QString m_path;
};

#endif
