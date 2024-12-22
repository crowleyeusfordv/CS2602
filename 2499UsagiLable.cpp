#include <iostream>
#include <algorithm>
#include <cmath>

int main() {
    long long n;
    std::cin >> n;
    int tmp;
    int* arr = new int[n];
    long long count0 = 0;
    long long count1 = 0;
    long long count2 = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> tmp;
        arr[i] = tmp;
        if (tmp == 0) {
            ++count0;
        }
        else if (tmp == 1) {
            ++count1;
        }
        else {
            ++count2;
        }
    }
    long long count01 = 0;
	long long count02 = 0;
	long long count10 = 0;
	long long count12 = 0;
	long long count20 = 0;
	long long count21 = 0;
	for (int i = 0; i < count0; ++i) {
		if (arr[i] == 1) {
			++count01;
		}
		else if (arr[i] == 2) {
			++count02;
		}
	}
	for (int i = count0; i < count0 + count1; ++i) {
		if (arr[i] == 0) {
			++count10;
		}
		else if (arr[i] == 2) {
			++count12;
		}
	}
	for (int i = count0 + count1; i < n; ++i) {
		if (arr[i] == 0) {
			++count20;
		}
		else if (arr[i] == 1) {
			++count21;
		}
	}

	int res = std::min(count01, count10) + std::min(count02, count20) + std::min(count12, count21) + 2 * std::abs(count01 - count10);
	std::cout << res << std::endl;
    delete[] arr;
}
