/*
  Author: Jakub Stavina, UID: --------
  Course: PHYS30762 Programming in C++
  Date: April 24, 2024
  Description: This C++ program implements the 'Journal' class. 
  Dependencies: Journal is a derived class of the LiteratureEntry class.
*/

#include "Journal.h"

// Parametrized constructor
Journal::Journal(const std::string& title, std::unique_ptr<std::vector<std::string>> names, int year, const float impact_factor, const std::string scope, int number_volumes)
: LiteratureEntry(title, std::move(names), year), scope(scope)
{
  // Input validation
  this->impact_factor = check_nonnegative(impact_factor, "Impact factor");
  this->number_volumes = check_nonnegative(number_volumes, "Number of volumes");
}

// Printing
void Journal::print_data() const
{
  std::cout << "JOURNAL:" << std::endl;
  std::cout << "Title        : " << title << ", " << std::endl;
  std::cout << "Editors      : ";
  for (const auto& name_ptr : *names) // Loop over names
  {
    std::cout << name_ptr << "; "; // Separate by ";"
  }
  std::cout << std::endl;
  std::cout << "Founded in   : " << year << std::endl;
  std::cout << "Impact fact. : " << impact_factor << ", " << std::endl;
  std::cout << "Num. of vol. : " << number_volumes << ", " << std::endl;
  std::cout << "Scope        : " << scope << ", " << std::endl;
}

// Output encoding in the style of the database .dat coument
std::string Journal::get_encoding() const
{
  std::string return_str{"JOURNAL\n" + title + "\n"};
  for (auto it = names->begin(); it != names->end(); ++it) // Use iterators to loop over names
  {
    if (std::next(it) != names->end()) {return_str += *it + ";";} // Separate names by ";"
    else {return_str +=  *it + "\n";} // The final name
  }
  // Output the rest of the info, convert numbers to strings
  return_str += std::to_string(year) + "\n" + std::to_string(impact_factor) + "\n" + scope + "\n" + std::to_string(number_volumes) + "\n";
  return return_str;
}