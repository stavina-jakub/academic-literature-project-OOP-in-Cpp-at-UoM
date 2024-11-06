/*
  Author: Jakub Stavina, UID: --------
  Course: PHYS30762 Programming in C++
  Date: April 24, 2024
  Description: This C++ program implements the 'Thesis' class. 
  Dependencies: Thesis is a derived class of the LiteratureEntry class.
*/

#include "Thesis.h"

// Parametrized constructor for Thesis
Thesis::Thesis(const std::string& title, std::unique_ptr<std::vector<std::string>> names, int year, const std::string& university, std::unique_ptr<std::vector<std::string>> supervisors)
: LiteratureEntry(title, std::move(names), year), university(university), supervisors(std::move(supervisors)) {}

// Copy constructor
Thesis::Thesis(const Thesis& other) : LiteratureEntry(other), university(other.university) 
{
  // Deep copy of supervisors
  supervisors = nullptr; // Clear existing supervisors
  supervisors = std::make_unique<std::vector<std::string>>(*other.supervisors);
}

// Move constructor
Thesis::Thesis(Thesis&& other) noexcept 
  : LiteratureEntry(std::move(other)), supervisors(std::move(other.supervisors)), university(std::move(other.university)) 
{
  // Define behaviour for the "other"
  other.university = "";
  other.supervisors = nullptr;
}

// Copy assignment operator
Thesis& Thesis::operator=(const Thesis& other) 
{
  if (this != &other) // Check for self-reference
  {
    LiteratureEntry::operator=(other);
    university = other.university;

    supervisors = nullptr; // Clear existing supervisors
    supervisors = std::make_unique<std::vector<std::string>>(*other.supervisors); // Deep copy of supervisors
  }
  return *this;
}

// Move assignment operator
Thesis& Thesis::operator=(Thesis&& other) noexcept
{
  if (this != &other) 
  {
    // Steal the "other"'s data members: 
    LiteratureEntry::operator=(std::move(other));
    university = std::move(other.university);

    // Define behaviour for the "other"
    other.university = ""; 
    other.supervisors = nullptr;
  }
  return *this;
}

void Thesis::add_supervisor(const std::string& supervisor)
{
  supervisors->push_back(supervisor);
}

void Thesis::remove_supervisor(const std::string& supervisor)
{
  // erase the supervisor to be removed from the end of the vector
  supervisors->erase(std::remove_if(supervisors->begin(), // move the supervisor to be removed to the end
                                   supervisors->end(),
                                   // lambda function to identify the supervisor to be removed
                                   [&](const std::string& name_) {return name_ == supervisor;}),
              supervisors->end());
}

// Printing
void Thesis::print_data() const
{
  std::cout << "THESIS:" << std::endl;
  LiteratureEntry::print_data();
  std::cout << "Supervisors  : ";
  for (const auto& supervisor : *supervisors) // Loop over supervisors
  {
    std::cout << supervisor << "; "; // Separate by ";"
  }
  std::cout << std::endl << "University   : " << university << ", " << std::endl;
}

// Print in BibTeX-style
void Thesis::print_bibtex() const
{
  std::cout << "@phdthesis{citekey," << std::endl;
  std::cout << "author    = \"";
  for (auto it = names->begin(); it != names->end(); ++it) // Use iterators to loop over names
  {
    if (std::next(it) != names->end()) {std::cout << *it << " and ";} // Separate names by "and"
    else {std::cout << *it;}
  }
  std::cout << "\" " << std::endl; // Print the rest of the info
  std::cout << "title     = \"" << title << "\" " << std::endl;
  std::cout << "school    = \"" << university << "\" " << std::endl;
  std::cout << "year      = \"" << year << "\" " << std::endl;
  std::cout << "}" << std::endl;
}

// Output the Thesis encoded in the style of the .dat database document
std::string Thesis::get_encoding() const
{
  std::string return_str{"THESIS\n" + title + "\n"};
  for (auto it = names->begin(); it != names->end(); ++it) // Use iterators to loop over names
  {
    if (std::next(it) != names->end()) {return_str += *it + ";";} // Separate by ";"
    else {return_str +=  *it + "\n";} // Final name 
  }
  return_str += std::to_string(year) + "\n" + university + "\n";
  for (auto it = supervisors->begin(); it != supervisors->end(); ++it) // Use iterators to loop over supervisors
  {
    if (std::next(it) != supervisors->end()) {return_str += *it + ";";} // Separate by ";"
    else {return_str +=  *it + "\n";} // Final supervisor 
  }
  return return_str;
}