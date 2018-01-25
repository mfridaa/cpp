#ifndef SAVVIEW_H
#define SAVVIEW_H

#include<vector>
#include<algorithm>

template<class C, class Comp = std::less<C> >
class sorted_array_view{
	std::vector<C> unsorted;
	C* sorted;
public:
	static const int npos = -1;

	sorted_array_view(C* arr, unsigned int size):sorted(arr)
	{
		for(unsigned int i = 0; i < size; i++){
			unsorted.push_back(arr[i]);
		}
		
		std::sort(arr, arr+size, Comp() );
	}
	
	~sorted_array_view()
	{
		for(unsigned int i = 0; i < size(); i++){
			sorted[i] = unsorted[i];
		}
	}
	
	unsigned int size() const
	{
		return unsorted.size();
	}
	
	unsigned int count(C c) const
	{
		int counter = 0;
		for(unsigned int i = 0; i < size(); i++){
			if(!(c < unsorted[i]) && !(unsorted[i] < c))
			{
				counter++;
			}
		}
		return counter;
	}
	
	int index_of(C c) const
	{
		for(unsigned int i = 0; i < size(); i++){
			if(!(c < sorted[i]) && !(sorted[i] < c))
			{
				return i;
			}
		}
		return npos;
	}
	
	template<class Co>
	void copy(Co& c) const
	{
		c.clear();
		for(unsigned int i = 0; i < size(); i++)
		{
			c.push_back(sorted[i]);
		}
	}
	
	C* begin() const
	{
		return sorted;
	}
	
	C* end() const
	{
		return sorted+size();
	}
};

#endif