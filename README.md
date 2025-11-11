# 📚 C++ Multimedia Library Management System Project

> Application console pour la gestion des médias (livres, vidéos, audios), incluant l'inventaire, les emprunts, les retours et la production de statistiques.

---

## 🎯 Objectif Général

Développer une application C++ en mode console pour gérer une bibliothèque multimédia. Le projet vise à maîtriser les concepts avancés de la POO (Programmation Orientée Objet).

## ✨ Fonctionnalités Clés

* **CRUD Médias:** Ajouter, modifier, supprimer et consulter les médias (Livres, Vidéos, Audios).
* **Recherche et Tri:** Recherche par titre/type et tri de la collection.
* **Gestion des Flux:** Contrôle de disponibilité, gestion des emprunts et des retours.
* **Statistiques Audiovisuelles:** Calcul de la durée totale et moyenne pour les contenus audiovisuels (Vidéos et Audios).
* **Rapports:** Export de rapports synthétiques au format texte (.txt).

---

## ⚙️ Aspects Techniques (POO et C++)

Le projet est strictement basé sur les concepts POO suivants:

| Concept POO | Implémentation |
| :--- | :--- |
| **Héritage** | Classe de base `Media` et classes dérivées `Livre`, `Audio`, `Video`. Option d'héritage multiple pour `LivreAudio`. |
| **Polymorphisme** | Utilisé pour l'affichage (`afficher()`) et le calcul des statistiques. |
| **Surcharge** | Surcharge des opérateurs de comparaison (`<`, `==`). |
| **Smart Pointers** | Utilisation de `unique_ptr` ou `shared_ptr` pour la gestion mémoire. |
| **Collections** | Utilisation de `vector` ou `list`.
| **Fichiers** | Gestion des fichiers pour la persistance des données (sauvegarde et chargement).

---

## 🚀 Planning & Livrables

Ce projet suit les jalons communs définis pour l'année universitaire 2025-2026.

| Période | Livrable |
| :--- | :--- |
| **Novembre 2025** | **Prototype:** Squelette des classes de base + menus. |
| **Décembre 2025** | **Version Alpha:** Fonctionnalités principales + gestion des fichiers. |
| **Janvier 2026** | **Version Finale:** Statistiques, robustesse (exceptions), nettoyage et documentation. |
| **Fin Janvier 2026** | **Soutenance:** Démonstration et rapport final (3-5 pages). |

## 🛠️ Configuration

* **Langage:** C++ (Standard C++11 minimum)
* **Environnement:** Console-based (sans interface graphique)
