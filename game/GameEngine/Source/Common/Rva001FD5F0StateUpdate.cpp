// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// Address-derived reconstruction of retail 0x001FD5F0.  The owner name is
// deliberately neutral: no named caller reaches this body in the current
// reverse index.  The offsets and helper ABIs below are directly established
// by the retail body and its existing callee rows.

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

class Rva001FD5F0Ranges
{
public:
	unsigned char m_pad00[0x28];
	BfmeStrF9 *m_first;
	BfmeStrF9 *m_second;
	unsigned char m_pad30[4];
	BfmeStrF9 *m_third;
	BfmeStrF9 *m_fourth;
};

class Rva001FD5F0Pathfinder
{
public:
	void call(void *);
};

class AI
{
public:
	unsigned char m_pad00[0x0c];
	Rva001FD5F0Pathfinder *m_pathfinder;
};

extern AI *TheAI;

extern void j_00048d6a();
extern void j_00013d95();
extern void j_0000c1ee();
extern void j_00020c20();
extern void j_0000b81b();

class Rva001FD5F0Owner
{
public:
	void update();

private:
	void *m_field00;
	void *m_field04;
	Rva001FD5F0Ranges *m_ranges;
	void *m_object;
	unsigned char m_pad10[0x1c];
	int m_state;
};

class Rva001FD5F0ObjectTarget
{
public:
	void call(int);
};

class Rva001FD5F0ResetTarget
{
public:
	void call(char);
};

typedef void (Rva001FD5F0ResetTarget::*Rva001FD5F0ResetCall)(char);
typedef void (Rva001FD5F0Owner::*Rva001FD5F0NoArgCall)();
typedef void (Rva001FD5F0ObjectTarget::*Rva001FD5F0ObjectCall)(int);
typedef void (Rva001FD5F0Pathfinder::*Rva001FD5F0PathCall)(void *);

void Rva001FD5F0Owner::update()
{
	if (m_state == 1)
		return;

	union { void *asVoid; Rva001FD5F0NoArgCall asMember; } stepCast;
	stepCast.asVoid = (void *)j_00048d6a;
	(this->*stepCast.asMember)();

	void *object = m_object;
	union { void *asVoid; Rva001FD5F0PathCall asMember; } pathCallCast;
	pathCallCast.asVoid = (void *)j_00013d95;
	(TheAI->m_pathfinder->*pathCallCast.asMember)(object);

	m_state = 1;
	union { void *asVoid; Rva001FD5F0ObjectCall asMember; } objectCallCast;
	objectCallCast.asVoid = (void *)j_0000c1ee;
	(reinterpret_cast<Rva001FD5F0ObjectTarget *>(object)->*
		objectCallCast.asMember)(9);

	Rva001FD5F0Ranges *ranges = m_ranges;
	BfmeObjF9 *flags = reinterpret_cast<BfmeObjF9 *>(
		reinterpret_cast<unsigned char *>(object) + 0xac);

	for (BfmeStrF9 *entry = ranges->m_first;
		 entry != ranges->m_second; ++entry)
		flags->setFlag(*entry, 0);

	for (BfmeStrF9 *entry = ranges->m_third;
		 entry != ranges->m_fourth; ++entry)
		flags->setFlag(*entry, 1);

	union { void *asVoid; Rva001FD5F0ResetCall asMember; } resetCast;
	resetCast.asVoid = (void *)j_00020c20;
	(reinterpret_cast<Rva001FD5F0ResetTarget *>(object)->*
		resetCast.asMember)(1);
	union { void *asVoid; Rva001FD5F0PathCall asMember; } addCast;
	addCast.asVoid = (void *)j_0000b81b;
	(TheAI->m_pathfinder->*addCast.asMember)(object);
}

// ?update@Rva001FD5F0Owner@@QAEXXZ
