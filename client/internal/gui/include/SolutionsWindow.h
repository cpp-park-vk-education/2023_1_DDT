#pragma once

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
#include "TasksWindow.h"

class SolutionsWindow : public QMainWindow {
Q_OBJECT

public:
    explicit SolutionsWindow(Task task, QWidget *parent = nullptr);

private slots:
    void on_backButton_clicked();
    void on_chooseFileButton_clicked();
    void on_sendButton_clicked();

private:

    Task task;
    std::string source;

    QWidget *centralwidget = nullptr;
    QGroupBox* taskBox = nullptr;
    QVBoxLayout* taskLayout = nullptr;
    QVBoxLayout* verticalLayout = nullptr;
    QLabel* taskDescription = nullptr;
    QPushButton* chooseFileButton = nullptr;
    QLabel* filename = nullptr;
    QPushButton* sendButton = nullptr;
    QLabel* result = nullptr;
    QPushButton* backButton = nullptr;

    void setupUi(QMainWindow *UserWindow);
};
