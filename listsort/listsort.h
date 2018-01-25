#ifndef LISTSORT_H
#define LISTSORT_H
#include<list>
#include<algorithm>

template<typename T, class Comp = std::less<T> >
class list_sorter{
	template<typename TP, class C>
	friend class list_sorter;
	std::list<T>& ls;
	int counter;
public:
	list_sorter(std::list<T>& l):ls(l)
	{
		counter = 1;
		ls.sort(Comp() );
	}
	
	list_sorter<T, Comp>& add(std::list<T>& l)
	{
		ls.insert(ls.begin(), l.begin(), l.end());
		l.clear();
		ls.sort(Comp() );
		counter++;
		return *this;
	}
	
	list_sorter<T, Comp>& remove(const T& t){
		typename std::list<T>::iterator itl = std::lower_bound(ls.begin(), ls.end(), t, Comp());
		typename std::list<T>::iterator itu = std::upper_bound(ls.begin(), ls.end(), t, Comp());
		ls.erase(itl, itu);
		return *this;
	}
	
	int list_count() const{
		return counter;
	}
	
	template<class C>
	void operator+=(list_sorter<T, C>& slg){
		add(slg.ls);
	}
};

#endif