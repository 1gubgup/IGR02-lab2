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

void Shape::setPosition(const QPoint& s, const QPoint& e){
    startPoint = s;
    endPoint = e;
}

QPoint Shape::getStartPosition() const{
    return startPoint;
}

QPoint Shape::getEndPosition() const{
    return endPoint;
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

void Shape::setShapeType(ShapeType newShapeType, const QPoint& startPoint, const QPoint& endPoint) {
    if (newShapeType == ShapeType::LineShape) {
        *this = Line(startPoint, endPoint);
    } else if (newShapeType == ShapeType::RectangleShape) {
        *this = Rectangle(startPoint, endPoint);
    } else if (newShapeType == ShapeType::EllipseShape) {
        *this = Ellipse(startPoint, endPoint);
    }
    shapeType = newShapeType;
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
