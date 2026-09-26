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
	void fillAll();
	void fill(int index, Rva0019A7D0Vector *out);

private:
	char m_head[0x28];
	int m_count;
};

void Rva001A0320Owner::fillAll()
{
	Rva0019A7D0Vector temp;
	int i = 0;
	if (m_count > 0)
	{
		do
		{
			fill(i, &temp);
			++i;
		} while (i < m_count);
	}
}
