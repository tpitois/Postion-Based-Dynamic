#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QDoubleSpinBox>
#include <QWidget>
#include <QTimer>
#include "context.h"


class DrawArea : public QWidget {
    Q_OBJECT

public:
    explicit DrawArea(QWidget *parent = nullptr);
    ~DrawArea() override;
    void setMassSpinBox(QDoubleSpinBox *spinBox){massSpinBox = spinBox;};
    void setRadiusSpinBox(QDoubleSpinBox *spinBox){radiusSpinBox = spinBox;};
    void setParticleColor(QColor color){particleColor = color;};
    void inverseGravity(){context.inverseGravity();};
    void changeFluid(int index){context.changeFluid(index);};

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private slots:
    void animate();

private:
    QTimer *animationTimer;
    Context context;
    QDoubleSpinBox *massSpinBox = nullptr;
    QDoubleSpinBox *radiusSpinBox = nullptr;
    QColor particleColor = Qt::green;
};

#endif // DRAWAREA_H
