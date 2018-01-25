#ifndef SETFILTER
#define SETFILTER

#include <set>

template<class C, class Comp = std::less<C> >
class set_filtering
{
	std::set<C, Comp>& unfiltered;
	std::set<C, Comp> filtered;
	typedef typename std::set<C, Comp>::iterator iterator;
public:
	set_filtering(std::set<C, Comp>& s):unfiltered(s){};
	
	~set_filtering()
	{
		unfiltered.insert(filtered.begin(), filtered.end());
	}
	
	void filter(const C& e)
	{
		std::pair<iterator,iterator> ret = unfiltered.equal_range(e);
		filtered.insert(ret.first, ret.second);
		unfiltered.erase(ret.first, ret.second);
	}
	
	void unfilter(const C& e)
	{
		std::pair<iterator,iterator> ret = filtered.equal_range(e);
		unfiltered.insert(ret.first, ret.second);
		filtered.erase(ret.first, ret.second);
	}
	
	void inverse()
	{
		std::swap(unfiltered, filtered);
	}
	
	void operator~ ()
	{
		inverse();
	}
	
	template<class Pred>
	void operator+= (Pred p)
	{
		for(typename std::set<C, Comp>::iterator it = unfiltered.begin(); it != unfiltered.end();)
		{
			if(p(*it)){
				std::pair<iterator,iterator> ret = unfiltered.equal_range(*it);
				filtered.insert(ret.first, ret.second);
				unfiltered.erase(ret.first, ret.second);
				it = ret.second;
			}else{
				it++;
			}
		}
	}
	
	template<class Pred>
	void operator-= (Pred p)
	{
		for(typename std::set<C, Comp>::iterator it = filtered.begin(); it != filtered.end();)
		{
			if(p(*it)){
				std::pair<iterator,iterator> ret = filtered.equal_range(*it);
				unfiltered.insert(ret.first, ret.second);
				filtered.erase(ret.first, ret.second);
				it = ret.second;
			}else{
				it++;
			}
		}
	}
	
	
};

#endif