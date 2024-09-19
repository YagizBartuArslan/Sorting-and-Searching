#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <cctype>



//                                            CS300 - Homework #4 – Sorting and Searching
// 
// Author: Yaðýz Bartu Arslan - Junior Computer Science Student in Sabanci University
// Start Date: 20.05.2024 
// End Date: 29.05.2024

// Information: The implementations of Sort algorithms inspired by Gülþen Demiröz (CS300 Instructor in Sabanci University) 's slides.


using namespace std;
using namespace std::chrono;

struct Contact {
    string name;
    string surname;
    string telephone;
    string city;

    bool operator<(const Contact& other) const {
        return compareContacts(*this, other);
    }

    bool operator<=(const Contact& other) const {
        return *this < other || (name == other.name && surname == other.surname);
    }

    bool operator==(const Contact& other) const {
        return name == other.name && surname == other.surname;
    }

    friend ostream& operator<<(ostream& os, const Contact& c) {
        os << toUpperCase(c.name) << " " << toUpperCase(c.surname) << " " << c.telephone << " " << toUpperCase(c.city);
        return os;
    }

public:
    // Helper function to convert string to uppercase
    static string toUpperCase(const string& str) {
        string result = str;
        transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }

    // Custom comparison for sorting by full name (name + surname)
    static bool compareContacts(const Contact& a, const Contact& b) {
        string fullNameA = toUpperCase(a.name) + " " + toUpperCase(a.surname);
        string fullNameB = toUpperCase(b.name) + " " + toUpperCase(b.surname);
        return fullNameA < fullNameB;
    }
};

vector<Contact> readPhoneBook(const string& filename) {
    vector<Contact> phoneBook;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        Contact contact;
        iss >> contact.name >> contact.surname >> contact.telephone >> contact.city;
        phoneBook.push_back(contact);
    }
    return phoneBook;
}

// Insertion Sort
template <class Comparable>
void insertionSort(vector<Comparable>& a) {
    for (int p = 1; p < a.size(); p++) {
        Comparable tmp = a[p];
        int j;
        for (j = p; j > 0 && tmp < a[j - 1]; j--)
            a[j] = a[j - 1];
        a[j] = tmp;
    }
}

// Merge Sort
template <class Comparable>
void merge(vector<Comparable>& a, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<Comparable> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = a[left + i];
    for (int j = 0; j < n2; j++) R[j] = a[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) a[k++] = L[i++];
        else a[k++] = R[j++];
    }
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
}

template <class Comparable>
void mergeSort(vector<Comparable>& a, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}

template <class Comparable>
void mergeSort(vector<Comparable>& a) {
    mergeSort(a, 0, a.size() - 1);
}

// Heap Sort
template <class Comparable>
void percDown(vector<Comparable>& a, int i, int n) {
    int child;
    Comparable tmp = a[i];
    for (; 2 * i + 1 < n; i = child) {
        child = 2 * i + 1;
        if (child != n - 1 && a[child] < a[child + 1]) child++;
        if (tmp < a[child]) a[i] = a[child];
        else break;
    }
    a[i] = tmp;
}

template <class Comparable>
void heapSort(vector<Comparable>& a) {
    for (int i = a.size() / 2 - 1; i >= 0; i--)
        percDown(a, i, a.size());
    for (int j = a.size() - 1; j > 0; j--) {
        swap(a[0], a[j]);
        percDown(a, 0, j);
    }
}

// Quick Sort
template <class Comparable>
const Comparable& median3(vector<Comparable>& a, int left, int right) {
    int center = (left + right) / 2;
    if (a[center] < a[left]) swap(a[left], a[center]);
    if (a[right] < a[left]) swap(a[left], a[right]);
    if (a[right] < a[center]) swap(a[center], a[right]);
    swap(a[center], a[right - 1]);
    return a[right - 1];
}

template <class Comparable>
void quicksort(vector<Comparable>& a, int left, int right) {
    if (left + 10 <= right) {
        Comparable pivot = median3(a, left, right);
        int i = left, j = right - 1;
        for (;;) {
            while (a[++i] < pivot) {}
            while (pivot < a[--j]) {}
            if (i < j) swap(a[i], a[j]);
            else break;
        }
        swap(a[i], a[right - 1]);
        quicksort(a, left, i - 1);
        quicksort(a, i + 1, right);
    }
    else {
        insertionSort(a, left, right);
    }
}

template <class Comparable>
void quicksort(vector<Comparable>& a) {
    quicksort(a, 0, a.size() - 1);
}

// Insertion Sort (used within Quick Sort for small subarrays)
template <class Comparable>
void insertionSort(vector<Comparable>& a, int left, int right) {
    for (int p = left + 1; p <= right; p++) {
        Comparable tmp = a[p];
        int j;
        for (j = p; j > left && tmp < a[j - 1]; j--)
            a[j] = a[j - 1];
        a[j] = tmp;
    }
}

// Sequential Search
vector<int> sequentialSearch(const vector<Contact>& a, const string& key) {
    vector<int> results;
    string upperKey = Contact::toUpperCase(key);
    for (int i = 0; i < a.size(); ++i) {
        string fullName = Contact::toUpperCase(a[i].name + " " + a[i].surname);
        if (fullName.find(upperKey) == 0) {
            results.push_back(i);
        }
    }
    return results;
}

