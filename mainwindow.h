#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include "tablero.h"
#include <stdio.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    static QGraphicsScene* partida;

    ~MainWindow();



private slots:
    void on_Inicio_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
