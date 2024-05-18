#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>

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
std::vector<int> process_key(std::vector<int>& key, std::vector<int>& alice_parities) {
    std::vector<int> n;
    std::vector<int> remaining_key = key;
    
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

int main() {
    std::vector<int> alice_key = {0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0};
    std::vector<int> bob_error_key = {1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1};
    
    // Alice's side: prepare key with parity bits
    auto [left_alice, right_alice] = divide_and_append_parity(alice_key);
    std::vector<int> alice_parities = left_alice;
    alice_parities.insert(alice_parities.end(), right_alice.begin(), right_alice.end());
    
    // Bob's side: correct errors using received parities from Alice
    std::vector<int> corrected_bob_key = process_key(bob_error_key, alice_parities);
    
    // Final check and correction
    std::vector<int> alice_final = alice_key;
    alice_final.push_back(calculate_parity(alice_key));
    std::vector<int> bob_final = corrected_bob_key;
    bob_final.push_back(calculate_parity(corrected_bob_key));
    
    if (hash_value(alice_final) != hash_value(bob_final)) {
        for (size_t i = 0; i < corrected_bob_key.size(); ++i) {
            if (corrected_bob_key[i] != alice_key[i]) {
                corrected_bob_key[i] ^= 1;
                break;
            }
        }
    }
    
    std::cout << "Alice's key: ";
    for (int bit : alice_key) {
        std::cout << bit;
    }
    std::cout << std::endl;
    
    std::cout << "Corrected Bob's key: ";
    for (int bit : corrected_bob_key) {
        std::cout << bit;
    }
    std::cout << std::endl;
    
    return 0;
}
