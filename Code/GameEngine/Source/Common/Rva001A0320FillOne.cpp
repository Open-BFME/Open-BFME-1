// cl: /O2 /EHsc

struct Gen_t_00199a10_p8cd
{
	int a[2];
};

namespace _STL
{

template <class Type> class allocator {};

template <class Type, class Alloc>
class vector
{
public:
	vector()
	{
		_M_start = 0;
		_M_finish = 0;
		_M_end_of_storage = 0;
	}
	~vector();
	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};

}

class Rva0019A7D0Vector : public _STL::vector<Gen_t_00199a10_p8cd, _STL::allocator<Gen_t_00199a10_p8cd> >
{
public:
	~Rva0019A7D0Vector();
};

class Rva001A0320Owner
{
public:
	void fillOne(int index);
	void fill(int index, Rva0019A7D0Vector *out);
};

void Rva001A0320Owner::fillOne(int index)
{
	Rva0019A7D0Vector temp;
	fill(index, &temp);
}
