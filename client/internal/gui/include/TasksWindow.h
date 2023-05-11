#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QScrollArea>
#include <QComboBox>
#include <QLabel>
#include <QFileDialog>
#include "Task.h"

class TasksWindow : public QMainWindow {
Q_OBJECT

public:
    explicit TasksWindow(QWidget *parent = nullptr);

public slots:
    void on_backButton_clicked();
    void on_goToTaskButton_clicked();
    void indexChanged();

private:

    QWidget *centralwidget = nullptr;
    QVBoxLayout* verticalLayout = nullptr;
    QGroupBox *taskChooseGroupBox = nullptr;
    QVBoxLayout* taskVerticalLayout = nullptr;
    QLabel* label = nullptr;
    QComboBox* tasks = nullptr;
    QLabel* taskDescription = nullptr;
    QPushButton* goToTaskButton = nullptr;
    QPushButton* backButton = nullptr;
    QWidget* buttonsWidget = nullptr;
    QHBoxLayout* buttonsLayout = nullptr;

    std::vector<Task> tasks_vector;

    void setupUi(QMainWindow *UserWindow);
};

#endif  // USERWINDOW_H
