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
#include "StatsDialog.h"

class UserWindow : public QMainWindow {
Q_OBJECT

public:
    explicit UserWindow(QWidget *parent = nullptr);
    ~UserWindow() override = default;

signals:
    void logout();

private slots:
    void onBackButtonClicked();
    void onListElementClicked();
    void onSendButtonClicked();

private:

    QTabWidget* tabs = nullptr;
    StatsDialog* statsDialog = nullptr;
    QPushButton *backButton = nullptr;
    QPushButton *sendButton = nullptr;
    QComboBox* comboBox = nullptr;
    QVBoxLayout* verticalLayout = nullptr;
    QLabel* label = nullptr;
    QLabel* description = nullptr;
    QFileDialog* fileDialog = nullptr;
    QStringList* list = nullptr;

    QWidget *centralwidget = nullptr;
};

#endif  // USERWINDOW_H
