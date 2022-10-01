#pragma once

#include <thread>
//#include <unistd.h>

#include "BetterQuickSort.h"

template <class _Compare, class _RandomAccessIterator>
void __half_quick_merge_sort(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
	typedef typename std::iterator_traits<_RandomAccessIterator>::difference_type difference_type;
	typedef typename std::iterator_traits<_RandomAccessIterator>::value_type value_type;

	difference_type __len = __last - __first;

	// if we can not divide into two parts
	if (__len < 2)
		return;

	difference_type __l2 = __len / 2;
	_RandomAccessIterator __mid = __first + __l2;

	// sort two halves of the array
	__better_quick_sort<_Compare>(__first, __mid, __comp);
	__better_quick_sort<_Compare>(__mid, __last, __comp);
	
	// merge this two halves
	std::vector<value_type> __leftArray, __rightArray;
	std::copy(__first, __mid, std::back_inserter(__leftArray));
	std::copy(__mid, __last, std::back_inserter(__rightArray));
	__merge<_Compare>(__leftArray.begin(), __leftArray.end(),
		__rightArray.begin(), __rightArray.end(), __first, __comp);
}

template <class _Compare, class _RandomAccessIterator>
void __better_half_quick_merge_sort(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
	typedef typename std::iterator_traits<_RandomAccessIterator>::difference_type difference_type;
	typedef typename std::iterator_traits<_RandomAccessIterator>::value_type value_type;

	difference_type __len = __last - __first;

	// if we can not divide into two parts
	if (__len < 2)
		return;

	difference_type __l2 = __len / 2;
	_RandomAccessIterator __mid = __first + __l2;

	// sort two halves of the array
	std::thread __half1(__better_quick_sort<_Compare, _RandomAccessIterator>, __first, __mid, __comp);
	std::thread __half2(__better_quick_sort<_Compare, _RandomAccessIterator>, __mid, __last, __comp);
	__half1.join();
	__half2.join();
	
	// merge this two halves
	std::vector<value_type> __leftArray, __rightArray;
	std::copy(__first, __mid, std::back_inserter(__leftArray));
	std::copy(__mid, __last, std::back_inserter(__rightArray));
	__merge<_Compare>(__leftArray.begin(), __leftArray.end(),
		__rightArray.begin(), __rightArray.end(), __first, __comp);
}

