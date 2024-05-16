#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/rand.h>
#include <cstring>

using namespace std;

// Global keys for Alice and Bob
const string aliceKey = "0000010010111100011101000110111111110011010100100010110011000110111111110100011010010011111100111110";
const string bobKey = "1000110010111100011111000110111111110011010100100010110011000110111111110100011010010011111100111101";
int passes = 5; // Number of passes in the Cascade protocol

// Function prototypes
void cascadeErrorCorrection(double qberValue, string bobKey);
void runLDPCErrorCorrection(double qberValue);
void run2DParityErrorCorrection(double qberValue, string bobKey);
vector<int> correctErrorsCascade(vector<int>& qubits, double qberValue);
vector<int> decodeLDPC(vector<int>& receivedCodeword, const vector<vector<int>>& parityCheckMatrix, double qberValue);
string arrayToString(const vector<int>& array);
vector<string> divideKey(const string& key, int numParts);
string longitudinalRedundancyCheck(const string& binaryString);
string verticalRedundancyCheck(const vector<string>& parts);
double calculateQBER(const string& originalKey, const string& erroredKey);
string generateCodeword(const std::string& aliceKey);
string generateRandomKey(size_t length);
string calculateHMAC(const std::string& key, const std::string& data);

int main() {
    double qberValue = calculateQBER(aliceKey, bobKey);
    cout << "Calculated QBER value: " << qberValue << "%" << endl;

    // Generate a random key for HMAC
    string randomKey = generateRandomKey(32); // Generate a 256-bit key
    string aliceHMAC = calculateHMAC(randomKey, aliceKey);
    string bobHMAC = calculateHMAC(randomKey, bobKey);

    if (aliceHMAC == bobHMAC) {
        cout << "Matched: HMAC values are the same. Exiting." << endl;
        return 0;
    }

    cout << "Mismatched: HMAC values are different. Proceeding with error correction." << endl;

    if (qberValue > 0 && qberValue < 5) {
        cout << "Selected Error Correction Mechanism: 2D-Parity" << endl;
        run2DParityErrorCorrection(qberValue, bobKey);
    } else if (qberValue >= 5 && qberValue <= 15) {
        cout << "Selected Error Correction Mechanism: Cascade" << endl;
        cascadeErrorCorrection(qberValue, bobKey);
    } else if (qberValue > 15 && qberValue <= 32) {
        cout << "Selected Error Correction Mechanism: LDPC" << endl;
        runLDPCErrorCorrection(qberValue);
    } else if (qberValue > 32) {
        cout << "QBER exceeds 32%. Cannot correct errors." << endl;
    } else {
        cout << "Invalid QBER value. Please check the measurement." << endl;
    }

    cout << "Final Alice's Key: " << aliceKey << endl;
    return 0;
}

// Function implementations remain unchanged (implementations of cascadeErrorCorrection, runLDPCErrorCorrection, etc.)

string generateRandomKey(size_t length) {
    string key;
    key.resize(length);
    if (!RAND_bytes(reinterpret_cast<unsigned char*>(&key[0]), length)) {
        cerr << "Error generating random key" << endl;
        exit(1);
    }
    return key;
}

string calculateHMAC(const string& key, const string& data) {
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLen;
    HMAC_CTX* ctx = HMAC_CTX_new();
    HMAC_Init_ex(ctx, key.c_str(), key.length(), EVP_sha256(), NULL);
    HMAC_Update(ctx, reinterpret_cast<const unsigned char*>(data.c_str()), data.length());
    HMAC_Final(ctx, hash, &hashLen);
    HMAC_CTX_free(ctx);

    string hmacStr;
    for (unsigned int i = 0; i < hashLen; i++) {
        char buf[3];
        sprintf(buf, "%02x", hash[i]);
        hmacStr.append(buf);
    }
    return hmacStr;
}

// Function to perform error correction using Cascade protocol
void cascadeErrorCorrection(double qberValue, string bobKey) {
    string correctedKey = bobKey;
    string codeword = generateCodeword(aliceKey);
    vector<int> errorFlag(passes, 0); // Initialize error flag for each pass

    for (int pass = 0; pass < passes; ++pass) {
        // Error detection and correction logic for each pass
        bool errorDetected = false;
        for (size_t i = 0; i < bobKey.size(); ++i) {
            if (bobKey[i] != codeword[i]) {
                errorFlag[pass] = 1; // Set flag for error detection in this pass
                correctedKey[i] = codeword[i]; // Correct the error
                errorDetected = true;
            }
        }
        // Print the corrected key for this pass
        std::cout << "Pass " << pass + 1 << " Corrected Key: " << correctedKey << std::endl;

        // If no error detected in this pass, break the loop
        if (!errorDetected) {
            std::cout << "No errors detected in Pass " << pass + 1 << std::endl;
            break;
        }
        bobKey = correctedKey; // Update the key for the next pass
    }

    // Print the final corrected key and error flags
    std::cout << "Final Corrected Key: " << correctedKey << std::endl;
    std::cout << "Error Flags: ";
    for (int flag : errorFlag) {
        std::cout << flag << " ";
    }
    std::cout << std::endl;
}

void runLDPCErrorCorrection(double qberValue) {
    cout << "Running LDPC Error Correction Mechanism..." << endl;
    vector<vector<int>> parityCheckMatrix = {
        {1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 0},
        {1, 0, 0, 1, 0, 1}
    };
    vector<int> receivedCodeword = {0, 1, 1, 0, 1, 0};
    vector<int> decodedCodeword = decodeLDPC(receivedCodeword, parityCheckMatrix, qberValue);

    cout << "Decoded Codeword: " << arrayToString(decodedCodeword) << endl;
}

void run2DParityErrorCorrection(double qberValue, string bobKey) { // Remove const from bobKey
    cout << "Running 2D Parity Error Correction Mechanism..." << endl;

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
}


bool calculateParity(const std::string& str, int start, int end) {
    bool parity = 0; // False (0) for even, true (1) for odd
    for (int i = start; i <= end; ++i) {
        parity ^= (str[i] == '1'); // XOR operation
    }
    return parity;
}

vector<int> decodeLDPC(vector<int>& receivedCodeword, const vector<vector<int>>& parityCheckMatrix, double qberValue) {
    vector<int> decodedCodeword(receivedCodeword.size());
    for (int i = 0; i < receivedCodeword.size(); i++) {
        if (static_cast<double>(rand()) / RAND_MAX <= qberValue / 100.0) {
            receivedCodeword[i] = 1 - receivedCodeword[i];  // Flip the bit
        }
        decodedCodeword[i] = receivedCodeword[receivedCodeword.size() - 1 - i];
    }
    return decodedCodeword;
}

string arrayToString(const vector<int>& array) {
    string result;
    for (int val : array) {
        result += to_string(val);
    }
    return result;
}

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


double calculateQBER(const string& originalKey, const string& erroredKey) {
    int errorCount = 0;
    for (size_t i = 0; i < originalKey.size(); i++) {
        if (originalKey[i] != erroredKey[i]) {
            errorCount++;
        }
    }
    return 100.0 * errorCount / originalKey.size();
}

// Function to generate a codeword using a simple parity check code
std::string generateCodeword(const std::string& key) {
    std::string codeword = key;
    int parity = 0;
    for (char bit : key) {
        parity ^= (bit - '0'); // XOR operation for parity calculation
    }
    codeword += (parity + '0'); // Append parity bit to the key
    return codeword;
}
