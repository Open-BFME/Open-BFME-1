// cl: /DNDEBUG /MD /EHsc
// Scratch: retail 0x00605710, 131 bytes. The installed vtables at
// 0x011155A0 / 0x01115594 belong to AnimationSoundClientBehavior.

class Rva00605710Source
{
public:
	char pad0[4];
	int field4;
	int field8;
	char padC[4];
	int field10;
};

struct Rva004091C0Node;
class Rva004091C0Registry
{
public:
	void rva_004091C0(Rva004091C0Node *node);
};

class BfmeResetSubsystem;
extern BfmeResetSubsystem *g_animationSoundClientBehaviorGlobal;

class Rva00605710Root
{
public:
	__forceinline Rva00605710Root(const Rva00605710Source &source)
		: field4(source.field4) {}
	virtual ~Rva00605710Root();
	int field4;
};

class Rva00605710Middle : public Rva00605710Root
{
public:
	__forceinline Rva00605710Middle(const Rva00605710Source &source)
		: Rva00605710Root(source), field8(source.field8) {}
	virtual ~Rva00605710Middle();
	int field8;
};

class Rva00605710Iface
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
};

class AnimationSoundClientBehavior : public Rva00605710Middle,
	public Rva00605710Iface
{
public:
	AnimationSoundClientBehavior(const Rva00605710Source &source);
	virtual ~AnimationSoundClientBehavior();
	virtual void slot0();
	virtual void slot1();
	int field10;
	AnimationSoundClientBehavior *next;
	AnimationSoundClientBehavior *prev;
};

AnimationSoundClientBehavior::AnimationSoundClientBehavior(const Rva00605710Source &source)
	: Rva00605710Middle(source), Rva00605710Iface(),
	  field10(source.field10), next(0), prev(0)
{
	if (g_animationSoundClientBehaviorGlobal)
		((Rva004091C0Registry *)g_animationSoundClientBehaviorGlobal)->rva_004091C0(
			(Rva004091C0Node *)this);
}
