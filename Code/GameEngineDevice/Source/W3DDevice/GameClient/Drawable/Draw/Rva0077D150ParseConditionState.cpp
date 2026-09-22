// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#include <vector>


extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)



// The string copy at 0x00887C90 is StringBase<char>::set: the state name
// comes from INI narrow tokens. Use canonical AsciiString, not the old
// misleading UnicodeString alias. Native vector removes synthetic stack pads
// and reproduces the real placement-construction exception state.
// The BFME field table reaches this callback through the ILT at 0x0000EE71.
// Its owner is not named by a live caller, so the symbol keeps the proven
// retail address while the callback signature and parser role are explicit.

typedef unsigned int UnsignedInt;

struct FieldParse;
class GenItem;

class INI
{
public:
	const char *getNextTokenOrNull(const char *previous);
	void initFromINI(void *instance, const FieldParse *fieldParse);
};

#include "ascii_string.h"

struct Gen000140D8
{
	UnsignedInt m_words[10];

	bool handle(GenItem *item, bool *first, bool *second);
};

struct Rva0077CC10Element
{
	Rva0077CC10Element();
	Rva0077CC10Element(const Rva0077CC10Element &source);
	~Rva0077CC10Element();

	AsciiString m_name;
	Gen000140D8 m_conditions;
	unsigned char m_tail[188 - sizeof(AsciiString) - sizeof(Gen000140D8)];
};

struct Gen_t_00776240_p128pod
{
	UnsignedInt m_words[47];

	Gen_t_00776240_p128pod();
	Gen_t_00776240_p128pod(const Gen_t_00776240_p128pod &source);
	~Gen_t_00776240_p128pod();
	Gen_t_00776240_p128pod &operator=(const Gen_t_00776240_p128pod &source);
};

typedef _STL::vector<Rva0077CC10Element,
	_STL::allocator<Rva0077CC10Element> > Rva0077D150Vector;
typedef _STL::vector<Gen_t_00776240_p128pod,
	_STL::allocator<Gen_t_00776240_p128pod> > Gen00776240Vector;

// ?parseConditionState0077D150@@YAXPAVINI@@PAX1PBX@Z
void parseConditionState0077D150(INI *ini, void *instance, void *store,
	const void *userData)
{
	register UnsignedInt mode = (UnsignedInt)userData;
	*(reinterpret_cast<UnsignedInt *>(0x012BB658)) = mode;

	Rva0077CC10Element element;
	Gen000140D8 conditions = { };
	_ReadWriteBarrier();
	AsciiString stateName;

	if (mode == 0)
	{
		bool second = false;
		bool first = false;
		const char *token = ini->getNextTokenOrNull(0);
		while (token != 0)
		{
			if (!conditions.handle(reinterpret_cast<GenItem *>(const_cast<char *>(token)),
				&second, &first))
			{
				break;
			}
			token = ini->getNextTokenOrNull(0);
		}
	}
	else if (mode != 1 && mode == 2)
	{
		const char *token = ini->getNextTokenOrNull(0);
		if (token != 0)
			stateName = token;
	}

	element.m_name.set(stateName);
	element.m_conditions = conditions;
	ini->initFromINI(&element,
		reinterpret_cast<const FieldParse *>(0x012BB650));

	if (mode == 1)
	{
		Gen00776240Vector *states = reinterpret_cast<Gen00776240Vector *>(
			reinterpret_cast<unsigned char *>(instance) + 0x24);
		states->insert(states->begin(),
			reinterpret_cast<const Gen_t_00776240_p128pod &>(element));
	}
	else
	{
		Rva0077D150Vector *states = reinterpret_cast<Rva0077D150Vector *>(
			reinterpret_cast<unsigned char *>(instance) + 0x24);
		states->push_back(element);
	}

}
