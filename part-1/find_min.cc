// Yamato Eguchi
// CPSC 120-01
// 2021-03-20
// yamatoe1227@csu.fullerton.edu
// @yamatoeguchi
//
// Lab 06-01
//
// This is my find minimunm assignment
//

// Add the following header files algorithm, array, cstdlib,
// iostream, random

#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <random>

using namespace std;

/// The RandomNumberGenerator class is a wrapper around the Standard C++
/// Library's Mersenne Twister pseudo random number generator.
/// This class is complete and correct; please do not make any changes to it.
///
/// In lieu of directly working with the [Mersenne Twister
/// class]
/// (https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine),
/// this class serves as a lightweight wrapper around the necessary elements of
/// the library. The usage of this class is very simple and requires a
/// minimum and maximum value for initialization.
/// \code
/// int minimum_random_number = 1;
/// int maximum_random_number = 10;
/// RandomNumberGenerator my_random_number_generator{minimum_random_number,
/// maximum_random_number}; int random_number =
/// my_random_number_generator.next();
/// \endcode
class RandomNumberGenerator {
 private:
  /// A hardware entropy source (a device on your computer to give random bits)
  std::random_device rd;
  /// A sequence of random bits to seed the Mersenne Twister engine
  std::seed_seq seed;
  /// A Mersenne Twister engine
  std::mt19937 mt_engine;
  /// A uniform distribution; select numbers randomly in a uniform manner
  std::uniform_int_distribution<> uniform_dist;

 public:
  /// Constructor to the RandomNumberGenerator class
  ///
  /// The RandomNumberGenerator generates random integer numbers between
  /// \p minimum and \p maximum. The constructor initializes and prepares
  /// the engine. To generate a number use the <RandomNumberGenerator::next>()
  /// method.
  ///
  /// \param minimum The lowest value the random number generator will return
  /// \param maximum The largest value the random number generator will return
  RandomNumberGenerator(int minimum, int maximum)
      : seed{rd()}, mt_engine{rd()}, uniform_dist{minimum, maximum} {}

  /// Return a random number
  ///
  /// Returns a random integer number between the minimum and maximum set
  /// when the constructor was called.
  /// \sa RandomNumberGenerator::RandomNumberGenerator
  ///
  /// \returns An integer between the minimum and maximum set when
  /// the constructor was called
  auto next() -> int {
    int random_number = uniform_dist(mt_engine);
    // std::cout << "Debugging: The random number is " << random_number << "\n";
    return random_number;
  }
};

/// number_elements defines how large the C++ array will be. It must be global
/// so that it can be used in all the functions.
const int number_elements = 10;

/// ErrorMessage prints out \p message first and then prints the standard
/// message
/// \code
/// "There was an error. Exiting.\n".
/// \endcode
///
/// \param message The programmer defined string that specifies the current
/// error.
void ErrorMessage(const string& message) {
  // implement ErrorMessage
  cout << message << "\n";
  cout << "There was an error. Exiting.\n";
}

/// PrintArray print out the elements of \p the_array each on a line of
/// their own.
///
/// \code
/// array<int, number_elements> the_array{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
/// PrintArray(array);
/// \endcode
///
/// This above code will print:
/// \code
/// 1
/// 2
/// 3
/// 4
/// 5
/// 6
/// 7
/// 8
/// 9
/// 10
/// \endcode
///
/// \param the_array This is the array of integers created in the main function.
void PrintArray(const array<int, number_elements>& the_array) {
  // Implement the function such that it prints out each element of
  // the given array, one element per line.
  for (const auto& elements : the_array) {
    cout << elements << "\n";
  }
}

/// FillArray filles \p the_array with random numbers given by
/// \p random_number_generator.
///
/// The body of this function loops through each location of the \p the_array
/// and assigns it a random value.
///
/// \param the_array The array of integers created in the main function.
/// \param random_number_generator The random number generator created in
/// the main function.
/// \sa RandomNumberGenerator::next()
void FillArray(array<int, number_elements>& the_array,
               RandomNumberGenerator& random_number_generator) {
  // assign a random number to each element in the array using
  // random_number_generator.next().
  
  for (int index = 0; index < the_array.size(); index++) {
    try{
      the_array.at(index) = random_number_generator.next();
    } catch(const exception& e) {
      ErrorMessage("Problem filling array.");
      exit(1);
    }
  }
}
/*
  for (auto elements : the_array) {
    elements = random_number_generator.next();
  }
}
*/
/// FindMinimum walks through each location of \p the_array, finds the
/// smallest value, and returns it.
///
/// The algorithm of FindMinimum is to first assume that the item at the zeroth
/// location is the minimum value. Save the value of the zeroth value to a
/// a variable. Next, enter a loop which starts at the 1st element and
/// continues until the the_array.size() value. At each iteration of the loop,
/// check to see if the current value is less than the existing minimum value.
/// If so, set the minimum value to the current value and continue. Return the
/// the final minimum value.
///
/// \param the_array The array of integers created in the main function.
///
/// \returns The minimum/smallest value in the array
int FindMinimum(const array<int, number_elements>& the_array) {
  // Find the minimum value in the array.
  int the_minimum = 0;
  try{
    the_minimum = the_array.at(0);
  } catch(const exception& e) {
    ErrorMessage("Can't initialize the minimum.");
    exit(1);
  }
  for (const auto& element : the_array) {
    if(element < the_minimum) {
      the_minimum = element;
    }
  }
  return the_minimum;
}

/// Entry point to the find_min program
/// \remark Must have at least 2 arguments. The first argument is the minimum
/// number generated by the random number generator and the second argument
/// is the maximum number generated by the random number generator.
int main(int argc, char* argv[]) {
  if (argc < 3) {
    ErrorMessage(
        "Please provide two positive integers as the maximum and "
        "minimum for this exercise.");
    exit(1);
  }
  string argv_one_minimum = string(argv[1]);
  string argv_two_maximum = string(argv[2]);
  int minimum_number = 0;
  int maximum_number = 0;
  // convert argv_one_minimum and argv_two_maximum to integers and
  // assign to minimum_number and maximum_number.
  try {
    minimum_number = stoi(argv_one_minimum);
    maximum_number = stoi(argv_two_maximum);
  } catch (const exception& e) {
    ErrorMessage("Error converting string to integer.");
    exit(1);
  }

  // Check to make sure minimum_number is less than maximum_number,
  // and that both of them are greater than zero. Otherwise, print an 
  // error message and exit.
  if (minimum_number >= maximum_number || minimum_number <= 0 || maximum_number <= 0) {
    ErrorMessage("Minimum number must be less than the maximum number and both minimum and maximum numbers must be greater than 0.");
    exit(1);
  }

  RandomNumberGenerator rng(minimum_number, maximum_number);
  array<int, number_elements> random_numbers{};

  FillArray(random_numbers, rng);
  PrintArray(random_numbers);
  int minimum_value = FindMinimum(random_numbers);
  cout << "The minimum value in the array is " << minimum_value << "\n";
  return 0;
}
