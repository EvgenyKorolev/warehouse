#ifndef YES_NO_H
#define YES_NO_H
#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QIcon>
#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>
// Виджет с вопросом "да или нет" :)
class yes_no : public QDialog
{
    Q_OBJECT
public:
    yes_no(QString arg, QWidget* parent = nullptr);
};

#endif // YES_NO_H
