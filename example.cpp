
#include <header.hpp>

int main() {

    // 1-dim vector
    MyOstreamIterator<int> myOstreamIter_vec1(std::cout, " ");
    std::vector<int> vec1 = {1, 2, 3, 4, 5};
    std::copy(vec1.begin(), vec1.end(), myOstreamIter_vec1);
    std::cout << std::endl;

    // 3-dim vector
    MyOstreamIterator<std::vector<std::vector<int>>> myOstreamIter_vec2(std::cout, " ");
    std::vector<std::vector<std::vector<int>>> vec2 = {{{2, 3}, {4, 5, 1, 4}}, {{3}, {2, 3}}};
    std::copy(vec2.begin(), vec2.end(), myOstreamIter_vec2);
    std::cout << std::endl;

    // Utilizzo con std::list
    MyOstreamIterator<int> myOstreamIter_list(std::cout, " ");
    std::list<int> myList = {10, 20, 30, 40, 50};
    std::copy(myList.begin(), myList.end(), myOstreamIter_list);
    std::cout << std::endl;

    // Utilizzo con std::list of vector
    MyOstreamIterator<std::vector<int>> myOstreamIter_list_vec(std::cout, " ");
    std::list<std::vector<int>> myList_vec = {{1, 2, 3}, {2, 3}};
    std::copy(myList_vec.begin(), myList_vec.end(), myOstreamIter_list_vec);
    std::cout << std::endl;

    // Utilizzo con std::map
    MyOstreamIterator<int, std::string> myOstreamIter_map(std::cout, " ");
    std::map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};
    std::copy(myMap.begin(), myMap.end(), myOstreamIter_map);
    std::cout << std::endl;

    // Utilizzo con std::map nested
    // MyOstreamIterator<std::vector<int>, std::string> myOstreamIter_map_vec(std::cout, " ");
    // std::map<std::vector<int>, std::string> myMap_vec = {{{1, 2}, "one"}, {{2, 4}, "two"}, {{3, 5}, "three"}};
    // std::copy(myMap_vec.begin(), myMap_vec.end(), myOstreamIter_map_vec);
    // std::cout << std::endl;

    // Utilizzo con std::array
    MyOstreamIterator<int> myOstreamIter_array(std::cout, " ");
    std::array<int, 3> myArray = {1, 2, 3};
    std::copy(myArray.begin(), myArray.end(), myOstreamIter_array);
    std::cout << std::endl;

    // Utilizzo con std::array of vec
    MyOstreamIterator<std::vector<int>> myOstreamIter_array_vec(std::cout, " ");
    std::array<std::vector<int>, 3> myArray_vec;
    myArray_vec[0] = {1, 2, 3};
    myArray_vec[1] = {4, 5, 6};
    myArray_vec[2] = {7, 8, 9};
    std::copy(myArray_vec.begin(), myArray_vec.end(), myOstreamIter_array_vec);
    std::cout << std::endl;

    return 0;
}