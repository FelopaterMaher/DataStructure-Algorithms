#include<bits/stdc++.h>
using namespace std;
// Function to check if a specific bit is set in a number
int isBitSet(int num, int bit) {
    return (num & (1 << bit)) != 0; // Check if the bit is set using bitwise AND
}

// Function to set a specific bit in a number
int setBit(int num, int bit) {
    return num | (1 << bit); // Set the bit using bitwise OR
}

// Function to unset a specific bit in a number
int unsetBit(int num, int bit) {
    return num & ~(1 << bit); // Unset the bit using bitwise AND with complement
}

// Function to toggle a specific bit in a number
int toggleBit(int num, int bit) {
    return num ^ (1 << bit); // Toggle the bit using bitwise XOR
}

// Function to count the number of set bits (popcount) in a number
int countSetBits(int num) {
    int count = 0;
    while (num) {
        count += num & 1; // Check if the last bit is set
        num >>= 1; // Right shift to check the next bit
    }
    return count;
}
/*
Subset Sum Problem: Given a set of positive integers and a target sum,
determine whether there exists a subset whose elements sum up to the target.*/
bool subsetSum(const vector<int>& nums, int target) {
    int n = nums.size();
    for (int mask = 0; mask < (1 << n); ++mask) {
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                sum += nums[i];
            }
        }
        if (sum == target) {
            return true;
        }
    }
    return false;
}
/*
Finding All Subsequences: Generate all possible subsequences of a given string.*/
void generateSubsequences(const string& s) {
    int n = s.length();
    for (int mask = 0; mask < (1 << n); ++mask) {
        cout << "{ ";
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                cout << s[i];
            }
        }
        cout << " }\n";
    }
}

//Finding All Permutations: Generate all permutations of a given string using bitmasking.
vector<string> generatePermutations(const string& s) {
    vector<string> permutations;
    int n = s.length();
    int totalPermutations = 1 << n;
    for (int mask = 0; mask < totalPermutations; ++mask) {
        string permutation;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                permutation += s[i];
            }
        }
        permutations.push_back(permutation);
    }
    return permutations;
}

// Example usage
int main() {
    int num = 10; // Binary representation: 1010

    // Example 1: Check if bit at position 2 is set
    printf("Bit at position 3 is set: %d\n", isBitSet(num, 3)); // Output: 1 (true)

    // Example 2: Set bit at position 3
    num = setBit(num, 3); // Now num is 1010 | 1000 = 1110 (binary)
    printf("After setting bit at position 3: %d\n", num); // Output: 14 (binary 1110)

    // Example 3: Unset bit at position 1
    num = unsetBit(num, 1); // Now num is 1110 & ~(0100) = 1010 (binary)
    printf("After unsetting bit at position 1: %d\n", num); // Output: 10 (binary 1010)

    // Example 4: Toggle bit at position 0
    num = toggleBit(num, 0); // Now num is 1010 ^ 0001 = 1011 (binary)
    printf("After toggling bit at position 0: %d\n", num); // Output: 11 (binary 1011)

    // Example 5: Count the number of set bits
    printf("Number of set bits: %d\n", countSetBits(num)); // Output: 4
    
    //Example 6: Subset Sum problem
    vector<int> nums = {3, 34, 4, 12, 5, 2}; // Example set
    int target = 9; // Example target sum
    cout << "Subset with sum " << target << " exists: " << (subsetSum(nums, target) ? "Yes" : "No") << endl;

    // Example 7: Generate all possible subsequences of a given string.
    string s = "abc";
    cout << "All subsequences of string \"" << s << "\" are:\n";
    generateSubsequences(s);
    
    //Example 8:
    cout << "All permutations of string \"" << s << "\" are:\n";
    vector<string> permutations = generatePermutations(s);
    for (const string& permutation : permutations) {
        cout << permutation << endl;
    }

    return 0;
}