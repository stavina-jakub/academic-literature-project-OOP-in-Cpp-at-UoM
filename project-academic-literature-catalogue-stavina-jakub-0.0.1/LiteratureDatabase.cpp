/*
  Author: Jakub Stavina, UID: --------
  Course: PHYS30762 Programming in C++
  Date: April 24, 2024
  Description: This C++ program implements the 'LiteratureDatabase' class. 
*/

#include "LiteratureDatabase.h"

// Function to split a string by a delimiter
std::vector<std::string> LiteratureDatabase::split(const std::string& s, char delimiter)
{
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {tokens.push_back(token);}
  return tokens;
}

// Function to print all the entries
void LiteratureDatabase::print_all_entries() const 
{
  int count{1};
  for (const auto& entry : entries) 
  {
    std::cout<<count<<". "; // Number the entries
    entry->print_data();
    std::cout<<std::endl;
    count++;
  }
}

// Function to print the entries satisfying a specific condition
void LiteratureDatabase::print_condition_entries(bool (*condition)(const LiteratureEntry&, std::string), std::string args) const
{
  int count{1};
  for (const auto& entry : entries) 
  {
    if (condition(*entry, args)) // Check for the specified condition
    {
      std::cout<<count<<". "; // Number the entries
      entry->print_data();
      std::cout<<std::endl;
      count++;
    }
  }
  if (count == 1)
  {
    std::cout<<std::endl<<"NO ENTRIES WERE FOUND."<<std::endl<<std::endl;
  }
  else if (count == 2)
  {
    // Case for correct grammar :D
    std::cout<<count-1<<" ENTRY WAS FOUND."<<std::endl<<std::endl;
  }
  else
  {
    // Print the total number of entries found
    std::cout<<count-1<<" ENTRIES WERE FOUND."<<std::endl<<std::endl;
  }
}

