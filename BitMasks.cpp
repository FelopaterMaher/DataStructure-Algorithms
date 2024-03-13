#include <bits/stdc++.h>
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

// Subset Sum Problem: Given a set of positive integers and a target sum,
// determine whether there exists a subset whose elements sum up to the target.
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

// Generate all possible subsequences of a given string
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

// Generate all permutations of a given string using bitmasking
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

// Function to perform bitwise left shift on a number
int leftShift(int num, int positions) {
    return num << positions;
}

// Function to perform bitwise right shift on a number
int rightShift(int num, int positions) {
    return num >> positions;
}

// Function to check if a number is a power of two
bool isPowerOfTwo(int num) {
    return num && !(num & (num - 1));
}

// Function to find the position of the first set bit in a number
int findFirstSetBit(int num) {
    int position = 0;
    while (!(num & (1 << position))) {
        position++;
    }
    return position + 1; // Adding 1 because bit positions start from 1
}

// Function to find the position of the last set bit in a number
int findLastSetBit(int num) {
    int position = 0;
    while (num >>= 1) {
        position++;
    }
    return position + 1; // Adding 1 because bit positions start from 1
}

// Function to reverse the bits of a number
int reverseBits(int num) {
    int reversedNum = 0;
    while (num) {
        reversedNum <<= 1; // Left shift reversedNum
        reversedNum |= (num & 1); // Add the least significant bit of num to reversedNum
        num >>= 1; // Right shift num
    }
    return reversedNum;
}

// Function to swap bits at given positions
int swapBits(int num, int pos1, int pos2) {
    // Extract the values of bits at pos1 and pos2
    int bit1 = (num >> pos1) & 1;
    int bit2 = (num >> pos2) & 1;
    // Swap the values of bits at pos1 and pos2
    num ^= (-bit1 ^ num) & (1 << pos2);
    num ^= (-bit2 ^ num) & (1 << pos1);
    return num;
}

// Function to count leading zeros in a number
int countLeadingZeros(int num) {
    int count = 0;
    while (!(num & (1 << ((sizeof(num) * 8) - 1)))) {
        count++;
        num <<= 1;
    }
    return count;
}

// Example usage
int main() {
    int num = 10; // Binary representation: 1010

    // Test cases for bit manipulation functions
    printf("Bit at position 3 is set: %d\n", isBitSet(num, 3)); // Output: 1 (true)
    num = setBit(num, 3);
    printf("After setting bit at position 3: %d\n", num); // Output: 14 (binary 1110)
    num = unsetBit(num, 1);
    printf("After unsetting bit at position 1: %d\n", num); // Output: 10 (binary 1010)
    num = toggleBit(num, 0);
    printf("After toggling bit at position 0: %d\n", num); // Output: 11 (binary 1011)
    printf("Number of set bits: %d\n", countSetBits(num)); // Output: 4
    printf("Number after left shifting by 2 positions: %d\n", leftShift(num, 2)); // Output: 44
    printf("Number after right shifting by 2 positions: %d\n", rightShift(num, 2)); // Output: 2
    printf("Is %d a power of two? %s\n", num, isPowerOfTwo(num) ? "Yes" : "No"); // Output: No
    printf("Position of first set bit: %d\n", findFirstSetBit(num)); // Output: 1
    printf("Position of last set bit: %d\n", findLastSetBit(num)); // Output: 4
    printf("Reversed bits of %d: %d\n", num, reverseBits(num)); // Output: 13
    printf("Number after swapping bits at positions 1 and 3: %d\n", swapBits(num, 1, 3)); // Output: 14
    printf("Number of leading zeros in %d: %d\n", num, countLeadingZeros(num)); // Output: 28

    // Test case for subset sum problem
    vector<int> nums = {3, 34, 4, 12, 5, 2};
    int target = 9;
    cout << "Subset with sum " << target << " exists: " << (subsetSum(nums, target) ? "Yes" : "No") << endl;

    // Test case for generating subsequences
    string s = "abc";
    cout << "All subsequences of string \"" << s << "\" are:\n";
    generateSubsequences(s);

    // Test case for generating permutations
    cout << "All permutations of string \"" << s << "\" are:\n";
    vector<string> permutations = generatePermutations(s);
    for (const string& permutation : permutations) {
        cout << permutation << endl;
    }

    return 0;
}
