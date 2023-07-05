/*!	\file		helpers.h
	\author		Alejandro Ramirez (Reference from Lecture)
	\date		2019-01-24

	Array abstract data type.
*/

#define _CRT_DEBUG_MAP_ALLOC
#include <crtdbg.h>				// CRT = C-RunTime, DBG=debug (Microsoft specific file)
#include <stdlib.h>				// malloc, etc.

#include <stdint.h>
#include <stdbool.h>

// like a class without methods/constructors
typedef struct {
	size_t		amtElements;
	size_t		maxCap;
	double*		data;
} my_array;


// declare that this function will exist, but not here
my_array my_array_init();
bool my_array_push_back(my_array* pArray, double datum);
void my_array_free(my_array* pArray);