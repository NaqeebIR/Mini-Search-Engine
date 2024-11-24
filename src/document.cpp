#include "document.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

Document::Document(const std::string& path) : path(path) {
    processContent();
    calculateWordFrequencies();
}

const std::string& Document::getPath() const {
    return path;
}

const std::string& Document::getContent() const {
    return content;
}

const std::unordered_map<std::string, int>& Document::getWordFrequencies() const {
    return wordFrequencies;
}

void Document::processContent() {
    std::ifstream file(path);
    if (file) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        content = buffer.str();
    }
}

void Document::calculateWordFrequencies() {
    std::istringstream iss(content);
    std::string word;
    
    while (iss >> word) {
        // Convert to lowercase and remove punctuation
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        word.erase(std::remove_if(word.begin(), word.end(), 
            [](char c) { return !std::isalnum(c); }), word.end());
            
        if (!word.empty()) {
            wordFrequencies[word]++;
        }
    }
}
