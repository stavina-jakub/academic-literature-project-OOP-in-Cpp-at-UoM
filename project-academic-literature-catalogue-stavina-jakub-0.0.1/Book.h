/*
  Author: Jakub Stavina, UID: --------
  Course: PHYS30762 Programming in C++
  Date: April 24, 2024
  Description: This C++ program defines the 'Book' class. 
  Dependencies: Book is a derived class of the LiteratureEntry class.
*/

#ifndef BOOK_H
#define BOOK_H

#include "LiteratureEntry.h"

// Defining Book class
class Book : public LiteratureEntry
{
private:
  std::string publisher{""};
  std::string subject{""};
  float price{0.0};

public:
  // Constructors
  Book() = default;
  // Parametrized constructor: 
  Book(const std::string& title, std::unique_ptr<std::vector<std::string>> names, int year, const std::string& publisher, const std::string& subject, float price);

  // Destructor
  ~Book() override {}

  // Implementation of clone function for Book
  std::unique_ptr<LiteratureEntry> clone() const override 
  {
    return std::make_unique<Book>(*this);
  }

  // Accessors
  std::string get_type() const override {return "Book";}
  std::string get_publisher() const {return publisher;}
  std::string get_subject() const {return subject;}
  float get_price() const {return price;}
  std::string get_encoding() const override; // Encode the object for database .dat file

  // Mutators
  void set_publisher(const std::string& publisher) {this->publisher = publisher;}
  void set_subject(const std::string& subject) {this->subject = subject;}
  void set_price(float price) 
  { 
    this->price = check_nonnegative(price, "Price");
  }

  // Printing
  void print_data() const override;
  void print_bibtex() const;

  // Additional method
  bool is_cheaper_than(float price) const {return this->price < price;}
};

#endif // BOOK_H
