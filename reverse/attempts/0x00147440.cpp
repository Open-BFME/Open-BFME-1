// ?d_00147440@@YAXXZ
// partial score=0.35 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Open-BFME: near-twin of parsePrerequisiteScience (twin 0x00147320,
// ParsePrerequisiteScienceThunk.cpp).  Same single-shot INI callback shape,
// but this one pushes a PrereqUnitRec (unit ptr + flags + AsciiString name,
// 12 bytes) into m_prereqUnits instead of a ScienceType into m_prereqSciences.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/RTS/ProductionPrerequisite.cpp addUnitPrereq

#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken(int);
};

template <class T>
class StringBase
{
public:
	void set(const StringBase<T> &other);
	StringBase(void) : m_data(0) {}
	StringBase(const T *text);

private:
	StringBase(const StringBase<T> &other);
	~StringBase(void);
	T *m_data;

	friend class AsciiString;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString(void) : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString(void) {}
	AsciiString &operator=(const AsciiString &other)
	{
		set(other);
		return *this;
	}
};

class ThingTemplate;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h
class ProductionPrerequisite
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h
	struct PrereqUnitRec
	{
		const ThingTemplate	*m_unit;
		int							m_flags;
		AsciiString			m_name;
	};

	ProductionPrerequisite();
	~ProductionPrerequisite();

	void addUnitPrereq(AsciiString unit, bool orUnitWithPrevious)
	{
		PrereqUnitRec info;
		info.m_unit = 0;
		info.m_flags = orUnitWithPrevious ? 1 : 0;
		info.m_name = unit;
		m_prereqUnits.push_back(info);
	}

private:
	_STL::vector<PrereqUnitRec> m_prereqUnits;
	_STL::vector<int> m_prereqSciences;
	_STL::vector<int> m_unused;
};

// ?parsePrerequisiteUnit@@YAXPAVINI@@PAX1PBX@Z
void __cdecl parsePrerequisiteUnit(INI *ini, void *instance, void *,
	const void *)
{
	_STL::vector<ProductionPrerequisite> *prerequisites =
		static_cast<_STL::vector<ProductionPrerequisite> *>(instance);

	ProductionPrerequisite prerequisite;
	prerequisite.addUnitPrereq(AsciiString(ini->getNextToken(0)), false);
	prerequisites->push_back(prerequisite);
}
