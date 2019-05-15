#ifndef NEXTGEN2_H
#define NEXTGEN2_H

#include <QWidget>

namespace Ui {
class NextGen2;
}

class NextGen2 : public QWidget
{
    Q_OBJECT

public:
    explicit NextGen2(QWidget *parent = 0);
    ~NextGen2();
    void modificarLabel(int i, QString label);

private:
    Ui::NextGen2 *ui;
};

#endif // NEXTGEN2_H
