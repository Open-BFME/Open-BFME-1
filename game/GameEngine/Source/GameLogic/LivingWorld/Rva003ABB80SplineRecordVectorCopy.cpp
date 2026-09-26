// Target 0x003ABB80: native STLport vector<Record> copy constructor.
// The matched Record lifecycle names an address-qualified tree subobject and
// pins its destructor at 0x003AB460. Its copy path uses the physical tree
// specialization at 0x003AB520; the mapped value stays address-qualified.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include <vector>
#include "StringInline.h"

struct Gen_t_003ab520_p24cd
{
	int a[6];
	Gen_t_003ab520_p24cd();
	Gen_t_003ab520_p24cd(const Gen_t_003ab520_p24cd &other);
	~Gen_t_003ab520_p24cd();
	Gen_t_003ab520_p24cd &operator=(const Gen_t_003ab520_p24cd &other);
};

bool operator==(const Gen_t_003ab520_p24cd &left,
	const Gen_t_003ab520_p24cd &right);
bool operator<(const Gen_t_003ab520_p24cd &left,
	const Gen_t_003ab520_p24cd &right);

struct Rva003AB460Tree
{
	_STL::map<int, Gen_t_003ab520_p24cd> m_map;
	~Rva003AB460Tree();
};

class Rva003BA660Record
{
public:
	Rva003BA660Record();
	virtual ~Rva003BA660Record() {}
	int m_prefix;
	char m_08;
	Rva003AB460Tree m_tree;
};

template _STL::vector<Rva003BA660Record, _STL::allocator<Rva003BA660Record> >::vector(
	const _STL::vector<Rva003BA660Record, _STL::allocator<Rva003BA660Record> > &);

// Instantiate the two exact vector helpers used by the copy constructor.
template class _STL::_Vector_base<Rva003BA660Record, _STL::allocator<Rva003BA660Record> >;
template _STL::allocator<Rva003BA660Record> _STL::vector<Rva003BA660Record, _STL::allocator<Rva003BA660Record> >::get_allocator() const;
template class _STL::_STLP_alloc_proxy<Rva003BA660Record *, Rva003BA660Record, _STL::allocator<Rva003BA660Record> >;
