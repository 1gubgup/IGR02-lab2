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

    void setColor(const QColor& c);
    void setThickness(int t);
    void setStyle(Qt::PenStyle s);
    void setShape(Shape::ShapeType p);

    QList<Shape*> getShapes();
    void addShape(Shape* shape);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

signals:
    void shapeSelected(const QColor& color, int thickness, Qt::PenStyle style, Shape::ShapeType shapeType);
    void noShapeSelected();

private:
    QColor currentColor;
    int currentThickness;
    Qt::PenStyle currentStyle;
    Shape::ShapeType currentShape;

    QPoint startPoint;
    QPoint endPoint;
    QPointF lastMousePos;
    bool isDrawing = false;
    bool isDragging = false;

    QList<Shape*> shapes;
    Shape* selectedShape = nullptr;

    void addShapeData();
    void setPenAttributes();
};

#endif // CANVAS_H
