#ifndef ARRAPP_H
#define ARRAPP_H

#include<vector>
#include<algorithm>
#include<utility>
#include<iostream>
/*
array_appender osztály template, amivel meglévő tömböket (és négyesért
vector-okat) lehet view-ként appendálni, a tömb/vector elemek ugyanott
maradnak, de folytonosan lehet indexelni az elemeket, végigiterálni az
elemeken. A template paraméter a tömb elemeinek típusát határozza meg.
*/

template<class C>
class array_appender
{
	std::vector<std::pair<C*, unsigned int> > view;
	unsigned int vsize;

public:
	array_appender(C* arr, unsigned int s)
	{
		view.push_back(std::make_pair(arr, s));
		vsize = s;
	}
	
	void append(C* arr, unsigned int s)
	{
		view.push_back(std::make_pair(arr, s));
		vsize += s;
	}
	
	void append(std::vector<C>& v)
	{
		view.push_back(std::make_pair(&v[0], v.size()));
		vsize += v.size();
	}
	
	unsigned int size() const
	{
		return vsize;
	}
	
	const C& at(unsigned int index) const
	{
		for(unsigned int i = 0; i < view.size(); i++){
			if(view[i].second <= index){
				index -= view[i].second;
			}else{
				return view[i].first[index];
			}
		}
		return view[0].first[0];
	}
	
	C& at(unsigned int index)
	{
		for(unsigned int i = 0; i < view.size(); i++){
			if(view[i].second <= index){
				index -= view[i].second;
			}else{
				return view[i].first[index];
			}
		}
		return view[0].first[0];
	}
	
	C& operator[](unsigned int index)
	{
		return at(index);
	}
	
	const C& operator[](unsigned int index) const
	{
		return at(index);
	}
	
	class iterator : public std::iterator<
                        std::input_iterator_tag,   // iterator_category
                        C,                      // value_type
                        long,                      // difference_type
                        const C*,               // pointer
                        C                       // reference
                                      >
	{
		unsigned int index;
		array_appender<C>& ap;
	public:
		iterator(unsigned int i, array_appender<C>& app):index(i),ap(app){};
		
		bool operator!=(const iterator& it) const
		{
			return index != it.index;
		}
		
		bool operator==(const iterator& it) const
		{
			return index == it.index;
		}
		
		C& operator*()
		{
			return ap.at(index);
		}
		
		iterator operator++()
		{
			index++;
			return *this;
		}
		
		
	};
	
	iterator begin(){
		return iterator(0, *this);
	}
	
	iterator end(){
		return iterator(vsize, *this);
	}
	
};

#endif