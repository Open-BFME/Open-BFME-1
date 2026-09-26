// cl: /DNDEBUG /MD /GX- /O2 /Ob2 /D_STLP_USE_STATIC_LIB
// stlport
#include <memory>

class Rva008F9E90DequeNodes
{
public:
	void create(void **first, void **last);
};
void Rva008F9E90DequeNodes::create(void **first, void **last)
{
	for (void **it = first; it < last; ++it)
		*it = _STL::__node_alloc<true, 0>::allocate(0x80);
}
