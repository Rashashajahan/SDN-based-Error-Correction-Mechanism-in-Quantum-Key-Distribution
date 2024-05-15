#include <iostream>
#include <vector>
#include <algorithm>

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

// Function to perform error correction using Cascade protocol
void cascadeErrorCorrection(std::string& key, const std::string& codeword, int passes) {
    std::string correctedKey = key;
    std::vector<int> errorFlag(passes, 0); // Initialize error flag for each pass

    for (int pass = 0; pass < passes; ++pass) {
        // Error detection and correction logic for each pass
        bool errorDetected = false;
        for (size_t i = 0; i < key.size(); ++i) {
            if (key[i] != codeword[i]) {
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
        key = correctedKey; // Update the key for the next pass
    }

    // Print the final corrected key and error flags
    std::cout << "Final Corrected Key: " << correctedKey << std::endl;
    std::cout << "Error Flags: ";
    for (int flag : errorFlag) {
        std::cout << flag << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::string aliceKey = "0000010010111100011101000110111111110011010100100010110011000110111111110100011010010011111100111110";
    std::string bobKey = "1000010010111100011101000110111111110011010100100010110011000110111111110100011010010011111100001111";

    int passes = 5; // Number of passes in the Cascade protocol

    std::cout << "Initial Key: " << aliceKey << std::endl;

    // Generate codeword using a simple parity check code
    std::string codeword = generateCodeword(aliceKey);
    std::cout << "Generated Codeword: " << codeword << std::endl;

    cascadeErrorCorrection(bobKey, codeword, passes);

    return 0;
}
