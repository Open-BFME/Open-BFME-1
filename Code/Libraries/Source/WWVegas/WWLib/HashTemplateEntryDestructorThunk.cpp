// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class StringClass;

template <class KeyType, class ValueType>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/hashtemplate.h
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
