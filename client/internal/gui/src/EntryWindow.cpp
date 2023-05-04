#include "EntryWindow.h"

#include <QMenuBar>
#include <QStatusBar>
#include <QApplication>
#include <QCoreApplication>
#include "AuthDialog.h"
#include "SignUpDialog.h"

EntryWindow::EntryWindow(QWidget *parent) : QMainWindow(parent) {}

EntryWindow::~EntryWindow() {}

void EntryWindow::setupUi(QMainWindow *MainWindow) {}

void EntryWindow::retranslateUi(QMainWindow *MainWindow) {}

void EntryWindow::onExitButtonClicked() {}

void EntryWindow::onLoginButtonClicked() {}


void EntryWindow::onSignUpButtonClicked() {}

std::shared_ptr<SignUpDialog> EntryWindow::getSignUpDialog() {}

std::shared_ptr<AuthDialog> EntryWindow::getAuthDialog() {}
