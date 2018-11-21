#ifndef EDITOR_HOLLYDAYS_H
#define EDITOR_HOLLYDAYS_H
#include <QDialog>
#include <QObject>
#include <QComboBox>

class editor_hollydays : public QDialog
{
public:
    editor_hollydays(QWidget* par = nullptr);

    QComboBox* years;
};

#endif // EDITOR_HOLLYDAYS_H
