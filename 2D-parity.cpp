#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to divide the key into equal parts
vector<string> divideKey(const string& key, int numParts) {
    vector<string> keyParts;
    int partSize = key.size() / numParts;
    for (int i = 0; i < numParts; ++i) {
        keyParts.push_back(key.substr(i * partSize, partSize));
    }
    return keyParts;
}

// Function to perform longitudinal redundancy check
string longitudinalRedundancyCheck(const string& binaryString) {
    string lrc;
    int count = 0;
    for (char bit : binaryString) {
        count += (bit == '1') ? 1 : 0;
    }
    lrc = (count % 2 == 0) ? "0" : "1";
    return lrc;
}

// Function to perform vertical redundancy check
string verticalRedundancyCheck(const vector<string>& parts) {
    string vrc;
    for (int i = 0; i < parts[0].size(); ++i) {
        int count = 0;
        for (const string& part : parts) {
            count += (part[i] == '1') ? 1 : 0;
        }
        vrc += (count % 2 == 0) ? '0' : '1';
    }
    return vrc;
}

int main() {
    srand(time(0)); // Seed for random number generation

    string aliceKey = "0000010010111100011101000110111111110011010100100010110011000110111111110100011010010011111100111110";
    string bobKey = "1000110010111100011101000110111111110011010100100010110011000110111111110100011010010011111100111101";

    for (int numParts = 2; numParts <= 10; numParts += 2) {
        // Divide Bob's key into equal parts for checks
        vector<string> bobKeyParts = divideKey(bobKey, numParts);

        // Perform longitudinal redundancy check on the partitioned key
        vector<string> lrcBobKeyParts;
        for (const string& part : bobKeyParts) {
            lrcBobKeyParts.push_back(longitudinalRedundancyCheck(part));
        }

        // Perform vertical redundancy check on the partitioned key
        string vrcBobKey = verticalRedundancyCheck(bobKeyParts);

        // Print Bob's key, partitioned key, and their check outputs
        cout << "Number of Parts: " << numParts << endl;
        cout << "Partitioned Bob's Key:" << endl;
        for (const string& part : bobKeyParts) {
            cout << part << endl;
        }
        cout << "Longitudinal Redundancy Check for Partitioned Bob's Key:" << endl;
        for (const string& lrcPart : lrcBobKeyParts) {
            cout << lrcPart << endl;
        }
        cout << "Vertical Redundancy Check for Partitioned Bob's Key: " << vrcBobKey << endl;

        // Compare Alice's key with Bob's corrected key and correct Bob's key if needed
        bool match = true;
        for (int i = 0; i < aliceKey.size(); ++i) {
            if (aliceKey[i] != bobKey[i]) {
                bobKey[i] = (bobKey[i] == '0') ? '1' : '0'; // Flip the bit
                match = false;
            }
        }

        if (match) {
            cout << "Match found after correction!" << endl;
        } else {
            cout << "Mismatch found. Bob's corrected key:" << endl;
            cout << bobKey << endl;
        }

        cout << "----------------------" << endl;
    }
    cout << "Bob's Key: " << bobKey << endl;
    cout << "Alice's Key: " << aliceKey << endl;
    return 0;
}
