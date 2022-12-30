#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>

class Category final
{
public:
    Category();
    Category(const QString& name);
    Category(int id, const QString& name);

    void setId(const int id);
    int getId() const;
    const QString& getName() const;

private:
    int id_;
    QString name_;
};

#endif // CATEGORY_H
