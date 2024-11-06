/*
  Author: Jakub Stavina, UID: --------
  Course: PHYS30762 Programming in C++
  Date: April 24, 2024
  Description: This C++ program defines the 'LiteratureEntry' class. 
*/

#ifndef LITERATUREENTRY_H
#define LITERATUREENTRY_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

// Defining LiteratureEntry class - NOTE: this class is purely virtual!
class LiteratureEntry 
{
protected:
  std::string title {""};
  std::unique_ptr<std::vector<std::string>> names {nullptr};
  int year {0};

public:
  // Constructors
  LiteratureEntry() = default; // Default constructor
  LiteratureEntry(const std::string& title, std::unique_ptr<std::vector<std::string>> names, int year); // Parametrized constructor
  LiteratureEntry(const LiteratureEntry& other); // Copy constructor
  LiteratureEntry(LiteratureEntry&& other) noexcept; // Move constructor

  // Destructor
  virtual ~LiteratureEntry() {}

  // Assignment operators
  virtual LiteratureEntry& operator=(const LiteratureEntry& other); // Copy assignment operator
  virtual LiteratureEntry& operator=(LiteratureEntry&& other) noexcept; // Move assignment operator

  // Pure virtual functions
  virtual std::unique_ptr<LiteratureEntry> clone() const = 0;
  virtual std::string get_type() const = 0;
  // Get encoding of the object in the same style as the database .dat file
  virtual std::string get_encoding() const = 0; 

  // Accessors
  std::string get_title() const {return title;}
  std::vector<std::string> get_names() const;
  bool is_name(const std::string& name) const; // Check if particular string is among the names
  int get_year() const {return year;}
  bool is_older_than(int year) const {return this->year < year;}
  
  // Mutators
  void set_title(const std::string& title) {this->title = title;}
  void add_name(const std::string& name);
  void remove_name(const std::string& name);
  void set_year(int year);

  // Printing
  virtual void print_data() const;
  // Input validation helper function template
  template<typename T> friend T check_nonnegative(T value, const std::string& value_name);
};

// IMplementation of the input validation helper function template
template<typename T> T check_nonnegative(T value, const std::string& value_name) {
  if (value < 0.0)
  {
    throw std::invalid_argument(value_name + " must be a non-negative value.");
  }
  return value;
}

#endif // LITERATUREENTRY_H
