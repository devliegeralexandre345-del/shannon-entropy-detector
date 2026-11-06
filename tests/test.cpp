#include <iostream>
#include <vector>
#include "entropy_calculator.h"

class TestRunner {
public:
    static bool runAllTests();

private:
    static void testShannonEntropy();
    static void testBlockEntropies();
    static void testObfuscationDetection();
};

bool TestRunner::runAllTests() {
    std::cout << "Lancement des tests unitaires..." << std::endl;
    
    try {
        testShannonEntropy();
        testBlockEntropies();
        testObfuscationDetection();
        
        std::cout << "Tous les tests ont réussi !" << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Erreur lors des tests: " << e.what() << std::endl;
        return false;
    }
}

void TestRunner::testShannonEntropy() {
    // Test avec un tableau de données uniformes (entropie maximale)
    std::vector<uint8_t> data1 = {0, 1, 2, 3, 4, 5};
    double entropy1 = EntropyCalculator::calculateShannonEntropy(data1);
    
    // Test avec un tableau de données identiques (entropie minimale)
    std::vector<uint8_t> data2(10, 0); // 10 zéros
    double entropy2 = EntropyCalculator::calculateShannonEntropy(data2);
    
    if (entropy1 <= 0 || entropy2 < 0) {
        throw std::runtime_error("Erreur dans le calcul de l'entropie");
    }
}

void TestRunner::testBlockEntropies() {
    // Création d'un tableau avec des données répétitives et aléatoires
    std::vector<uint8_t> data(100);
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = static_cast<uint8_t>(i % 256); // Données variées
    }
    
    auto entropies = EntropyCalculator::calculateBlockEntropies(data, 10);
    if (entropies.empty()) {
        throw std::runtime_error("Erreur dans le calcul des blocs d'entropie");
    }
}

void TestRunner::testObfuscationDetection() {
    // Test avec un tableau de haute entropie (simulation obfuscation)
    std::vector<double> highEntropyBlocks = {0.9, 0.85, 0.75};
    bool result1 = EntropyCalculator::isObfuscatedOrCompressed(highEntropyBlocks);
    
    // Test avec un tableau de faible entropie (pas d'obfuscation)
    std::vector<double> lowEntropyBlocks = {0.2, 0.3, 0.4};
    bool result2 = EntropyCalculator::isObfuscatedOrCompressed(lowEntropyBlocks);
    
    if (!result1 || result2) {
        throw std::runtime_error("Erreur dans la détection d'obfuscation");
    }
}

int main() {
    return TestRunner::runAllTests() ? 0 : 1;
}