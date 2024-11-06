/*
  Author: Jakub Stavina, UID: --------
  Course: PHYS30762 Programming in C++
  Date: April 28, 2024
  Description: This C++ program tests the LiteratureDatabase class. 
  Dependencies: LiteratureEntry, Book, Thesis, Journal, LiteratureDatabase
  Compilation: g++-11 -std=c++17 -fdiagnostics-color=always -g ./testing_lit_database.cpp ./LiteratureEntry.cpp ./Book.cpp ./Journal.cpp ./Thesis.cpp ./LiteratureDatabase.cpp -o ./testing_lit_database
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <sstream>
#include "LiteratureEntry.h"
#include "Book.h"    // Book    (title, names, year, publisher    , subject    , price         )
#include "Journal.h" // Journal (title, names, year, impact_factor, scope      , number_volumes)
#include "Thesis.h"  // Thesis  (title, names, year, university   , supervisors                )
#include "LiteratureDatabase.h"

bool condition_name(const LiteratureEntry& lit_entry, std::string name){return lit_entry.is_name(name);}
bool condition_title(const LiteratureEntry& lit_entry, std::string title){return lit_entry.get_title() == title;}
bool condition_type(const LiteratureEntry& lit_entry, std::string type){return lit_entry.get_type() == type;}

int main() 
{
  std::string database_name{"literature-database.dat"};

  try 
  {
    LiteratureDatabase lit_database(database_name);
    lit_database.print_condition_entries(condition_type, "Book");
    std::cout<<"Average Book Price: "<<lit_database.get_average_book_price()<<std::endl;
  }

  catch (const std::exception& e) 
  {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
