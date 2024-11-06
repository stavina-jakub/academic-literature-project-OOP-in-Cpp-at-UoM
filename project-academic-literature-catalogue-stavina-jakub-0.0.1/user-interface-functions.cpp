/*
  Author: Jakub Stavina, UID: --------
  Course: PHYS30762 Programming in C++
  Date: April 29, 2024
  Description: This C++ program implements the UI helper functions for the academic literature catalogue. 
  Dependencies: LiteratureDatabase
*/

#include "user-interface-functions.h"

// Define the conditions based on which to perform the field-base search: 
// Identify a specific name
bool condition_name(const LiteratureEntry& lit_entry, std::string name){return lit_entry.is_name(name);}
// Identify a specific title
bool condition_title(const LiteratureEntry& lit_entry, std::string title){return lit_entry.get_title() == title;}
// Identify a type from among "Book", "Thesis" and "Journal"
bool condition_type(const LiteratureEntry& lit_entry, std::string type){return lit_entry.get_type() == type;}

// dictionary between enumerators and strings for Commands
std::map<std::string, Commands> string_to_command = 
{
  {"INFO"  , Commands::INFO  },
  {"PRINT" , Commands::PRINT },
  {"QUIT"  , Commands::QUIT  },
  {"DELETE", Commands::DELETE},
  {"EDIT"  , Commands::EDIT  },
  {"ADD"   , Commands::ADD   },
  {"BIBTEX", Commands::BIBTEX},
  {"SAVE"  , Commands::SAVE  },
  {"PRICE" , Commands::PRICE }
};

// dictionary between enumerators and strings for Fields
std::map<std::string, Fields> string_to_field = 
{
  {"ALL"   , Fields::ALL  },
  {"NAME"  , Fields::NAME  },
  {"TITLE" , Fields::TITLE },
  {"TYPE"  , Fields::TYPE  },
};

// dictionary between enumerators and strings for Types
std::map<std::string, Types> string_to_type = 
{
  {"Book"   , Types::BOOK   },
  {"Thesis" , Types::THESIS },
  {"Journal", Types::JOURNAL},
};

void print_info()
{
  std::cout<<std::endl;
  std::cout<<".-----------INFO-----------."<<std::endl;
  std::cout<<"|  * Available Commands *  |"<<std::endl;
  std::cout<<"| 1. INFO   - Prints Info  |"<<std::endl;
  std::cout<<"| 2. PRINT  - Print Entry  |"<<std::endl;
  std::cout<<"| 3. QUIT   - Exit Program |"<<std::endl;  
  std::cout<<"| 4. DELETE - Remove Entry |"<<std::endl;
  std::cout<<"| 5. EDIT   - Edit Entry   |"<<std::endl;
  std::cout<<"| 6. ADD    - Add Entry    |"<<std::endl;
  std::cout<<"| 7. BIBTEX - Print BibTeX |"<<std::endl;
  std::cout<<"| 8. SAVE   - Save Data    |"<<std::endl;
  std::cout<<"| 9. PRICE  - Avg. Price   |"<<std::endl;
  std::cout<<"'--------------------------'"<<std::endl;
  std::cout<<".--------------------------."<<std::endl;
  std::cout<<"|     * Valid Fields *     |"<<std::endl;
  std::cout<<"| 1. ALL   - Prints All    |"<<std::endl;
  std::cout<<"| 2. NAME  - Find Name     |"<<std::endl;
  std::cout<<"| 3. TITLE - Find Title    |"<<std::endl;  
  std::cout<<"| 4. TYPE  - Find Type     |"<<std::endl;
  std::cout<<"'--------------------------'"<<std::endl;
  std::cout<<".--------------------------."<<std::endl;
  std::cout<<"|    * Supported Type *    |"<<std::endl;
  std::cout<<"| 1. Book                  |"<<std::endl;
  std::cout<<"| 2. Journal               |"<<std::endl;
  std::cout<<"| 3. Thesis                |"<<std::endl;  
  std::cout<<"'--------------------------'"<<std::endl;
  std::cout<<std::endl;
}

