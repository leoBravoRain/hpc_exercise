#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>

#include <cmath>

#define M 10

// Print array
int print_array(int n, int *array){

	printf("printint array\n");

	for(int i = 0; i < n; ++i){

		printf("%i\n", array[i]);

	}

	printf("finish printing array\n");

}

// Binary search
int binary_search(int n, int *array, int element, int left, int right){

	// printf("binary search with left: %i and right: %i\n",left, right);
	// Declare variables
	// int left, right, middle;
	int middle, result;

	// result
	result = -1;

	// flag find elmenet
	bool find = false;

	// initial values
	// left = 0;
	// right = n - 1;

	// Iteratae until find solution
	while(left <= right & !find){

		// printf("left: %i  --  right:  %i\n", left, right);

		middle = (left + right) >> 1; // biwtsie operation

		// printf("middle: %i, array element is %i \n", middle, array[middle]);

		// If element is smaller than m
		if(array[middle] > element){

			// printf("%i is smaller than %i, so update right to %i \n", element, array[middle], middle - 1);
			// update right
			right = middle - 1;

		}

		// if element is greater than m
		else if(array[middle] < element){

			// update left
			left = middle + 1;

		}

		// If the element is in middle
		else{

			// printf("The element %i is in %i\n", element, middle );

			// Update result
			result =  middle;
			find = true;

		}

	}

	// Message
	if(!find){

		// If element is not in array
		// printf("element %i is not in array \n", element);

	}
	
	// return result
	return result;

}

// Create samping array
void build_sampling_array(int *array, int sampling, int *sampling_array, int n_samp){

	// Iterate in sampling length
	for(int i = 0; i <= n_samp; ++i){

		// Assin vale to sampling element
		sampling_array[i] = array[i*sampling];

	}


}

// Sequential seach
int sequential_search(int left, int right, int *array, int element){

	// flag
	// bool find = false;

	// result
	int result = -1;

	// Iterate through the array
	for(int i = left; i <= right; ++i){

		// if it's the same, return result
		if(element == array[i]){

			// update variables
			// find = true;
			result = i;
			break;

		}

	}

	// return results
	return result;

}
// Searching using binary search (hacking) on sampling array and then scanning the block
// sampling is sampling size
int sampling_binary_search(int n, int *array, int sampling, int element, int *sampling_array, int n_samp){

	// printf("binary search new\n");

	// printf("binary search with left: %i and right: %i\n",left, right);
	// Declare variables
	int left, right, middle, result;
	// bool find_in_last_block = false;

	// flag if number it could be in any block
	bool find_block = false;

	// int middle, result;

	// result
	result = -1;

	// flag find elmenet
	// bool find = false;

	// initial values
	left = 0;
	right = n - 1;

	// // If elemnt is greater than the last element in sampling array
	// // it can be the element is in the last block
	// // if(!in_firsts_blocks){
	// if(element >= sampling_array[n_samp - 1]){

	// 	printf("Maybe it's in the last block\n");

	// 	// Binary search in the last block
	// 	// Left = lenght of array - (sampling size - 1)
	// 	left = n - (sampling - 1);

	// 	// Right = length of array - 1
	// 	right = n - 1;

	// 	// printf("Binary search in the last block\n");
	// 	// sequential_search(int left, int right, int *array, int element)
	// 	result = sequential_search(left, right, array, element);

	// 	// flag variable
	// 	find_in_last_block = true;

	// }

	// Iteratae until find solution
	// while(left <= right & !find){
	while(left <= right){
	// while(left <= right & !find_in_last_block){

		// printf("left: %i  --  right:  %i\n", left, right);
		middle = (left + right) >> 1; // biwtsie operation

		// printf("middle: %i, array element is %i \n", middle, array[middle]);

		// If element is smaller than m
		if(element < sampling_array[middle]){

			// if element is between m-1 and m
			if(element >= sampling_array[middle - 1]){

				// printf("find block smaller\n");
				// Sequential search in this block (block between m-1 and m)
				// arguments = left, right, array, element
				// sequential_search(int left, int right, int *array, int element)
				result = sequential_search(std::max((middle - 1)*sampling, 0), (middle)*sampling, array, element);

				// update flag
				find_block = true;

				break;

			}

			// If is smaller than m-1 element
			else{

				// printf("%i is smaller than %i, so update right to %i \n", element, array[middle], middle - 1);
				// update right
				right = middle - 1;

			}


		}

		// if element is greater than m
		else if(element > sampling_array[middle]){

			// if element is between m-1 and m
			if(element <= sampling_array[middle + 1]){

				// printf("find block greater\n");

				// Sequential search in this block (block between m-1 and m)
				// arguments = left, right, array, element
				result = sequential_search((middle)*sampling, std::min((middle + 1)*sampling, n), array, element);

				// update flag
				find_block = true;

				break;

			}

			else{

				// update left
				left = middle + 1;

			}

		}

		// If the element is in middle
		else{

			// printf("The element %i is in %i\n", element, middle );

			// printf("find block equal\n");

			// Update result
			result =  (middle)*sampling;
			// find = true;

			// update flag
			find_block = true;

			break;

		}

	}

	// If elemnt is greater than the last element in sampling array
	// it can be the element is in the last block
	// if(!in_firsts_blocks){
	if(!find_block & element >= sampling_array[n_samp - 1]){

		printf("Maybe it's in the last block\n");

		// Binary search in the last block
		// Left = lenght of array - (sampling size - 1)
		left = n - (sampling - 1);

		// Right = length of array - 1
		right = n - 1;

		// printf("Binary search in the last block\n");
		// sequential_search(int left, int right, int *array, int element)
		result = sequential_search(left, right, array, element);

		// // flag variable
		// find_in_last_block = true;

	}

	// // Message
	// if(!find){

	// 	// If element is not in array
	// 	printf("element %i is not in array \n", element);

	// }
	
	// return result
	return result;

}

