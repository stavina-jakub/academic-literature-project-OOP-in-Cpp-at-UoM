/*
  Author: Jakub Stavina, UID: --------
  Course: PHYS30762 Programming in C++
  Date: April 24, 2024
  Description: This C++ program defines the 'Thesis' class. 
  Dependencies: Thesis is a derived class of the LiteratureEntry class.
*/

#ifndef THESIS_H
#define THESIS_H

#include "LiteratureEntry.h"

// Defining Thesis class
class Thesis : public LiteratureEntry
{
private:
  std::string university{""};
  std::unique_ptr<std::vector<std::string>> supervisors{nullptr};

public:
  // Constructors
  Thesis() = default;
  // Parametrized constructor
  Thesis(const std::string& title, std::unique_ptr<std::vector<std::string>> names, int year, const std::string& university, std::unique_ptr<std::vector<std::string>> supervisors);
  Thesis(const Thesis& other); // Copy constructor
  Thesis(Thesis&& other) noexcept; // Move constructor

  // Destructor
  ~Thesis() override {}

  // Implementation of clone function for Thesis
  std::unique_ptr<LiteratureEntry> clone() const override 
  {
    return std::make_unique<Thesis>(*this);
  }

  // Assignment operators
  Thesis& operator=(const Thesis& other); // Copy assignment operator
  Thesis& operator=(Thesis&& other) noexcept; // Move assignment operator

  // Accessors
  std::string get_type() const override {return "Thesis";}
  std::string get_university() const {return university;}
  std::vector<std::string> get_supervisors() const;
  std::string get_encoding() const override;
    
  // Mutators
  void set_university(const std::string& university) {this->university = university;}
  void add_supervisor(const std::string& supervisor);
  void remove_supervisor(const std::string& supervisor);

  // Printing
  void print_data() const override;
  void print_bibtex() const;
};

#endif // THESIS_H

