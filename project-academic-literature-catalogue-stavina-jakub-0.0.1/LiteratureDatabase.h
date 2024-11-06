/*
  Author: Jakub Stavina, UID: --------
  Course: PHYS30762 Programming in C++
  Date: April 24, 2024
  Description: This C++ program defines the 'LiteratureDatabase' class. 
  Dependencies: LiteratureDatabase contains objects of the class LiteratureEntry and its derived classes Book, Journal and Thesis.
*/

#ifndef LITERATURE_DATABASE_H
#define LITERATURE_DATABASE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <sstream>
#include "LiteratureEntry.h"
#include "Book.h"
#include "Journal.h"
#include "Thesis.h"


class LiteratureDatabase 
{
  private:
    std::vector<std::unique_ptr<LiteratureEntry>> entries;
    // Function to split a string by a delimiter
    static std::vector<std::string> split(const std::string& s, char delimiter);

  public:
    // Default constructor
    LiteratureDatabase() = default;
    // Destructor
    ~LiteratureDatabase() = default;
    // Copy constructor
    LiteratureDatabase(const LiteratureDatabase& other);
    // Move constructor
    LiteratureDatabase(LiteratureDatabase&& other) noexcept;
    // Copy assignment operator
    LiteratureDatabase& operator=(const LiteratureDatabase& other);
    // Move assignment operator
    LiteratureDatabase& operator=(LiteratureDatabase&& other) noexcept;
    // Parametrized constructor taking a file name
    explicit LiteratureDatabase(const std::string& filename);

    // Function to print all the entries in the database
    void print_all_entries() const;
    // Function to print the entries satisfying a specific condition
    void print_condition_entries(bool (*condition)(const LiteratureEntry&, std::string), std::string args) const;
    // Function to print entry by index
    void print_entry(int index) const{entries[index]->print_data();}
    // Function to print bibtex entry by index
    void print_bibtex(int index) const;

    // Function to remove an entry by index
    void remove_entry(int index);
    // Function to insert a new entry
    void insert_entry(std::unique_ptr<LiteratureEntry> entry);

    // Mutators
    void add_name(int index, std::string name) {entries[index]->add_name(name);}
    void remove_name(int index, std::string name) {entries[index]->remove_name(name);}
    void set_title(int index, std::string title) {entries[index]->set_title(title);}
    void set_year(int index, int year) {entries[index]->set_year(year);}

    void set_publisher(int index, std::string publisher);
    void set_subject(int index, std::string subject);
    void set_price(int index, float price);

    void set_impact_factor(int index, float impact_factor);
    void set_scope(int index, std::string scope);
    void set_number_volumes(int index, int number_volumes);

    void set_university(int index, std::string university);
    void add_supervisor(int inde, std::string supervisor);
    void remove_supervisor(int index, std::string supervisor);

    // Accessor-like functions
    float get_average_book_price();
    int get_number_entries() {return entries.size();}
    // Get encoding of the entire catalogue in the appropriate style
    std::unique_ptr<std::string> get_encoded_data(); 
    std::string get_type(int index) {return entries[index]->get_type();} // Outputs: "Book", "Journal" or "Thesis"
};

#endif // LITERATURE_DATABASE_H
