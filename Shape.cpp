#include "Shape.h"


// draw the shape using its color, thickness, and style
void Shape::draw(QPainter& painter){
    QPen pen(color, thickness, style);
    painter.setPen(pen);
    painter.drawPath(path);
}

// check if a point is within the shape's outline
bool Shape::contains(const QPointF& point) const{
    QPainterPathStroker stroker;
    stroker.setWidth(thickness);   // set width
    return stroker.createStroke(path).contains(point);
}

// move the shape by a given offset
void Shape::moveBy(const QPointF& offset){
    QTransform transform;
    transform.translate(offset.x(),offset.y());
    path = transform.map(path);
}

// resize the shape by a scale factor, using a center point
void Shape::resizeBy(float scaleFactor, const QPointF& center){
    QTransform transform;
    transform.translate(center.x(),center.y());
    transform.scale(scaleFactor,scaleFactor);
    transform.translate(-center.x(),-center.y());
    path = transform.map(path);
}


// Set shape attributes: color, thickness, style, and type
void Shape::setAttributes(const QColor& c, int t, const Qt::PenStyle s, const ShapeType p){
    color = c;
    thickness = t;
    style = s;
    shapeType = p;
}


// set and get methods for shape attributes
void Shape::setPath(const QPainterPath& p){path = p;}

void Shape::setColor(const QColor& c){color = c;}

void Shape::setThickness(int t){thickness = t;}

void Shape::setStyle(Qt::PenStyle s){style = s;}

QPainterPath Shape::getPath(){return path;}

QColor Shape::getColor(){return color;}

int Shape::getThickness(){return thickness;}

Qt::PenStyle Shape::getStyle(){return style;}

Shape::ShapeType Shape::getShape(){return shapeType;}


// constructors for Line, Rectangle, and Ellipse shapes
Line::Line(const QPoint& start, const QPoint& end){
    path.moveTo(start);
    path.lineTo(end);
}

Rectangle::Rectangle(const QPoint& start, const QPoint& end){
    path.addRect(QRect(start,end));
}

Ellipse::Ellipse(const QPoint& start, const QPoint& end){
    path.addEllipse(QRect(start,end));
}