// Print the specified entry in the BibTeX style 
void LiteratureDatabase::print_bibtex(int index) const
{
  if (index >= 0 && index < entries.size()) 
  {
    try // Try dynamic cast to Book
    {
      Book* bookEntry = dynamic_cast<Book*>(entries[index].get());
      if (bookEntry)
      {
        std::cout<<std::endl; 
        bookEntry->print_bibtex(); // If successful print @book{...}
        std::cout<<std::endl;
      }
      else // Try dynamic cast to Thesis
      {
        Thesis* thesisEntry = dynamic_cast<Thesis*>(entries[index].get());
        if (thesisEntry)
        {
          std::cout<<std::endl;
          thesisEntry->print_bibtex(); // If successful print @phdthesis{...}
          std::cout<<std::endl;
        }
        else // If this fails, let the user know
        {
          std::cerr << "Entry at index " << index + 1 << " does not have a print_bibtex() method." << std::endl;
        }
      }
    }
    catch (std::bad_cast& e)  // Catch bad cast
    {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }
  else 
  {
    std::cerr << "Invalid index: " << index + 1<< ". Printing BibTeX failed." << std::endl;
  }
}


// Copy constructor
LiteratureDatabase::LiteratureDatabase(const LiteratureDatabase& other) 
{
  for (const auto& entry : other.entries) 
  {
    if (entry) 
    {
      entries.push_back(entry->clone());
    }
  }
}

// Move constructor
LiteratureDatabase::LiteratureDatabase(LiteratureDatabase&& other) noexcept 
{
  entries = std::move(other.entries); // Steal data members
  other.entries.clear(); // Define the behaviour for the "other" object
}

// Copy assignment operator
LiteratureDatabase& LiteratureDatabase::operator=(const LiteratureDatabase& other) 
{
  if (this != &other) // Check for self-reference
  {
    entries.clear();
    for (const auto& entry : other.entries) 
    {
      if (entry) 
      {
        // Perform a deep copy
        entries.push_back(entry->clone());
      }
    }
  }
  return *this;
}

// Move assignment operator
LiteratureDatabase& LiteratureDatabase::operator=(LiteratureDatabase&& other) noexcept 
{
  if (this != &other) 
  {
    entries = std::move(other.entries); // Steal data members
    other.entries.clear(); // Define behaviour for the "other" object
  }
  return *this;
}

// Parametrized constructor taking a file name
LiteratureDatabase::LiteratureDatabase(const std::string& filename)
{
  // Open the input file stream
  std::ifstream file(filename);

  // Check if the file was opened successfully
  if (!file.is_open()) 
  {
    throw std::runtime_error("Failed to open the input file.");
  }

  std::string line;

  while (std::getline(file, line)) // Read the 1st line
  {
    // Identify literature entry type: Book, Journal or Thesis
    if (line == "BOOK")
    {
      std::vector<std::string> data(6);
      for (auto& str : data) {std::getline(file, str);} // Load the data for Book
      auto authors = std::make_unique<std::vector<std::string>>(split(data[1], ';')); // Separate the authors
      // Create a new Book object, push unique pointer to entries
      entries.push_back(std::make_unique<Book>(data[0], std::move(authors), std::stoi(data[2]), data[3], data[4], std::stof(data[5])));
    }
    
    else if (line == "JOURNAL") 
    {
      std::vector<std::string> data(6);
      for (auto& str : data) {std::getline(file, str);} // Load the data for Journal
      auto authors = std::make_unique<std::vector<std::string>>(split(data[1], ';')); // Separate the  authors
      // Create a new Journal object, push unique pointer to entries
      entries.push_back(std::make_unique<Journal>(data[0], std::move(authors), std::stoi(data[2]),  std::stof(data[3]), data[4], std::stoi(data[5])));
    }

    else if (line == "THESIS") 
    {
      std::vector<std::string> data(5);
      for (auto& str : data) {std::getline(file, str);} // Load the data for Thesis
      auto authors = std::make_unique<std::vector<std::string>>(split(data[1], ';')); // Separate the  authors
      auto supervisors = std::make_unique<std::vector<std::string>>(split(data[4], ';')); // Get supervisors
      // Create a new Thesis object, push unique pointer to entries
      entries.push_back(std::make_unique<Thesis>(data[0], std::move(authors), std::stoi(data[2]), data[3], std::move(supervisors)));
    }

    else
    {
      std::cerr<<"WARNING: Bad entry in the data file."<<std::endl;
    }
    
  }

  // Close the file stream after reading
  file.close();
} 

// Function for literature removal of entry at a specific index
void LiteratureDatabase::remove_entry(int index)
{
  if (index >= 0 && index < entries.size()) // Check for correct index
  {
    entries.erase(entries.begin() + index); // Erase entry, inform user
    std::cout << "Entry at index " << index + 1<< " removed successfully." << std::endl;
  } 
  else // Warn the user if invalid index was given
  {
    std::cerr << "Invalid index: " << index + 1<< ". Entry removal failed." << std::endl;
  }
}

// Function for entry insertion
void LiteratureDatabase::insert_entry(std::unique_ptr<LiteratureEntry> entry)
{
  entries.push_back(std::move(entry));
  std::cout << "New entry inserted successfully." << std::endl;
}

// Setter for publisher at specified index; attempt at a dynamic cast
void LiteratureDatabase::set_publisher(int index, std::string publisher)
{
  if (entries[index]->get_type() == "Book")
  {
    dynamic_cast<Book*>(entries[index].get())->set_publisher(publisher);
  }
}

// Setter for subject at specified index; attempt at a dynamic cast
void LiteratureDatabase::set_subject(int index, std::string subject) 
{
  if (entries[index]->get_type() == "Book")
  {
    dynamic_cast<Book*>(entries[index].get())->set_subject(subject);
  }
}

// Setter for proce at specified index; attempt at a dynamic cast
void LiteratureDatabase::set_price(int index, float price)
{
  if (entries[index]->get_type() == "Book")
  {
    dynamic_cast<Book*>(entries[index].get())->set_price(price);
  }
}

// Setter for impact factor at specified index; attempt at a dynamic cast
void LiteratureDatabase::set_impact_factor(int index, float impact_factor)
{
  if (entries[index]->get_type() == "Journal")
  {
    dynamic_cast<Journal*>(entries[index].get())->set_impact_factor(impact_factor);
  }
}

// Setter for scope at specified index; attempt at a dynamic cast
void LiteratureDatabase::set_scope(int index, std::string scope)
{
  if (entries[index]->get_type() == "Journal")
  {
    dynamic_cast<Journal*>(entries[index].get())->set_scope(scope);
  }
}

// Setter for number of volumes at specified index; attempt at a dynamic cast
void LiteratureDatabase::set_number_volumes(int index, int number_volumes)
{
  if (entries[index]->get_type() == "Journal")
  {
    dynamic_cast<Journal*>(entries[index].get())->set_number_volumes(number_volumes);
  }
}

// Setter for university at specified index; attempt at a dynamic cast
void LiteratureDatabase::set_university(int index, std::string university)
{
  if (entries[index]->get_type() == "Thesis")
  {
    dynamic_cast<Thesis*>(entries[index].get())->set_university(university);
  }
}

// Mutator; adds supervisor at specified index; attempt at a dynamic cast
void LiteratureDatabase::add_supervisor(int index, std::string supervisor)
{
  if (entries[index]->get_type() == "Thesis")
  {
    dynamic_cast<Thesis*>(entries[index].get())->add_supervisor(supervisor);
  }
}

// Mutator; removes supervisor at specified index; attempt at a dynamic cast
void LiteratureDatabase::remove_supervisor(int index, std::string supervisor)
{
  if (entries[index]->get_type() == "Thesis")
  {
    dynamic_cast<Thesis*>(entries[index].get())->remove_supervisor(supervisor);
  }
}

// Accessor-like functions: 
// Compute and return average book price (Books averaged over the entire database)
float LiteratureDatabase::get_average_book_price()
{
  float average{0.0};
  int counter{0};

  for (int i = 0; i < entries.size(); i++) // Loop over the entries, sum the prices
  {
    if (entries[i]->get_type() == "Book")
    {
      // Attempt dynamic cast, get price
      average += dynamic_cast<Book*>(entries[i].get())->get_price(); 
      counter++;
    } 
  }
  return average / counter; // Compute average
}

// Get encoding of the entire catalogue in the appropriate style
std::unique_ptr<std::string> LiteratureDatabase::get_encoded_data()
{
  auto return_ptr = std::make_unique<std::string>("");
  for (int i = 0; i < entries.size(); i++) // Loop over entries
  {
    *return_ptr += entries[i]->get_encoding(); // Collect encodings of inidividual entries
  }
  return return_ptr; // Return pointer to the encoded database
}