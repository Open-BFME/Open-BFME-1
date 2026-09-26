// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

enum NameKeyType
{
};
class ObjectCreationList;

namespace _STL
{
template <class First, class Second>
class pair
{
public:
	~pair();
};

class NameKeyObjectCreationPairDestructorShim
{
public:
	void destroy();
};

pair<NameKeyType const, ObjectCreationList>::~pair()
{
	((NameKeyObjectCreationPairDestructorShim *)this)->destroy();
}
}
