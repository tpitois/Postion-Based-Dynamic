#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>


#include "drawarea.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void onColorButtonClicked();
    void onGravityButtonClicked() const;
    void onFluidComboBoxChanged() const;


private:
    Ui::MainWindow *ui;
    DrawArea *drawArea;
    QHBoxLayout *horizontalLayout;
    QLabel *radiusLabel;
    QDoubleSpinBox *radiusSpinBox;
    QLabel *massLabel;
    QDoubleSpinBox *massSpinBox;
    QPushButton *colorButton;
    QPushButton *gravityButton;
    QComboBox *fluidComboBox;
};
#endif // MAINWINDOW_H
