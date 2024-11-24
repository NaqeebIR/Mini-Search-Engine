#include "indexer.h"
#include <cmath>

void Indexer::addDocument(const Document& doc) {
    size_t docId = documents.size();
    documents.push_back(doc);
    
    // Update inverted index
    for (const auto& wordFreq : doc.getWordFrequencies()) {
        invertedIndex[wordFreq.first].push_back({docId, wordFreq.second});
    }
}

std::vector<std::pair<std::string, double>> Indexer::calculateTFIDF(const std::string& term) const {
    std::vector<std::pair<std::string, double>> results;
    
    auto it = invertedIndex.find(term);
    if (it != invertedIndex.end()) {
        double idf = calculateIDF(term);
        
        for (const auto& docFreq : it->second) {
            double tf = calculateTF(docFreq.second);
            double score = tf * idf;
            results.push_back({documents[docFreq.first].getPath(), score});
        }
    }
    
    return results;
}

double Indexer::calculateTF(int termFreq) const {
    return termFreq > 0 ? 1 + std::log10(termFreq) : 0;
}

double Indexer::calculateIDF(const std::string& term) const {
    auto it = invertedIndex.find(term);
    if (it != invertedIndex.end()) {
        double numDocs = documents.size();
        double docsWithTerm = it->second.size();
        return std::log10(numDocs / docsWithTerm);
    }
    return 0;
}
