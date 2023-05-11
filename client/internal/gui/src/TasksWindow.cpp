#include "TasksWindow.h"

#include <QMenuBar>
#include <QStatusBar>
#include <QApplication>

#include "SolutionsWindow.h"
#include "UIManager.h"

TasksWindow::TasksWindow(QWidget *parent) : QMainWindow(parent) {
    tasks_vector.push_back({1, "1 description                            1\n"
                               "1\n"
                               "2\n"
                               "3\n"
                               "4\n"
                               "5\n"
                               "6\n"
                               "7\n"
                               "8\n"
                               "9\n"
                               "10\n"
                               "11\n"
                               "12\n"
                               "13\n"
                               "14\n"});
    tasks_vector.push_back({2, "2 description"});
    tasks_vector.push_back({3, "3 description"});

    setupUi(this);
    connect(tasks, &QComboBox::currentIndexChanged, this, &TasksWindow::indexChanged);
    connect(goToTaskButton, &QPushButton::clicked, this, &TasksWindow::on_goToTaskButton_clicked);
    connect(backButton, &QPushButton::clicked, this, &TasksWindow::on_backButton_clicked);
}



void TasksWindow::setupUi(QMainWindow *UserWindow) {
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(UserWindow->sizePolicy().hasHeightForWidth());
    UserWindow->setSizePolicy(sizePolicy);

    centralwidget = new QWidget(UserWindow);
    verticalLayout = new QVBoxLayout(centralwidget);

    taskChooseGroupBox = new QGroupBox(centralwidget);
    sizePolicy.setHeightForWidth(taskChooseGroupBox->sizePolicy().hasHeightForWidth());
    taskChooseGroupBox->setFixedHeight(85);
    taskChooseGroupBox->setSizePolicy(sizePolicy);

    taskVerticalLayout = new QVBoxLayout(taskChooseGroupBox);

    label = new QLabel(this);
    label->setText(QString::fromUtf8("Выберите номер задания:"));

    tasks = new QComboBox(this);
    for (int i = 0; i < tasks_vector.size(); i++) {
        tasks->insertItem(i, QString::number(tasks_vector[i].id));
    }
    tasks->setCurrentIndex(0);

    taskVerticalLayout->addWidget(label);
    taskVerticalLayout->addWidget(tasks);

    taskDescription = new QLabel(this);
    std::string description = tasks_vector[0].description;
    taskDescription->setText(QString(description.c_str()));

    buttonsWidget = new QWidget(centralwidget);
    sizePolicy.setHeightForWidth(buttonsWidget->sizePolicy().hasHeightForWidth());
    buttonsWidget->setFixedHeight(45);

    buttonsLayout = new QHBoxLayout(buttonsWidget);

    goToTaskButton = new QPushButton(this);
    goToTaskButton->setText(QString::fromUtf8("Перейти к сдаче"));

    backButton = new QPushButton(this);
    backButton->setText(QString::fromUtf8("Выйти"));

    buttonsLayout->addWidget(goToTaskButton);
    buttonsLayout->addWidget(backButton);

    verticalLayout->addWidget(taskChooseGroupBox);
    verticalLayout->addWidget(taskDescription);
    verticalLayout->addWidget(buttonsWidget);

    UserWindow->setCentralWidget(centralwidget);
}

void TasksWindow::indexChanged() {
    std::string description = tasks_vector[tasks->currentIndex()].description;
    taskDescription->setText(QString(description.c_str()));
}

void TasksWindow::on_backButton_clicked() {
    // Core::logout();
    close();
    qobject_cast<UIManager*>(parent())->showEntryWindow();
}

void TasksWindow::on_goToTaskButton_clicked() {
    hide();
    auto* solutionsWindow = new SolutionsWindow(tasks_vector[tasks->currentIndex()], this);
    solutionsWindow->show();
}
