//
// Created by march on 02.05.2023.
//

#include "TextMetricsLib.h"


void PrepareDataTextMetric::getData(std::istream &fin1, std::istream &fin2) {
    std::string text1( (std::istreambuf_iterator<char>(fin1) ),
                       (std::istreambuf_iterator<char>()    ) );

    std::string text2( (std::istreambuf_iterator<char>(fin2) ),
                       (std::istreambuf_iterator<char>()    ) );

    std::string non_comm_text1 = deleteComments(text1);
    std::string non_comm_text2 = deleteComments(text2);

    tokens1 = tbmTokenizer(non_comm_text1);
    tokens2 = tbmTokenizer(non_comm_text2);
}

std::string PrepareDataTextMetric::deleteComments(const std::string& text) {
    std::string modif;
    std::string res;

    std::stringstream ss;
    std::string line;

    ss << text;

    while(getline(ss, line)){
        line.pop_back();
        line.push_back('\0');
        modif += line;
    }

    bool s_comm = false;
    bool m_comm = false;

    for (int i = 0; i < modif.size(); i++){
        if (s_comm && modif[i] == '\0')
            s_comm = false;
        else if  (m_comm && modif[i] == '*' && modif[i + 1] == '/')
            m_comm = false,  i++;
        else if (s_comm || m_comm)
            continue;
        else if (modif[i] == '/' && modif[i+1] == '/')
            s_comm = true, i++;
        else if (modif[i] == '/' && modif[i+1] == '*')
            m_comm = true,  i++;

        else if (modif[i] != '\0')
            res += modif[i];
        else{
            res += '\n';
        }
    }
    return res;
}

std::vector <std::string> PrepareDataTextMetric::tbmTokenizer(const std::string &text) {
    boost::char_separator <char> sep(" {}();,\"\0\'");
    std::vector <std::string> res;
    boost::tokenizer < boost::char_separator <char> > tokens(text, sep);

    for (const std::string &s: tokens) {
        if (!s.empty() && s[0] != '\n' && s[0] != '\0'){
            res.push_back(s);
        }
    }
    return res;
}



