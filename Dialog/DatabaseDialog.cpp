#include "DatabaseDialog.h"
#include "ui_DatabaseDialog.h"

DatabaseDialog::DatabaseDialog(QString path, QWidget *parent):
    QDialog(parent),
    ui(new Ui::DatabaseDialog),
    m_path(path)
{
    ui->setupUi(this);
    ui->edtPath->setText(m_path);
}

DatabaseDialog::~DatabaseDialog()
{
    delete ui;
}    

void DatabaseDialog::accept()
{
   m_path = ui->edtPath->text();
   QDialog::accept();
}

void DatabaseDialog::reject()
{
    QDialog::reject();
}
