#ifndef THREAD_H
#define THREAD_H

#include <QThread>

class Thread : public QThread
{
    Q_OBJECT
public:
    explicit Thread(QObject *parent = 0);

    bool getF();
    void setF(bool finish);
signals:
    void boolFinish(bool);
protected:
    void run();
private:
    bool _finish;
};

#endif // THREAD_H
