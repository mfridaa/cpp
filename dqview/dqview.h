#ifndef DQVIEW_H 
#define DQVIEW_H

#include<deque>
#include<iostream>
#include<algorithm>

template<class C>
class deques_view
{
std::deque<std::deque<C>* > dq;
public:
	deques_view(std::deque<C>& d)
	{
		dq.push_back(&d);
	}
	
	void add(std::deque<C>& d)
	{
		dq.push_back(&d);
	}
	
	const C& at(unsigned int index) const
	{
		for(int i = 0; i < dq.size(); i++)
		{
			if(dq[i]->size() > index){
				return dq[i]->at(index);
			}else
			{
				index -= dq[i]->size();
			}
		}
		return dq[0]->at(0);
	}
	
	C& at(unsigned int index)
	{
		for(int i = 0; i < dq.size(); i++)
		{
			if(dq[i]->size() > index){
				return dq[i]->at(index);
			}else
			{
				index -= dq[i]->size();
			}
		}
		return dq[0]->at(0);
	}
	
	unsigned int size() const
	{
		unsigned int s = 0;
		for(int i = 0; i < dq.size(); i++)
		{
			s += dq[i]->size();
		}
		return s;
	}
	
	C& operator[](unsigned int index){
		return at(index);
	}
	
	const C& operator[](unsigned int index) const{
		return at(index);
	}

	void sort()
	{
			std::sort(dq.begin(), dq.end());

	}
	
	template<class Comp>
	void sort(Comp c)
	{
		for(int i = 0; i < dq.size(); i++){
			std::sort(dq[i]->begin(), dq[i]->end(), c);
		}
	}
};

#endif