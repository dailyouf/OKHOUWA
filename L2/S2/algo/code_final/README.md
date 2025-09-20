# README

Ce projet contient plusieurs implémentations de l'algorithme de multiplication de chaînes de matrices :

* Backtracking non optimisé
* Backtracking optimisé (avec énumération et tri des solutions)
* Programmation dynamique
* Trois variantes gloutonnes

Quatre scripts Shell sont fournis pour compiler, exécuter et comparer les performances sur différents jeux de données :

---

## 1. Prérequis

* Un compilateur C (gcc ou clang).
* Un shell Unix (bash).

---

## 2. Compilation et exécution générale

Tous les scripts prennent en charge :

1. La compilation automatique de tous les binaires.
2. L'exécution sur un jeu de matrices pseudo‑aléatoires.
3. La comparaison des temps d'exécution entre les algorithmes.

### 2.1. `./run`

```bash
./run
```

* Compile les programmes :

  * `solve_backtracking.c`
  * `solve_backtracking_optimisé.c`
  * `solve_dp.c`
  * `solve_greedy1.c`, `solve_greedy2.c`, `solve_greedy3.c`
* Génère des instances entièrement pseudo‑aléatoires de tailles variées.
* Exécute tous les algorithmes sur ces instances.
* Affiche un tableau comparatif des temps CPU.

  ```
  Heuristique, EcartsMoyen, %Espace
  greedy1, …, …
  greedy2, …, …
  greedy3, …, …
  ```

### 2.2. `./run_10`

```bash
./run_10
```

Même comportement que `./run`, mais **toutes** les instances sont des chaînes de matrices de longueur **10**.

### 2.3. `./run_inc`

```bash
./run_inc
```

Même comportement que `./run`, mais génère des instances dont la taille de la chaîne est **croissante** .

### 2.4. `./run_dec`

```bash
./run_dec
```

Même comportement que `./run`, mais génère des instances dont la taille de la chaîne est **décroissante** .

---

## 3. Structure des scripts

Chaque script suit ces étapes :

1. **compilation** : `gcc -O2 -o solve_backtracking_naif solve_backtracking_naif.c`, etc.
2. **génération** : appel d’un petit générateur en ligne de commande ou fonction interne pour produire les fichiers d’instances.
3. **exécution** : boucle sur chaque exécutable avec redirection des sorties.
5. **comparaison** : collecte des temps (via `time` ou `clock()` intégré) et affichage résumé.

---

## 4. Exemple d’utilisation

```bash
# Rendre les scripts exécutables
chmod u+x run run_10 run_inc run_dec

# Lancer la comparaison complète
./run

# Lancer uniquement sur taille 10
./run_10

# Lancer sur taille croissante
./run_inc

# Lancer sur taille décroissante
./run_dec
```

---


