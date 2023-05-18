#include "PythonAntlr.h"

#include <iostream>

PythonAntlr::PythonAntlr(std::istream& in) {
    input_ptr = std::make_unique<antlr4::ANTLRInputStream>(in);
    lexer_ptr = std::make_unique<antlrcpptest::Python3Lexer>(&(*input_ptr));
    tokenStream_ptr = std::make_unique<antlr4::CommonTokenStream>(&(*lexer_ptr));
    parser_ptr = std::make_unique<antlrcpptest::Python3Parser>(&(*tokenStream_ptr));
}

std::vector<antlr4::Token*> PythonAntlr::getTokens() {
    tokenStream_ptr->fill();
    std::vector<antlr4::Token*> ans(tokenStream_ptr->size());

    int i = 0;
    for (antlr4::Token* token : tokenStream_ptr->getTokens()) {
        ans[i] = token;
        i++;
    }

    return ans;
}

std::vector<int> PythonAntlr::getTokensTypes() {
    tokenStream_ptr->fill();
    std::vector<int> ans(tokenStream_ptr->size());

    int i = 0;
    for (antlr4::Token* token : tokenStream_ptr->getTokens()) {
        ans[i] = token->getType();
        i++;
    }

    return ans;
}

std::string PythonAntlr::getTokensString() {
    tokenStream_ptr->fill();
    std::string res;

    for (antlr4::Token* token : tokenStream_ptr->getTokens()) {
        res += token->toString() + " ";
    }

    return res;
}

std::string PythonAntlr::getTreeString() {
    auto tree = parser_ptr->file_input();
    return tree->toStringTree(&(*parser_ptr));
}

std::pair<std::string, std::string> PythonAntlr::getTokensAndTree() {
    std::string tokens = getTokensString();
    std::string astTree = getTreeString();
    return std::make_pair(tokens, astTree);
}
