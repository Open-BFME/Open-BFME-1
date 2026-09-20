// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// The 5-byte incremental-link thunk at 0x0002E15E forwards to the matched
// map<AsciiString, Coord3D> tree-copy body at 0x000BFF50.
#define _STLP_NO_EXCEPTIONS 1
#include <map>

#include "ascii_string.h"

typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

namespace _STL
{
class AsciiCoordTreeCopyShim
{
public:
	_Rb_tree_node<pair<const AsciiString, Coord3D> > *copy(
		_Rb_tree_node<pair<const AsciiString, Coord3D> > *destination,
		_Rb_tree_node<pair<const AsciiString, Coord3D> > *source);
};
}

class Rva0002E15EAsciiStringCoordTreeCopyThunk
{
public:
	_STL::_Rb_tree_node<_STL::pair<const AsciiString, Coord3D> > *forward(
		_STL::_Rb_tree_node<_STL::pair<const AsciiString, Coord3D> > *destination,
		_STL::_Rb_tree_node<_STL::pair<const AsciiString, Coord3D> > *source);
};

_STL::_Rb_tree_node<_STL::pair<const AsciiString, Coord3D> > *
Rva0002E15EAsciiStringCoordTreeCopyThunk::forward(
	_STL::_Rb_tree_node<_STL::pair<const AsciiString, Coord3D> > *destination,
	_STL::_Rb_tree_node<_STL::pair<const AsciiString, Coord3D> > *source)
{
	return ((_STL::AsciiCoordTreeCopyShim *)this)->copy(destination, source);
}
