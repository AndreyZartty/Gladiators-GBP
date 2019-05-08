#ifndef NEXTGEN_H
#define NEXTGEN_H

#include <QDialog>

namespace Ui {
class NextGen;
}

class NextGen : public QDialog
{
    Q_OBJECT

public:
    explicit NextGen(QWidget *parent = 0);
    ~NextGen();

private:
    Ui::NextGen *ui;
};

#endif // NEXTGEN_H
