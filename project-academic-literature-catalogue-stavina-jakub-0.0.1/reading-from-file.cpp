/*
  Author: Jakub Stavina, UID: --------
  Course: PHYS30762 Programming in C++
  Date: April 27, 2024
  Description: This C++ program reads the academic literature database and prints it. 
  Dependencies: LiteratureEntry, Book, Thesis, Journal
  Compilation: g++-11 -std=c++17 -fdiagnostics-color=always -g ./reading-from-file.cpp ./LiteratureEntry.cpp ./Book.cpp ./Journal.cpp ./Thesis.cpp -o ./reading-from-file
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


// Function to split a string by a delimiter
std::vector<std::string> split(const std::string& s, char delimiter) 
{
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {tokens.push_back(token);}
  return tokens;
}

int main() 
{
  std::vector<std::unique_ptr<LiteratureEntry>> entries;

  try 
  {
    // Open the input file stream
    std::ifstream file("literature-database.dat");

    // Check if the file was opened successfully
    if (!file.is_open()) 
    {
      throw std::runtime_error("Failed to open the input file.");
    }

    std::string line;

    while (std::getline(file, line)) 
    {
      if (line == "BOOK") 
      {
        std::vector<std::string> data(6);
        for (auto& str : data) {std::getline(file, str);}
        auto authors = std::make_unique<std::vector<std::string>>(split(data[1], ';'));
        entries.push_back(std::make_unique<Book>(data[0], std::move(authors), std::stoi(data[2]), data[3], data[4], std::stof(data[5])));
      }
      
      else if (line == "JOURNAL") 
      {
        std::vector<std::string> data(6);
        for (auto& str : data) {std::getline(file, str);}
        auto authors = std::make_unique<std::vector<std::string>>(split(data[1], ';'));
        entries.push_back(std::make_unique<Journal>(data[0], std::move(authors), std::stoi(data[2]),  std::stof(data[3]), data[4], std::stoi(data[5])));
      }

      else if (line == "THESIS") 
      {
        std::vector<std::string> data(5);
        for (auto& str : data) {std::getline(file, str);}
        auto authors = std::make_unique<std::vector<std::string>>(split(data[1], ';'));
        auto supervisors = std::make_unique<std::vector<std::string>>(split(data[4], ';'));
        entries.push_back(std::make_unique<Thesis>(data[0], std::move(authors), std::stoi(data[2]), data[3], std::move(supervisors)));
      }
    }

    // Close the file stream after reading
    file.close();
    } 
    
    catch (const std::exception& e) 
    {
      std::cerr << "Error: " << e.what() << std::endl;
      return 1; // Return error code
    }

  // Print the entries
  std::cout<<std::endl;
  for (const auto& entry : entries) 
  {
    entry->print_data();
    std::cout<<std::endl;
  }

  return 0;
}
