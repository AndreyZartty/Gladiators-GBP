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

    void modificarLabel(int i, QString label);

private:
    Ui::NextGen *ui;
};

#endif // NEXTGEN_H
