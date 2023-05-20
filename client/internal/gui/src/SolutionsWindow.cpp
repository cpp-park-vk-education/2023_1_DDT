#include "SolutionsWindow.h"

#include <utility>
#include <fstream>
#include <sstream>
#include <QMessageBox>

#include "Solution.h"
#include "Core.h"

SolutionsWindow::SolutionsWindow(Task task, QWidget *parent) : QMainWindow(parent), task(std::move(task)) {
    setupUi(this);
    connect(backButton, &QPushButton::clicked, this, &SolutionsWindow::on_backButton_clicked);
    connect(chooseFileButton, &QPushButton::clicked, this, &SolutionsWindow::on_chooseFileButton_clicked);
    connect(sendButton, &QPushButton::clicked, this, &SolutionsWindow::on_sendButton_clicked);
}

void SolutionsWindow::setupUi(QMainWindow *SolutionsWindow) {
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(SolutionsWindow->sizePolicy().hasHeightForWidth());
    SolutionsWindow->setSizePolicy(sizePolicy);

    centralwidget = new QWidget(SolutionsWindow);
    verticalLayout = new QVBoxLayout(centralwidget);

    taskBox = new QGroupBox(centralwidget);
    taskLayout = new QVBoxLayout(taskBox);

    taskDescription = new QLabel(taskBox);
    std::string description = task.description;
    taskDescription->setText(QString(description.c_str()));

    taskLayout->addWidget(taskDescription);

    filename = new QLabel(this);

    chooseFileButton = new QPushButton(this);
    chooseFileButton->setText(QString::fromUtf8("Выберите файл"));

    sendButton = new QPushButton(this);
    sendButton->setText(QString::fromUtf8("Отправить"));

    result = new QTextEdit(this);
    result->setReadOnly(true);
    result->setText(QString::fromUtf8("Отправьте для принятия решения"));

    backButton = new QPushButton(this);
    backButton->setText(QString::fromUtf8("Назад"));

    verticalLayout->addWidget(taskBox);
    verticalLayout->addWidget(filename);
    verticalLayout->addWidget(chooseFileButton);
    verticalLayout->addWidget(sendButton);
    verticalLayout->addWidget(result);
    verticalLayout->addWidget(backButton);

    SolutionsWindow->setCentralWidget(centralwidget);
}

void SolutionsWindow::on_backButton_clicked() {
    close();
    qobject_cast<QMainWindow*>(parent())->show();
}

void SolutionsWindow::on_chooseFileButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose a file to send"), QDir::homePath());
    filename->setText(QFileInfo(fileName).fileName());
    path_to_file = fileName.toUtf8().constData();
}

void SolutionsWindow::on_sendButton_clicked() {
    if (path_to_file.empty()) {
        QMessageBox::warning(this, "Ошибка отправки", "Файл должен быть указан");
        return;
    }
    Solution sol = Core::submitSolution(task.id, filename->text().toUtf8().constData(), path_to_file);
    result->setText(QString::fromStdString(sol.result));
}


