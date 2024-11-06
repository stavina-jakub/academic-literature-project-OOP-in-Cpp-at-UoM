# Academic Literature Catalogue

## Overview
This project is an academic literature catalogue implemented in C++ for the PHYS30762 Object-Oriented Programming in C++ 2023-24 2nd Semester. It allows users to manage and interact with a database of literature entries, including books, journals, and theses.

## Compilation
To compile the project, use the following command:

```
g++-11 -std=c++17 -fdiagnostics-color=always -g ./acad-lit-catalogue.cpp ./LiteratureEntry.cpp ./Book.cpp ./Journal.cpp ./Thesis.cpp ./LiteratureDatabase.cpp ./user-interface-functions.cpp -o ./acad-lit-catalogue
```

## Usage
After compiling, execute the compiled binary `acad-lit-catalogue` to run the program. The program provides a user interface for interacting with the literature catalogue. Users can add new entries, search for existing ones, modify entries, and delete entries as needed.

## Files
- `acad-lit-catalogue.cpp`: Main program file containing the entry point and user interface functions.
- `LiteratureEntry.cpp`: Implementation file for the base class `LiteratureEntry`.
- `Book.cpp`: Implementation file for the `Book` class, derived from `LiteratureEntry`.
- `Journal.cpp`: Implementation file for the `Journal` class, derived from `LiteratureEntry`.
- `Thesis.cpp`: Implementation file for the `Thesis` class, derived from `LiteratureEntry`.
- `LiteratureDatabase.cpp`: Implementation file for the `LiteratureDatabase` class responsible for managing the collection of literature entries.
- `user-interface-functions.cpp`: Implementation file containing functions for user interaction and input/output operations.

## Contributors
- Jakub Šťavina

## License
