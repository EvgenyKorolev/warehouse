#ifndef PROXY_DATA_H
#define PROXY_DATA_H
#include "persisted_object.h"
#include "settings.h"
#include <memory>
#include <QVector>

class proxy_data
{
public:
    proxy_data();
    ~proxy_data() = default;

    int size() const;
    int count() const;
    std::shared_ptr<persisted_object> at(std::size_t arg) const;
    void append(std::shared_ptr<persisted_object> arg);
    void insert(std::shared_ptr<persisted_object> arg);
    void insert(std::size_t row, std::shared_ptr<persisted_object> arg);
    void del(std::shared_ptr<persisted_object> arg);
private:
    QVector<std::shared_ptr<persisted_object>> data;
};

#endif // PROXY_DATA_H
