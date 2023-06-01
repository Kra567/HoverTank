#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>
//#include "polynomial.h"
#include "polynomcurve.h"
#include "body.h"
#include "gametimer.h"
#include "bodycollider.h"
#include "curvecollider.h"
#include "damagecollider.h"
#include "gameworld.h"
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    Ui::MainWindow *ui;
    GameWorld world = GameWorld();
private slots:
    void first_slot();
    void second_slot();
};
#endif // MAINWINDOW_H