// Function to answer the question: Is this string among valid commands? 
bool validate_command(std::string str, std::set<std::string> valid_commands)
{
  return valid_commands.find(str) != valid_commands.end();
}

// Prompt the user to give a command (from among valid commands) and collect it
Commands collect_and_validate_command()
{
  std::string user_input;
  std::cout<<"Enter a valid command: "; // Prompt user
  std::getline(std::cin, user_input);
  while(!validate_command(user_input, valid_commands)) // Keep prompting until valid command is given
  {
    std::cout<<"INVALID COMMAND; try again; for a list of commndas, type \"INFO\": ";
    std::getline(std::cin, user_input);
  }
  return string_to_command[user_input]; // Output a valid enumerator from among Commands
}

// Prompt the user to give a type (from among valid types) and collect it
Types collect_and_validate_type()
{
  std::string user_input;
  std::cout<<"Enter a valid type: "; // Prompt user
  std::getline(std::cin, user_input);
  while(!validate_command(user_input, valid_types)) // Keep prompting until valid type is given
  {
    std::cout<<"INVALID TYPE; try again; valid types are \"Book\", \"Journal\", \"Thesis\": ";
    std::getline(std::cin, user_input);
  }
  return string_to_type[user_input]; // Output a valid enumerator from among Types
}

// Prompt the user to give a field (from among valid fields) and collect it
Fields collect_and_validate_field()
{
  std::string user_input;
  std::cout<<"Enter a valid field: "; // Prompt user
  std::getline(std::cin, user_input);
  while(!validate_command(user_input, valid_fields)) // Keep prompting until field field is given
  {
    std::cout<<"INVALID FIELD; try again; valid fields are \"ALL\", \"NAME\", \"TITLE\", \"TYPE\": ";
    std::getline(std::cin, user_input);
  }
  return string_to_field[user_input]; // Output a valid enumerator from among Fields
}

// Function to answer the question: Is this integer non-zero? 
bool validate_nonzero_int(std::string str)
{
  bool answer{true};
  for(int i{}; i<str.length(); ++i) {answer = answer && std::isdigit(str[i]);}
  return answer;
}

// Function to collect a valid non-negative integer
int collect_and_validate_int()
{
  std::string user_input;
  std::getline(std::cin, user_input); // Read line
  while(!validate_nonzero_int(user_input)) // Keep prompting until non-negative integer is given
  {
    std::cout<<"Your input was invalid, please enter a non-negative integer: ";
    std::getline(std::cin, user_input);
  }
  return std::stoi(user_input); // Output a non-negative integer
}

// Function to collect a valid non-negative float
float collect_and_validate_float()
{
  std::string user_input;
  float return_value;
  size_t pos;
  bool valid_input = false;

  while (!valid_input) 
  {
    std::getline(std::cin, user_input);
    try // Attempt to convert the provided string to float
    {
      return_value = std::stof(user_input, &pos);
      if (pos == user_input.size() && return_value >= 0.0) // Check for nonnegativity
      {
        valid_input = true; // Input is valid
      } else 
      {
        std::cout << "Your input was invalid or negative, please enter a non-negative real number: ";
      }
    } 
    catch (const std::invalid_argument& e) // Catch bad cast
    {
      std::cout << "Invalid input. Please enter a valid number: ";
    } 
    catch (const std::out_of_range& e) // Catch input out of range for float datatype
    {
    std::cout << "Input out of range. Please enter a valid number: ";
    }
  }
  return return_value; // Output a valid non-negative float
}

