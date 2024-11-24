#include <iostream>
#include <string>
#include <sstream>
#include "search_engine.h"

void printUsage() {
    std::cout << "Available commands:\n"
              << "  add [file_path] - Add a document to the search engine\n"
              << "  search [query]  - Search for documents matching the query\n"
              << "  quit           - Exit the program\n";
}

int main() {
    SearchEngine engine;
    std::string command;
    
    std::cout << "Mini Search Engine\n"
              << "=================\n\n";
    printUsage();
    
    while (true) {
        std::cout << "\nEnter command: ";
        std::getline(std::cin, command);
        
        if (command.empty()) {
            continue;
        }
        
        // Parse command
        std::istringstream iss(command);
        std::string cmd;
        iss >> cmd;
        
        if (cmd == "quit") {
            break;
        }
        else if (cmd == "add") {
            std::string filepath;
            iss >> filepath;
            
            if (filepath.empty()) {
                std::cout << "Error: Please provide a file path\n";
                continue;
            }
            
            try {
                engine.addDocument(filepath);
                std::cout << "Document added successfully\n";
            }
            catch (const std::exception& e) {
                std::cout << "Error adding document: " << e.what() << "\n";
            }
        }
        else if (cmd == "search") {
            std::string query;
            std::getline(iss >> std::ws, query);
            
            if (query.empty()) {
                std::cout << "Error: Please provide a search query\n";
                continue;
            }
            
            auto results = engine.search(query);
            
            if (results.empty()) {
                std::cout << "No results found\n";
            }
            else {
                std::cout << "Search results:\n";
                for (size_t i = 0; i < results.size(); ++i) {
                    std::cout << i + 1 << ". " << results[i] << "\n";
                }
            }
        }
        else {
            std::cout << "Unknown command\n";
            printUsage();
        }
    }
    
    return 0;
}
