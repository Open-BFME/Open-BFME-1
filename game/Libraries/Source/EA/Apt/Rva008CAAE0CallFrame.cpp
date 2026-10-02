// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Apt opcode 0x9E handler (Flash ActionCall slot 0x00ED5CE0 of the table at 0x00ED5A68):
// pops a frame label or number and runs that frame's actions on the calling instance.

struct Rva008CAAE0StringBlock { unsigned short m_refs; };
namespace EAStringC { class StringDataC; }
extern EAStringC::StringDataC g_rva012D5298Empty;
struct BfmeStringPool3AF0;
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;

class Rva008CAAE0String
{
public:
	Rva008CAAE0String()
	{
		m_block = reinterpret_cast<Rva008CAAE0StringBlock *>(
			&g_rva012D5298Empty);
		++m_block->m_refs;
	}
	~Rva008CAAE0String()
	{
		Rva008CAAE0StringBlock *block = m_block;
		--block->m_refs;
		if (block->m_refs == 0)
			reinterpret_cast<void (__cdecl **)(void *)>(
				g_rva01337A30AllocPair)[1](block);
	}
	Rva008CAAE0StringBlock *m_block;
};

class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();

	bool isUndefined() const
	{
		return ((unsigned char)~(m_valueBits >> 15) & 1) != 0;
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

class BfmeA1226
{
public:
	void bfmeDump1226(void *a, int k);
	int m_bfme00;
	void *m_bfme04;
};

struct Rva008CAAE0Definition
{
	char m_pad00[8];
	BfmeA1226 m_frames;
};

struct Rva008CAAE0Character
{
	int findFrame(Rva008CAAE0String *name)
	{
		return ((BfmeF1034 *)&m_definition->m_frames)->bfmeGo1034F((int)name);
	}
	char m_pad00[0xc];
	Rva008CAAE0Definition *m_definition;
};

struct Rva008CAAE0Instance
{
	char m_pad00[0x50];
	Rva008CAAE0Character *m_character;
};

extern void d_008c6320();
typedef void (__cdecl *Rva008CAAE0ResolveName)(void *, void *, Rva008CAAE0String *,
	Rva008CAAE0Instance **, Rva008CAAE0String *);

class AptActionInterpreter
{
public:
	struct LocalContextT
	{
		const unsigned char *m_pc;
		Rva008CAAE0Instance *m_owner;
		void *m_scope;
	};

	static void _FunctionRva008CAAE0(
		AptActionInterpreter *interpreter, LocalContextT *context);

	int m_stackTop;
	int m_stackCapacity;
	AptValue **m_stack;
};

void AptActionInterpreter::_FunctionRva008CAAE0(
	AptActionInterpreter *interpreter, LocalContextT *context)
{
	AptValue *value = interpreter->m_stack[interpreter->m_stackTop - 1];
	int type = value->m_valueBits & 63;
	int frame = -1;

	if ((type == 1 || type == 42) && !value->isUndefined())
	{
		Rva008CAAE0Instance *target;
		Rva008CAAE0String name;
		((Rva008CAAE0ResolveName)d_008c6320)(context->m_owner, context->m_scope,
			&value->string(), &target, &name);
		frame = target->m_character->findFrame(&name);
	}
	else if (type == 7 && !value->isUndefined())
	{
		frame = value->toInteger();
	}

	AptValue *old = interpreter->m_stack[interpreter->m_stackTop - 1];
	if (!old->GetMaxRefCountHit())
		old->Release();
	interpreter->m_stackTop--;

	if (frame != -1)
		context->m_owner->m_character->m_definition->m_frames.bfmeDump1226(context->m_owner, frame);
}
