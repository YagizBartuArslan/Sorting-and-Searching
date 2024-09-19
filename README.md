# Project Overview
This project is a solution to Homework #4 from the CS300 course at Sabancı University. The task involves sorting an unsorted phonebook using four comparison-based sorting algorithms and searching for names using two search algorithms. The program measures and compares the performance of each algorithm to identify the most efficient approach.

## Sorting Algorithms Implemented:
Insertion Sort: A simple, but less efficient sorting method for larger datasets.
Quick Sort (pivot = median, with Insertion Sort for subarrays < 10): A faster sorting method, especially for large datasets.
Merge Sort (in-place): A divide-and-conquer sorting algorithm that performs efficiently, without auxiliary memory storage.
Heap Sort: A sorting method based on the heap data structure.

## Searching Algorithms Implemented:
Sequential Search: A linear search method, which compares each entry one by one.
Binary Search: A fast search method that operates on sorted data, using divide-and-conquer to quickly locate the target.

## Features
Phonebook Loading: The program reads an unsorted phonebook from a text file and loads it into multiple vectors to be sorted using different algorithms.
Full and Partial Name Search: Allows searching for full or partial names in the phonebook, returning all matches.
Performance Measurements: Sorting and searching times are measured in nanoseconds, and speedups between algorithms are calculated.
Comparison of Algorithms: Provides a detailed comparison of execution times for both sorting and searching, along with calculated speedups.

## How It Works
Input: The program asks for a file containing the phonebook and a search query (either full or partial name).
Sorting: Four different sorting algorithms (Insertion, Quick, Merge, Heap) are applied to the dataset, and their execution times are measured.
Searching: Sequential and Binary searches are performed on the sorted data, and the search times are compared.
Output: The program displays the sorting and search times, the speedups between algorithms, and the search results.

## Sample Input
Please enter the contact file name:
PhoneBook-sample1.txt
Please enter the word to be queried:
Robert

## Sample Output
Sorting the vector copies
======================================
Quick Sort Time: 78328 Nanoseconds
Insertion Sort Time: 480387 Nanoseconds
Merge Sort Time: 373165 Nanoseconds
Heap Sort Time: 137644 Nanoseconds

Searching for Robert
======================================
ROBERT CAMACHO +905556997035 Istanbul
ROBERT COY +905559274775 Bursa
...

Binary Search Time: 2370 Nanoseconds
Sequential Search Time: 62255 Nanoseconds

SpeedUp between Search Algorithms
======================================
(Sequential Search/ Binary Search) SpeedUp = 26.27

SpeedUps between Sorting Algorithms
======================================
(Insertion Sort/ Quick Sort) SpeedUp = 6.13
(Merge Sort / Quick Sort) SpeedUp = 4.76
...
## Setup
Clone the repository:
git clone https://github.com/your-repo/cs300-homework4-sorting-searching.git
cd cs300-homework4-sorting-searching

Compile the C++ code:
g++ -std=c++11 bartu.arslan_Arslan_YagizBartu_HW4.cpp -o phonebook_sort_search

Run the program:
./phonebook_sort_search

## Code Structure
bartu.arslan_Arslan_YagizBartu_HW4.cpp: The main file containing the implementation of sorting and searching algorithms.
PhoneBook-sample1.txt and PhoneBook-sample2.txt: Sample phonebook data used for testing.
