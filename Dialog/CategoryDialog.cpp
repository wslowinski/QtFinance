#include "CategoryDialog.h"
#include "ui_CategoryDialog.h"

#include "Class/Category.h"

CategoryDialog::CategoryDialog(Category& category, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CategoryDialog),
    category_{category}
{
    ui->setupUi(this);

    connect(ui->btnBox, &QDialogButtonBox::accepted, this, &CategoryDialog::accept);
    connect(ui->btnBox, &QDialogButtonBox::rejected, this, &CategoryDialog::reject);
}

CategoryDialog::~CategoryDialog()
{
    delete ui;
}

void CategoryDialog::accept()
{
    category_ = Category{ui->edtName->text()};

    QDialog::accept();
}

void CategoryDialog::reject()
{
    QDialog::reject();
}
