/*
  Author: Jakub Stavina, UID: --------
  Course: PHYS30762 Programming in C++
  Date: April 24, 2024
  Description: This C++ program defines the 'Journal' class. 
  Dependencies: Journal is a derived class of the LiteratureEntry class.
*/

#ifndef JOURNAL_H
#define JOURNAL_H

#include "LiteratureEntry.h"
#include <vector>
#include <memory>

// Define the Journal class
class Journal : public LiteratureEntry
{
private:
  float impact_factor{0.0};
  std::string scope{""};
  int number_volumes{0};

public:
  // Constructors
  Journal() = default;
  Journal(const std::string& title, std::unique_ptr<std::vector<std::string>> names, int year, const float impact_factor, const std::string scope, int number_volumes);

  // Destructor
  ~Journal() override {}

  // Implementation of clone function for Journal
  std::unique_ptr<LiteratureEntry> clone() const override 
  {
    return std::make_unique<Journal>(*this);
  }

  // Accessors
  std::string get_type() const override {return "Journal";}
  float get_impact_factor() const {return impact_factor;}
  std::string get_scope() const {return scope;}
  int get_number_volumes() const {return number_volumes;}
  std::string get_encoding() const override;

  // Mutators
  void set_impact_factor(float impact_factor) {this->impact_factor = check_nonnegative(impact_factor, "Impact factor");}
  void set_scope(const std::string scope) {this->scope = scope;}
  void set_number_volumes(int number_volumes) {this->number_volumes = check_nonnegative(number_volumes, "Number of volumes");}

  // Printing
  void print_data() const override;
};

#endif // JOURNAL_H
