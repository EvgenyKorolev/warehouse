#ifndef PROXY_DATA_H
#define PROXY_DATA_H
#include "persisted_object.h"
#include <memory>

class proxy_data
{
public:
    proxy_data();
    ~proxy_data();

    int size() const;
    int count() const;
    std::unique_ptr<persisted_object> at(std::size_t arg) const;
    void append(std::shared_ptr<persisted_object> arg);
    void insert(size_t row, std::shared_ptr<persisted_object> arg);
    void del(std::shared_ptr<persisted_object> arg);
};

#endif // PROXY_DATA_H
