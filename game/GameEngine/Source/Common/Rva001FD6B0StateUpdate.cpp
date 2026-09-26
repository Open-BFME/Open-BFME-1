// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// Address-derived reconstruction of retail 0x001FD6B0.  No named caller is
// present in the current reverse index, so the owner remains deliberately
// neutral.  The state, range, object, helper, and Bool-argument ABIs below
// are taken from the retail body and existing callee rows.

typedef bool Bool;

class BfmeStrF9
{
public:
	unsigned int m_data;
};

class BfmeObjF9
{
public:
	void setFlag(const BfmeStrF9 &, char);
};

class Rva001FD6B0Ranges
{
public:
	unsigned char m_pad00[0x28];
	BfmeStrF9 *m_first;
	BfmeStrF9 *m_second;
	unsigned char m_pad30[4];
	BfmeStrF9 *m_third;
	BfmeStrF9 *m_fourth;
};

class Rva001FD6B0Pathfinder
{
public:
	void call(void *);
};

class AI
{
public:
	unsigned char m_pad00[0x0c];
	Rva001FD6B0Pathfinder *m_pathfinder;
};

extern AI *TheAI;

extern void j_00048d6a();
extern void j_00013d95();
extern void j_0002bb0c();
extern void j_00020c20();
extern void j_0000b81b();

class Rva001FD6B0Owner
{
public:
	void update(Bool enabled);

private:
	void *m_field00;
	void *m_field04;
	Rva001FD6B0Ranges *m_ranges;
	void *m_object;
	unsigned char m_pad10[0x1c];
	int m_state;
};

class Rva001FD6B0ObjectTarget
{
public:
	void call(int);
};

class Rva001FD6B0ResetTarget
{
public:
	void call(char);
};

typedef void (Rva001FD6B0ResetTarget::*Rva001FD6B0ResetCall)(char);

typedef void (Rva001FD6B0Owner::*Rva001FD6B0OwnerCall)();
typedef void (Rva001FD6B0ObjectTarget::*Rva001FD6B0ObjectCall)(int);
typedef void (Rva001FD6B0Pathfinder::*Rva001FD6B0PathCall)(void *);

void Rva001FD6B0Owner::update(Bool enabled)
{
	if (m_state == 2 && !enabled)
		return;

	union { void *asVoid; Rva001FD6B0OwnerCall asMember; } stepCast;
	stepCast.asVoid = (void *)j_00048d6a;
	(this->*stepCast.asMember)();

	void *object = m_object;
	union { void *asVoid; Rva001FD6B0PathCall asMember; } pathCallCast;
	// This retail call also loads ECX. The target is stdcall and ignores it;
	// this TU-local adapter retains the observed call-site register setup.
	pathCallCast.asVoid = (void *)j_00013d95;
	(TheAI->m_pathfinder->*pathCallCast.asMember)(object);

	m_state = 2;
	union { void *asVoid; Rva001FD6B0ObjectCall asMember; } objectCallCast;
	objectCallCast.asVoid = (void *)j_0002bb0c;
	(reinterpret_cast<Rva001FD6B0ObjectTarget *>(object)->*
		objectCallCast.asMember)(9);

	Rva001FD6B0Ranges *ranges = m_ranges;
	BfmeObjF9 *flags = reinterpret_cast<BfmeObjF9 *>(
		reinterpret_cast<unsigned char *>(object) + 0xac);

	for (BfmeStrF9 *entry = ranges->m_first;
		 entry != ranges->m_second; ++entry)
		flags->setFlag(*entry, 1);

	for (BfmeStrF9 *entry = ranges->m_third;
		 entry != ranges->m_fourth; ++entry)
		flags->setFlag(*entry, 0);

	union { void *asVoid; Rva001FD6B0ResetCall resetCast; } reset;
	reset.asVoid = (void *)j_00020c20;
	(reinterpret_cast<Rva001FD6B0ResetTarget *>(object)->*
		reset.resetCast)(1);
	union { void *asVoid; Rva001FD6B0PathCall addCast; } add;
	add.asVoid = (void *)j_0000b81b;
	(TheAI->m_pathfinder->*add.addCast)(object);
}

// ?update@Rva001FD6B0Owner@@QAEX_N@Z
