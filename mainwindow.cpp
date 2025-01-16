#include "mainwindow.h"

#include <iostream>

#include "./ui_mainwindow.h"
#include "drawarea.h"
#include <QColor>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMinimumSize(800, 850);
    this->setMaximumSize(800, 850);

    drawArea = new DrawArea(this);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setAlignment(Qt::AlignCenter);

    radiusLabel = new QLabel();
    radiusLabel->setText("Radius:");

    radiusSpinBox = new QDoubleSpinBox();
    radiusSpinBox->setValue(20);
    drawArea->setRadiusSpinBox(radiusSpinBox);

    massLabel = new QLabel();
    massLabel->setText("Mass:");

    massSpinBox = new QDoubleSpinBox();
    massSpinBox->setValue(1);
    drawArea->setMassSpinBox(massSpinBox);

    colorButton = new QPushButton(tr("Select color"));
    connect(
        colorButton, &QPushButton::clicked,
        this  , &MainWindow::onColorButtonClicked
    );

    gravityButton = new QPushButton(tr("Inverse gravity"));
    connect(
        gravityButton, &QPushButton::clicked,
        this  , &MainWindow::onGravityButtonClicked
    );

    fluidComboBox = new QComboBox();
    connect(
        fluidComboBox, &QComboBox::currentIndexChanged,
        this, &MainWindow::onFluidComboBoxChanged
    );
    fluidComboBox->addItem("Air");
    fluidComboBox->addItem("Water");
    fluidComboBox->addItem("Gasoline");
    fluidComboBox->setCurrentIndex(0);


    horizontalLayout->addWidget(radiusLabel);
    horizontalLayout->addWidget(radiusSpinBox);
    horizontalLayout->addWidget(massLabel);
    horizontalLayout->addWidget(massSpinBox);
    horizontalLayout->addWidget(colorButton);
    horizontalLayout->addWidget(gravityButton);
    horizontalLayout->addWidget(fluidComboBox);

    ui->verticalLayout->addWidget(drawArea);
    ui->verticalLayout->addLayout(horizontalLayout);
}

MainWindow::~MainWindow() {
    delete ui;
    delete drawArea;
    delete horizontalLayout;
    delete radiusLabel;
    delete radiusSpinBox;
    delete massLabel;
    delete massSpinBox;
    delete colorButton;
    delete gravityButton;
    delete fluidComboBox;
}

void MainWindow::onColorButtonClicked() {
    QColor color = QColorDialog::getColor(Qt::green, this);
    drawArea->setParticleColor(color);
}

void MainWindow::onGravityButtonClicked() const {
    drawArea->inverseGravity();
}

void MainWindow::onFluidComboBoxChanged() const {
    drawArea->changeFluid(fluidComboBox->currentIndex());
}
