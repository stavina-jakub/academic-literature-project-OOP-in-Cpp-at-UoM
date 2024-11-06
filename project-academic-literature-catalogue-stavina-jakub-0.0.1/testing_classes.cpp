/*
  Author: Jakub Stavina, UID: --------
  Course: PHYS30762 Programming in C++
  Date: April 24, 2024
  Description: This C++ program tests the classes Book, Thesis, Journal. 
  Dependencies: LiteratureEntry, Book, Thesis, Journal
  Compilation: g++-11 -std=c++17 -fdiagnostics-color=always -g ./testing_classes.cpp ./LiteratureEntry.cpp ./Book.cpp ./Journal.cpp ./Thesis.cpp -o ./testing_classes
*/

#include "LiteratureEntry.h"
#include "Book.h"
#include "Journal.h"
#include "Thesis.h"

int main()
{
    auto vector_ptr = std::make_unique<std::vector<std::string>>();
    vector_ptr->push_back("Name Surename 1");
    vector_ptr->push_back("Name Surename 2");

    auto vector_ptr_2 = std::make_unique<std::vector<std::string>>();
    vector_ptr_2->push_back("Editor Name 1");
    vector_ptr_2->push_back("Editor Name 2");

    Thesis thesis_1("Thesis title", std::move(vector_ptr), 1998, "UoM", std::move(vector_ptr_2));
    Thesis thesis_2 = thesis_1;

    thesis_1.print_data();
    thesis_2.print_data();

    Thesis thesis_3 = std::move(thesis_1);

    thesis_3.print_bibtex();
    thesis_2.print_bibtex();

    return 0;
}
