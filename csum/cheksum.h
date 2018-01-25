#ifndef CHEKSUM_H
#define CHEKSUM_H

template<class C, class Id, class T>
class checksum
{
	C con;
public:
	checksum(C container):con(container);
	
	int get_checksum() const
	{
		return 0;
	}
}

#endif