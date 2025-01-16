#include "drawarea.h"
#include "mainwindow.h"
#include <QPainter>
#include <QMouseEvent>

DrawArea::DrawArea(QWidget *parent)
    : QWidget(parent), animationTimer(new QTimer(this)) {

    this->setMinimumSize(800, 800);
    this->setMaximumSize(800, 800);
    
    Vec2 drawAreaSize = {this->size().width(), this->size().height()};

    context.addPlaneCollider({{1, 1}, {0, 1}});
    context.addPlaneCollider({{1, 1}, {1, 0}});
    context.addPlaneCollider({drawAreaSize - Vec2(12, 2), {0, -1}});
    context.addPlaneCollider({drawAreaSize - Vec2(12, 2), {-1, 0}});

    context.addPlaneCollider({{150, 100}, {1, 1}});
    context.addPlaneCollider({{drawAreaSize.x - 50, 150}, {-1.5, 1}});
    context.addPlaneCollider({{100, drawAreaSize.y-100}, {1, -1}});
    context.addPlaneCollider({drawAreaSize - Vec2(50, 50) , {-1, -1}});


    context.addCircleCollider({drawAreaSize/2, 50});


    // Set up timer for animation
    connect(animationTimer, &QTimer::timeout, this, &DrawArea::animate);
    animationTimer->start(16);// ~60 FPS
}

DrawArea::~DrawArea() {
    delete animationTimer;
}

void DrawArea::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    // Clear the background
    painter.fillRect(rect(), QBrush(QColor(255, 255, 255)));

    // Draw all circles


    std::vector<Particle> vec = context.getVec();

    for (const auto &particle : vec) {
        painter.setPen(particle.color);
        painter.setBrush(particle.color);
        painter.drawEllipse(QPointF(particle.pos.x, particle.pos.y), particle.radius, particle.radius);
    }

    // Draw all colliders

    painter.setPen(QPen(Qt::magenta, 3));
    painter.setBrush(Qt::magenta);


    std::vector<Plane> planeCollider = context.getPlaneCollider();

    for (const auto &plane: planeCollider) {
        Line line = plane.toLine(this->size().width(), this->size().height());
        painter.drawLine(static_cast<int>(line.p1.x), static_cast<int>(line.p1.y),
            static_cast<int>(line.p2.x), static_cast<int>(line.p2.y));
    }

    std::vector<Circle> circleCollider = context.getCircleCollider();

    for (const auto &circle: circleCollider) {
        painter.drawEllipse(QPointF(circle.center.x, circle.center.y), circle.radius, circle.radius);
    }



}

void DrawArea::mouseDoubleClickEvent(QMouseEvent *event) {
    // Add a new circle at the double-click position
    Particle particle;
    particle.pos.x = static_cast<double>(event->x());
    particle.pos.y = static_cast<double>(event->y());
    particle.radius = this->radiusSpinBox->value();
    particle.setMass(this->massSpinBox->value());
    particle.color = particleColor;
    context.addParticle(particle);
    update(); // Trigger a repaint
}

void DrawArea::animate() {
    context.updatePhysicalSystem(0.1);
    update(); // Trigger a repaint
}
