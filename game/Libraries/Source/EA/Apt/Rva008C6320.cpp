// ?rva008C6320@@YA_NPAVBfmeNode1220@@0PBVBfmeStrVKI@@PAPAV1@PAV2@@Z
// cl: /DNDEBUG /MD /EHsc
// Apt target-path parsing (0x008C6320, 0x008C4DA0) and the opcode-0x3D
// handler that uses it (0x008D0B00), kept in one unit: VC7.1 /O2 keeps the
// handler's &selected/&key outputs unaliased (retail's register allocation)
// only while both parser bodies are visible to it, transitively
// (targets/game/reverse/identity_evidence/008d0b00-parser-visibility.md).
//
// 0x008D0B00: Apt opcode-table entry 0x3D (VA 0x012D5B5C in the table at
// 0x012D5A68); cdecl (interpreter, context). Its name/params/function locals
// follow Open BFME 2's _FunctionAptActionCallFunction
// (Code/Libraries/Source/Apt/AptActionInterpreterConstantHandlers.cpp at
// b5a7b8290a), the same opcode slot there; BFME 1's body has no debug call
// stack and keeps its address-derived name.

struct Rva008C6320StringData
{
	unsigned short references;
	unsigned short length;
	unsigned short capacity;
	unsigned short flags;
	char text[ 1 ];
};

// VA 0x01337A30 is Apt.cpp's ?g_rva01337A30AllocPair@@3PAUBfmeStringPool3AF0@@A (data_rows).
struct BfmeStringPool3AF0 { void *m_alloc; void (__cdecl *m_free)(void *storage); };
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;

class BfmeStrVKI
{
public:
	BfmeStrVKI( const char *text ) { bfmeSetVKI( text ); }
	~BfmeStrVKI()
	{
		Rva008C6320StringData *block = data;
		if( --block->references == 0 )
			g_rva01337A30AllocPair->m_free(block );
	}
	void bfmeSetVKI( const char *text );
	const char *str() const { return (const char *)data + 8; }
	Rva008C6320StringData *data;
};

extern "C" char *strcpy(char *,const char *);
#pragma intrinsic(strcpy)
class BfmeNode1220 { public: int bfmeTest1220(int *,int); };
struct Root8C4DA0 { char pad[0x58]; BfmeNode1220 *root; };
struct Owner8C4DA0 { Root8C4DA0 *root; };
struct State8C4DA0 { char pad[0x122c]; Owner8C4DA0 *owner; };
extern State8C4DA0 *g_bfmeHolderBU;

// ?ParsePath8C4DA0@@YA_NPAVBfmeNode1220@@0PBVBfmeStrVKI@@PAPAV1@PAD@Z
bool ParsePath8C4DA0(BfmeNode1220 *inputScope,BfmeNode1220 *context,const BfmeStrVKI *path,BfmeNode1220 **out,char *name)
{
 BfmeNode1220 *scope=inputScope;
 const char *src=path->str();
 *name=0;
 bool absolute=false;
 if (*src=='/') {
  scope=g_bfmeHolderBU->owner->root->root;
  ++src;
  *out=scope;
  absolute=true;
 } else *out=scope;
 char buffer[256];
 char *dest=buffer;
 while (*src) {
  switch (*src) {
  case '.':
   if (src[1]=='.') {
    *dest++=*src;
    *dest++=*++src;
   } else {
    *dest=0;
    BfmeNode1220 *next=(BfmeNode1220 *)scope->bfmeTest1220((int *)&BfmeStrVKI(buffer),(int)context);
    context=0;
    if (!next) { *out=0; return absolute; }
    scope=next;
    dest=buffer;
   }
   break;
  case ':': {
   *dest=0;
   BfmeNode1220 *found=(BfmeNode1220 *)scope->bfmeTest1220((int *)&BfmeStrVKI(buffer),(int)context);
   context=0;
   if (found) {
    *out=found;
    strcpy(name,src+1);
    return absolute;
   }
   dest=buffer;
   break;
  }
  default: *dest++=*src; break;
  }
  ++src;
 }
 *dest=0;
 if (context) scope=context;
 *out=scope;
 strcpy(name,buffer);
 return absolute;
}


