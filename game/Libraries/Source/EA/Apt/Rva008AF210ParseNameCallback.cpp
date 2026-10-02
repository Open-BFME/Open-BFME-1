// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
struct Rva008AF210StringData
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
};
struct Rva008AF210StringPool
{
	void *m_unused;
	void (__cdecl *free)(void *);
};
// The shared empty EA string block at 0x012D5298 is defined once, as
// EAStringC::StringDataC, in game/GameEngine/Source/Common/Data/Rva012D5298.cpp;
// this TU keeps its own local view of the block and casts at each use.
class EAStringC
{
public:
	class StringDataC;
};
extern EAStringC::StringDataC g_rva012D5298Empty;
extern Rva008AF210StringPool *g_bfmeStringPool1284;
class Rva8CD130String
{
public:
	Rva8CD130String() : m_data((Rva008AF210StringData *)&g_rva012D5298Empty)
	{
		++((Rva008AF210StringData *)&g_rva012D5298Empty)->m_refCount;
	}
	~Rva8CD130String()
	{
		Rva008AF210StringData *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}
	Rva008AF210StringData *m_data;
};
class Rva8CD130Value
{
public:
	void getName(Rva8CD130String *name);
};
class AptValue;
class Rva008CF3C0String;
// The global stack object's defining spelling (no real header declares it);
// the parseAndAppend method keeps its own proven class spelling, so the
// method call goes through a cast, as in the sibling callbacks.
struct Rva008AE770Stack
{
	int m_count;
};
class Rva008CF3C0State
{
public:
	void parseAndAppend(void *owner, void *scope, Rva008CF3C0String *input);
};
extern Rva008AE770Stack Rva008AE770TheStack;
extern Rva8CD130Value **g_bfmeArr1233;
extern AptValue *g_bfmeFallbackDB;

AptValue *rva008AF210ParseNameCallback(void *owner, int argc)
{
	if (argc > 0)
	{
		Rva8CD130Value *value = g_bfmeArr1233[Rva008AE770TheStack.m_count - 1];
		Rva8CD130String name;
		value->getName(&name);
		((Rva008CF3C0State *)&Rva008AE770TheStack)->parseAndAppend(
			owner, 0, (Rva008CF3C0String *)&name);
	}
	return g_bfmeFallbackDB;
}
