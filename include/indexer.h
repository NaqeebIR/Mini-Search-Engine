#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "document.h"

class Indexer {
public:
    void addDocument(const Document& doc);
    std::vector<std::pair<std::string, double>> calculateTFIDF(const std::string& term) const;
    
private:
    std::vector<Document> documents;
    std::unordered_map<std::string, std::vector<std::pair<size_t, int>>> invertedIndex;
    
    double calculateTF(int termFreq) const;
    double calculateIDF(const std::string& term) const;
};
