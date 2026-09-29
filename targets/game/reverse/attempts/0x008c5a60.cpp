// ?_FunctionAptActionGotoLabel@AptActionInterpreter@@SAXPAV1@PAULocalContextT@1@@Z
// partial score=0.873 date=2026-09-30
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// EA Apt ActionScript GoToLabel (opcode 0x8C), retail 0x008C5A60: slot 0x8C of
// the opcode table based at 0x00ED5A68 (see
// AptActionInterpreterStoreRegister.cpp), at 0x00ED5C98.
//
// The aligned operand is the label text.  The current target sprite (context
// +0x08, when it is a live sprite value) or else the default target (+0x04)
// looks the label up in its timeline's frame-label table and, when found,
// jumps there and clears the timeline's 0x02000000 flag.  The label string is
// the same ref-counted Apt string DispatchLiteral008C5840.cpp models.

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
};

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

class BfmeStrVKI
{
public:
	BfmeStrVKI(const char *text) { bfmeSetVKI(text); }
	~BfmeStrVKI()
	{
		BfmeStringData3AF0 *data = m_data;
		--data->m_refCount;
		if (data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	void bfmeSetVKI(const char *text);

	BfmeStringData3AF0 *m_data;
};

class BfmeF1034
{
public:
	int bfmeGo1034F(int label);
};

struct Rva008C5A60Labels
{
	char m_pad00[8];
	BfmeF1034 m_labels;
};

struct Rva008C5A60Timeline
{
	char m_pad00[0x0c];
	Rva008C5A60Labels *m_labelTable;
	char m_pad10[0x0c];
	unsigned int m_flags;
};

class BfmeThingCBC
{
public:
	void bfmeStepCBC(int frame);
};

class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();

	bool isSprite() const
	{
		int type = m_valueBits & 0x3f;
		return type >= 0x0c && type <= 0x13 && !isUndefined();
	}

	bool isUndefined() const
	{
		return ((unsigned char)~(m_valueBits >> 15) & 1) != 0;
	}

	unsigned int m_valueBits;
	char m_pad08[0x48];
	Rva008C5A60Timeline *m_timeline;
};

class AptActionInterpreter
{
public:
	struct LocalContextT
	{
		const unsigned char *m_pc;
		AptValue *m_defaultTarget;
		AptValue *m_target;
	};

	static void _FunctionAptActionGotoLabel(
		AptActionInterpreter *interpreter, LocalContextT *context);
};

void AptActionInterpreter::_FunctionAptActionGotoLabel(
	AptActionInterpreter *interpreter, LocalContextT *context)
{
	const unsigned char *p = (const unsigned char *)(((unsigned int)context->m_pc + 3) & ~3u);
	context->m_pc = p + 4;
	BfmeStrVKI label(*(const char *const *)p);

	AptValue *target = context->m_target;
	if (target == 0 || !target->isSprite())
		target = context->m_defaultTarget;

	int frame = target->m_timeline->m_labelTable->m_labels.bfmeGo1034F((int)&label);
	if (frame >= 0)
	{
		((BfmeThingCBC *)target)->bfmeStepCBC(frame);
		target->m_timeline->m_flags &= ~0x02000000;
	}
}
