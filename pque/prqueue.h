#ifndef PRQUEUE_H
#define PRQUEUE_H
#include<vector>
#include<algorithm>
#include<queue>

template<class K, class V, class Comp = std::less<K> >
class priority_queue
{
	std::vector<std::pair<K, V> > que;
	static const Comp c;
	
	struct compPair
	{
		bool operator ()(const std::pair<K,V>& lhs, const std::pair<K,V>& rhs) const
		{
			return c(lhs.first, rhs.first);
		}
	};
public:
	
	priority_queue(){}
	
	template<class Q>
	priority_queue(Q pq)
	{
		while(!pq.empty())
		{
			push(pq.top(), pq.top());
			pq.pop();
		}
	}
	
	void push(const K& k, const V& v)
	{
		typename std::vector<std::pair<K, V> >::iterator it = std::upper_bound(que.begin(), que.end(), std::make_pair(k, v), compPair());
		que.insert(it, std::make_pair(k, v));
	}
	
	void update_priority(const K& k, const V& v, const K& newk)
	{
		typename std::vector<std::pair<K, V> >::iterator it = std::lower_bound(que.begin(), que.end(), std::make_pair(k, v), compPair());
		if(*it == std::make_pair(k, v))
		{
			que.erase(it);
			push(newk, v);
		}
	}
	
	const V& top() const
	{
		return que.back().second;
	}
	
	V& top()
	{
		return que.back().second;
	}
	
	unsigned int size() const
	{
		return que.size();
	}
	
	void pop()
	{
		que.pop_back();
	}
	
};

template<class K, class V, class Comp >
const Comp priority_queue<K, V, Comp>::c;


#endif