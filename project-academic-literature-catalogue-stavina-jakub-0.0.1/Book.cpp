/*
  Author: Jakub Stavina, UID: --------
  Course: PHYS30762 Programming in C++
  Date: April 24, 2024
  Description: This C++ program implements the 'Book' class. 
  Dependencies: Book is a derived class of the LiteratureEntry class.
*/

#include "Book.h"

// Parametrized constructor
Book::Book(const std::string& title, std::unique_ptr<std::vector<std::string>> names, int year, const std::string& publisher, const std::string& subject, float price)
: LiteratureEntry(title, std::move(names), year), publisher(publisher), subject(subject)
{
  this->price = check_nonnegative(price, "Price");
}

// Printing
void Book::print_data() const
{
  std::cout << "BOOK:" << std::endl;
  LiteratureEntry::print_data();
  std::cout << "Publisher    : " << publisher << ", " << std::endl;
  std::cout << "Subject      : " << subject << ", " << std::endl;
  std::cout << "Price        : " << price << ", " << std::endl;
}

// Printing entry in BibTeX style
void Book::print_bibtex() const
{
  std::cout << "@Book{citekey" << std::endl;
  std::cout << "author    = \"";
  for (auto it = names->begin(); it != names->end(); ++it) // Iterate over authors, separate by "and"
  {
    if (std::next(it) != names->end()) {std::cout << *it << " and ";}
    else {std::cout << *it << "\"," << std::endl;} // Do not print "and" after the finak author, add endline
  }
  std::cout << "title     = \"" << title << "\"," << std::endl;
  std::cout << "publisher = \"" << publisher << "\"," << std::endl;
  std::cout << "year      = \"" << year << "\" " << std::endl;
  std::cout << "}" << std::endl;
}

// Get encoding in the appropriate style for the database .dat document
std::string Book::get_encoding() const
{
  std::string return_str{"BOOK\n" + title + "\n"};
  for (auto it = names->begin(); it != names->end(); ++it) // Use iterators to get authors, separate ba ";"
  {
    if (std::next(it) != names->end()) {return_str += *it + ";";}
    else {return_str +=  *it + "\n";} // Do not print ";" after the finak author, add endline
  }
  // Get rest of the information
  return_str += std::to_string(year) + "\n" + publisher + "\n" + subject + "\n" + std::to_string(price) + "\n";
  return return_str;
}