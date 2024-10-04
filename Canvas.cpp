#include "Canvas.h"

#include <QPainter>
#include <QDebug>


Canvas::Canvas(QWidget* parent)
    : QWidget(parent), currentColor(Qt::red), currentThickness(5), currentStyle(Qt::SolidLine), currentShape(Shape::LineShape)
{
    // set minimum  window size
    setMinimumSize(600,400);
}

Canvas::~Canvas(){
    // free allocated memory and clear the container
    qDeleteAll(shapes);
    shapes.clear();
}


// set current or selected shape attributes
void Canvas::setColor(const QColor& color) {
    currentColor = color;
    if (selectedShape){
        selectedShape->setColor(color);
        update();
    }
}

void Canvas::setThickness(int thickness) {
    currentThickness = thickness;
    if (selectedShape){
        selectedShape->setThickness(thickness);
        update();
    }
}

void Canvas::setStyle(Qt::PenStyle style) {
    currentStyle = style;
    if (selectedShape){
        selectedShape->setStyle(style);
        update();
    }
}

void Canvas::setShape(Shape::ShapeType shape) {
    currentShape = shape;
}


// manage the shapes container
QList<Shape*> Canvas::getShapes(){
    return shapes;
}

void Canvas::addShape(Shape* shape) {
    shapes.append(shape);
}


// paint event
void Canvas::paintEvent(QPaintEvent* e){

    // standard behavior(draw the background)
    QWidget::paintEvent(e);

    // creat a painter for this widget
    QPainter painter(this);
    for (Shape* shape : shapes) {
        shape->draw(painter);
    }

    // for shape being drawn
    if (isDrawing == true) {
        QPen pen(currentColor, currentThickness, currentStyle);
        painter.setPen(pen);

        switch(currentShape){
            case Shape::LineShape:
                painter.drawLine(startPoint,endPoint);
                break;
            case Shape::RectangleShape:
                painter.drawRect(QRect(startPoint,endPoint));
                break;
            case Shape::EllipseShape:
                painter.drawEllipse(QRect(startPoint,endPoint));
                break;
        }
    }
}


// mouse event
void Canvas::mousePressEvent(QMouseEvent* event) {

    // left-click: drawing mode (only when no shape is selected)
    if (event->button() == Qt::LeftButton && !selectedShape) {
        emit noShapeSelected();
        startPoint = event->pos();
        isDrawing = true;
    }

    // right-click: edit mode
    else if (event->button() == Qt::RightButton) {
        bool isContain = false;

        // check if the click position contains any shape
        for (Shape* shape : shapes) {
            if (shape->contains(event->pos())) {
                selectedShape = shape;   // select the shape
                lastMousePos = event->pos();
                isDragging = false;
                isContain = true;

                // update toolbar status
                emit shapeSelected(shape->getColor(), shape->getThickness(), shape->getStyle(), shape->getShape());
                qDebug() << "Shape selected : Edit mode";
                break;
            }
        }

        // if no shape is selected, deselect and enter drawing mode
        if (!isContain) {
            setPenAttributes();
            emit noShapeSelected();
            selectedShape = nullptr;
            qDebug() << "No shape selected : drawing mode";
        }
    }
}

void Canvas::mouseMoveEvent(QMouseEvent* event) {

    // draw the shape in drawing mode
    if (isDrawing && !selectedShape) {
        endPoint = event->pos();
        update();
    }

    // drag the shape in edit mode
    else if (selectedShape && event->buttons() & Qt::RightButton) {
        QPointF offset = event->pos() - lastMousePos;
        if (offset.manhattanLength() > 5) {
            selectedShape->moveBy(offset);
            lastMousePos = event->pos();
            isDragging = true;
            update();
        }
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent* event) {

    // complite drawing
    if (isDrawing && event->button() == Qt::LeftButton) {
        endPoint = event->pos();
        isDrawing = false;
        addShapeData();
        update();
    }

    // complite dragging
    else if (isDragging && event->button() == Qt::RightButton) {
        isDragging = false;
    }
}

void Canvas::wheelEvent(QWheelEvent* event) {

    // resize the shape in edit mode
    if (selectedShape) {
        int delta = event->angleDelta().y();
        float scaleFactor = (delta > 0) ? 1.1 : 0.9;
        selectedShape->resizeBy(scaleFactor, lastMousePos);
        update();
    }
}


// add new shape data in shapes container
void Canvas::addShapeData(){
    Shape* shape = nullptr;
    if (currentShape == Shape::LineShape) {
        shape = new Line(startPoint, endPoint);
    } else if (currentShape == Shape::RectangleShape) {
        shape = new Rectangle(startPoint, endPoint);
    } else if (currentShape == Shape::EllipseShape) {
        shape = new Ellipse(startPoint, endPoint);
    }
    if (shape) {
        shape->setAttributes(currentColor, currentThickness, currentStyle, currentShape);
        addShape(shape);
    }
}


// update pen attributes
void Canvas::setPenAttributes(){
    if (selectedShape) {
        currentColor = selectedShape->getColor();
        currentThickness = selectedShape->getThickness();
        currentStyle = selectedShape->getStyle();
        currentShape = selectedShape->getShape();
    }
}
