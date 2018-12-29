#include <vector>
#include <iterator>
#include <iostream>

template <class T, class Comparator>
void QuickSort (std::vector<T> &myArray, Comparator comp);

template <class T, class Comparator>
void helper(std::vector<T> &myArray, long int start, long int end, Comparator comp);

template <class T, class Comparator>
T MedianOfThree(std::vector<T> &myArray, long int start, long int end, Comparator comp);

template <class T, class Comparator> //find median of the start end and middle
T MedianOfThree(std::vector<T> &myArray, long int start, long int end, Comparator comp){

	T begin = myArray[start];
	T middle = myArray[(start + end)/2];
	T finish = myArray[end];

	if(comp(finish, middle)){//check if end is smaller than middle
		std::swap(myArray[(start + end)/2], myArray[end]);//swap
	}
	if(comp(middle, begin)){//check if middle is smaller than start
		std::swap(myArray[(start + end)/2], myArray[start]);//swap
	}
	if(comp(finish, begin)){//check if end is smaller than start
		std::swap(myArray[end], myArray[start]);//swap
	}
	return myArray[(start + end)/2];

}

template <class T, class Comparator>
void QuickSort (std::vector<T> &myArray, Comparator comp){
	if(myArray.size() == 0) return;

	long int s = 0;
	long int e = myArray.size() - 1;
	helper(myArray, s, e, comp);
}

template <class T, class Comparator>
void helper(std::vector<T> &myArray, long int start, long int end, Comparator comp){
	long int i = start;
	long int j = end;
	T pivot = MedianOfThree(myArray, start, end, comp);
	while(i <= j){
		while(comp(myArray[i], pivot)){//check if at i value is less than pivot
			i++;//if so increase i
		}
		while(comp(pivot, myArray[j])){
			j--;//do same for j but if greater than pivot
		}
		if(i <= j){
			std::swap(myArray[i], myArray[j]);
			i++;
			j--;
		}
	}
	if (i < end){
        helper(myArray, i, end, comp);
	}
	
	if(start < j){ 
        helper(myArray, start, j, comp);
   }
}