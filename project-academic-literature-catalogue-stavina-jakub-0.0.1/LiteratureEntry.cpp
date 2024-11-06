/*
  Author: Jakub Stavina, UID: --------
  Course: PHYS30762 Programming in C++
  Date: April 24, 2024
  Description: This C++ program implements the 'LiteratureEntry' class. 
*/

#include "LiteratureEntry.h"

// Constructors
// Parametrized constructor
LiteratureEntry::LiteratureEntry(const std::string& title, std::unique_ptr<std::vector<std::string>> names, int year)
  : title(title), names(std::move(names))
{
  // Input validation for year
  this->year = check_nonnegative(year, "Year");
}

// Copy constructor, deep copy of names
LiteratureEntry::LiteratureEntry(const LiteratureEntry& other) 
: title(other.title), year(other.year), names(std::make_unique<std::vector<std::string>>(*other.names)) {}

// Move constructor
LiteratureEntry::LiteratureEntry(LiteratureEntry&& other) noexcept 
  : title(std::move(other.title)), names(std::move(other.names)), year(std::move(other.year))
{
  // Define behaviour for the "other"
  other.title = "";
  other.year = 0;
  other.names = nullptr;
}

// Assignment operators
// Copy assignment 
LiteratureEntry& LiteratureEntry::operator=(const LiteratureEntry& other) 
{
  if (this != &other) 
  {
    title = other.title;
    year = other.year;
    // Deep copy of names
    names = nullptr;
    names = std::make_unique<std::vector<std::string>>(*other.names);
  }
  return *this;
}

// Move assignment
LiteratureEntry& LiteratureEntry::operator=(LiteratureEntry&& other) noexcept 
{
  if (this != &other) 
  {
    title = std::move(other.title);
    names = std::move(other.names);
    year = other.year;
    // Define behaviour for the "other": 
    other.title = ""; 
    other.year = 0;  
    other.names = nullptr; 
  }
  return *this;
}

// Accessors
std::vector<std::string> LiteratureEntry::get_names() const {return *names;}

bool LiteratureEntry::is_name(const std::string& name) const 
{
  if (!names) {return false;} // Handle case where the unique pointer is null
  const std::vector<std::string>* vec_raw_ptr = names.get(); // Use get() to access the raw pointer to the vector
  auto iter = std::find(vec_raw_ptr->begin(), vec_raw_ptr->end(), name); // Use std::find to search for the entry in the vector
  return iter != vec_raw_ptr->end(); // If iterator is not equal to end, entry is found
}

// Mutators
void LiteratureEntry::add_name(const std::string& name) {names->push_back(name);}

void LiteratureEntry::remove_name(const std::string& name) 
{
  // erase the name to be removed from the end of the vector
  names->erase(std::remove_if(names->begin(), // move the name to be removed to the end
                              names->end(),
                              // lambda function to identify the name to be removed
                              [&](const std::string& name_) {return name_ == name;}),  
               names->end());
}

void LiteratureEntry::set_year(int year) {this->year = check_nonnegative(year, "Year");}

// Printing
void LiteratureEntry::print_data() const 
{
  // Print Title, Authors and Year
  std::cout << "Title        : " << title << ", " << std::endl;
  std::cout << "Authors      : ";
  for (const auto& name_ptr : *names) // Loop over authors - print separated by ";"
  {
    std::cout << name_ptr << "; ";
  }
  std::cout << std::endl;
  std::cout << "Year         : " << year << std::endl;
}

