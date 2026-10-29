// ?rva8D0B00RouteAction@@YAXPAVRva8D0B00State@@PAURva8D0B00Context@@@Z
// partial score=0.9034 date=2026-10-29
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva8D0B00StringBlock
{
	unsigned short m_refs;
	char m_header[6];
	char text[1];
};

extern Rva8D0B00StringBlock g_bfmeDefaultString1284;
extern void (__cdecl **Rva01337A30ReleaseTable)(void *);

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
		Rva8D0B00StringBlock *block = m_block;
		--block->m_refs;
		if (block->m_refs == 0)
			Rva01337A30ReleaseTable[1](block);
	}

public:
	Rva8D0B00StringBlock *m_block;
};

class Rva8D0B00Value
{
public:
	virtual void addRef();
	virtual void release();
	Rva8D0B00Value *lookup0089C290(Rva8D0B00String *key, Rva8D0B00Value *context);
	int toInteger() const; // thiscall 0x00898300, EAX signed count, no stack args
	Rva8D0B00Value *at(int index) const; // thiscall 0x008B8E50, ret 4, EAX value

	bool maxRefCountHit() const
	{
		return ((m_flags >> 30) & 1) != 0;
	}

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
	Rva8D0B00Value *makeValue(Rva8D0B00Value *number, void *contextValue, Rva8D0B00String *key,
		int one1, int one2, int zero);
	void finish(Rva8D0B00Value *primary, Rva8D0B00Value *value, int number);

	int m_count;
	int m_unused;
	Rva8D0B00Value **m_stack;
};

inline __declspec(noinline) bool rva8C6320PrepareRoute(Rva8D0B00Value *first, void *second, const void *data,
	Rva8D0B00Value **lookup, Rva8D0B00String *key);

extern "C" char *strcpy(char *, const char *);
#pragma intrinsic(strcpy)
struct Rva8D0B00Root { char pad[0x58]; Rva8D0B00Value *root; };
struct Rva8D0B00Owner { Rva8D0B00Root *root; };
struct Rva8D0B00Global { char pad[0x122c]; Rva8D0B00Owner *owner; };
extern Rva8D0B00Global *g_bfmeHolderBU;
inline __declspec(noinline) bool ParsePath8C4DA0(Rva8D0B00Value *inputScope,Rva8D0B00Value *context,const Rva8D0B00String *path,Rva8D0B00Value **out,char *name)
{
 Rva8D0B00Value *scope=inputScope;
 const char *src=path->m_block->text;
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
    Rva8D0B00Value *next=(Rva8D0B00Value *)scope->lookup0089C290(&Rva8D0B00String(buffer),context);
    context=0;
    if (!next) { *out=0; return absolute; }
    scope=next;
    dest=buffer;
   }
   break;
  case ':': {
   *dest=0;
   Rva8D0B00Value *found=(Rva8D0B00Value *)scope->lookup0089C290(&Rva8D0B00String(buffer),context);
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

inline __declspec(noinline) bool rva8C6320PrepareRoute( Rva8D0B00Value *context, void *rawScope,
	const void *rawPath, Rva8D0B00Value **targetOut,
	Rva8D0B00String *nameOut )
{
	Rva8D0B00Value *scopePointer = (Rva8D0B00Value *)rawScope;
	const Rva8D0B00String *path = (const Rva8D0B00String *)rawPath;
	const Rva8D0B00String &input = *path;
	Rva8D0B00StringBlock *inputBlock = input.m_block;
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
		++inputBlock->m_refs;
		Rva8D0B00StringBlock *oldBlock = nameOut->m_block;
		if( --oldBlock->m_refs == 0 )
			Rva01337A30ReleaseTable[ 1 ]( oldBlock );
		nameOut->m_block = input.m_block;
		*targetOut = context;
		return false;
	}

parse:
	bool absolute = ParsePath8C4DA0( context, scopePointer, &input, targetOut, name );
	Rva8D0B00String parsedName( name );
	++parsedName.m_block->m_refs;
	Rva8D0B00StringBlock *oldBlock = nameOut->m_block;
	if( --oldBlock->m_refs == 0 )
		Rva01337A30ReleaseTable[ 1 ]( oldBlock );
	nameOut->m_block = parsedName.m_block;
	return absolute;
}

void rva8D0B00RouteAction(Rva8D0B00State *state,
	Rva8D0B00Context *context)
{
	Rva8D0B00State *owner = state;
	int count = owner->m_count;
	Rva8D0B00Value *top = owner->m_stack[count - 1];
	Rva8D0B00Value *under = owner->m_stack[count - 2];
	int number = under->toInteger();
	Rva8D0B00String key;
	Rva8D0B00Value *selected = 0;
	{

		unsigned flags = top->m_flags;
		int type = flags & 0x3f;
		if (type == 22)
		{
			flags >>= 15;
			if (!((unsigned char)~flags & 1))
				top = top->at(0);
		}

		flags = top->m_flags;
		type = flags & 0x3f;
		if (type == 1 || type == 42)
		{
			flags >>= 15;
			if (!((unsigned char)~flags & 1))
			{
				Rva8D0B00Value *stringValue = type == 1 ? top : top->m_indirect;
				Rva8D0B00Context *routeContext = context;
				rva8C6320PrepareRoute(routeContext->m_first,
					routeContext->m_second,
					(char *)stringValue + 8, &selected, &key);
				top = owner->makeValue(selected, routeContext->m_second,
					&key, 1, 1, 0);
			}
		}

	}
	top->addRef();
	for (int i = 1; i <= 2; ++i)
	{
		Rva8D0B00Value *value = owner->m_stack[owner->m_count - i];
		if (!((unsigned char)(value->m_flags >> 30) & 1))
			value->release();
	}
	owner->m_count -= 2;
	owner->finish(selected != 0 ? selected : context->m_first,
		top, number);
	top->release();
}