// Searching using samplign and binary search
// This is wrong because it do a sequential search through sampling array and then do a binary search on the block
// int sampling_binary_search_wrong_version(int n, int *array, int sampling, int element){
int sampling_binary_search_wrong_version(int n, int *array, int sampling, int element, int *sampling_array){

	// binary search variables
	int left, right, result;

	// result
	result = -1;

	// Get length of sampling array
	int n_samp = n/sampling;

	// // Define sampling array
	// int sampling_array[n_samp];

 //    // Buidl sampling array
	// build_sampling_array(array, sampling, sampling_array, n_samp);

	// Flag for indicate that element is in array OR It's not in the FINAL block 
	// (when it's in the final block, it can be that the element is greater than 
	// the last element in the sampling array)
	bool in_firsts_blocks = false;

	// printf("printing array \n");

	// print_array(n_samp, sampling_array);

	// If elemnt is greater than the last element in sampling array
	// it can be the element is in the last block
	// if(!in_firsts_blocks){
	if(element >= sampling_array[n_samp - 1]){

		// printf("Maybe it's in the last block\n");

		// Binary search in the last block
		// Left = lenght of array - (sampling size - 1)
		left = n - (sampling - 1);

		// Right = length of array - 1
		right = n - 1;

		// printf("Binary search in the last block\n");

		result = binary_search(n, array, element, left, right);

	}

    // Iterate over each element in sampling array
	for(int i = 0; i < n_samp & !in_firsts_blocks; i++){

    	// If element is smaller or equal than sampling array element
		if(element <= sampling_array[i]){

			// Define left as sampling * (i -1)
			left = std::max(0, (i-1)*sampling);

			// Define right as sampling * i
			right = (i)*sampling;

			// Update flag
			in_firsts_blocks = true;

			// printf("ijosdjas\n");

			// Do binarysearch betweetn left and right
			result = binary_search(n, array, element, left, right);

		}

	}

	// // If elemnt is greater than the last element in sampling array
	// // it can be the element is in the last block
	// if(!in_firsts_blocks){

	// 	// printf("Maybe it's in the last block\n");

	// 	// Binary search in the last block
	// 	// Left = lenght of array - (sampling size - 1)
	// 	left = n - (sampling - 1);

	// 	// Right = length of array - 1
	// 	right = n - 1;

	// 	// printf("Binary search in the last block\n");

	// 	result = binary_search(n, array, element, left, right);

	// }

	return result;


}

//  Create an non-decreasing array
void create_array(int n, int *array){

	// Initial value
	array[0] = 0;

	int inc;

	// Iterate over each elmenet
	// from 1 to n-1
	for(int i = 1; i < n; i++){

		// Crate random inc value
		// M is defined in header
		inc = rand() % M;    

		// printf("random: %i\n", inc);

		// Define next element
		array[i] = array[i-1] + inc;

	}

}

int main(int argc, char *argv[]){

	// Check arguments
	if(argc != 3){

		printf("run as ./prog number_elements sampling_size(32, 64, etc)\n");

		exit(EXIT_FAILURE);
	}

	/* initialize random seed: */
  	srand (time(NULL));

	// Declare
	int n, element, sampling_size;
	// Initialize variabels
	n = atoi(argv[1]);
	// n = 5;
	sampling_size = atoi(argv[2]);
	// sampling_size = 2;

	// Random element
	// element = rand() % M; ;
	element = 0;

	// Define array
	// int array [n] = { 0, 1, 2, 3, 4}; 

	// print_array(n, array);

	int array [n];

	// Create array 
	create_array(n, array);

	// printf("binary search\n");

	clock_t begin = clock();

	// Brute force binary search
	// arguments: length of array, array, elemento to find, left, right
	int result = binary_search(n, array, element, 0, n-1);

	// Finish time
	clock_t end = clock();

  	// printf("Binary search: %f [ms]\n", 1000*double(end - begin) / CLOCKS_PER_SEC); 

	// printf("result: %i\n", result);

	// printf("Sampling binary search\n");


	// Get length of sampling array
	int n_samp = ceil((double)n/(double)sampling_size);

	// Define sampling array
	int sampling_array[n_samp];

	// Buidl sampling array
	build_sampling_array(array, sampling_size, sampling_array, n_samp);

	// print_array(n_samp, sampling_array);

	begin = clock();

	// Sampling binary search
	// sampling_binary_search_wrong_version(int n, int *array, int sampling, int element)
	// int result_samp = sampling_binary_search_wrong_version(n, array, sampling_size, element);
	// int result_samp = sampling_binary_search_wrong_version(n, array, sampling_size, element, sampling_array);
	int result_samp = sampling_binary_search(n, array, sampling_size, element, sampling_array, n_samp);

	// Finish time
	end = clock();

	// print time
  	// printf("Sampling binary search: %f [ms]\n", 1000*double(end - begin) / CLOCKS_PER_SEC); 

	// printf("result: %i\n", result_samp);

	// Compare results
	if(result != result_samp){

		// printf("Results are equals\n");
		printf("ERROR: Results are NOT equals. Element: %i\nBS: %i\n BS sampling: %i\n", element, result, result_samp);

		print_array(n, array);

	}

	// else if(result == result_samp){

		// printf("Results ARE equals. Element: %i\nBS: %i\n BS sampling: %i\n", element, result, result_samp);		

	// }



	// printf("element: %i\n", element);

	// Print array
	// print_array(n, array);

	// Return to OS
	return 0;

}