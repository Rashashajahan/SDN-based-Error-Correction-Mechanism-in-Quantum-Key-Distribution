#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// Global keys for Alice and Bob
const string aliceKey = "0000010010111100011101000110111111110011010100100010110011000110111111110100011010010011111100111110";
const string bobKey = "1000110010111100011111000110111111110011010100100010110011000110111111110100011010010011111100111101";

double calculateQBER(const string& originalKey, const string& erroredKey) {
    int errorCount = 0;
    for (size_t i = 0; i < originalKey.size(); i++) {
        if (originalKey[i] != erroredKey[i]) {
            errorCount++;
        }
    }
    return 100.0 * errorCount / originalKey.size();
}

int main() {
    double qberValue = calculateQBER(aliceKey, bobKey);
    cout << "Alice key: " << aliceKey << "%" << endl;
    cout << "Bob key: " << bobKey << "%" << endl;
    cout << "Calculated QBER value: " << qberValue << "%" << endl;
    return 0;
}