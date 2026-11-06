#include "entropy_calculator.h"
#include <cmath>
#include <algorithm>
#include <numeric>
#include <map>

double EntropyCalculator::calculateShannonEntropy(const std::vector<uint8_t>& data) {
    if (data.empty()) return 0.0;

    // Compter les occurrences de chaque octet
    std::map<uint8_t, int> frequencyMap;
    for (uint8_t byte : data) {
        ++frequencyMap[byte];
    }

    double entropy = 0.0;
    size_t totalBytes = data.size();

    // Calcul de l'entropie selon la formule: H(X) = -Σ(p(x)*log2(p(x)))
    for (const auto& pair : frequencyMap) {
        double probability = static_cast<double>(pair.second) / totalBytes;
        entropy -= probability * std::log2(probability);
    }

    return entropy;
}

std::vector<double> EntropyCalculator::calculateBlockEntropies(
    const std::vector<uint8_t>& data, 
    size_t blockSize
) {
    if (data.empty() || blockSize == 0) return {};

    std::vector<double> entropies;
    size_t numBlocks = (data.size() + blockSize - 1) / blockSize; // Division arrondie au supérieur

    for (size_t i = 0; i < numBlocks; ++i) {
        size_t start = i * blockSize;
        size_t end = std::min(start + blockSize, data.size());
        
        if (start >= data.size()) break;
        
        // Extraction du bloc
        std::vector<uint8_t> block(data.begin() + start, data.begin() + end);
        
        double entropy = calculateShannonEntropy(block);
        entropies.push_back(entropy);
    }

    return entropies;
}

bool EntropyCalculator::isObfuscatedOrCompressed(
    const std::vector<double>& entropies,
    double threshold
) {
    if (entropies.empty()) return false;
    
    // Si la majorité des blocs ont une entropie élevée (> seuil), le fichier est suspect
    size_t highEntropyCount = 0;
    for (double entropy : entropies) {
        if (entropy > threshold) ++highEntropyCount;
    }
    
    // Si plus de la moitié des blocs ont une haute entropie, on considère que le fichier est obfusqué ou compressé
    return highEntropyCount > entropies.size() / 2;
}