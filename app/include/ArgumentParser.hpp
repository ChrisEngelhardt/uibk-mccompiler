#ifndef __ARGUMENTPARSER_HPP__
#define __ARGUMENTPARSER_HPP__

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

/**
 * Arugment parser class which provides some
 * convenient functions to parse the input parameters
 * @param argc [description]
 * @param argv [description]
 */
class ArgumentParser{
private:
  std::vector <std::string> tokens;

public:

  /**
  * Creates an instance of Arugment parser which provides some
  * convenient functions to parse the input parameters
  * @param argc Simply forward the argc from main functtion
  * @param argv Simply forward the argv from main function
  */
  ArgumentParser (const int &argc, const char **argv);

  /**
  * Get the value defined by its flag
  * @param option Flag for which we are looking e.g. "-h"
  * @return       Returns the options value
  */
  const std::string& getCmdOption(const std::string &option) const;

  /**
  * Check if some option is set
  * @param option Flag for which we are looking e.g. "-h"
  * @return       true if set, false if not
  */
  bool cmdOptionExists(const std::string &option) const;

  /**
   * Calculates the number of unkown flags provided, which can be used as number of files counter
   * @param  knownFlags Vector of unkown flags
   * @return            Number of unkown flags
   */
  int numberOfFiles(std::vector<std::string> knownFlags);

};

#endif /* END __ARGUMENTPARSER_HPP__ */
