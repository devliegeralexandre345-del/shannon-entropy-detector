#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "entropy_calculator.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }

    const std::string filePath = argv[1];
    
    // Lecture du fichier
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier '" << filePath << "'." << std::endl;
        return 1;
    }

    // Lecture de tout le contenu du fichier dans un vector
    std::vector<uint8_t> data((std::istreambuf_iterator<char>(file)),
                              std::istreambuf_iterator<char>());
    file.close();

    if (data.empty()) {
        std::cerr << "Erreur: Le fichier est vide." << std::endl;
        return 1;
    }

    // Calcul de l'entropie globale
    double globalEntropy = EntropyCalculator::calculateShannonEntropy(data);
    
    // Calcul des entropies par bloc (par exemple, 64 octets)
    const size_t blockSize = 64;
    auto blockEntropies = EntropyCalculator::calculateBlockEntropies(data, blockSize);

    std::cout << "Analyse du fichier: '" << filePath << "'" << std::endl;
    std::cout << "Taille totale: " << data.size() << " octets" << std::endl;
    std::cout << "Entropie globale de Shannon: " << globalEntropy << std::endl;

    // Affichage des entropies par bloc
    std::cout << "Entropies par bloc (taille du bloc: " << blockSize << ") :" << std::endl;
    for (size_t i = 0; i < blockEntropies.size(); ++i) {
        std::cout << "Bloc " << i+1 << ": " << blockEntropies[i] << std::endl;
    }

    // Détection d'obfuscation ou de compression
    bool isObfuscated = EntropyCalculator::isObfuscatedOrCompressed(blockEntropies);
    if (isObfuscated) {
        std::cout << "\nAttention: Le fichier semble obfusqué ou compressé." << std::endl;
    } else {
        std::cout << "\nLe fichier ne semble pas obfusqué ni compressé." << std::endl;
    }

    return 0;
}