// ?d_003c2100@@YAXXZ
// partial score=0.32 date=2026-09-23
// ?process@Rva003C2100Owner@@QAEXPAURva003C2100Record@@@Z
// Retail 0x003C2100: LivingWorld record-range processing body.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

extern void j_000012f3(void);
extern void j_00032a56(void);
extern void j_00043275(void);
extern void j_00006fb9(void);
extern void j_0004958a(void);
extern void j_000191e1(void);

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class Rva003C2100NameString
{
public:
	~Rva003C2100NameString()
	{
		((AsciiString *)this)->~AsciiString();
	}

	void *m_data;
};

#define _M_insert_overflow j_00007e96
#include <vector>
#undef _M_insert_overflow

struct Rva003C2100Pair
{
	float m_x;
	float m_y;
};

struct Rva003C2100Record
{
	char m_pad00[0xD4];
	_STL::vector<AsciiString> m_items;
};

class Rva003C2100CallOwner
{
};

struct Gen003BD8D0Built;

class Rva003C2100Owner
{
public:
	void process(Rva003C2100Record *record);

private:
	char m_pad00[0x28];
	void *m_manager;
};

struct Rva00367E30Logic
{
};

extern Rva00367E30Logic *TheBfmeGameLogic;

typedef bool (Rva003C2100CallOwner::*Rva003C2100Filter)(
	AsciiString *, AsciiString *);
typedef void *(Rva003C2100CallOwner::*Rva003C2100Find)(
	AsciiString *);
typedef Gen003BD8D0Built *(Rva003C2100CallOwner::*Rva003C2100Build)(void);
typedef int (Rva003C2100CallOwner::*Rva003C2100Select)(
	void *, Gen003BD8D0Built *, Rva003C2100Pair *);
typedef Rva003C2100NameString *(Rva003C2100CallOwner::*Rva003C2100Copy)(
	Rva003C2100NameString *);
typedef void (Rva003C2100CallOwner::*Rva003C2100Dispatch)(
	Rva003C2100NameString *, int, Rva003C2100Pair *, bool);

union Rva003C2100FilterCall
{
	void (*asFunction)(void);
	Rva003C2100Filter asMember;
};

union Rva003C2100FindCall
{
	void (*asFunction)(void);
	Rva003C2100Find asMember;
};

union Rva003C2100BuildCall
{
	void (*asFunction)(void);
	Rva003C2100Build asMember;
};

union Rva003C2100SelectCall
{
	void (*asFunction)(void);
	Rva003C2100Select asMember;
};

union Rva003C2100CopyCall
{
	void (*asFunction)(void);
	Rva003C2100Copy asMember;
};

union Rva003C2100DispatchCall
{
	void (*asFunction)(void);
	Rva003C2100Dispatch asMember;
};

void Rva003C2100Owner::process(Rva003C2100Record *record)
{
	Rva003C2100CallOwner *owner = (Rva003C2100CallOwner *)this;
	unsigned int index = 0;
	unsigned int count = (unsigned int)record->m_items.size();
	Rva003C2100FilterCall filter;
	Rva003C2100FindCall find;
	Rva003C2100BuildCall build;
	Rva003C2100SelectCall select;
	Rva003C2100CopyCall copy;
	Rva003C2100DispatchCall dispatch;
	filter.asFunction = j_000012f3;
	find.asFunction = j_00032a56;
	build.asFunction = j_00043275;
	select.asFunction = j_00006fb9;
	copy.asFunction = j_0004958a;
	dispatch.asFunction = j_000191e1;
	while (index < count)
	{
		AsciiString filtered;
		bool useFiltered = (owner->*filter.asMember)(
			&record->m_items[index], &filtered);
		void *key = useFiltered
			? (void *)&filtered
			: (void *)&record->m_items[index];
		void *result = (owner->*find.asMember)(
			(AsciiString *)key);
		if (result != 0)
		{
			Rva003C2100CallOwner *found =
				(Rva003C2100CallOwner *)result;
			Rva003C2100Pair pair;
			int selected = (owner->*select.asMember)(
				record, (found->*build.asMember)(), &pair);
			if (selected != -1)
			{
				Rva003C2100NameString name;
				Rva003C2100CallOwner *logic =
					(Rva003C2100CallOwner *)TheBfmeGameLogic;
				(logic->*dispatch.asMember)(
					(found->*copy.asMember)(&name),
					selected, &pair, useFiltered);
			}
		}
		++index;
		count = (unsigned int)record->m_items.size();
	}
}
