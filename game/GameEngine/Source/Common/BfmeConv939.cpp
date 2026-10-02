// Open-BFME5 conversions.

class BfmeGlob939A
{
public:
	virtual void bfmeSlot939A00();
	virtual void bfmeSlot939A01();
	virtual void bfmeSlot939A02();
	virtual void bfmeSlot939A03();
	virtual void bfmeTail939A();
};

// Retail's global at 0x012F64BC is ParticleSystemManager *TheParticleSystemManager;
// only the global's spelling matters to the link, so the pointee keeps this
// TU's own vtable view (BfmeGlob939A) and is cast at the use.
class ParticleSystemManager;

extern ParticleSystemManager *TheParticleSystemManager;
void bfmeCall939A(void);

void bfmeGo939A(void)
{
	bfmeCall939A();
	((BfmeGlob939A *)TheParticleSystemManager)->bfmeTail939A();
}

class Object;
class DelayedLuaEventList;

struct BfmeElem939B
{
	int m_bfmeA;
	int m_bfmeB;
};

class BfmeOwnerBR
{
public:
	void bfmeGo939B(int i, Object *object, DelayedLuaEventList *events);
	void bfmeTail939B(BfmeElem939B *e, Object *object, DelayedLuaEventList *events);
	char m_bfmePad[0x10];
	BfmeElem939B m_bfmeArr[1];
};

void BfmeOwnerBR::bfmeGo939B(int i, Object *object, DelayedLuaEventList *events)
{
	bfmeTail939B(&m_bfmeArr[i], object, events);
}

class BfmeGlob939C
{
public:
	virtual void bfmeSlot939C00();
	virtual void bfmeSlot939C01();
	virtual void bfmeSlot939C02();
	virtual void bfmeSlot939C03();
	virtual void bfmeSlot939C04();
	virtual void bfmeSlot939C05();
	virtual void bfmeSlot939C06();
	virtual void bfmeSlot939C07();
	virtual void bfmeSlot939C08();
	virtual void bfmeSlot939C09();
	virtual void bfmeSlot939C10();
	virtual void bfmeSlot939C11();
	virtual void bfmeSlot939C12();
	virtual void bfmeSlot939C13();
	virtual void bfmeSlot939C14();
	virtual void bfmeSlot939C15();
	virtual void bfmeSlot939C16();
	virtual void bfmeSlot939C17();
	virtual void bfmeSlot939C18();
	virtual void bfmeSlot939C19();
	virtual void bfmeSlot939C20();
	virtual void bfmeSlot939C21();
	virtual void bfmeSlot939C22();
	virtual void bfmeSlot939C23();
	virtual void bfmeSlot939C24();
	virtual void bfmeSlot939C25();
	virtual void bfmeSlot939C26();
	virtual void bfmeSlot939C27();
	virtual void bfmeSlot939C28();
	virtual void bfmeSlot939C29();
	virtual void bfmeSlot939C30();
	virtual int bfmeVirt939C(int f);
};

// Retail's global at 0x012ED668 is `AudioManager *TheAudio`, defined once in
// Common/Audio/GameAudio.cpp. Only the name has to be canonical for the link;
// this TU keeps its own TU-local view of the pointee and casts at the use.
class AudioManager;

extern AudioManager *TheAudio;

int bfmeGo939C(void)
{
	int r = ((BfmeGlob939C *)TheAudio)->bfmeVirt939C(0);
	return r == 0;
}

// Retail global at 0x012F0898 is GameLogic *TheGameLogic (defined once in
// game_logic.cpp). This TU calls through a local view type, so keep the view
// and cast at the use; the global itself uses the canonical spelling.
class BfmeGlob939D
{
public:
	char bfmeCall939D();
};

class GameLogic;
extern GameLogic *TheGameLogic;

int __stdcall bfmeGo939D(char v)
{
	char r = reinterpret_cast<BfmeGlob939D *>(TheGameLogic)->bfmeCall939D();
	return (char)(r - v) == 0;
}

extern char g_bfme939Str[];

class BfmeSub939E
{
public:
	void bfmeCall939E(int *out, char *s);
};

void bfmeGo939E(BfmeSub939E *a)
{
	int tmp;
	a->bfmeCall939E(&tmp, g_bfme939Str);
}

class BfmeSub939G
{
public:
	void bfmeCall939G();
	void *m_bfmeP;
};

class BfmeThing939G
{
public:
	void bfmeGo939G(void *a);
	char m_bfmePad[8];
	BfmeSub939G m_bfmeSub;
};

void BfmeThing939G::bfmeGo939G(void *a)
{
	BfmeSub939G *s = &m_bfmeSub;
	if (!a && s->m_bfmeP)
		s->bfmeCall939G();
}
