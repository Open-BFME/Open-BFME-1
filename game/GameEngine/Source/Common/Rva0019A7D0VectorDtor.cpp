// cl: /DNDEBUG /MD /EHsc

struct Gen_t_00199a10_p8cd
{
	int a[2];
};

class Rva0019A7D0Owned
{
public:
	virtual ~Rva0019A7D0Owned();
};

namespace _STL
{

template <class Type> class allocator {};

template <class Type, class Alloc>
class vector
{
public:
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

Rva0019A7D0Vector::~Rva0019A7D0Vector()
{
	Gen_t_00199a10_p8cd *e = _M_finish;
	Gen_t_00199a10_p8cd *p = _M_start;
	for (; p != e; ++p)
	{
		Rva0019A7D0Owned *owned = (Rva0019A7D0Owned *)p->a[1];
		if (owned)
			delete owned;
	}
}
