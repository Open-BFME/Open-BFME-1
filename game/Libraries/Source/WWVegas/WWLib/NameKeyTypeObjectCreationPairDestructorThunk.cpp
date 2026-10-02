// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

enum NameKeyType
{
};
class ObjectCreationList;

// The incremental-link thunk at 0x00654BA0 is retail's own body
// (`?invoke@Rva00654BA0@@QAEXXZ`, matched in
// game/GameEngine/Source/Common/MemberOffsetTailThunks.cpp), so the destructor
// below tail-jumps to that defining name rather than to a private stand-in.
class Rva00654BA0
{
public:
	void invoke();
};

namespace _STL
{
template <class First, class Second>
class pair
{
public:
	~pair();
};

pair<NameKeyType const, ObjectCreationList>::~pair()
{
	((Rva00654BA0 *)this)->invoke();
}
}
