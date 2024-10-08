#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QPainterPath>


class Shape {
public:
    virtual ~Shape(){}

    void draw(QPainter &painter);
    bool contains(const QPointF& point) const;
    void moveBy(const QPointF& offset);
    void resizeBy(float scaleFactor, const QPointF& center);

    enum ShapeType { LineShape, RectangleShape, EllipseShape };
    void setAttributes(const QColor& c, int t, const Qt::PenStyle s, const ShapeType p);

    QColor getColor() const;
    void setColor(const QColor& c);
    int getThickness() const;
    void setThickness(int t);
    Qt::PenStyle getStyle() const;
    void setStyle(Qt::PenStyle s);
    ShapeType getShapeType() const;

protected:
    QPainterPath path;
    QColor color;
    int thickness;
    Qt::PenStyle style;
    ShapeType shapeType;
};


class Line : public Shape {
public:
    Line(const QPoint& start, const QPoint& end);
};


class Rectangle : public Shape {
public:
    Rectangle(const QPoint& start, const QPoint& end);
};


class Ellipse : public Shape {
public:
    Ellipse(const QPoint& start, const QPoint& end);
};


#endif // SHAPE_H
