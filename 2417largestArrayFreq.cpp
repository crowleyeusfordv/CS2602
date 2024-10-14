#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm> // 可能用于后续扩展

int main() {
    int n; // array length
    std::cin >> n; 

    std::vector<int> a(n); 

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i]; 
    }

    // store frequency with unordered map
    std::unordered_map<int, int> frequency;

	// calculate each number's frequency
    for (int num : a) {
        ++frequency[num];
    }

	// find the max frequency
    int maxFrequency = 0;
    for (const auto& pair : frequency) {
        if (pair.second > maxFrequency) {
            maxFrequency = pair.second;
        }
    }

    std::cout << maxFrequency;

    return 0;
}
