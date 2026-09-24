// ?onContaining@Rva0021D5D0Secondary@@QAEXPAVObject@@_N@Z
// partial score=0.99 date=2026-09-24
// cl: /O2 /DNDEBUG /MD /EHsc
typedef bool Bool;

class Object
{
public:
	void setStatusBit(int status, Bool enable);
	unsigned char m_beforeStatus[0x94];
	unsigned char m_status;
};

struct Rva0021D5D0Node
{
	Rva0021D5D0Node *m_next;
	Rva0021D5D0Node *m_prev;
	Object *m_object;
};

class GarrisonContain
{
public:
	virtual void onContaining(Object *object, Bool selected);
};

class Gen0021CE60
{
public:
	void handle(int objectBits);
};

class Rva0021D180Primary
{
public:
	void handle();
};

class Rva00202DF0Face;
class Rva00202DF0Head
{
public:
	void apply(Rva00202DF0Face *object, int delay);
};

class GameLogic
{
public:
	unsigned char m_beforeFrame[0x3c];
	unsigned int m_frame;
};
extern GameLogic *TheBfmeGameLogic;

// This receiver is ContestableContain's secondary interface at primary+0x20.
// The ctor at 0x0021BEE0 installs its 0x010AB140 vtable here; slot 17
// (ILT 0x000494A4) routes to this 0x0021D5D0 body.
class Rva0021D5D0Secondary
{
public:
	void onContaining(Object *object, Bool selected);

private:
	void *primary() const { return (char *)this - 0x20; }
	Object *owner() const
	{
		return *(Object *const *)((const char *)this - 0x18);
	}
	Rva0021D5D0Node *contestHead() const
	{
		return *(Rva0021D5D0Node *const *)((const char *)this + 0x99c);
	}
	Rva0021D5D0Node *containHead() const
	{
		return *(Rva0021D5D0Node *const *)((const char *)this + 0x18);
	}
	Bool disabled() const { return *((const char *)this + 0x9b8) != 0; }
	void setNextFrame(unsigned int frame)
	{
		*(unsigned int *)((char *)this + 0x9b4) = frame;
	}
};

void Rva0021D5D0Secondary::onContaining(Object *object, Bool selected)
{
	((GarrisonContain *)this)->GarrisonContain::onContaining(object, selected);
	Object *host = owner();
	if (disabled())
		return;
	if (contestHead()->m_next == contestHead())
		return;

	if (host->m_status & 8) {
		((Gen0021CE60 *)primary())->handle((int)object);
	} else {
		if (containHead()->m_next == containHead()) {
			((Rva0021D180Primary *)primary())->handle();
			return;
		}

		host->setStatusBit(0x23, true);
		for (Rva0021D5D0Node *node = containHead()->m_next;
			node != containHead(); node = node->m_next)
			((Gen0021CE60 *)primary())->handle((int)node->m_object);

		for (Rva0021D5D0Node *node = contestHead()->m_next;
			node != contestHead(); node = node->m_next)
			((Gen0021CE60 *)primary())->handle((int)node->m_object);
	}

	((Rva00202DF0Head *)primary())->apply((Rva00202DF0Face *)host, 1);
	setNextFrame(TheBfmeGameLogic->m_frame);
}
