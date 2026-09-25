// ?d_002e9680@@YAXXZ
// partial score=0.34 date=2026-09-25
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

#define _STLP_NO_EXCEPTIONS 1

#include <string.h>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

typedef int Int;
typedef bool Bool;

struct StringBaseCharHeader
{
	int references;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

template <typename T> class StringBase;
template <> class StringBase<char>
{
public:
	StringBase() : m_data(0) {}
	StringBase(const StringBase &other);
	StringBase(const char *text);
	void set(const char *text, int length);

	public:
	~StringBase() { releaseBuffer(); }

	private:
	void releaseBuffer();

public:
	StringBaseCharHeader *m_data;
};

typedef StringBase<char> AsciiString;

struct Gen000140D8
{
	unsigned int m_words[10];
};

class XmlNameSlotList
{
public:
	Int count();
	const char *tagAt(Int index);
	const char *nameAt(Int index);
	Int finish();
};

class BfmeLexEAN
{
public:
	char *getTailEAN();
};

class WeaponTemplateSet
{
	char m_data[0x54];
};

struct Rva002E9680Record
{
	void *m_name;
	unsigned int m_required[10];
	unsigned int m_forbidden[10];
};

typedef WeaponTemplateSet Gen84;

namespace _STL
{
struct __false_type
{
};

template <class Type> class allocator
{
};

template <class Type, class Allocator = allocator<Type> > class vector
{
public:
	void push_back(const Type *value);
	Type *begin() { return m_start; }
	Type *end() { return m_finish; }

protected:
	void _M_insert_overflow(Type *position, const Type &value,
		const __false_type &tag, unsigned int fillLength, bool atEnd);

	Type *m_start;
	Type *m_finish;
	Type *m_end_of_storage;
};

template <class Type, class Allocator>
void vector<Type, Allocator>::push_back(const Type *value)
{
	if (m_finish != m_end_of_storage)
	{
		if (m_finish != 0)
			*m_finish = *value;
		++m_finish;
	}
	else
	{
		_M_insert_overflow(m_finish, *value,
			reinterpret_cast<const __false_type &>(value), 1, true);
	}
}
}

struct Gen20
{
	char m_data[20];
};

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual bool loadIniFilesFromLegend();
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw();

private:
	void *m_name;
};

class __declspec(novtable) LuaScriptEngine : public SubsystemInterface
{
public:
	void rva002EA5D0ParseModelConditionEvent(BfmeLexEAN *parser);

private:
	void *m_luaState;
	void *m_luaStateForGame;
	char m_events[13 * 8];
	int m_eventCount;
	_STL::vector<int> m_eventCapacity;
	unsigned char m_eventEnd;
	_STL::vector<Gen20> m_eventBuffer;
	_STL::vector<Gen84> m_eventBufferCapacity;
};

class BfmeThingBLC
{
public:
	void bfmeGoBLC(void *what);
};

class Gen_002df780
{
public:
	void *m();
};

class Rva002E7E00Owner
{
public:
	void parse(AsciiString text);
};

#pragma comment(linker, "/alternatename:?count@XmlNameSlotList@@QAEHXZ=?j_00038fc8@@YAXXZ")
#pragma comment(linker, "/alternatename:?tagAt@XmlNameSlotList@@QAEPBDH@Z=?j_0003a5fd@@YAXXZ")
#pragma comment(linker, "/alternatename:?nameAt@XmlNameSlotList@@QAEPBDH@Z=?j_00027a7a@@YAXXZ")
#pragma comment(linker, "/alternatename:?finish@XmlNameSlotList@@QAEHXZ=?j_00049ae4@@YAXXZ")
#pragma comment(linker, "/alternatename:?getTailEAN@BfmeLexEAN@@QAEPADXZ=?j_000262ba@@YAXXZ")
#pragma comment(linker, "/alternatename:?m@Gen_002df780@@QAEPAXXZ=?j_00025e1e@@YAXXZ")
#pragma comment(linker, "/alternatename:?parse@Rva002E7E00Owner@@QAEXV?$StringBase@D@@@Z=?j_000208a6@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeGoBLC@BfmeThingBLC@@QAEXPAX@Z=?j_00022bf6@@YAXXZ")
#pragma comment(linker, "/alternatename:?_M_insert_overflow@?$vector@VWeaponTemplateSet@@V?$allocator@VWeaponTemplateSet@@@_STL@@@_STL@@IAEXPAVWeaponTemplateSet@@ABV2@ABU__false_type@2@I_N@Z=?Rva0001636FThunk@?$vector@VWeaponTemplateSet@@V?$allocator@VWeaponTemplateSet@@@_STL@@@_STL@@QAEXPAVWeaponTemplateSet@@ABV3@ABU__false_type@2@I_N@Z")

