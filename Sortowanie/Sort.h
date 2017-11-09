#pragma once
#include <vector>
#include <iostream>

#undef min
#undef max

template <class T>
class Sort
{
private:
	inline void Swap(T & s1, T & s2);
	void MERGE(std::vector<T> & vec, int r, int l, int center);
	void mergesort(std::vector<T> & vec, int r, int l);
	void quicksort(std::vector<T> & vec, int l, int r);
	void radix(std::vector<T> & vec, std::vector<T> & vHelp, const int & mask);

public:
	Sort() {}
	~Sort() {}

	void bubble(std::vector<T> & vec);
	void selection(std::vector<T> & vec);
	void insert(std::vector<T> & vec);
	void merge(std::vector<T> & vec);
	inline void quick(std::vector<T> & vec);
	void counting(std::vector<T> & vec);
	void radix(std::vector<T> & vec);
	
	T max(std::vector<T> & vec);
	T min(std::vector<T> & vec);

	void show(std::vector<T> & vec);
	bool sorted(std::vector<T> & vec);
};

template<class T>
void Sort<T>::bubble(std::vector<T> & vec)
{
	bool bChange;
	int n = vec.size() - 1;
	do
	{
		bChange = false;
		for (int i = 0; i < n; i++)
		{
			if (vec[i] > vec[i + 1])
			{
				Swap(vec[i], vec[i + 1]);
				bChange = true;
			}
			else continue;
		}
		n--;
	} while (bChange == true);
}

template<class T>
void Sort<T>::selection(std::vector<T>& vec)
{
	for (int i = 0; i < vec.size() - 1; i++)
	{
		int min = i;
		for (int j = i; j < vec.size(); j++)
		{
			if (vec[j] < vec[min])
				min = j;
		}
		Swap(vec[i], vec[min]);
	}
}

template<class T>
void Sort<T>::insert(std::vector<T>& vec)
{
	T element;
	int j;
	for (int i = 1; i < vec.size(); i++)
	{
		element = vec[i];
		j = i - 1;
		while ((j >= 0) && (vec[j] > element)) 
		{
			vec[j + 1] = vec[j];
			j--;
		}
		vec[j + 1] = element;
	}
}

template<class T>
void Sort<T>::merge(std::vector<T>& vec)
{
	mergesort(vec, vec.size() - 1, 0);
}

template<class T>
inline void Sort<T>::quick(std::vector<T>& vec)
{
	quicksort(vec, 0, vec.size() - 1);
}

/*Only for Integer type.
*/
template<class T>
inline void Sort<T>::counting(std::vector<T>& vec)
{
	T max = Sort<T>::max(vec);
	T min = Sort<T>::min(vec);

	std::vector<int> vCount(max - min + 1);
	std::vector<T> vTemp(vec.size());
	std::copy(vec.begin(), vec.end(), vTemp.begin());

	for (int i = 0; i < vec.size(); i++) vCount[vec[i] - min]++;
	for (int i = 1; i < vCount.size(); i++) vCount[i] += vCount[i-1];
	for (int i = vec.size() - 1; i >= 0 ; --i) vec[vCount[vTemp[i] - min]-- - 1] = vTemp[i];
}


template<class T>
void Sort<T>::quicksort(std::vector<T>& vec, int l, int r)
{
	int i, j, v, temp;
	i = l;
	j = r;
	v = vec[div(l + r, 2).quot];
	do
	{
		while (vec[i]<v) i++;
		while (v<vec[j]) j--;
		if (i <= j)
		{
			Swap(vec[i], vec[j]);
			i++;
			j--;
		}
	} while (i <= j);

	if (l<j) quicksort(vec, l, j);
	if (i<r) quicksort(vec, i, r);
}

template<class T>
void Sort<T>::radix(std::vector<T>& vec, std::vector<T>& vHelp, const int & mask)
{
	unsigned L[2], i;

	L[0] = L[1] = 0;
	for (i = 0; i < vec.size(); i++) L[(vec[i] & mask) > 0]++;
	L[1] += L[0];
	for (i = vec.size(); i >= 0; i--) vHelp[L[(vec[i] & mask) > 0]--] = vec[i];
}

template<class T>
inline void Sort<T>::radix(std::vector<T>& vec)
{
	int mask = 1;
	std::vector<T> vHelper(vec.size());
	while (mask < vec.size())
	{
		radix(vec, vHelper, mask); mask << 1;
		radix(vHelper, vec, mask); mask << 1;
	}
}

template<class T>
void Sort<T>::mergesort(std::vector<T>& vec, int r, int l)
{
	int center = (r + l) / 2;
	if (l< r)
	{
		mergesort(vec, center, l);
		mergesort(vec, r, center + 1);
		MERGE(vec, r, l, center);
	}
}

template<class T>
void Sort<T>::MERGE(std::vector<T>& vec, int r, int l, int cen)
{
	int i, j, q;
	std::vector<T> help{ vec };
	i = l; j = cen + 1; q = l;
	while (i <= cen && j <= r) { 
		if (help[i]<help[j])
			vec[q++] = help[i++];
		else
			vec[q++] = help[j++];
	}
	while (i <= cen) vec[q++] = help[i++];
}

template<class T>
inline void Sort<T>::Swap(T & s1, T & s2)
{
	T temp = std::move(s1);
	s1 = std::move(s2);
	s2 = std::move(temp);
}

template<class T>
inline T Sort<T>::max(std::vector<T>& vec)
{
	int maximum = 0;

	for (int i = 1; i < vec.size(); i++)
		if (vec[maximum] < vec[i]) maximum = i;

	return vec[maximum];
}

template<class T>
inline T Sort<T>::min(std::vector<T>& vec)
{
	int minimum = 0;

	for (int i = 1; i < vec.size(); i++)
		if (vec[minimum] > vec[i]) minimum = i;

	return vec[minimum];
}

template<class T>
void Sort<T>::show(std::vector<T> & vec)
{
	for (T x : vec)
	{
		std::cout << x << ", ";
	}
	std::cout << std::endl;
}

template<class T>
bool Sort<T>::sorted(std::vector<T>& vec)
{
	for (int i = 0; i < static_cast<int>(vec.size() - 1); i++)
	{
		if (vec[i] > vec[i + 1])
			return false;
	}
	return true;
}
