#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <stdio.h>

#include "nextgen.h"

#include "tablero.h"

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

    NextGen* nextG;

};

#endif // MAINWINDOW_H
