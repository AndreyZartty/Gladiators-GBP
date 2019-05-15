/**
  * @file thread.h
  * @version 1.0
  * @date 15/05/2019
  * @authors Edgar Gonzales, Ruben Salas, Andrey Sanchez, Jose Solano
  * @title Hilo
  */


#ifndef THREAD_H
#define THREAD_H

#include <QThread>

class Thread : public QThread
{
    Q_OBJECT
public:

    /**
     * @brief Thread Setea el hilo en la ventana principal
     * @param parent Ventana principal
     */
    explicit Thread(QObject *parent = 0);

    /**
     * @brief getF Devuelve si el hilo termino
     * @return _finish Boolean de finalizacion
     */
    bool getF();

    /**
     * @brief setF Setea el Boolean de finalizacion
     * @param finish Boolean a setear
     */
    void setF(bool finish);
signals:
    void boolFinish(bool);
protected:
    void run();
private:
    bool _finish;
};

#endif // THREAD_H
