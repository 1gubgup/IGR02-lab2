#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QMenuBar>
#include <QButtonGroup>
#include <QFileDialog>
#include <QTextEdit>
#include <QPainterPath>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), canvas(new Canvas(this))
{
    ui->setupUi(this);

    // -------------------- menu bar --------------------
    QMenuBar* menuBar = this->menuBar();

    QMenu* fileMenu = menuBar->addMenu(tr("&File"));

    QAction* openAction = new QAction(QIcon(":/images/open.png"),tr("&Open"),this);
    QAction* saveAction = new QAction(QIcon(":/images/save.png"),tr("&Save"),this);

    openAction->setShortcut(tr("Ctrl+O"));
    saveAction->setShortcut(tr("Ctrl+S"));

    openAction->setStatusTip(tr("Open"));
    saveAction->setStatusTip(tr("Save"));

    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);

    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);

    // -------------------- color button --------------------
    QButtonGroup* colorGroup = new QButtonGroup(this);
    colorGroup->addButton(ui->redButton);
    colorGroup->addButton(ui->greenButton);
    colorGroup->addButton(ui->blueButton);
    colorGroup->addButton(ui->yellowButton);

    ui->redButton->setStyleSheet(
        "QPushButton { background-color: red; border: 1px solid black; }"
        "QPushButton:checked { background-color: darkred; border: 2px solid white; }"
        );
    ui->greenButton->setStyleSheet(
        "QPushButton { background-color: green; border: 1px solid black; }"
        "QPushButton:checked { background-color: darkgreen; border: 2px solid white; }"
        );
    ui->blueButton->setStyleSheet(
        "QPushButton { background-color: blue; border: 1px solid black; }"
        "QPushButton:checked { background-color: darkblue; border: 2px solid white; }"
        );
    ui->yellowButton->setStyleSheet(
        "QPushButton { background-color: yellow; border: 1px solid black; }"
        "QPushButton:checked { background-color: gold; border: 2px solid white; }"
        );

    connect(colorGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, [this](QAbstractButton *button) {
        QColor color;
        if (button == ui->redButton) {
            color = Qt::red;
        } else if (button == ui->greenButton) {
            color = Qt::green;
        } else if (button == ui->blueButton) {
            color = Qt::blue;
        } else if (button == ui->yellowButton) {
            color = Qt::yellow;
        }
        canvas->setColor(color);
    });

    // -------------------- thickness button --------------------
    connect(ui->thicknessSlider, &QSlider::valueChanged, this, [this](int value) {
        canvas->setThickness(value);
    });

    // -------------------- style button --------------------
    QButtonGroup* styleGroup = new QButtonGroup(this);
    styleGroup->addButton(ui->solidButton, 0);
    styleGroup->addButton(ui->dashButton, 1);
    styleGroup->addButton(ui->dotButton, 2);

    connect(styleGroup, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked), this, [this](QAbstractButton* button) {
        if (button == ui->solidButton) {
            canvas->setStyle(Qt::SolidLine);
        } else if (button == ui->dashButton) {
            canvas->setStyle(Qt::DashLine);
        } else if (button == ui->dotButton) {
            canvas->setStyle(Qt::DotLine);
        }
    });

    // -------------------- type button --------------------
    QButtonGroup* shapeGroup = new QButtonGroup(this);
    shapeGroup->addButton(ui->lineButton, 0);
    shapeGroup->addButton(ui->rectangleButton, 1);
    shapeGroup->addButton(ui->ellipseButton, 2);

    connect(shapeGroup, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked), this, [this](QAbstractButton* button) {
        if (button == ui->lineButton) {
            canvas->setShape(Shape::LineShape);
        } else if (button == ui->rectangleButton) {
            canvas->setShape(Shape::RectangleShape);
        } else if (button == ui->ellipseButton) {
            canvas->setShape(Shape::EllipseShape);
        }
    });

    // initialize
    createCanvas();
    initializeButton();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::createCanvas() {
    canvas = new Canvas(this);
    setCentralWidget(canvas);
    connect(canvas, &Canvas::shapeSelected, this, &MainWindow::enterEditMode);
    connect(canvas, &Canvas::noShapeSelected, this, &MainWindow::exitEditMode);
    statusBar()->showMessage("Drawing mode");
}

void MainWindow::initializeButton() {
    ui->redButton->setCheckable(true);
    ui->greenButton->setCheckable(true);
    ui->blueButton->setCheckable(true);
    ui->yellowButton->setCheckable(true);
    ui->redButton->setChecked(true);

    ui->thicknessSlider->setValue(5);

    ui->solidButton->setCheckable(true);
    ui->dashButton->setCheckable(true);
    ui->dotButton->setCheckable(true);
    ui->solidButton->setChecked(true);

    ui->lineButton->setCheckable(true);
    ui->rectangleButton->setCheckable(true);
    ui->ellipseButton->setCheckable(true);
    ui->lineButton->setChecked(true);

    exitEditMode();
}


