// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
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

class GenItem;
class INI;

struct FieldParse
{
	const char *token;
	void (*parse)(INI *ini, void *instance, void *store, const void *userData);
	const void *userData;
	unsigned int offset;
};

class INI
{
public:
	const char *getNextTokenOrNull(const char *previous);
	void initFromINI(void *instance, const FieldParse *fieldParse);
	static void parseAsciiString(INI *, void *, void *, const void *);
	static void parseBitString32(INI *, void *, void *, const void *);
	static void parseBool(INI *, void *, void *, const void *);
	static void parseFXList(INI *, void *, void *, const void *);
	static void parseInt(INI *, void *, void *, const void *);
};

void parseAnimation(INI *, void *, void *, const void *);
void parseFXEvent(INI *, void *, void *, const void *);
void parseParticleSysBone(INI *, void *, void *, const void *);
void d_008522a0();

const char *g_00EBB5DC[10] =
{
	"RANDOMSTART",
	"START_FRAME_FIRST",
	"START_FRAME_LAST",
	"ADJUST_HEIGHT_BY_CONSTRUCTION_PERCENT",
	"MAINTAIN_FRAME_ACROSS_STATES",
	"RESTART_ANIM_WHEN_COMPLETE",
	"MAINTAIN_FRAME_ACROSS_STATES2",
	"MAINTAIN_FRAME_ACROSS_STATES3",
	"MAINTAIN_FRAME_ACROSS_STATES4",
	0
};

extern FieldParse g_012BB650[11];
extern "C" FieldParse __identifier("?g_012BB650@@3PAUFieldParse@@A")[11] =
{
	{ "Animation", parseAnimation, 0, 0x2C },
	{ "StateName", INI::parseAsciiString, 0, 0 },
	{ "Flags", INI::parseBitString32, g_00EBB5DC, 0x38 },
	{ "ShareAnimation", INI::parseBool, 0, 0x40 },
	{ "EnteringStateFX", INI::parseFXList, 0, 0x44 },
	{ "BeginScript", reinterpret_cast<void (*)(INI *, void *, void *, const void *)>(d_008522a0), 0, 0x48 },
	{ "FrameForPristineBonePositions", INI::parseInt, 0, 0x3C },
	{ "FXEvent", parseFXEvent, 0, 0 },
	{ "ParticleSysBone", parseParticleSysBone, 0, 0 },
	{ "SimilarRestart", INI::parseBool, 0, 0x6C },
	{ 0, 0, 0, 0 }
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
	g_012BB650[0].userData = reinterpret_cast<const void *>(mode);

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
	ini->initFromINI(&element, g_012BB650);

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
