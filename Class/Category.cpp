#include "Category.h"

Category::Category() : id_{-1}
{

}

Category::Category(const QString& name) : id_{-1}, name_{name}
{

}

Category::Category(int id, const QString& name) : id_{id}, name_{name}
{

}

void Category::setId(const int id)
{
    id_ = id;
}

int Category::getId() const
{
    return id_;
}

const QString &Category::getName() const
{
    return name_;
}