// change mode by update the buttons and the status bar
void MainWindow::enterEditMode(const QColor& color, int thickness, Qt::PenStyle style, Shape::ShapeType shapeType) {

    if (color == Qt::red) {
        ui->redButton->setChecked(true);
    } else if (color == Qt::green) {
        ui->greenButton->setChecked(true);
    } else if (color == Qt::blue) {
        ui->blueButton->setChecked(true);
    } else if (color == Qt::yellow) {
        ui->yellowButton->setChecked(true);
    }

    ui->thicknessSlider->setValue(thickness);

    if (style == Qt::SolidLine) {
        ui->solidButton->setChecked(true);
    } else if (style == Qt::DashLine) {
        ui->dashButton->setChecked(true);
    } else if (style == Qt::DotLine) {
        ui->dotButton->setChecked(true);
    }

    if (shapeType == Shape::LineShape) {
        ui->lineButton->setChecked(true);
        ui->lineButton->show();
        ui->rectangleButton->hide();
        ui->ellipseButton->hide();
    } else if (shapeType == Shape::RectangleShape) {
        ui->rectangleButton->setChecked(true);
        ui->lineButton->hide();
        ui->rectangleButton->show();
        ui->ellipseButton->hide();
    } else if (shapeType == Shape::EllipseShape) {
        ui->ellipseButton->setChecked(true);
        ui->lineButton->hide();
        ui->rectangleButton->hide();
        ui->ellipseButton->show();
    }

    statusBar()->showMessage("Edit mode");
}

void MainWindow::exitEditMode() {
    ui->lineButton->show();
    ui->rectangleButton->show();
    ui->ellipseButton->show();

    statusBar()->showMessage("Drawing mode");
}


// open and save the file
void MainWindow::openFile() {
    // get file name to open
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Path File"), "", tr("Path Files (*.path)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);

        // open file for reading
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);

            // delete the old canvas and create a new one
            delete canvas;
            createCanvas();
            initializeButton();

            // read each line from the file
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList shapeData = line.split(",");

                // parse shape attributes
                Shape::ShapeType shapeType = static_cast<Shape::ShapeType>(shapeData[0].toInt());
                QColor color = QColor(shapeData[1]);
                int thickness = shapeData[2].toInt();
                Qt::PenStyle style = static_cast<Qt::PenStyle>(shapeData[3].toInt());

                // rebuild path
                QPainterPath path;
                int index = 4;
                while (index < shapeData.size()) {
                    QString elementType = shapeData[index];
                    if (elementType == "M") {
                        qreal x = shapeData[++index].toDouble();
                        qreal y = shapeData[++index].toDouble();
                        path.moveTo(x, y);
                    } else if (elementType == "L") {
                        qreal x = shapeData[++index].toDouble();
                        qreal y = shapeData[++index].toDouble();
                        path.lineTo(x, y);
                    }
                    ++index;
                }

                // create shape and add to canvas
                Shape* shape = nullptr;
                if (shapeType == Shape::LineShape) {
                    shape = new Line(QPoint(), QPoint());
                } else if (shapeType == Shape::RectangleShape) {
                    shape = new Rectangle(QPoint(), QPoint());
                } else if (shapeType == Shape::EllipseShape) {
                    shape = new Ellipse(QPoint(), QPoint());
                }
                if (shape) {
                    shape->setAttributes(color, thickness, style, shapeType);
                    shape->setPath(path);
                    canvas->addShape(shape);
                }
            }

            // close file and update canvas
            file.close();
            statusBar()->showMessage(tr("Path file opened"));
            qDebug() << "open" << fileName;
            canvas->update();
        }
    } else {
        qDebug() << "error";
    }
}

void MainWindow::saveFile() {
    // get file name to save
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Path File"), "", tr("Path Files (*.path)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);

        // open file for writing
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);

            // save all shapes
            for (Shape* shape : canvas->getShapes()) {
                out << QString::number(shape->getShape()) << ",";
                out << shape->getColor().name() << ",";
                out << QString::number(shape->getThickness()) << ",";
                out << QString::number(static_cast<int>(shape->getStyle())) << ",";

                // serialize path
                const QPainterPath& path = shape->getPath();
                for (int i = 0; i < path.elementCount(); ++i) {
                    QPainterPath::Element element = path.elementAt(i);
                    if (element.isMoveTo()) {
                        out << "M," << element.x << "," << element.y << ",";
                    } else if (element.isLineTo()) {
                        out << "L," << element.x << "," << element.y << ",";
                    }
                }
                out << "\n"; // new line for each shape
            }

            // close file
            file.close();
            statusBar()->showMessage(tr("Path file saved"));
            qDebug() << "save" << fileName;
        }
    } else {
        qDebug() << "error";
    }
}



// close event
void MainWindow::closeEvent(QCloseEvent* event){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Quit"), tr("Do you want to quit?"), QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}

