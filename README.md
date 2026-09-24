# Hades\_Town

Serveur web léger écrit en **C++**, supportant uniquement les méthodes HTTP **GET** et **HEAD**.

## Description

Hades\_Town est un serveur HTTP minimaliste conçu pour être simple, rapide et facile à comprendre. Il accepte les connexions entrantes, analyse les requêtes HTTP et y répond en implémentant :

- **GET** — renvoie le corps de la ressource demandée (fichiers statiques).
- **HEAD** — renvoie les mêmes en-têtes que `GET`, mais sans le corps de la réponse.

Toute autre méthode renvoie une erreur **405 Method Not Allowed** ou **501 Not Implemented**.

## Fonctionnalités

- Réponses HTTP/1.1 conformes pour `GET` et `HEAD`
- Gestion des codes d'erreur courants (`200`, `404`, `405`, …)
- Servir des fichiers statiques depuis un répertoire racine
- Code C++ modulaire

## Compilation

```bash
make
```

## Utilisation

```bash
./hades_town [port] [répertoire_racine]
# Exemple :
./hades_town 8080 ./www
```

Le serveur écoute ensuite sur le port indiqué et sert les fichiers du répertoire racine.

## Structure du projet

```text
Hades_Town/
├── include/    # Fichiers d'en-tête (.hpp)
├── src/        # Code source C++
└── Makefile
```
