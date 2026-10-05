// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail's 144-byte body reads byte +0x6b from GameLogic and byte +0x54 from
// GameState. It then walks the bone range. The callers do not prove a method
// name, so the owner uses its retail address.

struct Rva00774AA0Record
{
	char m_pad[0xac];
	unsigned char m_flags;
};

struct Rva00774AA0LogicView
{
	char m_pad[0x6b];
	bool m_flag;
};

struct Rva00774AA0StateView
{
	char m_pad[0x54];
	bool m_flag;
};

class GameLogic;
class GameState;
extern GameLogic *TheGameLogic;
extern GameState *TheGameState;

struct Rva00774AA0Bones
{
	void **m_begin;
	void **m_end;
};

extern void j_00005bcd();
extern void j_0001929a();
extern void j_0003a11b();
extern void j_0001550f();

class Rva00774AA0Owner
{
public:
	void method(float, int, Rva00774AA0Bones *, Rva00774AA0Record *, int);

private:
	void add(void **item)
	{
		typedef void (Rva00774AA0Owner::*Call)(const void *);
		union { void (*function)(void); Call method; } target;
		target.function = j_00005bcd;
		(this->*target.method)(item);
	}

	void validate(float a, int b, Rva00774AA0Record *record, int e)
	{
		typedef void (Rva00774AA0Owner::*Call)(float, int, Rva00774AA0Record *, int);
		union { void (*function)(void); Call method; } target;
		target.function = j_0001929a;
		(this->*target.method)(a, b, record, e);
	}

	void turret(Rva00774AA0Record *record)
	{
		typedef void (Rva00774AA0Owner::*Call)(Rva00774AA0Record *);
		union { void (*function)(void); Call method; } target;
		target.function = j_0003a11b;
		(this->*target.method)(record);
	}
};

struct Rva00774AA0Receiver : Rva00774AA0Record
{
	void call1550f(Rva00774AA0Owner *owner)
	{
		typedef void (Rva00774AA0Receiver::*Call)(Rva00774AA0Owner *);
		union { void (*function)(void); Call method; } target;
		target.function = j_0001550f;
		(this->*target.method)(owner);
	}
};

void Rva00774AA0Owner::method(float a, int b, Rva00774AA0Bones *bones,
	Rva00774AA0Record *record, int e)
{
	if (!record)
		return;
	if (!(record->m_flags & 16) &&
		((TheGameLogic && ((Rva00774AA0LogicView *)TheGameLogic)->m_flag) ||
		 (TheGameState && ((Rva00774AA0StateView *)TheGameState)->m_flag)))
	{
		for (void **it = bones->m_begin; it != bones->m_end; ++it)
			add(it);
		record->m_flags |= 16;
	}
	validate(a, b, record, e);
	turret(record);
	((Rva00774AA0Receiver *)record)->call1550f(this);
}
