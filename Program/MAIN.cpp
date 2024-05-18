#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/rand.h>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <sstream>

using namespace std;

// Global keys for Alice and Bob
const string aliceKey = "0000010010111100011101000110111111110011010100100010110011000110111111110100011010010011111100111110";
const string bobKey = "0000110010111100011111000110111111110011010100100010110011000110111111110100011010010011111100111101";

// Function prototypes
void cascadeErrorCorrection(double qberValue, string bobKey);
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
    } else {
        cout << "Invalid QBER value. Please check the measurement." << endl;
    }

    cout << "Alice's Key: " << aliceKey << endl;
    return 0;
}

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

std::string arrayToString(const std::vector<int>& array) {
    std::string str;
    for (int bit : array) {
        str += std::to_string(bit);
    }
    return str;
} 

// Function to calculate the parity bit
int calculate_parity(const std::vector<int>& bits) {
    return std::accumulate(bits.begin(), bits.end(), 0) % 2;
}

// Function to calculate the SHA-256 hash
std::string hash_value(const std::vector<int>& bits) {
    std::string bit_string;
    for (int bit : bits) {
        bit_string += std::to_string(bit);
    }
    
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(bit_string.c_str()), bit_string.size(), hash);
    
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    
    return ss.str();
}

// Function to divide the key and append the parity bit
std::pair<std::vector<int>, std::vector<int>> divide_and_append_parity(std::vector<int>& key) {
    int mid = key.size() / 2;
    std::vector<int> left(key.begin(), key.begin() + mid);
    std::vector<int> right(key.begin() + mid, key.end());
    
    left.push_back(calculate_parity(left));
    right.push_back(calculate_parity(right));
    
    return {left, right};
}

// Function to remove the parity bit
std::vector<int> remove_parity(const std::vector<int>& bits) {
    return std::vector<int>(bits.begin(), bits.end() - 1);
}

// Function to compare and correct the key
std::vector<int> compare_and_correct(const std::vector<int>& bob_part, const std::vector<int>& alice_part) {
    std::vector<int> corrected = bob_part;
    for (size_t i = 0; i < bob_part.size() - 1; ++i) {
        if (bob_part[i] != alice_part[i]) {
            corrected[i] ^= 1;
            break;
        }
    }
    return corrected;
}

// Function to process the key and correct errors
std::vector<int> process_key(const std::vector<int>& key, const std::vector<int>& aliceparities) {
std::vector<int> n;
    std::vector<int> remaining_key = key;
    std::vector<int> alice_parities =aliceparities;
    
    while (n.size() < key.size()) {
        auto [left_bob, right_bob] = divide_and_append_parity(remaining_key);
        std::string left_bob_hash = hash_value(left_bob);
        std::string right_bob_hash = hash_value(right_bob);
        
        auto [left_alice, right_alice] = divide_and_append_parity(alice_parities);
        std::string left_alice_hash = hash_value(left_alice);
        std::string right_alice_hash = hash_value(right_alice);
        
        std::vector<int> left_corrected;
        if (left_bob_hash != left_alice_hash) {
            left_corrected = compare_and_correct(left_bob, left_alice);
            left_corrected = remove_parity(left_corrected);
        } else {
            left_corrected = remove_parity(left_bob);
        }
        
        std::vector<int> right_corrected;
        if (right_bob_hash != right_alice_hash) {
            right_corrected = compare_and_correct(right_bob, right_alice);
            right_corrected = remove_parity(right_corrected);
        } else {
            right_corrected = remove_parity(right_bob);
        }
        
        n.insert(n.end(), left_corrected.begin(), left_corrected.end());
        n.insert(n.end(), right_corrected.begin(), right_corrected.end());
        remaining_key = n;
    }
    
    return n;
}



// Function to perform error correction using Cascade protocol
void cascadeErrorCorrection(double qberValue, const std::string bobKey) {
    std::vector<int> alice_Key(aliceKey.begin(), aliceKey.end());
    std::vector<int> bob_Key(bobKey.begin(), bobKey.end());
    string correctedKey = bobKey;
    string codeword = generateCodeword(aliceKey);
    
    // Convert the vector of ASCII values to a vector of integers (0 and 1)
    auto convertAsciiToBinary = [](const std::vector<int>& asciiVec) {
        std::vector<int> binaryVec;
        for (int ascii : asciiVec) {
            if (ascii == 48) {
                binaryVec.push_back(0);
            } else if (ascii == 49) {
                binaryVec.push_back(1);
            }
        }
        return binaryVec;
    };

    // Convert the keys
    alice_Key = convertAsciiToBinary(alice_Key);
    bob_Key = convertAsciiToBinary(bob_Key);

    // Alice's side: prepare key with parity bits
    auto [left_alice, right_alice] = divide_and_append_parity(alice_Key);
    std::vector<int> alice_parities = left_alice;
    alice_parities.insert(alice_parities.end(), right_alice.begin(), right_alice.end());
    
    // Bob's side: correct errors using received parities from Alice
    std::vector<int> corrected_bob_key = process_key(bob_Key, alice_parities);

    // Final check and correction
    std::vector<int> alice_final = alice_Key;
    alice_final.push_back(calculate_parity(alice_Key));
    std::vector<int> bob_final = corrected_bob_key;
    bob_final.push_back(calculate_parity(corrected_bob_key));
    
    for (size_t i = 0; i < bobKey.size(); ++i) {
            if (bobKey[i] != codeword[i]) {
                correctedKey[i] = codeword[i]; // Correct the error
            }
        }
    
    if (hash_value(alice_final) != hash_value(bob_final)) {
        for (size_t i = 0; i < corrected_bob_key.size(); ++i) {
            if (corrected_bob_key[i] != alice_Key[i]) {
                corrected_bob_key[i] ^= 1;
                break;
            }
        }
    }
    std::cout << "Alice's key: ";
    for (int bit : alice_Key) {
        std::cout << bit;
    }
    std::cout << std::endl;

    std::cout << "Corrected Bob's key: ";
    for (int bit : correctedKey) {
        std::cout << bit;
    }
    std::cout << std::endl;
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
    }
    cout << "Bob's Key: " << bobKey << endl;
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