template <class _Compare, class _RandomAccessIterator>
void __four_quick_merge_sort(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
	typedef typename std::iterator_traits<_RandomAccessIterator>::difference_type difference_type;
	typedef typename std::iterator_traits<_RandomAccessIterator>::value_type value_type;

	difference_type __len = __last - __first;

	// if we can not divide into four parts
	if (__len < 4)
		return;

	difference_type __l4 = __len / 4;
	_RandomAccessIterator __x1 = __first + __l4, __x2 = __first + 2 * __l4, __x3 = __first + 3 * __l4;

	/*
	// sort four quads of the array in four threads
	std::thread __quad1(__better_quick_sort<_Compare, _RandomAccessIterator>, __first, __x1, __comp);
	std::thread __quad2(__better_quick_sort<_Compare, _RandomAccessIterator>, __x1, __x2, __comp);
	std::thread __quad3(__better_quick_sort<_Compare, _RandomAccessIterator>, __x2, __x3, __comp);
	std::thread __quad4(__better_quick_sort<_Compare, _RandomAccessIterator>, __x3, __last, __comp);
	__quad1.join();
	__quad2.join();
	__quad3.join();
	__quad4.join();

	// merge this four quads
	std::vector<value_type> __array1, __array2, __array3, __array4;
	std::copy(__first, __x1, std::back_inserter(__array1));
	std::copy(__x1, __x2, std::back_inserter(__array2));
	std::copy(__x2, __x3, std::back_inserter(__array3));
	std::copy(__x3, __last, std::back_inserter(__array4));
	//*/

	///*
	std::vector<value_type> __array1, __array2, __array3, __array4;
	std::copy(__first, __x1, std::back_inserter(__array1));
	std::copy(__x1, __x2, std::back_inserter(__array2));
	std::copy(__x2, __x3, std::back_inserter(__array3));
	std::copy(__x3, __last, std::back_inserter(__array4));

	int pid = fork();

	if (pid == 1) {
		std::thread __quad1(__better_quick_sort<_Compare, _RandomAccessIterator>, __array1.begin(), __array1.end(), __comp);
		std::thread __quad2(__better_quick_sort<_Compare, _RandomAccessIterator>, __array2.begin(), __array2.end(), __comp);
		__quad1.join();
		__quad2.join();
	}
	else {
		std::thread __quad3(__better_quick_sort<_Compare, _RandomAccessIterator>, __array3.begin(), __array3.end(), __comp);
		std::thread __quad4(__better_quick_sort<_Compare, _RandomAccessIterator>, __array4.begin(), __array4.end(), __comp);
		__quad3.join();
		__quad4.join();
	}
	//*/

	/*
	std::vector<value_type> __array1, __array2, __array3, __array4;
	std::copy(__first, __x1, std::back_inserter(__array1));
	std::copy(__x1, __x2, std::back_inserter(__array2));
	std::copy(__x2, __x3, std::back_inserter(__array3));
	std::copy(__x3, __last, std::back_inserter(__array4));

	int pid = fork(), ppid = fork();

	if (pid == 1 && ppid == 1) {
		std::thread __quad1(__better_quick_sort<_Compare, _RandomAccessIterator>, __array1.begin(), __array1.end(), __comp);
		__quad1.join();
	}
	else if (pid == 1 && ppid == 0) {
		std::thread __quad2(__better_quick_sort<_Compare, _RandomAccessIterator>, __array2.begin(), __array2.end(), __comp);
		__quad2.join();
	}
	else if (pid == 0 && ppid == 1) {
		std::thread __quad3(__better_quick_sort<_Compare, _RandomAccessIterator>, __array3.begin(), __array3.end(), __comp);
		__quad3.join();
	}
	else {
		std::thread __quad4(__better_quick_sort<_Compare, _RandomAccessIterator>, __array4.begin(), __array4.end(), __comp);
		__quad4.join();
	}
	//*/

	__merge<_Compare>(__array1.begin(), __array1.end(),
		__array2.begin(), __array2.end(), __first, __comp);
	__merge<_Compare>(__array3.begin(), __array3.end(),
		__array4.begin(), __array4.end(), __x2, __comp);

	// merge this two halves
	std::vector<value_type> __leftArray, __rightArray;
	std::copy(__first, __x2, std::back_inserter(__leftArray));
	std::copy(__x2, __last, std::back_inserter(__rightArray));
	__merge<_Compare>(__leftArray.begin(), __leftArray.end(),
		__rightArray.begin(), __rightArray.end(), __first, __comp);
}

template <class _RandomAccessIterator>
void halfQuickMergeSort(_RandomAccessIterator __first, _RandomAccessIterator __last)
{
	__half_quick_merge_sort(__first, __last,
		__less<typename std::iterator_traits<_RandomAccessIterator>::value_type>());
}

template <class _Compare, class _RandomAccessIterator>
void halfQuickMergeSort(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
	__half_quick_merge_sort<_Compare>(__first, __last, __comp);
}

template <class _RandomAccessIterator>
void betterHalfQuickMergeSort(_RandomAccessIterator __first, _RandomAccessIterator __last)
{
	__better_half_quick_merge_sort(__first, __last,
		__less<typename std::iterator_traits<_RandomAccessIterator>::value_type>());
}

template <class _Compare, class _RandomAccessIterator>
void betterHalfQuickMergeSort(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
	__better_half_quick_merge_sort<_Compare>(__first, __last, __comp);
}

template <class _RandomAccessIterator>
void fourQuickMergeSort(_RandomAccessIterator __first, _RandomAccessIterator __last)
{
	__four_quick_merge_sort(__first, __last,
		__less<typename std::iterator_traits<_RandomAccessIterator>::value_type>());
}

template <class _Compare, class _RandomAccessIterator>
void fourQuickMergeSort(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
	__four_quick_merge_sort<_Compare>(__first, __last, __comp);
}