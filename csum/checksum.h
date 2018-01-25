#ifndef CHEKSUM_H
#define CHEKSUM_H

template<class C, class Id, class T = typename C::value_type, class Mul = std::plus<int> >
class checksum
{
	C con;
	C* conref;
	int start;
public:
	checksum(C& container, int s = 0):con(container), conref(&container),start(s){};
	
	int get_checksum() const
	{
		int sum = start;
		for(typename C::const_iterator it = con.begin(); it != con.end(); it++)
		{
			Id d;
			Mul m;
			sum = m(sum, d(*it));
		}
		return sum;
	}
	
	bool validate_checksum() const
	{
		int sum = start;
		for(typename C::const_iterator it = conref->begin(); it != conref->end(); it++)
		{
			Id d;
			Mul m;
			sum = m(sum, d(*it));
		}
		return get_checksum() == sum;
	}
	
	void update_checksum()
	{
		con = *conref;
	}
};

#endif