// Function to prompt user if they did not enter 'y' or 'n' and collect valid input
bool collect_and_validate_y_or_n()
{
  bool output;
  std::string y_or_n;
  std::getline(std::cin, y_or_n);

  // Continue looping so long as input fails or the entered character invalid
  while(y_or_n!="y" && y_or_n!="n")
  {
    std::cout<<"Your input was invalid, please enter 'y' or 'n': ";
    std::getline(std::cin, y_or_n);
  }
  if(y_or_n=="y"){output = true;}
  else{output = false;}

  return output; // Output false if user inputs 'n', true if 'y'
}

// A wrapper function for printing a ALL entries of a specified valid type from a database
void type_print(LiteratureDatabase lit_database, Types type)
{
  std::cout<<"--------------------------------------------"<<std::endl;
  switch (type)
  {
  case Types::BOOK:
    lit_database.print_condition_entries(condition_type, "Book"); // Print ALL entries of type Book
    break;

  case Types::JOURNAL:
    lit_database.print_condition_entries(condition_type, "Journal"); // Print ALL entries of type Journal
    break;

  case Types::THESIS:
    lit_database.print_condition_entries(condition_type, "Thesis"); // Print ALL entries of type Thesis
    break; 

  default:
    std::cout<<"WARNING: This should not be reached. Likely error in collect_and_validate_type()."<<std::endl;
    break;
  }
}

// A wrapper function for printing ALL entries of a specified valid field from a database
void general_print(LiteratureDatabase& lit_database, Fields field)
{
  std::string user_input;

  switch (field)
  {
  case Fields::ALL:
    std::cout<<"--------------------------------------------"<<std::endl;
    lit_database.print_all_entries(); // Print ALL entries
    break;
    
  case Fields::NAME:
    std::cout<<"Enter a name to search for: "; // Prompt user for a name
    std::getline(std::cin, user_input); // Collect the title
    std::cout<<"--------------------------------------------"<<std::endl;
    lit_database.print_condition_entries(condition_name, user_input); // Print ALL entries with this name among authors/editors
    break;

  case Fields::TITLE:
    std::cout<<"Enter a title to search for: "; // Prompt user for a title
    std::getline(std::cin, user_input);  // Collect the title
    std::cout<<"--------------------------------------------"<<std::endl;
    lit_database.print_condition_entries(condition_title, user_input); // Print ALL entries with this title 
    break;

  case Fields::TYPE:
    type_print(lit_database, collect_and_validate_type()); // Print ALL entries of a specified type
    break; 

  default:
    std::cout<<"WARNING: This should not be reached. Likely error in collect_and_validate_field()."<<std::endl;
    break;
  }
}

// Helper function that spilts a string by a specified delimiter
std::vector<std::string> split_string_(const std::string& str, char delimiter)
{
  std::vector<std::string> substrings;
  std::istringstream iss(str); // Use string stream 
  std::string token;
  while (std::getline(iss, token, delimiter)){substrings.push_back(token);}
  return substrings;
}

// Function for adding a Book, prompts user with questions and collects answers
std::unique_ptr<Book> add_book()
{
  std::string title{};
  std::cout<<"Enter the Book title: "; // Prompt user
  std::getline(std::cin, title); // Collect input 

  std::string raw_names{};
  std::cout<<"Enter the Book authors separated by \"/\": ";
  std::getline(std::cin, raw_names);
  std::vector<std::string> names = split_string_(raw_names, '/');

  std::cout<<"Enter the year of the Book publication: "; // Prompt user
  int year{collect_and_validate_int()}; // Collect year, validate it, initialize variable to it

  std::string publisher{};
  std::cout<<"Enter the Book publisher: ";
  std::getline(std::cin, publisher);

  std::string subject{};
  std::cout<<"Enter the Book subject: ";
  std::getline(std::cin, subject);

  std::cout<<"Enter the price of the Book: ";
  float price{collect_and_validate_float()};

  auto names_ptr = std::make_unique<std::vector<std::string>>(std::move(names));

  // Create a Book object with the desired data
  auto return_ptr = std::make_unique<Book>(title, std::move(names_ptr), year, publisher, subject, price);
  return return_ptr;
}

