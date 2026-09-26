// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

class StringClass;

template <class KeyType, class ValueType>
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/hashtemplate.h
class HashTemplateClass
{
public:
	class Entry
	{
	public:
		~Entry();
	};
};

class HashTemplateEntryDestructorShim
{
public:
	void destroy();
};

HashTemplateClass<StringClass, int>::Entry::~Entry()
{
	((HashTemplateEntryDestructorShim *)this)->destroy();
}
