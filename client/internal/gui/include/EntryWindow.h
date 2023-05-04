#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "AuthDialog.h"
#include "SignUpDialog.h"

class EntryWindow : public QMainWindow {
Q_OBJECT

public:
    EntryWindow(QWidget *parent = nullptr);
    ~EntryWindow() override;

    std::shared_ptr<SignUpDialog> getSignUpDialog();
    std::shared_ptr<AuthDialog> getAuthDialog();

private slots:
    static void onExitButtonClicked();
    void onLoginButtonClicked();
    void onSignUpButtonClicked();

private:
    std::shared_ptr<AuthDialog> authDialog = nullptr;
    std::shared_ptr<SignUpDialog> signUpDialog = nullptr;
    QWidget *centralwidget = nullptr;
    QVBoxLayout *verticalLayout = nullptr;
    QLabel *introLabel = nullptr;
    QPushButton *loginButton = nullptr;
    QSpacerItem *horizontalSpacer = nullptr;
    QPushButton *signUpButton = nullptr;
    QSpacerItem *horizontalSpacer_2 = nullptr;
    QPushButton *exitButton = nullptr;
    QMenuBar *menubar = nullptr;
    QStatusBar *statusbar = nullptr;

    void setupUi(QMainWindow *MainWindow);
    void retranslateUi(QMainWindow *MainWindow);
};

#endif  // MAINWINDOW_H