// Function for adding a Journal, prompts user with questions and collects answers
std::unique_ptr<Journal> add_journal()
{
  std::string title{};
  std::cout<<"Enter the Journal title: "; // Prompt user
  std::getline(std::cin, title); // Collect line 

  std::string raw_names{};
  std::cout<<"Enter the Journal editors separated by \"/\": ";
  std::getline(std::cin, raw_names);
  std::vector<std::string> names = split_string_(raw_names, '/');

  std::cout<<"Enter the year the Journal was founded: ";
  int year{collect_and_validate_int()};
  
  std::cout<<"Enter the Journal impact factor: ";
  float impact_factor{collect_and_validate_float()};

  std::string scope{};
  std::cout<<"Enter the Journal scope: ";
  std::getline(std::cin, scope);

  std::cout<<"Enter the number volumes of the Journal to date: ";
  int number_volumes{collect_and_validate_int()};

  auto names_ptr = std::make_unique<std::vector<std::string>>(std::move(names));

  // Create a Journal object with the desired data
  auto return_ptr = std::make_unique<Journal>(title, std::move(names_ptr), year, impact_factor, scope, number_volumes);
  return return_ptr;
}

// Function for adding a Thesis, prompts user with questions and collects answers
std::unique_ptr<Thesis> add_thesis()
{
  std::string title{};
  std::cout<<"Enter the Thesis title: "; // Prompt user
  std::getline(std::cin, title); // Collect title 

  std::string raw_names{};
  std::cout<<"Enter the Thesis authors separated by \"/\": "; // Prompt user
  std::getline(std::cin, raw_names); // Collect all names
  std::vector<std::string> names = split_string_(raw_names, '/'); // Split names

  std::cout<<"Enter the year the Thesis was written: ";
  int year{collect_and_validate_int()}; // Collect year, validate it, initialize variable to it

  std::string university{};
  std::cout<<"Enter the university: ";
  std::getline(std::cin, university);

  std::string raw_supervisors{};
  std::cout<<"Enter the Thesis supervisors separated by \"/\": ";
  std::getline(std::cin, raw_supervisors);
  std::vector<std::string> supervisors = split_string_(raw_supervisors, '/');

  auto names_ptr = std::make_unique<std::vector<std::string>>(std::move(names));
  auto supervisors_ptr = std::make_unique<std::vector<std::string>>(std::move(supervisors));

  // Create a Thesis object with the desired data
  auto return_ptr = std::make_unique<Thesis>(title, std::move(names_ptr), year, university, std::move(supervisors_ptr));
  return return_ptr;
}

// Wrapper function for collection of a new entry of specified type
void add_general_entry(LiteratureDatabase& lit_database, Types type)
{
  switch (type)
  {
  case Types::BOOK:
    lit_database.insert_entry(add_book());
    break;
  case Types::JOURNAL:
    lit_database.insert_entry(add_journal());
    break;
  case Types::THESIS:
    lit_database.insert_entry(add_thesis());
    break;  
  default:
    std::cout<<"WARNING: This should not be reached. Likely error in collect_and_validate_type()."<<std::endl;
    break;
  }
}

// A function which will save a single string to a file of specified name
void save_string_to_file(const std::unique_ptr<std::string>& str_ptr, const std::string& filename) 
{
  if (!str_ptr) // Check if a null pointer to a string was provided
  {
    std::cerr << "Error: Null pointer to string provided." << std::endl;
    return;
  }
  std::ofstream file(filename, std::ios::binary);
  if (!file.is_open()) // Check if the file was opened successfuly
  {
    std::cerr << "Error: Unable to open file " << filename << std::endl;
    return;
  }
  const std::string& str = *str_ptr;
  file.write(str.c_str(), str.size()); // Write into file
  file.close();
  if (file.fail()) // Let the user know of writing into file failed
  {
    std::cerr << "Error: Failed to write to file." << std::endl;
    return;
  }
  // Succesful save message: 
  std::cout << "Database saved to " << filename << " successfully." << std::endl;
}

