#ifndef SOURCEDOUT_METRICSTAT_HPP
#define SOURCEDOUT_METRICSTAT_HPP

#include <iostream>

class MetricStat {
public:
    MetricStat(size_t solutionId, float textBasedRes, float tokenBasedRes, float treeBasedRes, bool verdict,
               float meanRes);

    MetricStat(size_t id, size_t solutionId, float textBasedRes, float tokenBasedRes, float treeBasedRes, bool verdict,
               float meanRes);

    [[nodiscard]] size_t getId() const;

    void setId(size_t id);

    [[nodiscard]] size_t getSolutionId() const;

    void setSolutionId(size_t solutionId);

    [[nodiscard]] float getTextBasedRes() const;

    void setTextBasedRes(float textBasedRes);

    [[nodiscard]] float getTokenBasedRes() const;

    void setTokenBasedRes(float tokenBasedRes);

    [[nodiscard]] float getTreeBasedRes() const;

    void setTreeBasedRes(float treeBasedRes);

    [[nodiscard]] bool isVerdict() const;

    void setVerdict(bool verdict);

    [[nodiscard]] float getMeanRes() const;

    void setMeanRes(float meanRes);

    bool operator==(const MetricStat &rhs) const;

    bool operator!=(const MetricStat &rhs) const;

private:
    size_t id;
    size_t solution_id;
    float text_based_res;
    float token_based_res;
    float tree_based_res;
    bool verdict;
    float mean_res;
};

#endif //SOURCEDOUT_METRICSTAT_HPP
