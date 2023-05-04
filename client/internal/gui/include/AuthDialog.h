#ifndef AUTH_DIALOG_H
#define AUTH_DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLineEdit>

class AuthDialog : public QDialog {
    Q_OBJECT

public:
    explicit AuthDialog(QWidget *parent = nullptr);
    ~AuthDialog() override;

signals:
    void showMainWindow();
    void showUserWindow();

private slots:
    void on_loginButton_clicked();
    void on_backButton_clicked();

private:
    QGroupBox *groupBox = nullptr;
    QWidget *layoutWidget = nullptr;
    QVBoxLayout *verticalLayout = nullptr;
    QHBoxLayout *horizontalLayout = nullptr;
    QLabel *loginLabel = nullptr;
    QLineEdit *login = nullptr;
    QHBoxLayout *horizontalLayout_2 = nullptr;
    QLabel *passwordLabel = nullptr;
    QLineEdit *password = nullptr;
    QPushButton *loginButton = nullptr;
    QPushButton *backButton = nullptr;

    void setupUi(QDialog *AuthDialog);

    void setTexts(QDialog *AuthDialog);
};

#endif  // AUTH_DIALOG_H
