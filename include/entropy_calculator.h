#pragma once
#include <vector>
#include <string>
#include <cstdint>

class EntropyCalculator {
public:
    static double calculateShannonEntropy(const std::vector<uint8_t>& data);
    static std::vector<double> calculateBlockEntropies(
        const std::vector<uint8_t>& data, 
        size_t blockSize
    );
    static bool isObfuscatedOrCompressed(
        const std::vector<double>& entropies,
        double threshold = 0.7
    );
};