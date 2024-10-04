#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Canvas.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createCanvas();
    void initializeButton();

private:
    Ui::MainWindow* ui;   // UI object for managing the interface
    Canvas* canvas;       // Canvas object for drawing shapes

    void enterEditMode(const QColor& color, int thickness, Qt::PenStyle style, Shape::ShapeType shape);
    void exitEditMode();

    void openFile();
    void saveFile();
    void closeEvent(QCloseEvent* event) override;
};

#endif // MAINWINDOW_H

