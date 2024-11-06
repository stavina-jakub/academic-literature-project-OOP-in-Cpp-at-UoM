/*
  Author: Jakub Stavina, UID: --------
  Course: PHYS30762 Programming in C++
  Date: April 24, 2024
  Description: This C++ program implements the UI for the academic literature catalogue. 
  Dependencies: LiteratureEntry, Book, Thesis, Journal, LiteratureDatabase and user-interface-functions
  Compilation: g++-11 -std=c++17 -fdiagnostics-color=always -g ./acad-lit-catalogue.cpp ./LiteratureEntry.cpp ./Book.cpp ./Journal.cpp ./Thesis.cpp ./LiteratureDatabase.cpp ./user-interface-functions.cpp -o ./acad-lit-catalogue
*/

#include "LiteratureDatabase.h"
#include "user-interface-functions.h"

int main() 
{
  std::string database_name;
  std::cout<<"Please enter the database file name: "; // Prompt user to input database name
  std::getline(std::cin, database_name);
  // std::string database_name{"literature-database.dat"}; // Hardcoded database name

  try 
  {
    LiteratureDatabase lit_database(database_name); // Initialize and load the database
    bool proceed{true};
    
    print_info();
    while(proceed)
    {
      // Collect any commands from the user, execute the commands
      proceed = execute_command(lit_database, collect_and_validate_command()); 
    }
  }
  catch (const std::exception& e) 
  {
    // Catch exceptions in file loading
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
