#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

// Function to generate pattern for a given text
vector<int> generatePattern(const vector<string>& text) {
    unordered_map<string, int> wordIndex;
    vector<int> pattern;
    int index = 0;

    for (const string& word : text) {
        if (wordIndex.find(word) == wordIndex.end()) {
            wordIndex[word] = index++;
        }
        pattern.push_back(wordIndex[word]);
    }

    return pattern;
}

int main() {
    string originalLine, encryptedLine;

    // Read input
    getline(cin, originalLine, '$');
    getline(cin, encryptedLine, '$');

    // Parse the original and encrypted lines into word lists
    istringstream originalStream(originalLine);
    istringstream encryptedStream(encryptedLine);
    vector<string> originalWords, encryptedWords;
    string word;

    while (originalStream >> word) {
        originalWords.push_back(word);
    }
    while (encryptedStream >> word) {
        encryptedWords.push_back(word);
    }

    // Generate pattern for encrypted text
    vector<int> encryptedPattern = generatePattern(encryptedWords);
    int encryptedLength = encryptedWords.size();

    // Search for encrypted pattern in original text
    for (size_t i = 0; i <= originalWords.size() - encryptedLength; ++i) {
        vector<string> subOriginalWords(originalWords.begin() + i, originalWords.begin() + i + encryptedLength);
        vector<int> originalPattern = generatePattern(subOriginalWords);

        if (originalPattern == encryptedPattern) {
            // Output the 1-based index of the first word in the original text
            cout << i + 1 << endl;
            break;
        }
    }

    return 0;
}
