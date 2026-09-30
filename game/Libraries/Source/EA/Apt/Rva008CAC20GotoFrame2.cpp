// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Apt opcode 0x9F handler (Flash ActionGotoFrame2, slot 0x00ED5CE4 of the table at 0x00ED5A68):
// pops a frame label or number, moves the target clip there and sets its play flag.

struct Rva008CAAE0StringBlock { unsigned short m_refs; };
extern Rva008CAAE0StringBlock g_bfmeDefaultString1284;
extern void (__cdecl **g_bfmeStringPool1284)(void *);

class Rva008CAAE0String
{
public:
	Rva008CAAE0String()
	{
		m_block = &g_bfmeDefaultString1284;
		++m_block->m_refs;
	}
	~Rva008CAAE0String()
	{
		Rva008CAAE0StringBlock *block = m_block;
		--block->m_refs;
		if (block->m_refs == 0)
			g_bfmeStringPool1284[1](block);
	}
	Rva008CAAE0StringBlock *m_block;
};

class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();

	int type() const { return m_valueBits & 63; }
	bool isUndefined() const
	{
		return ((unsigned char)~(m_valueBits >> 15) & 1) != 0;
	}
	bool isCharacterInst() const
	{
		int kind = m_valueBits & 63;
		return kind >= 12 && kind <= 19 && !isUndefined();
	}
	bool GetMaxRefCountHit() const
	{
		return (m_valueBits >> 30 & 1) != 0;
	}
	int toInteger() const;
	Rva008CAAE0String &string()
	{
		int type = m_valueBits & 63;
		return *(Rva008CAAE0String *)((char *)(type == 1 ? this : m_stringObject) + 8);
	}

	unsigned int m_valueBits;
	char m_pad08[0x18];
	AptValue *m_stringObject;
};

class BfmeF1034
{
public:
	int bfmeGo1034F(int k);
};

struct Rva008CAAE0Definition
{
	char m_pad00[8];
	BfmeF1034 m_frames;
};

struct Rva008CAC20Character
{
	int findFrame(Rva008CAAE0String *name)
	{
		return m_definition->m_frames.bfmeGo1034F((int)name);
	}
	char m_pad00[0xc];
	Rva008CAAE0Definition *m_definition;
	char m_pad10[0xc];
	unsigned int m_flagsLow : 25;
	unsigned int m_playing : 1;
	unsigned int m_flagsHigh : 6;
};

class BfmeThingCBC
{
public:
	void bfmeStepCBC(int count);
};

class Rva008CAC20Instance : public AptValue
{
public:
	void gotoFrame(int frame) { ((BfmeThingCBC *)this)->bfmeStepCBC(frame); }

	char m_pad24[0x2c];
	Rva008CAC20Character *m_character;
};

extern void d_008c6320();
typedef void (__cdecl *Rva008CAC20ResolveName)(Rva008CAC20Instance *, Rva008CAC20Instance *,
	Rva008CAAE0String *, Rva008CAC20Instance **, Rva008CAAE0String *);

class AptActionInterpreter
{
public:
	struct LocalContextT
	{
		const unsigned char *m_pc;
		Rva008CAC20Instance *m_owner;
		Rva008CAC20Instance *m_scope;
	};

	static void _FunctionRva008CAC20(
		AptActionInterpreter *interpreter, LocalContextT *context);

	int m_stackTop;
	int m_stackCapacity;
	AptValue **m_stack;
};

void AptActionInterpreter::_FunctionRva008CAC20(
	AptActionInterpreter *interpreter, LocalContextT *context)
{
	const int *play = (const int *)(((unsigned int)context->m_pc + 3) & ~3u);
	context->m_pc = (const unsigned char *)(play + 1);
	AptValue *value = interpreter->m_stack[interpreter->m_stackTop - 1];

	Rva008CAC20Instance *target = 0;
	if (context->m_scope && context->m_scope->isCharacterInst())
		target = context->m_scope;
	else if (context->m_owner->isCharacterInst())
		target = context->m_owner;

	int type = value->m_valueBits & 63;
	int frame = -1;
	if ((type == 1 || type == 42) && !value->isUndefined())
	{
		Rva008CAC20Instance *found;
		Rva008CAAE0String name;
		((Rva008CAC20ResolveName)d_008c6320)(context->m_owner, context->m_scope,
			&value->string(), &found, &name);
		if (found->isCharacterInst() && (found->type() == 13 || found->type() == 18))
			frame = found->m_character->findFrame(&name);
	}
	else if (type == 7 && !value->isUndefined())
	{
		frame = value->toInteger();
	}

	if (frame != -1)
	{
		target->gotoFrame(frame);
		target->m_character->m_playing = *play != 0;
	}

	AptValue *old = interpreter->m_stack[interpreter->m_stackTop - 1];
	if (!old->GetMaxRefCountHit())
		old->Release();
	interpreter->m_stackTop--;
}
