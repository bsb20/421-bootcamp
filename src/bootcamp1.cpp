#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

int main() {
    std::string sentence = "the quick brown fox jumps over the lazy dog the quick fox";
    std::stringstream ss(sentence);
    std::string word;
    std::vector<std::string> words_vector;
    while (ss >> word) {
        words_vector.push_back(word);
    }

    std::unordered_map<std::string, int> word_counts;
    
    return 0;
}
