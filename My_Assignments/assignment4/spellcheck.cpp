#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
    // 找到所有空格字符的位置
    auto space_positions = find_all(source.begin(), source.end(), 
                                  [](unsigned char c) { return std::isspace(c); });
    
    // 创建一个set来存储tokens
    std::set<Token> tokens;
    
    // 使用transform将连续的空格位置转换为Token
    std::transform(space_positions.begin(), space_positions.end() - 1,
                  space_positions.begin() + 1,
                  std::inserter(tokens, tokens.end()),
                  [&source](auto it1, auto it2) {
                      return Token(source, it1, it2);
                  });
    
    // 删除空的tokens
    std::erase_if(tokens, [](const Token& token) {
        return token.content.empty();
    });
    
    return tokens;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
    namespace rv = std::ranges::views;
    
    // 1. 过滤出拼写错误的单词
    auto misspelled = source | rv::filter([&dictionary](const Token& token) {
        return !dictionary.contains(token.content);
    });
    
    // 2. 将拼写错误的单词转换为Misspelling对象，并找出建议
    auto with_suggestions = misspelled | rv::transform([&dictionary](const Token& token) {
        // 找出所有编辑距离为1的单词作为建议
        auto suggestions_view = dictionary | rv::filter([&token](const std::string& word) {
            return levenshtein(token.content, word) == 1;
        });
        
        // 将建议转换为set
        std::set<std::string> suggestions(suggestions_view.begin(), suggestions_view.end());
        
        // 创建Misspelling对象
        return Misspelling{token, suggestions};
    });
    
    // 3. 过滤掉没有建议的拼写错误
    auto valid_misspellings = with_suggestions | rv::filter([](const Misspelling& m) {
        return !m.suggestions.empty();
    });
    
    // 将结果转换为set并返回
    return std::set<Misspelling>(valid_misspellings.begin(), valid_misspellings.end());
}

/* Helper methods */

#include "utils.cpp"