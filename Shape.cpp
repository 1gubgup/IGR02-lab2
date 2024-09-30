#include "Shape.h"


void Shape::draw(QPainter& painter){
    QPen pen(color, thickness, style);
    painter.setPen(pen);
    painter.drawPath(path);
}

bool Shape::contains(const QPointF& point) const{
    QPainterPathStroker stroker;
    stroker.setWidth(thickness);   // set width
    return stroker.createStroke(path).contains(point);
}

void Shape::moveBy(const QPointF& offset){
    QTransform transform;
    transform.translate(offset.x(),offset.y());
    path = transform.map(path);
}

void Shape::resizeBy(float scaleFactor, const QPointF& center){
    QTransform transform;
    transform.translate(center.x(),center.y());
    transform.scale(scaleFactor,scaleFactor);
    transform.translate(-center.x(),-center.y());
    path = transform.map(path);
}

void Shape::setAttributes(const QColor& c, int t, const Qt::PenStyle s, const ShapeType p){
    color = c;
    thickness = t;
    style = s;
    shapeType = p;
}


QColor Shape::getColor() const {
    return color;
}

void Shape::setColor(const QColor& c) {
    color = c;
}

int Shape::getThickness() const {
    return thickness;
}

void Shape::setThickness(int t) {
    thickness = t;
}

Qt::PenStyle Shape::getStyle() const {
    return style;
}

void Shape::setStyle(Qt::PenStyle s) {
    style = s;
}

Shape::ShapeType Shape::getShapeType() const {
    return shapeType;
}


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
