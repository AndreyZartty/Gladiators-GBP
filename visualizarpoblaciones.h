#ifndef VISUALIZARPOBLACIONES_H
#define VISUALIZARPOBLACIONES_H

#include <QWidget>

namespace Ui {
class VisualizarPoblaciones;
}

class VisualizarPoblaciones : public QWidget
{
    Q_OBJECT

public:
    explicit VisualizarPoblaciones(QWidget *parent = 0);
    ~VisualizarPoblaciones();

    bool botonC();
    bool botonV();

private slots:
    void on_botonContinuar_clicked();

    void on_botonMostrar_clicked();

private:
    Ui::VisualizarPoblaciones *ui;

    bool BC;
    bool BV;
};

#endif // VISUALIZARPOBLACIONES_H