// Function which prompts the user with y/n questions and lets them change generic aspects of LiteratureEntry objects
void edit_literature_entry(LiteratureDatabase& lit_database, int index)
{
  std::cout<<"Would you like to edit the title? y/n: "; // Prompt user
  if (collect_and_validate_y_or_n()) // Collect y/n answer, proceed based on this
  {
    std::string title;
    std::cout<<"Please enter the new title: "; // Prompt user
    std::getline(std::cin, title); //Collect title
    lit_database.set_title(index, title); // Set title
  }
  std::cout<<"Would you like to add an author? y/n: ";
  if (collect_and_validate_y_or_n())
  {
    std::string name;
    std::cout<<"Please enter the new name: ";
    std::getline(std::cin, name); // Collect 
    lit_database.add_name(index, name); // Set 
  }
  std::cout<<"Would you like to remove an author? y/n: ";
  if (collect_and_validate_y_or_n())
  {
    std::string name;
    std::cout<<"Please enter the name to be removed: ";
    std::getline(std::cin, name);
    lit_database.remove_name(index, name);
  }
  std::cout<<"Would you like to edit the year? y/n: ";
  if (collect_and_validate_y_or_n())
  {
    std::cout<<"Please enter the new year: "<<std::endl;
    lit_database.set_year(index, collect_and_validate_int());
  }
}

// Function which prompts the user with y/n questions and lets them change specific aspects of Book objects
void edit_book(LiteratureDatabase& lit_database, int index)
{
  edit_literature_entry(lit_database, index);
  std::cout<<"Would you like to edit the publisher? y/n: "; // Prompt user
  if (collect_and_validate_y_or_n()) // Collect y/n answer, proceed based on this
  {
    std::string publisher;
    std::cout<<"Please enter the new publisher: "; // Prompt user
    std::getline(std::cin, publisher); // Collect publisher
    lit_database.set_publisher(index, publisher); // Set publisher 
  }
  std::cout<<"Would you like to edit the subject? y/n: "; // Prompt user
  if (collect_and_validate_y_or_n()) // Collect y/n answer, proceed based on this
  {
    std::string subject;
    std::cout<<"Please enter the new subject: ";
    std::getline(std::cin, subject);
    lit_database.set_subject(index, subject);
  }
  std::cout<<"Would you like to edit the price? y/n: ";
  if (collect_and_validate_y_or_n())
  {
    std::cout<<"Please enter the new price: ";
    lit_database.set_price(index, collect_and_validate_float());
  }
}

// Function which prompts the user with y/n questions and lets them change specific aspects of Thesis objects
void edit_thesis(LiteratureDatabase& lit_database, int index)
{
  edit_literature_entry(lit_database, index);
  std::cout<<"Would you like to add a supervisor? y/n: "; // Prompt user
  if (collect_and_validate_y_or_n()) // Collect y/n answer, proceed based on this
  {
    std::string name;
    std::cout<<"Please enter the new name: ";
    std::getline(std::cin, name); // Collect name to be added 
    lit_database.add_supervisor(index, name); // Add the name
  }
  std::cout<<"Would you like to remove a supervisor? y/n: "; 
  if (collect_and_validate_y_or_n()) 
  {
    std::string name;
    std::cout<<"Please enter the name to be removed: ";
    std::getline(std::cin, name); // Collect name to be removed
    lit_database.remove_supervisor(index, name); // Remove the name
  }
 std::cout<<"Would you like to edit the university? y/n: "; 
  if (collect_and_validate_y_or_n()) 
  {
    std::string university;
    std::cout<<"Please enter the new university: ";
    std::getline(std::cin, university); // Collect
    lit_database.set_university(index, university); // Set
  }
}