#pragma optimize("y", off)
void LuaScriptEngine::rva002EA5D0ParseModelConditionEvent(BfmeLexEAN *parser)
{
	Int nameLength;
	AsciiString name;
	if (reinterpret_cast<XmlNameSlotList *>(parser)->count() > 0)
	{
		Int index = 0;
		do
		{
			const char *tag = reinterpret_cast<XmlNameSlotList *>(parser)->tagAt(index);
			Int nameCompare = memcmp(tag, reinterpret_cast<const char *>(0x0109C094), 5);
			if (nameCompare == 0)
			{
				const char *value = reinterpret_cast<XmlNameSlotList *>(parser)->nameAt(index);
				nameLength = value != 0 ? (Int)strlen(value) : 0;
				name.set(value, nameLength);
			}
			++index;
		}
		while (index < reinterpret_cast<XmlNameSlotList *>(parser)->count());
	}

	if (reinterpret_cast<XmlNameSlotList *>(parser)->finish() != 1)
		return;
	char *tail = parser->getTailEAN();
	Int conditionsCompare = memcmp(tail, reinterpret_cast<const char *>(0x0109418C), 11);
	Bool conditionsMatch = conditionsCompare == 0;
	if (!conditionsMatch)
		return;
	if (reinterpret_cast<XmlNameSlotList *>(parser)->finish() != 3)
		return;

	{
	AsciiString conditions(parser->getTailEAN());
	Gen000140D8 required = {};
	Gen000140D8 forbidden = {};
	_ReadWriteBarrier();
	for (Int i = 0; i < 10; ++i)
		forbidden.m_words[i] = ~forbidden.m_words[i];

	reinterpret_cast<Rva002E7E00Owner *>(&required)->parse(conditions);
	reinterpret_cast<Rva002E7E00Owner *>(&forbidden)->parse(conditions);

	Gen84 record;
	reinterpret_cast<Gen_002df780 *>(&record)->m();
	memcpy(reinterpret_cast<Rva002E9680Record *>(&record)->m_required,
		required.m_words, sizeof(required.m_words));
	memcpy(reinterpret_cast<Rva002E9680Record *>(&record)->m_forbidden,
		forbidden.m_words, sizeof(forbidden.m_words));
	const char *nameText = name.m_data != 0
		? reinterpret_cast<const char *>(name.m_data) + 8
		: reinterpret_cast<const char *>(0x0107388B);
	reinterpret_cast<BfmeThingBLC *>(&record)->bfmeGoBLC(
		const_cast<char *>(nameText));
	for (Gen84 *it = m_eventBufferCapacity.begin();
		it != m_eventBufferCapacity.end(); ++it)
	{
		if (reinterpret_cast<Rva002E9680Record *>(it)->m_name ==
			reinterpret_cast<Rva002E9680Record *>(&record)->m_name)
		{
			Int i = 0;
			while (i < 10 &&
				reinterpret_cast<Rva002E9680Record *>(it)->m_required[i] ==
				reinterpret_cast<Rva002E9680Record *>(&record)->m_required[i])
				++i;
			if (i == 10)
			{
				i = 0;
				while (i < 10 &&
					reinterpret_cast<Rva002E9680Record *>(it)->m_forbidden[i] ==
					reinterpret_cast<Rva002E9680Record *>(&record)->m_forbidden[i])
					++i;
				if (i == 10)
					goto cleanup;
			}
		}
	}
	m_eventBufferCapacity.push_back(&record);
	}

cleanup:
	if (reinterpret_cast<XmlNameSlotList *>(parser)->finish() == 2)
		reinterpret_cast<XmlNameSlotList *>(parser)->finish();
}
#pragma optimize("y", on)
