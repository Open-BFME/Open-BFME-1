// cl: /O2
// stlport

#include <vector>

typedef int Int;

struct ICoord2D
{
	Int x, y;
};

template _STL::vector<ICoord2D> &_STL::vector<ICoord2D>::operator=(
	const _STL::vector<ICoord2D> &);