// Function which prompts the user with y/n questions and lets them change specific aspects of Thesis objects
void edit_journal(LiteratureDatabase& lit_database, int index)
{
  edit_literature_entry(lit_database, index);
  std::cout<<"Would you like to edit the impact factor? y/n: "; // Prompt user
  if (collect_and_validate_y_or_n()) // Collect y/n answer, proceed based on this
  {
    std::cout<<"Please enter the impact factor: ";
    lit_database.set_impact_factor(index, collect_and_validate_float()); // Collect float, set it as impact_factor
  }
  std::cout<<"Would you like to edit the number of volumes? y/n: "; // Prompt user
  if (collect_and_validate_y_or_n()) // Collect y/n answer, proceed based on this
  {
    std::cout<<"Please enter the new number of volumes: "<<std::endl;
    lit_database.set_number_volumes(index, collect_and_validate_int()); // Collect int, set it as number_volumes
  }
  std::cout<<"Would you like to edit the scope? y/n: "; 
  if (collect_and_validate_y_or_n()) // Collect y/n answer, proceed based on this
  {
    std::string scope;
    std::cout<<"Please enter the new scope: "; 
    std::getline(std::cin, scope); // Collect scope
    lit_database.set_scope(index, scope); // Set new scope
  }
}

// Wrapper function which prompts the user with y/n questions and lets them change specific aspects of object of specified type
void edit_entry(LiteratureDatabase& lit_database, int index)
{
  // Check for invalid index
  if (index >= 0 && index < lit_database.get_number_entries())
  {
    // Print the entry to be edited
    std::cout<<"----------------NOW EDITING:----------------"<<std::endl;
    lit_database.print_entry(index);
    std::cout<<"--------------------------------------------"<<std::endl;

    switch (string_to_type[lit_database.get_type(index)])
    {
    case Types::BOOK:
      edit_book(lit_database, index);
      break;

    case Types::THESIS:
      edit_thesis(lit_database, index);
      break;

    case Types::JOURNAL:
      edit_journal(lit_database, index);
      break;
    
    default:
      std::cout<<"WARNING: This should not be reached."<<std::endl;
      break;
    }
  }
  else // Warn against invalid index
  {
    std::cout<<"Invalid index out of bounds was specified. Try again."<<std::endl;
  }
}

// Wrapper function for execution of any specified command from among valid commands
bool execute_command(LiteratureDatabase& lit_database, Commands command)
{
  std::string filename;

  switch (command)
  {
  case Commands::INFO:
    print_info();
    return true;

  case Commands::PRINT:
    general_print(lit_database, collect_and_validate_field());
    return true;

  case Commands::QUIT:
    return false;

  case Commands::DELETE:
    std::cout<<"Please enter an index from the list of ALL entries: ";
    lit_database.remove_entry(collect_and_validate_int() - 1);
    return true;

  case Commands::EDIT:
    std::cout<<"Please enter an index from the list of ALL entries: ";
    edit_entry(lit_database, collect_and_validate_int() - 1);
    return true;

  case Commands::ADD:
    add_general_entry(lit_database, collect_and_validate_type());
    return true;

  case Commands::BIBTEX:
    std::cout<<"Please enter an index from the list of ALL entries: ";
    lit_database.print_bibtex(collect_and_validate_int() - 1);
    return true;

  case Commands::SAVE:
    std::cout<<"Please enter a file name: ";
    std::getline(std::cin, filename);
    save_string_to_file(lit_database.get_encoded_data(), filename);
    return true;

  case Commands::PRICE:
    std::cout<<"The average Book price is: "<<lit_database.get_average_book_price()<<std::endl;
    return true;

  default:
    std::cout<<"WARNING: This should not be reached. Likely error in collect_and_validate_command() or validate_command()."<<std::endl;
    return false;
  }
}
