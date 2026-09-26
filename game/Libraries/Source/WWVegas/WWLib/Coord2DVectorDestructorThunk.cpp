// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

struct ICoord2D;

namespace _STL
{
template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
public:
	~vector();
};

class ICoord2DVectorDestructorShim
{
public:
	void destroy();
};

vector<ICoord2D, allocator<ICoord2D> >::~vector()
{
	((ICoord2DVectorDestructorShim *)this)->destroy();
}
}
