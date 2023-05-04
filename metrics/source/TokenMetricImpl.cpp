//
// Created by march on 04.05.2023.
//

#include "TokenMetricLib.h"

void PrepareDataTokenMetric::setData(std::vector<std::string> _tokens1, std::vector<std::string> _tokens2) {}

double PrepareDataTokenMetric::getMetric() {
    return metric_res;
}

void LivDistTokenMetric::countMetric() {}

void WShinglingTokenMetric::countMetric() {}
