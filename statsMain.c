/*
* program name: statsMain
* purpose: to compile statistics based on user or file input
* author: Alejandro Ramirez
* Date: June 14, 2021
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"

//insertion sort function
void insertionSort(double dataArr[], size_t amtElements) {
	for (size_t oneIdx = 1; oneIdx < amtElements; oneIdx++) {
		double key = dataArr[oneIdx];
		size_t zeroIdx = oneIdx - 1;

		//compare key with every number to its left, until a smaller element comes up
		while (key < dataArr[zeroIdx] && zeroIdx >= 0) {
			dataArr[zeroIdx + 1] = dataArr[zeroIdx];
			--zeroIdx;
		}
		dataArr[zeroIdx + 1] = key;
	}
}

int main(int argc, char* argv[]) {
	
	//File input stdin
	FILE* stream = stdin;
	
	//Ask the user to enter data
	printf("Enter a list of whitespace-separated real numbers terminated by EOF or 'end'.\n\n");
	
	double datum = 0;
	my_array dataSet = my_array_init();
	int returnedSc = 0;
	size_t i = 0;

	if (argc > 2) {
		printf("Error: too many command-line arguments (%d)\n", argc);
		printf("Usage: fcount [filename]\n"
			"\twhere filename is the name of a file.\n"
			"\tuses (keyboard) if there is no filename.\n"
		);
		return EXIT_FAILURE;
	}
	if (argc == 2) {
		if ((stream = fopen(argv[1], "rb")) == NULL) {
			printf("error <%s> not found.", argv[1]);
			return EXIT_FAILURE;
		}
	}
	
	char buffer[100] = {0};
	//Check user input while it is not the word 'end'
	while (((returnedSc = fscanf(stream, "%s", buffer)) != EOF)) {
		if ((strcmp(buffer, "end") == 0)) {
			break;
		}
		if (isdigit(buffer[0])) {
			datum = strtod(buffer, NULL);  
			my_array_push_back(&dataSet, datum);
		}
	}

	//sorting the data set
	insertionSort(dataSet.data, dataSet.amtElements);

	printf("__________________________________________________________________________\n");
	//# of elements in the data set
	printf("# elements %*zu", 15, dataSet.amtElements);

	//Stats calculations
	double min = dataSet.data[0];
	double max = dataSet.data[dataSet.amtElements - 1];
	double range = (dataSet.data[dataSet.amtElements - 1] - dataSet.data[0]);
	double median;
	//if odd:
	if (dataSet.amtElements % 2 == 0) {
		median = (dataSet.data[(dataSet.amtElements - 1) / 2] + dataSet.data[dataSet.amtElements / 2]) / 2;
	}
	//if even
	else {
		median = dataSet.data[dataSet.amtElements / 2];
	}
	//Mean
	double sum = 0;
	double arithMean = 0;
	for (i = 0; i < dataSet.amtElements; ++i) {
		sum += dataSet.data[i];
		arithMean = sum / dataSet.amtElements;
	}
	
//	//Arr to iterate through the numbers to find max length
//#define STATS_SZ 5u
//	double statsArr[STATS_SZ] = {min, max, range, median, arithMean};
//	for (i = 0; i < STATS_SZ; ++i) {
//		
//	}

	////reporting min and max values
	printf("\nminimum  %*.3lf\nmaximum %*.3lf", 15, min, 15, max);

	////What is the range of the data set
	printf("\nrange %*.3lf", 15, range);

	//Find the median
	printf("\nmedian %*.3lf", 15, median);

	////ToDo: Find the arithmetic mean - sum of all values divided by the number of values
	printf("\nmean %*.3lf", 15, arithMean);

	//Standard deviation and Variance
	double standardDev = 0;
	double variance = 0;
	for (i = 0; i < dataSet.amtElements; ++i) {
		variance += (double)pow(dataSet.data[i] - arithMean, 2.0);
	}
	variance = variance / dataSet.amtElements;
	standardDev = (double)sqrt(variance);

	printf("\nvariance %*.3lf\nstd. dev. %*.3lf\n", 15, variance, 15, standardDev);
	printf("__________________________________________________________________________\n");

	////TODO: Output
	//  //Frequency table
	//  //Histogram
	//  //log-transformed versions of both the above

	return 0;

}