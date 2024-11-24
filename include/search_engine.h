#pragma once
#include <string>
#include <vector>
#include "indexer.h"

class SearchEngine {
public:
    void addDocument(const std::string& filePath);
    std::vector<std::string> search(const std::string& query) const;
    
private:
    Indexer indexer;
    
    std::vector<std::string> tokenizeQuery(const std::string& query) const;
    std::vector<std::pair<std::string, double>> rankResults(
        const std::vector<std::pair<std::string, double>>& results) const;
};
