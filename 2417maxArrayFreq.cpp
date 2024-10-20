#include <iostream>
using namespace std;

int main() {
    int n; // array length
    cin >> n;
	int* arr = new int[n + 1];
    int x;
	for (int i = 0; i < n; i++) {
		cin >> x;
		arr[i] = x;
	}
	//bubble sort
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				x = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = x;
			}
		}
	}
	arr[n] = arr[n - 1] + 1; 
	//count the frequency
	int maxFreq = 1;
	int curFreq = 1;
	for (int i = 1; i <= n; i++) {
		if (arr[i] == arr[i - 1]) {
			curFreq++;
		}
		else {
			if (curFreq > maxFreq) {
				maxFreq = curFreq;
			}
			curFreq = 1;
		}
	}
	cout << maxFreq;
	delete[] arr;
    return 0;
}