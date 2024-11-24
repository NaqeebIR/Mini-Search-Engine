#include "search_engine.h"
#include <sstream>
#include <algorithm>
#include <unordered_map>

void SearchEngine::addDocument(const std::string& filePath) {
    Document doc(filePath);
    indexer.addDocument(doc);
}

std::vector<std::string> SearchEngine::search(const std::string& query) const {
    std::vector<std::string> queryTokens = tokenizeQuery(query);
    std::unordered_map<std::string, double> documentScores;
    
    // Calculate scores for each query term
    for (const auto& term : queryTokens) {
        auto results = indexer.calculateTFIDF(term);
        for (const auto& result : results) {
            documentScores[result.first] += result.second;
        }
    }
    
    // Convert to vector for sorting
    std::vector<std::pair<std::string, double>> rankedResults;
    for (const auto& score : documentScores) {
        rankedResults.push_back(score);
    }
    
    // Sort by score
    std::sort(rankedResults.begin(), rankedResults.end(),
        [](const std::pair<std::string, double>& a, 
           const std::pair<std::string, double>& b) { 
            return a.second > b.second; 
        });
    
    // Extract just the document paths
    std::vector<std::string> paths;
    for (const auto& result : rankedResults) {
        paths.push_back(result.first);
    }
    
    return paths;
}

std::vector<std::string> SearchEngine::tokenizeQuery(const std::string& query) const {
    std::vector<std::string> tokens;
    std::istringstream iss(query);
    std::string token;
    
    while (iss >> token) {
        // Convert to lowercase
        std::transform(token.begin(), token.end(), token.begin(), ::tolower);
        tokens.push_back(token);
    }
    
    return tokens;
}
