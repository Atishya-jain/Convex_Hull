#ifndef UTIL_H
#define	UTIL_H
#include <vector>
#include <utility>
#include <string>
using namespace std;


/**
 * Utility Function to split string message, using give delimiter. The result is stored in result[] array.
 * 
 * @param message string to be splitted
 * @param delimter delimiter used to split string
 * @param result result will be stored in this array
 * @param expcted length of the result
 */
void splitString(string message, string delimiter, float result[], int n);

/**
 * Utility Function to input from a file, using given filename. The result is stored in inp vector given as input.
 * 
 * @param filename string to be read
 * @param vector to store the triplets of coordinates
 */
void get_input(string filename, vector<pair<float,pair<float,float>>> &inp);

/**
 * Utility Function to output to a file, given filename.
 * 
 * @param filename string to be read
 * @param vector with stored the triplets of coordinates
 */
void get_output(string filename, vector<pair<float, pair<float,float>>> &out);

#endif	/* UTIL_H */