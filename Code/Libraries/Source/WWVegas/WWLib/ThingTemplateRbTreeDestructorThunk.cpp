// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class ThingTemplate;
class AsciiString;
class UnicodeString;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LanguageFilter.h
struct UnicodeStringLessThan
{
};

namespace _STL
{
template <class First, class Second>
struct pair
{
};

template <class Pair>
struct _Select1st
{
};

template <class Type>
struct less
{
};

template <class Type>
class allocator
{
};

template <class Key, class Value, class Select, class Compare, class Allocator>
class _Rb_tree
{
public:
	~_Rb_tree();
};

class ThingTemplateRbTreeDestructorShim
{
public:
	void destroy();
};

class AsciiStringRbTreeDestructorShim
{
public:
	void destroy();
};

class UnicodeStringRbTreeDestructorShim
{
public:
	void destroy();
};

_Rb_tree<ThingTemplate const *, pair<ThingTemplate const *const, int>, _Select1st<pair<ThingTemplate const *const, int> >, less<ThingTemplate const *>, allocator<pair<ThingTemplate const *const, int> > >::~_Rb_tree()
{
	((ThingTemplateRbTreeDestructorShim *)this)->destroy();
}

_Rb_tree<AsciiString, pair<AsciiString const, bool>, _Select1st<pair<AsciiString const, bool> >, less<AsciiString>, allocator<pair<AsciiString const, bool> > >::~_Rb_tree()
{
	((AsciiStringRbTreeDestructorShim *)this)->destroy();
}

_Rb_tree<UnicodeString, pair<UnicodeString const, bool>, _Select1st<pair<UnicodeString const, bool> >, UnicodeStringLessThan, allocator<pair<UnicodeString const, bool> > >::~_Rb_tree()
{
	((UnicodeStringRbTreeDestructorShim *)this)->destroy();
}
}
