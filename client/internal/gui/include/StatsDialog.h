//
// Created by Николай Степанов on 04.05.2023.
//

#ifndef SOURCEDOUT_STATSDIALOG_H
#define SOURCEDOUT_STATSDIALOG_H

#include <QTableView>
#include <QTableWidget>
#include "Metric.h"

class StatsDialog : public QDialog {
    Q_OBJECT

public:
    explicit StatsDialog(QWidget *parent = nullptr) {};
    ~StatsDialog() override {};

private:
    QTableView* tableView = nullptr;
    QTableWidget* tableWidget = nullptr;
    QVector<Metric> metrics;
};

#endif //SOURCEDOUT_STATSDIALOG_H
