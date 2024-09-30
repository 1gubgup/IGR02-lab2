#include "Canvas.h"

#include <QPainter>
#include <QToolBar>
#include <QToolButton>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDebug>


Canvas::Canvas(QWidget* parent)
    : QWidget(parent), currentColor(Qt::red), currentThickness(3), currentStyle(Qt::SolidLine), currentShape(Shape::LineShape)
{
    // set minimum  window size
    setMinimumSize(600,400);

    // create layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    // ------------------color group------------------
    QToolBar* colorToolBar = new QToolBar("Color", this);
    colorToolBar->setWindowTitle("Color");
    colorToolBar->setOrientation(Qt::Vertical);
    colorGroup = new QButtonGroup(this);

    // create color button
    QToolButton* redButton = new QToolButton(colorToolBar);
    redButton->setText("Red");
    redButton->setCheckable(true);
    redButton->setChecked(true);

    QToolButton* blueButton = new QToolButton(colorToolBar);
    blueButton->setText("Blue");
    blueButton->setCheckable(true);

    QToolButton* greenButton = new QToolButton(colorToolBar);
    greenButton->setText("Green");
    greenButton->setCheckable(true);

    // add color button
    colorToolBar->addWidget(redButton);
    colorToolBar->addWidget(blueButton);
    colorToolBar->addWidget(greenButton);

    colorGroup->addButton(redButton, 0);
    colorGroup->addButton(blueButton, 1);
    colorGroup->addButton(greenButton, 2);

    // ------------------thickness group------------------
    QToolBar* thicknessToolBar = new QToolBar("Thickness", this);
    thicknessToolBar->setWindowTitle("Thickness");
    thicknessToolBar->setOrientation(Qt::Vertical);
    thicknessGroup = new QButtonGroup(this);

    // create thickness button
    QToolButton* thinButton = new QToolButton(thicknessToolBar);
    thinButton->setText("Thin");
    thinButton->setCheckable(true);
    thinButton->setChecked(true);

    QToolButton* mediumButton = new QToolButton(thicknessToolBar);
    mediumButton->setText("Medium");
    mediumButton->setCheckable(true);

    QToolButton* thickButton = new QToolButton(thicknessToolBar);
    thickButton->setText("Thick");
    thickButton->setCheckable(true);

    // add thickness button
    thicknessToolBar->addWidget(thinButton);
    thicknessToolBar->addWidget(mediumButton);
    thicknessToolBar->addWidget(thickButton);

    thicknessGroup->addButton(thinButton, 0);
    thicknessGroup->addButton(mediumButton, 1);
    thicknessGroup->addButton(thickButton, 2);

    // ------------------style group------------------
    QToolBar* styleToolBar = new QToolBar("Style", this);
    styleToolBar->setWindowTitle("Style");
    styleToolBar->setOrientation(Qt::Vertical);
    styleGroup = new QButtonGroup(this);

    // create style button
    QToolButton* solidButton = new QToolButton(styleToolBar);
    solidButton->setText("Solid");
    solidButton->setCheckable(true);
    solidButton->setChecked(true);

    QToolButton* dashButton = new QToolButton(styleToolBar);
    dashButton->setText("Dash");
    dashButton->setCheckable(true);

    QToolButton* dotButton = new QToolButton(styleToolBar);
    dotButton->setText("Dot");
    dotButton->setCheckable(true);

    // add style button
    styleToolBar->addWidget(solidButton);
    styleToolBar->addWidget(dashButton);
    styleToolBar->addWidget(dotButton);

    styleGroup->addButton(solidButton, 0);
    styleGroup->addButton(dashButton, 1);
    styleGroup->addButton(dotButton, 2);

    // ------------------shape group------------------
    QToolBar* shapeToolBar = new QToolBar("Shape", this);
    shapeToolBar->setWindowTitle("Shape");
    shapeToolBar->setOrientation(Qt::Vertical);
    shapeGroup = new QButtonGroup(this);

    // create shape button
    QToolButton* lineButton = new QToolButton(shapeToolBar);
    lineButton->setText("Line");
    lineButton->setCheckable(true);
    lineButton->setChecked(true);

    QToolButton* rectangleButton = new QToolButton(shapeToolBar);
    rectangleButton->setText("Rectangle");
    rectangleButton->setCheckable(true);

    QToolButton* ellipseButton = new QToolButton(shapeToolBar);
    ellipseButton->setText("Ellipse");
    ellipseButton->setCheckable(true);

    // add shape button
    shapeToolBar->addWidget(lineButton);
    shapeToolBar->addWidget(rectangleButton);
    shapeToolBar->addWidget(ellipseButton);

    shapeGroup->addButton(lineButton, 0);
    shapeGroup->addButton(rectangleButton, 1);
    shapeGroup->addButton(ellipseButton, 2);

    // ------------------end------------------

    // connect signal and slot
    connect(colorGroup, &QButtonGroup::buttonClicked, this, &Canvas::setColor);
    connect(thicknessGroup, &QButtonGroup::buttonClicked, this, &Canvas::setThickness);
    connect(styleGroup, &QButtonGroup::buttonClicked, this, &Canvas::setStyle);
    connect(shapeGroup, &QButtonGroup::buttonClicked, this, &Canvas::setShape);

    // set layout
    layout->addWidget(new QLabel("Color", this));
    layout->addWidget(colorToolBar);

    layout->addWidget(new QLabel("Thickness", this));
    layout->addWidget(thicknessToolBar);

    layout->addWidget(new QLabel("Style", this));
    layout->addWidget(styleToolBar);

    layout->addWidget(new QLabel("Shape", this));
    layout->addWidget(shapeToolBar);
}