bool rva008C6320( BfmeNode1220 *context, BfmeNode1220 *scope,
	const BfmeStrVKI *path, BfmeNode1220 **targetOut,
	BfmeStrVKI *nameOut )
{
	BfmeNode1220 *scopePointer = scope;
	const BfmeStrVKI &input = *path;
	Rva008C6320StringData *inputBlock = input.data;
	const char *cursor = inputBlock->text;
	char name[ 256 ];
	char character = *cursor++;
	while( character != 0 )
	{
		if( character < '0' || character == ':' )
			goto parse;
		character = *cursor++;
	}
	if( scopePointer == 0 )
	{
		++inputBlock->references;
		Rva008C6320StringData *oldBlock = nameOut->data;
		if( --oldBlock->references == 0 )
			g_rva01337A30AllocPair->m_free(oldBlock );
		nameOut->data = input.data;
		*targetOut = context;
		return false;
	}

parse:
	bool absolute = ParsePath8C4DA0( context, scopePointer, &input, targetOut, name );
	BfmeStrVKI parsedName( name );
	++parsedName.data->references;
	Rva008C6320StringData *oldBlock = nameOut->data;
	if( --oldBlock->references == 0 )
		g_rva01337A30AllocPair->m_free(oldBlock );
	nameOut->data = parsedName.data;
	return absolute;
}

struct Rva8D0D80StringBlock
{
	unsigned short m_refs;
	char m_header[6];
	char text[1];
};

extern Rva8D0D80StringBlock g_bfmeDefaultString1284;

class Rva8D0B00String
{
public:
	Rva8D0B00String()
	{
		m_block = &g_bfmeDefaultString1284;
		++g_bfmeDefaultString1284.m_refs;
	}
	Rva8D0B00String(const char *text) { setText0089E680(text); }
	void setText0089E680(const char *text);
	~Rva8D0B00String()
	{
		Rva8D0D80StringBlock *block = m_block;
		--block->m_refs;
		if (block->m_refs == 0)
			g_rva01337A30AllocPair->m_free(block);
	}

public:
	Rva8D0D80StringBlock *m_block;
};

class Rva8D0B00Value
{
public:
	virtual void addRef();
	virtual void release();

	unsigned m_flags;
	char m_gap[0x18];
	Rva8D0B00Value *m_indirect;
};

struct Rva8D0B00Context
{
	int m_unused;
	Rva8D0B00Value *m_first;
	void *m_second;
};

class Rva8D0B00State
{
public:
	int m_count;
	int m_unused;
	Rva8D0B00Value **m_stack;
};


// Pinned callee views: toInteger 0x00898300, the bounded lookup 0x008B8E50,
// createString 0x008CC940 and the call hub 0x008CF740.
class AptValue { public: int toInteger() const; };
class Gen_008B8E50 { public: int bfmeAt(int index) const; };
class Rva00899770;
class Rva008AE770Stack
{
public:
	Rva00899770 *createString(void *, int, BfmeStrVKI *, int, int, int);
};
class Rva008CF740Value;
class Rva008CF740
{
public:
	void run(Rva008CF740Value *primary, Rva008CF740Value *value, int count);
};

// ?rva8D0B00RouteAction@@YAXPAVRva8D0B00State@@PAURva8D0B00Context@@@Z
void rva8D0B00RouteAction(Rva8D0B00State *state,
	Rva8D0B00Context *context)
{
	Rva8D0B00State *owner = state;
	int count = owner->m_count;
	Rva8D0B00Value *name = owner->m_stack[count - 1];
	Rva8D0B00Value *params = owner->m_stack[count - 2];
	int number = ((const AptValue *)params)->toInteger();
	Rva8D0B00String key;
	Rva8D0B00Value *function = 0;
	Rva8D0B00Value *selected = 0;
	{

		unsigned flags = name->m_flags;
		int type = flags & 0x3f;
		if (type == 22)
		{
			flags >>= 15;
			if (!((unsigned char)~flags & 1))
				name = (Rva8D0B00Value *)((const Gen_008B8E50 *)name)->bfmeAt(0);
		}

		flags = name->m_flags;
		type = flags & 0x3f;
		if ((type == 1 || type == 42) && !((unsigned char)~(flags >> 15) & 1))
		{
			Rva8D0B00Value *stringValue = type == 1 ? name : name->m_indirect;
			rva008C6320((BfmeNode1220 *)context->m_first,
				(BfmeNode1220 *)context->m_second,
				(const BfmeStrVKI *)((char *)stringValue + 8),
				(BfmeNode1220 **)&selected, (BfmeStrVKI *)&key);
			function = (Rva8D0B00Value *)((Rva008AE770Stack *)owner)->createString(
				selected, (int)context->m_second, (BfmeStrVKI *)&key, 1, 1, 0);
		}
		else
			function = name;

	}
	function->addRef();
	for (int i = 1; i <= 2; ++i)
	{
		Rva8D0B00Value *value = owner->m_stack[owner->m_count - i];
		if (!((unsigned char)(value->m_flags >> 30) & 1))
			value->release();
	}
	owner->m_count -= 2;
	((Rva008CF740 *)owner)->run(
		(Rva008CF740Value *)(selected != 0 ? selected : context->m_first),
		(Rva008CF740Value *)function, number);
	function->release();
}
