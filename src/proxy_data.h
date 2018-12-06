#ifndef PROXY_DATA_H
#define PROXY_DATA_H
#include "persisted_object.h"
#include "settings.h"
#include <memory>
#include <QVector>
#include <QMutex>

class proxy_data
{
public:
    static proxy_data& getInstance(){
        static proxy_data _instance;
        return _instance;
    }
    int size() const;
    int count() const;
    std::shared_ptr<persisted_object> at(std::size_t arg) const;
    void append(std::shared_ptr<persisted_object> arg);
    void insert(std::shared_ptr<persisted_object> arg);
    void insert(std::size_t row, std::shared_ptr<persisted_object> arg);
    bool del(std::shared_ptr<persisted_object> arg);
    bool del(const QString& un);
private:
    proxy_data();
    ~proxy_data() = default;
    QVector<std::shared_ptr<persisted_object>> data;
    QMutex* data_lock{new QMutex()};
};

#endif // PROXY_DATA_H
