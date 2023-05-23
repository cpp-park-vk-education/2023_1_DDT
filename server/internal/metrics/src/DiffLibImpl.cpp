//
// Created by march on 22.05.2023.
//
#include <utility>

#include "DiffLib.h"

void FoundSame::setData(std::string text1, std::string text2) {
    tokens1 = diffTokenizer(text1);
    tokens2 = diffTokenizer(text2);

}

std::vector<std::string> FoundSame::diffTokenizer(const std::string& text) {
    boost::char_separator <char> sep(" \r", "\n");
    std::vector <std::string> res;
    boost::tokenizer < boost::char_separator <char> > tokens(text, sep);

    for (const std::string &s: tokens) {
        if (s == "\n" && !res.empty()){
            res.back() += "\n";
        }
        else
            res.push_back(s);
    }
    return res;
}

std::pair <std::string, std::string> FoundSame::getTexts() {
    unsigned long n = tokens1.size();
    unsigned long m = tokens2.size();

    std::vector <std::vector <int> > dist (n + 1, std::vector <int> (m + 1, 0));

    for (size_t i = 0; i < n + 1; i++){
        dist[i][0] = static_cast <int> (i);
    }

    for (size_t i = 0; i < m + 1; i++){
        dist[0][i] = static_cast <int> (i);
    }

    std::vector <std::vector <Elem> > cache (n + 1, std::vector <Elem > (m + 1));

    for (size_t i = 1; i <= n; i++){
        cache[i][0] = {"I", (tokens1[i-1].back() == '\n' && tokens1[i-1].size() > 2 ? "%\n" : "%"), tokens1[i-1]};
    }
    for (size_t i = 1; i <= m; i++){
        cache[0][i] = {"D", tokens2[i-1], (tokens2[i-1].back() == '\n' && tokens1[i-1].size() > 2 ? "#\n" : "#")};
    }

    std::string r, h;
    for (size_t i = 1; i <= n; i++){
        for (size_t j = 1; j <= m; j++){
            h = tokens1[i-1], r = tokens2[j-1];
            std::vector <std::pair <int, Elem> > cases;

            if (delServSimbols(r) == delServSimbols(h))
                cases.push_back( {dist[i - 1][j - 1], {"C", r, h} } );
            else
                cases.push_back({dist[i - 1][j - 1] + 1, {"R", r, h}});
            cases.push_back( { dist[i][j-1] + 1, {"D", r, (r.back() == '\n' && r.size() > 2 ? "#\n" : "#")} } );
            cases.push_back( { dist[i-1][j] + 1, {"I", (h.back() == '\n' && h.size() > 2 ? "%\n" : "%"), h} } );

            dist[i][j] = cases[0].first;
            cache[i][j] = cases[0].second;

            for (size_t k = 1; k < cases.size(); k++){
                if (dist[i][j] > cases[k].first){
                    dist[i][j] = cases[k].first;
                    cache[i][j] = cases[k].second;
                }
            }
        }
    }

    for (size_t i = 0; i < dist.size(); i++){
        for (size_t j = 0; j < dist[0].size(); j++){
            std::cout << dist[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::vector <Elem> alignment;
    size_t i = n, j = m;
    while (i != 0 || j != 0){
        std::string op = cache[i][j].op;
        alignment.push_back(cache[i][j]);
        if (op == "C" || op == "R"){
            i--, j--;
        } else if (op == "I"){
            i--;
        } else{
            j--;
        }
    }
    std::reverse(alignment.begin(), alignment.end());

    res_alignment = alignment;
    tokens2text();

    return {"", ""};
}

void FoundSame::setData2(std::vector<std::string> _tokens1, std::vector<std::string> _tokens2) {
    tokens1 = std::move(_tokens1);
    tokens2 = std::move(_tokens2);
}

void FoundSame::tokens2text() {

    std::vector <std::string> ops;

    for (auto & k : res_alignment){
        std::cout << k.op << " " << k.token1 << " " << k.token2 << std::endl;
    }

    for (const auto& elem : res_alignment){
        std::cout << elem.token1;
        if (elem.token1.back() != '\n')
            std::cout << " ";
    }
    std::cout << std::endl;
    for (const auto &elem : res_alignment){
        ops.push_back(elem.op);
        if (elem.token2.back() == '\n') {
            std::string t_token = elem.token2;
            t_token.pop_back();
            std::cout << t_token << "\t";
            for (const auto& oper : ops)
                std::cout << oper << " ";
            std::cout << std::endl;
            ops.clear();
        }
        else{
            std::cout << elem.token2;
            if (elem.token2.back() != '\n')
                std::cout << " ";
        }
    }
}

std::string FoundSame::delServSimbols(std::string s) {
    std::string res = std::move(s);
    while(!res.empty() && res.back() == '\n'){
        res.pop_back();
    }
    return res;
}


