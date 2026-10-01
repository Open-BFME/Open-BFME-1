// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <memory>

class Rva0069C710Owner
{
public:
	void releaseSmall(void *memory);
};

void Rva0069C710Owner::releaseSmall(void *memory)
{
	if (memory != 0) {
		_STL::__node_alloc<true, 0>::deallocate(memory, 8);
	}
}
