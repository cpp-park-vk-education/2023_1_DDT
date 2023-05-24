//
// Created by march on 22.05.2023.
//
#include <utility>

#include "DiffLib.h"

void FoundSame::setData(std::string text1, std::string text2) {
    tokens1 = diffTokenizer(text1);
    tokens2 = diffTokenizer(text2);
}

void FoundSame::setData2(std::vector <std::pair <std::string, int> > _tokens1, std::vector <std::pair <std::string, int> > _tokens2) {
    str_int_tokens1 = std::move(_tokens1);
    str_int_tokens2 = std::move(_tokens2);
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
        cache[i][0] = {"I", (tokens1[i-1].back() == '\n' && tokens1[i-1].size() > 1 ? "%\n" : "%"), tokens1[i-1]};
    }
    for (size_t i = 1; i <= m; i++){
        cache[0][i] = {"D", tokens2[i-1], (tokens2[i-1].back() == '\n' && tokens1[i-1].size() > 1 ? "#\n" : "#")};
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
            cases.push_back( { dist[i][j-1] + 1, {"D", r, (r.back() == '\n' && r.size() > 1 ? "#\n" : "#")} } );
            cases.push_back( { dist[i-1][j] + 1, {"I", (h.back() == '\n' && h.size() > 1 ? "%\n" : "%"), h} } );

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

std::pair <std::string, std::string> FoundSame::getTexts2() {
    unsigned long n = str_int_tokens1.size();
    unsigned long m = str_int_tokens2.size();

    std::vector <std::vector <int> > dist (n + 1, std::vector <int> (m + 1, 0));

    for (size_t i = 0; i < n + 1; i++){
        dist[i][0] = static_cast <int> (i);
    }

    for (size_t i = 0; i < m + 1; i++){
        dist[0][i] = static_cast <int> (i);
    }

    std::vector <std::vector <Elem2> > cache (n + 1, std::vector <Elem2> (m + 1));

    for (size_t i = 1; i <= n; i++){
        cache[i][0] = {"I", {"%", str_int_tokens1[i-1].second}, str_int_tokens1[i-1]}; // str_int_tokens1[i-1].second мб кал
    }
    for (size_t i = 1; i <= m; i++){
        cache[0][i] = {"D", str_int_tokens2[i-1], {"#", str_int_tokens2[i-1].second}}; //аналогично
    }

    std::pair <std::string, int> r, h;
    for (size_t i = 1; i <= n; i++){
        for (size_t j = 1; j <= m; j++){
            h = str_int_tokens1[i-1], r = str_int_tokens2[j-1];
            std::vector <std::pair <int, Elem2> > cases;

            if (r.first == h.first)
                cases.push_back( {dist[i - 1][j - 1], {"C", r, h} } );
            else
                cases.push_back({dist[i - 1][j - 1] + 1, {"R", r, h}});
            cases.push_back( { dist[i][j-1] + 1, {"D", r, {"#", r.second} } } );
            cases.push_back( { dist[i-1][j] + 1, {"I", {"%", h.second}, h} } );

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

    std::vector <Elem2> alignment;
    size_t i = n, j = m;
    while (i != 0 || j != 0){
        std::string op = cache[i][j].op;
        auto temp = cache[i][j];
        if (temp.token1.second > temp.token2.second) {
            temp.token2.second = temp.token1.second;
        }
        else{
            temp.token1.second = temp.token2.second;
        }
        cache[i][j] = temp;
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

    for (auto & a : alignment){
        std::cout << a.op << " {" << a.token1.first << " " << a.token1.second << "} {"
                  << a.token2.first << " " << a.token2.second << "}" << std::endl;
    }

    res_alignment2 = alignment;
    tokens2text2();

    return {"", ""};
}

void FoundSame::tokens2text2() {
    std::string res1, res2;
    std::vector <std::string> ops;

    int line = res_alignment2[0].token1.second;

    for (auto & i : res_alignment2){
        if (i.token1.second > line){
            while(line != i.token1.second){
                res1 += '\n';
                line++;
            }
        }
        res1 += i.token1.first, res1 += " ";
    }

    line = res_alignment2[0].token2.second;
    for (auto & i : res_alignment2){
        if (i.token2.second > line){
            res2 += '\t';
            for (auto & op : ops){
                res2 += op, res2 += " ";
            }
            ops.clear();
            while(line < i.token2.second){
                res2+= '\n';
                line++;
            }
        }
        ops.push_back(i.op);
        res2 += i.token2.first, res2 += " ";
    }

    res1.pop_back(), res2.pop_back();

    std::cout << res1 << "\n\n" << res2 << std::endl;
}


