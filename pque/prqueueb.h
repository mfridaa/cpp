#ifndef PRQUEUE_H
#define PRQUEUE_H
#include<vector>
#include<algorithm>
#include<queue>

template<class K, class V, class Comp = std::less<K> >
class priority_queue{
	std::vector<std::pair<K, V> > que;
public:
	static bool sortPair(const std::pair<K,V>& lhs, const std::pair<K,V>& rhs){
		Comp c;
		return c(lhs.first, rhs.first);
	}
	
	priority_queue(){}
	
	template<class Q>
	priority_queue(Q pq){
		while(!pq.empty()){
			push(pq.top(), pq.top());
			pq.pop();
		}
	}
	
	void push(const K& k, const V& v){
		que.push_back(std::pair<K, V>(k, v));
		std::sort(que.begin(), que.end(), sortPair);
	}
	
	void update_priority(const K& k, const V& v, const K& newk){
		for(typename std::vector<std::pair<K, V> >::iterator it = que.begin(); it != que.end(); it++){
			if(it->first == k && it->second == v){
				it->first = newk;
			}
		}
		std::sort(que.begin(), que.end(), sortPair);
	}
	
	V top() const{
		return que.back().second;
	}
	
	V& top(){
		return que.back().second;
	}
	
	int size() const{
		return que.size();
	}
	
	void pop(){
		que.pop_back();
	}
	
};


#endif