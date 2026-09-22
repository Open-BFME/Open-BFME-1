// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// The complete retail body is a five-byte incremental-link tail jump to the
// independently matched STLport vector<bool>::_M_initialize at 0x00526BC0.
class Rva0003B1A1Thunk : public _STL::vector<bool>
{
public:
	void forward(unsigned int size);
};

void Rva0003B1A1Thunk::forward(unsigned int size)
{
	_M_initialize(size);
}
