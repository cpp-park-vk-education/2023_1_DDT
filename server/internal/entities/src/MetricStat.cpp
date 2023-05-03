
#include "MetricStat.hpp"

MetricStat::MetricStat(unsigned long solutionId, float textBasedRes, float tokenBasedRes, float treeBasedRes,
                       bool verdict, float meanRes) : id(0), solution_id(solutionId),
                                                      text_based_res(textBasedRes), token_based_res(tokenBasedRes),
                                                      tree_based_res(treeBasedRes), verdict(verdict), mean_res(meanRes) {}

MetricStat::MetricStat(size_t id, size_t solutionId, float textBasedRes, float tokenBasedRes, float treeBasedRes,
                       bool verdict, float meanRes) : id(id), solution_id(solutionId), text_based_res(textBasedRes),
                                                      token_based_res(tokenBasedRes), tree_based_res(treeBasedRes),
                                                      verdict(verdict), mean_res(meanRes) {}

size_t MetricStat::getId() const {
    return id;
}

void MetricStat::setId(size_t id_) {
    id = id_;
}

size_t MetricStat::getSolutionId() const {
    return solution_id;
}

void MetricStat::setSolutionId(size_t solutionId) {
    solution_id = solutionId;
}

float MetricStat::getTextBasedRes() const {
    return text_based_res;
}

void MetricStat::setTextBasedRes(float textBasedRes) {
    text_based_res = textBasedRes;
}

float MetricStat::getTokenBasedRes() const {
    return token_based_res;
}

void MetricStat::setTokenBasedRes(float tokenBasedRes) {
    token_based_res = tokenBasedRes;
}

float MetricStat::getTreeBasedRes() const {
    return tree_based_res;
}

void MetricStat::setTreeBasedRes(float treeBasedRes) {
    tree_based_res = treeBasedRes;
}

bool MetricStat::isVerdict() const {
    return verdict;
}

void MetricStat::setVerdict(bool verdict_) {
    verdict = verdict_;
}

float MetricStat::getMeanRes() const {
    return mean_res;
}

void MetricStat::setMeanRes(float meanRes) {
    mean_res = meanRes;
}
