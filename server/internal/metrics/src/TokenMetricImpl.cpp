//
// Created by march on 04.05.2023.
//

#include "TokenMetricLib.h"

double LevDistTokenMetric::getMetric() {
    unsigned long n = tokens1.size();
    unsigned long m = tokens2.size();
    int x, y, z;

    std::vector <std::vector <int> > lev (n, std::vector <int> (m, 0));

    for (size_t i = 0; i < n; i++){
        for (size_t j = 0; j < m; j++){
            if (std::min(i, j) == 0){
                lev[i][j] = static_cast <int> (std::max(i, j));
            }
            else{
                x = lev[i-1][j];
                y = lev[i][j-1];
                z = lev[i-1][j-1];
                lev[i][j] = std::min(x, std::min(y, z));
                if (tokens1[i] != tokens2[j]){
                    lev[i][j]++;
                }
            }
        }
    }

    if (n == 0 || m == 0)
        return 0;
    double res = 1.0 - static_cast<double> (lev[n-1][m-1]) / static_cast<double> (std::max(n ,m));
    return  res;
}

double WShinglingTokenMetric::getMetric() {}

void PrepareDataTokenMetric::setData(std::vector<int> _tokens1, std::vector<int> _tokens2) {
    tokens1 = _tokens1;
    tokens2 = _tokens2;
}
