#pragma once
#include <string>
#include <unordered_map>

class Document {
public:
    Document(const std::string& path);
    
    const std::string& getPath() const;
    const std::string& getContent() const;
    const std::unordered_map<std::string, int>& getWordFrequencies() const;
    
private:
    std::string path;
    std::string content;
    std::unordered_map<std::string, int> wordFrequencies;
    
    void processContent();
    void calculateWordFrequencies();
};