Canvas::~Canvas(){
    // free allocated memory
    qDeleteAll(shapes);
}


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


// add shape data
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
        shape->setPosition(startPoint, endPoint);
        shapes.append(shape);
    }
}


// set mouse event
void Canvas::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && !selectedShape) {
        // 左键：绘图模式（只有当没有选中图形时）
        startPoint = event->pos();
        isDrawing = true;
    } else if (event->button() == Qt::RightButton) {
        // 右键：编辑模式
        bool isContain = false;

        // 检查点击位置是否包含某个图形
        for (Shape* shape : shapes) {
            if (shape->contains(event->pos())) {
                selectedShape = shape;  // 选中图形
                lastMousePos = event->pos();
                isDragging = false;
                isContain = true;
                updateToolbarButtons();  // 更新工具栏状态
                qDebug() << "选择图案，进入编辑模式";
                break;
            }
        }

        // 如果没有选中任何图形，则取消选择并进入画笔模式
        if (!isContain) {
            selectedShape = nullptr;
            updatePenProperties();
            qDebug() << "未选择图案，进入画笔模式";
        }
    }
}

void Canvas::mouseMoveEvent(QMouseEvent* event) {
    if (isDrawing && !selectedShape) {
        // 在绘图模式下拖动鼠标
        endPoint = event->pos();
        update();
    } else if (selectedShape && event->buttons() & Qt::RightButton) {
        // 在编辑模式下拖动鼠标
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
    if (isDrawing && !selectedShape && event->button() == Qt::LeftButton) {
        // 完成绘图
        endPoint = event->pos();
        isDrawing = false;
        addShapeData();
        update();
    } else if (isDragging && event->button() == Qt::RightButton) {
        // 完成拖动
        isDragging = false;
    }
}

void Canvas::wheelEvent(QWheelEvent* event) {
    if (selectedShape) {
        // 只在编辑模式下使用滚轮缩放图形
        int delta = event->angleDelta().y();
        float scaleFactor = (delta > 0) ? 1.1 : 0.9;
        selectedShape->resizeBy(scaleFactor, lastMousePos);
        update();
    }
}


// set property slot
void Canvas::setColor(QAbstractButton* button){
    if (button->text() == "Red") {
        currentColor = Qt::red;
    } else if (button->text() == "Blue") {
        currentColor = Qt::blue;
    } else if (button->text() == "Green") {
        currentColor = Qt::green;
    }

    if (selectedShape) {
        selectedShape->setColor(currentColor);
        update();
    }
}

void Canvas::setThickness(QAbstractButton* button){
    if (button->text() == "Thin") {
        currentThickness = 3;
    } else if (button->text() == "Medium") {
        currentThickness = 5;
    } else if (button->text() == "Thick") {
        currentThickness = 7;
    }

    if (selectedShape) {
        selectedShape->setThickness(currentThickness);
        update();
    }
}

void Canvas::setStyle(QAbstractButton* button){
    if (button->text() == "Solid") {
        currentStyle = Qt::SolidLine;
    } else if (button->text() == "Dash") {
        currentStyle = Qt::DashLine;
    } else if (button->text() == "Dot") {
        currentStyle = Qt::DotLine;
    }

    if (selectedShape) {
        selectedShape->setStyle(currentStyle);
        update();
    }
}

void Canvas::setShape(QAbstractButton* button){
    if (button->text() == "Line") {
        currentShape = Shape::LineShape;
    } else if (button->text() == "Rectangle") {
        currentShape = Shape::RectangleShape;
    } else if (button->text() == "Ellipse") {
        currentShape = Shape::EllipseShape;
    }

    if (selectedShape) {
        selectedShape->setShapeType(currentShape, selectedShape->getStartPosition(), selectedShape->getEndPosition());
        update();
    }
}

void Canvas::updateToolbarButtons(){
    if (!selectedShape) return;

    // update color button
    if (selectedShape->getColor() == Qt::red) {
        colorGroup->button(0)->setChecked(true);
    } else if (selectedShape->getColor() == Qt::blue) {
        colorGroup->button(1)->setChecked(true);
    } else if (selectedShape->getColor() == Qt::green) {
        colorGroup->button(2)->setChecked(true);
    }

    // update thickness button
    if (selectedShape->getThickness() == 3) {
        thicknessGroup->button(0)->setChecked(true);
    } else if (selectedShape->getThickness() == 5) {
        thicknessGroup->button(1)->setChecked(true);
    } else if (selectedShape->getThickness() == 7) {
        thicknessGroup->button(2)->setChecked(true);
    }

    // update style button
    if (selectedShape->getStyle() == Qt::SolidLine) {
        styleGroup->button(0)->setChecked(true);
    } else if (selectedShape->getStyle() == Qt::DashLine) {
        styleGroup->button(1)->setChecked(true);
    } else if (selectedShape->getStyle() == Qt::DotLine) {
        styleGroup->button(2)->setChecked(true);
    }

    // update shape buttons
    if (selectedShape->getShapeType() == Shape::LineShape) {
        shapeGroup->button(0)->setChecked(true);
    } else if (selectedShape->getShapeType() == Shape::RectangleShape) {
        shapeGroup->button(1)->setChecked(true);
    } else if (selectedShape->getShapeType() == Shape::EllipseShape) {
        shapeGroup->button(2)->setChecked(true);
    }
}

void Canvas::updatePenProperties(){
    // update color
    if (colorGroup->button(0)->isChecked()) {
        currentColor = Qt::red;
    } else if (colorGroup->button(1)->isChecked()) {
        currentColor = Qt::blue;
    } else if (colorGroup->button(2)->isChecked()) {
        currentColor = Qt::green;
    }

    // update thickness
    if (thicknessGroup->button(0)->isChecked()) {
        currentThickness = 3;
    } else if (thicknessGroup->button(1)->isChecked()) {
        currentThickness = 5;
    } else if (thicknessGroup->button(2)->isChecked()) {
        currentThickness = 7;
    }

    // update style
    if (styleGroup->button(0)->isChecked()) {
        currentStyle = Qt::SolidLine;
    } else if (styleGroup->button(1)->isChecked()) {
        currentStyle = Qt::DashLine;
    } else if (styleGroup->button(2)->isChecked()) {
        currentStyle = Qt::DotLine;
    }

    // update shape
    if (shapeGroup->button(0)->isChecked()) {
        currentShape = Shape::LineShape;
    } else if (shapeGroup->button(1)->isChecked()) {
        currentShape = Shape::RectangleShape;
    } else if (shapeGroup->button(2)->isChecked()) {
        currentShape = Shape::EllipseShape;
    }
}

// close event
void Canvas::closeEvent(QCloseEvent* event){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,tr("Quit"),tr("Do you want to quit?"),QMessageBox::Yes|QMessageBox::No);
    if (reply==QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}
