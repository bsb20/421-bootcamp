#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

int main() {
    std::vector<std::string> words_vector;
    std::string word;
    while (std::cin >> word) {
        words_vector.push_back(word);
    }

    std::unordered_map<std::string, int> word_counts;
    
    return 0;
}
