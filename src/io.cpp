#include <fstream>
#include <iostream>

#include "io.h"

void io::write_result(int result)
{
	std::ofstream file;
	
	// Create file if it doesn't exist
    file.open(FILEPATH, std::ios::out | std::ios::app);

    // Make sure write fails with exception if something is wrong
    file.exceptions(file.exceptions() | std::ios::failbit | std::ifstream::badbit);

    file << result << std::endl;
}