#ifndef __MCCCOMMON_HPP__
#define __MCCCOMMON_HPP__


#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>


void writeToFile(const std::string& file, const std::string& dot){
  std::ofstream outfile;
  outfile.open(file, std::ios::trunc);
  outfile << dot << std::endl;
  outfile.close();
}


#endif /* END __MCCCOMMON_HPP__ */
