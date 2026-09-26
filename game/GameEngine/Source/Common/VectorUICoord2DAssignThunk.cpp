// cl: /O2
// stlport

#include <vector>

typedef int Int;

struct ICoord2D
{
	Int x, y;
};

template class _STL::vector<ICoord2D>;
