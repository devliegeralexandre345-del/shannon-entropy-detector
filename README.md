# Shannon Entropy Detector

Outil CLI pour le calcul de l'entropie de Shannon par bloc afin de détecter des payloads obfusqués ou compressés.

## Fonctionnalités
- Calcul de l'entropie globale selon la formule de Shannon
- Analyse par blocs (taille configurable)
- Détection automatique d'obfuscation ou compression

## Compilation
```bash
cmake -B build
cd build && cmake --build .
```

## Utilisation
```bash
./shannon_entropy_detector <chemin_fichier>
```

## Exemple de sortie
```
Analyse du fichier: 'exemple.bin'
Taille totale: 1024 octets
Entropie globale de Shannon: 7.89
Entropies par bloc (taille du bloc: 64) :
Bloc 1: 7.5
Bloc 2: 7.9
...
Attention: Le fichier semble obfusqué ou compressé.
```

## Tests unitaires
```bash
cd build && ctest
```