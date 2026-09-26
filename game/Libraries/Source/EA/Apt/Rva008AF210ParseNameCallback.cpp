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
extern Rva008AF210StringData g_bfmeDefaultString1284;
extern Rva008AF210StringPool *g_bfmeStringPool1284;
class Rva8CD130String
{
public:
	Rva8CD130String() : m_data(&g_bfmeDefaultString1284)
	{
		++g_bfmeDefaultString1284.m_refCount;
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
class Rva008CF3C0State
{
public:
	int m_count;
	void parseAndAppend(void *owner, void *scope, Rva008CF3C0String *input);
};
extern Rva008CF3C0State Rva008AE770TheStack;
extern Rva8CD130Value **g_bfmeArr1233;
extern AptValue *g_bfmeFallbackDB;

AptValue *rva008AF210ParseNameCallback(void *owner, int argc)
{
	if (argc > 0)
	{
		Rva8CD130Value *value = g_bfmeArr1233[Rva008AE770TheStack.m_count - 1];
		Rva8CD130String name;
		value->getName(&name);
		Rva008AE770TheStack.parseAndAppend(owner, 0, (Rva008CF3C0String *)&name);
	}
	return g_bfmeFallbackDB;
}
