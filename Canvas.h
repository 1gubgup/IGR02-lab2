#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QAbstractButton>
#include "Shape.h"

class Canvas : public QWidget{
    Q_OBJECT

public:
    explicit Canvas(QWidget* parent = nullptr);
    ~Canvas();

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void closeEvent(QCloseEvent* event) override;

private slots:
    void setColor(QAbstractButton* button);
    void setThickness(QAbstractButton* button);
    void setStyle(QAbstractButton* button);
    void setShape(QAbstractButton* button);

private:
    // button group
    QButtonGroup* colorGroup;
    QButtonGroup* thicknessGroup;
    QButtonGroup* styleGroup;
    QButtonGroup* shapeGroup;

    QColor currentColor;
    int currentThickness;
    Qt::PenStyle currentStyle;
    Shape::ShapeType currentShape;

    QPoint startPoint;
    QPoint endPoint;
    QPointF lastMousePos;
    bool isDrawing;
    bool isDragging = false;
    QList<Shape*> shapes;
    Shape* selectedShape = nullptr;

    void addShapeData();
    void updateToolbarButtons();
    void updatePenProperties();
};

#endif // CANVAS_H
