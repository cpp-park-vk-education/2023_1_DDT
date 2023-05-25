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
#include <QTextEdit>
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
    std::string path_to_file;

    QWidget *centralwidget = nullptr;
    QGroupBox* taskBox = nullptr;
    QVBoxLayout* taskLayout = nullptr;
    QVBoxLayout* verticalLayout = nullptr;
    QLabel* taskDescription = nullptr;
    QPushButton* chooseFileButton = nullptr;
    QLabel* filename = nullptr;
    QPushButton* sendButton = nullptr;
    QTextEdit* result = nullptr;
    QPushButton* backButton = nullptr;
    QWidget* solutionWidget = nullptr;
    QGridLayout* solutionLayout = nullptr;
    QLabel* originalLabel = nullptr;
    QTextEdit* original = nullptr;
    QLabel* currentLabel = nullptr;
    QTextEdit* current = nullptr;

    void setupUi(QMainWindow *UserWindow);
};
