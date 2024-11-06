/*
  Author: Jakub Stavina, UID: --------
  Course: PHYS30762 Programming in C++
  Date: April 28, 2024
  Description: This C++ program defines the UI helper functions for the academic literature catalogue. 
  Dependencies: LiteratureDatabase
*/

#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "LiteratureDatabase.h"
#include<set>
#include<map>
#include <fstream>

// Define the conditions based on which to perform the field-base search: 
bool condition_name(const LiteratureEntry& lit_entry, std::string name);
bool condition_title(const LiteratureEntry& lit_entry, std::string title);
bool condition_type(const LiteratureEntry& lit_entry, std::string type);

const std::set<std::string> valid_commands {"INFO", "PRINT", "QUIT", "DELETE", "EDIT", "ADD", "BIBTEX", "SAVE", "PRICE"};
const std::set<std::string> valid_fields {"ALL", "NAME", "TITLE", "TYPE"};
const std::set<std::string> valid_types {"Book", "Journal", "Thesis"};

enum class Commands {INFO, PRINT, QUIT, DELETE, EDIT, ADD, BIBTEX, SAVE, PRICE};
enum class Fields {ALL, NAME, TITLE, TYPE};
enum class Types {BOOK, JOURNAL, THESIS};

// dictionary between enumerators and strings for Commands
extern std::map<std::string, Commands> string_to_command;
// dictionary between enumerators and strings for Fields
extern std::map<std::string, Fields> string_to_field;
// dictionary between enumerators and strings for Types
extern std::map<std::string, Types> string_to_type;

void print_info();

// Function to answer the question: Is this string among valid commands? 
bool validate_command(std::string str, std::set<std::string> valid_commands);

// Prompt the user to give a command (from among valid commands) and collect it
Commands collect_and_validate_command();

// Prompt the user to give a type (from among valid types) and collect it
Types collect_and_validate_type();

// Prompt the user to give a field (from among valid fields) and collect it
Fields collect_and_validate_field();

// Function to answer the question: Is this integer and is it non-zero? 
bool validate_nonzero_int(std::string str);

// Function to collect a valid non-negative integer
int collect_and_validate_int();

// Function to collect a valid non-negative float
float collect_and_validate_float();

// Function to prompt user if they did not enter 'y' or 'n' and collect valid input
bool collect_and_validate_y_or_n(); // Output false if user inputs 'n', true if 'y'

// A wrapper function for printing a ALL entries of a specified valid type from a database
void type_print(LiteratureDatabase lit_database, Types type);

// A wrapper function for printing ALL entries of a specified valid field from a database
void general_print(LiteratureDatabase& lit_database, Fields field);

// Helper function that spilts a string by a specified delimiter
std::vector<std::string> split_string_(const std::string& str, char delimiter);

// Function for adding a Book, prompts user with questions and collects answers
std::unique_ptr<Book> add_book();

// Function for adding a Journal, prompts user with questions and collects answers
std::unique_ptr<Journal> add_journal();

// Function for adding a Thesis, prompts user with questions and collects answers
std::unique_ptr<Thesis> add_thesis();

// Wrapper function for collection of a new entry of specified type
void add_general_entry(LiteratureDatabase& lit_database, Types type);

// A function which will save a single string to a file of specified name
void save_string_to_file(const std::unique_ptr<std::string>& str_ptr, const std::string& filename);

// Function which prompts the user with y/n questions and lets them change generic aspects of LiteratureEntry objects
void edit_literature_entry(LiteratureDatabase& lit_database, int index);

// Function which prompts the user with y/n questions and lets them change specific aspects of Book objects
void edit_book(LiteratureDatabase& lit_database, int index);

// Function which prompts the user with y/n questions and lets them change specific aspects of Thesis objects
void edit_thesis(LiteratureDatabase& lit_database, int index);

// Function which prompts the user with y/n questions and lets them change specific aspects of Thesis objects
void edit_journal(LiteratureDatabase& lit_database, int index);

// Wrapper function which prompts the user with y/n questions and lets them change specific aspects of object of specified type
void edit_entry(LiteratureDatabase& lit_database, int index);

// Wrapper function for execution of any specified command from among valid commands
bool execute_command(LiteratureDatabase& lit_database, Commands command);

#endif
