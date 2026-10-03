// cl: /DNDEBUG /MD /EHs-c-
// Convert 0x0026D820: GameLogic findObjectByID + Coord3D + this-adj -8.

struct Coord3D
{
	float x, y, z;
};

class Object
{
public:
	char m_bfmePad00[0x38];
	Coord3D m_bfmePos;
	char m_bfmePad44[0x204 - 0x44];
	void *m_bfmeMod;
};

class BfmeHelpD820;
class BfmeTailD820;

// The two callees of the tail body are reached through the retail five-byte
// incremental-link thunks at 0x00002B49 and 0x00044B0C, so the only names
// defined at those addresses are the ?j_ thunk symbols (game/gen_small/
// thunks_000.cpp and thunks_033.cpp).  Reference those names.  Both callees are
// thiscall: `this` in ECX and the arguments stacked.  VC7.1 reserves __thiscall
// in a free-function-pointer typedef, so route each address through a member
// pointer (the technique Rva003855F0Transition.cpp uses): the object holds the
// pointer and the call still carries the direct ILT relocation the plain ?j_
// name gives.
extern "C" void __cdecl __identifier("?j_00002b49@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_00044b0c@@YAXXZ")();

// BfmeHelpD820 is reached only as the ECX `this` of the 0x00002B49 thunk. It
// must be a complete type for the member-pointer route below, so it stays the
// empty view the file has always used.
class BfmeHelpD820
{
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;

class BfmeHeadD820
{
public:
	Object *m_bfmeObject;
	char m_bfmePad[4];
};

class BfmeTailD820
{
public:
	void bfmeTickD820(void);

	char m_bfmePad00[0x20];
	int m_bfmeMode;
	char m_bfmePad24[0x9c - 0x24];
	int m_bfmeId;
};

class BfmeBothD820 : public BfmeHeadD820, public BfmeTailD820
{
};

void BfmeTailD820::bfmeTickD820(void)
{
	if (m_bfmeMode == 2)
	{
		Object *parent = static_cast<BfmeBothD820 *>(this)->m_bfmeObject;
		Object *found = TheGameLogic->findObjectByID(m_bfmeId);
		void *mod = parent->m_bfmeMod;
		if (found && mod)
		{
			Coord3D pos;
			pos.x = found->m_bfmePos.x;
			pos.y = found->m_bfmePos.y;
			pos.z = found->m_bfmePos.z;
			BfmeHelpD820 *help = *(BfmeHelpD820 **)((char *)mod + 0x1cc);
			union { void (*raw)(); void (BfmeHelpD820::*member)(Object *, const Coord3D *, int); } go;
			go.raw = __identifier("?j_00002b49@@YAXXZ");
			(help->*go.member)(parent, &pos, 0);
		}
	}
	union { void (*raw)(); void (BfmeTailD820::*member)(void); } tail;
	tail.raw = __identifier("?j_00044b0c@@YAXXZ");
	(this->*tail.member)();
}