// Binary Search
vector<int> binarySearch(const vector<Contact>& a, const string& key) {
    vector<int> results;
    string upperKey = Contact::toUpperCase(key);
    int left = 0, right = a.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        string fullName = Contact::toUpperCase(a[mid].name + " " + a[mid].surname);
        if (fullName.find(upperKey) == 0) {
            // Find all matches around mid
            int l = mid;
            while (l >= left && Contact::toUpperCase(a[l].name + " " + a[l].surname).find(upperKey) == 0) {
                results.push_back(l);
                l--;
            }
            int r = mid + 1;
            while (r <= right && Contact::toUpperCase(a[r].name + " " + a[r].surname).find(upperKey) == 0) {
                results.push_back(r);
                r++;
            }
            break;
        }
        else if (fullName < upperKey) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    // Sort the results by full name (name + surname)
    sort(results.begin(), results.end(), [&](int i, int j) {
        return Contact::toUpperCase(a[i].name + " " + a[i].surname) < Contact::toUpperCase(a[j].name + " " + a[j].surname);
        });
    return results;
}

// Measure time and display sorting times and speedups
template <typename Func>
long long measureSortTime(Func sortFunction, vector<Contact>& contacts) {
    auto start = high_resolution_clock::now();
    sortFunction(contacts);
    auto end = high_resolution_clock::now();
    return duration_cast<nanoseconds>(end - start).count();
}

void printContacts(const vector<Contact>& contacts, const vector<int>& indices) {
    for (const auto& index : indices) {
        cout << contacts[index] << endl;
    }
}

int main() {
    string filename;
    cout << "Please enter the contact file name:\n";
    cin >> filename;
    cout << "Please enter the word to be queried:\n";
    string query;
    cin.ignore();
    getline(cin, query);

    vector<Contact> phoneBook = readPhoneBook(filename);

    vector<Contact> phoneBookInsertion = phoneBook;
    vector<Contact> phoneBookQuick = phoneBook;
    vector<Contact> phoneBookMerge = phoneBook;
    vector<Contact> phoneBookHeap = phoneBook;

    long long insertionSortTime = measureSortTime([](vector<Contact>& contacts) { insertionSort(contacts); }, phoneBookInsertion);
    long long quickSortTime = measureSortTime([](vector<Contact>& contacts) { quicksort(contacts); }, phoneBookQuick);
    long long mergeSortTime = measureSortTime([](vector<Contact>& contacts) { mergeSort(contacts); }, phoneBookMerge);
    long long heapSortTime = measureSortTime([](vector<Contact>& contacts) { heapSort(contacts); }, phoneBookHeap);

    cout << "Sorting the vector copies\n";
    cout << "======================================\n";
    cout << "Quick Sort Time: " << quickSortTime << " Nanoseconds\n";
    cout << "Insertion Sort Time: " << insertionSortTime << " Nanoseconds\n";
    cout << "Merge Sort Time: " << mergeSortTime << " Nanoseconds\n";
    cout << "Heap Sort Time: " << heapSortTime << " Nanoseconds\n";

    cout << "Searching for " << query << "\n";
    cout << "======================================\n";

    auto start = high_resolution_clock::now();
    vector<int> binarySearchResults = binarySearch(phoneBookQuick, query);
    auto end = high_resolution_clock::now();
    long long binarySearchTime = duration_cast<nanoseconds>(end - start).count();

    cout << "Binary Search Time: " << binarySearchTime << " Nanoseconds\n";

    if (!binarySearchResults.empty()) {
        cout << "Binary Search Results:\n";
        printContacts(phoneBookQuick, binarySearchResults);
    }
    else {
        cout << query << " does NOT exist in the dataset\n";
    }

    start = high_resolution_clock::now();
    vector<int> sequentialSearchResults = sequentialSearch(phoneBookQuick, query);
    end = high_resolution_clock::now();
    long long sequentialSearchTime = duration_cast<nanoseconds>(end - start).count();

    cout << "Sequential Search Time: " << sequentialSearchTime << " Nanoseconds\n";



    if (!sequentialSearchResults.empty()) {
        cout << "Sequential Search Results:\n";
        printContacts(phoneBookQuick, sequentialSearchResults);
    }
    else {
        cout << query << " does NOT exist in the dataset\n";
    }

    cout << "SpeedUp between Search Algorithms\n";
    cout << "======================================\n";
    cout << "(Sequential Search/ Binary Search) SpeedUp = " << static_cast<double>(sequentialSearchTime) / binarySearchTime << "\n";

    cout << "SpeedUps between Sorting Algorithms\n";
    cout << "======================================\n";
    cout << "(Insertion Sort/ Quick Sort) SpeedUp = " << static_cast<double>(insertionSortTime) / quickSortTime << "\n";
    cout << "(Merge Sort / Quick Sort) SpeedUp = " << static_cast<double>(mergeSortTime) / quickSortTime << "\n";
    cout << "(Heap Sort / Quick Sort) SpeedUp = " << static_cast<double>(heapSortTime) / quickSortTime << "\n";

    return 0;
}
