// ?rva008A4960@Rva8CBB80Derived@@UAE_NPAXPAVRva8CBB80FieldString@@PAVRva8CD130Value@@@Z
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// The Rva8CBB80 constructors install vtable 0x011366E0.  Its slot 11 is this
// method, which copies a value name into the message or name field selected by
// the second argument.

extern "C" int __cdecl strcmp(const char *, const char *);
#pragma intrinsic(strcmp)

struct Rva8CBB80StringData
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
	char m_text[1];
};

struct Rva8CBB80StringPool
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern Rva8CBB80StringPool *g_bfmeStringPool1284;

class EAStringC
{
public:
	// 0x012D5298: the shared empty EA string block, defined once in
	// game/GameEngine/Source/Common/Data/Rva012D5298.cpp.  This TU keeps its
	// own Rva8CBB80StringData view of it and casts at the use.
	class StringDataC;

	EAStringC &Assign(const EAStringC &other);

	Rva8CBB80StringData *m_data;
};

extern EAStringC::StringDataC g_rva012D5298Empty;

class Rva8CBB80FieldString
{
public:
	Rva8CBB80StringData *m_data;
};

class Rva8CD130String
{
public:
	Rva8CD130String()
	{
		Rva8CBB80StringData *block = (Rva8CBB80StringData *)&g_rva012D5298Empty;
		++block->m_refCount;
		m_data = block;
	}
	~Rva8CD130String()
	{
		Rva8CBB80StringData *data = m_data;
		--data->m_refCount;
		if (data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	Rva8CBB80StringData *m_data;
};

class Rva8CD130Value
{
public:
	void getName(Rva8CD130String *name);
};

class Rva899F00Base
{
public:
	virtual ~Rva899F00Base();

private:
	char m_base[0x1c];
};

class Rva8CBB80Derived : public Rva899F00Base
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual bool rva008A4960(void *unused, Rva8CBB80FieldString *field,
		Rva8CD130Value *value);
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();

private:
	EAStringC m_message;
	EAStringC m_name;
};

bool Rva8CBB80Derived::rva008A4960(void *, Rva8CBB80FieldString *field,
	Rva8CD130Value *value)
{
	if (strcmp(field->m_data->m_text, "message") == 0)
	{
		Rva8CD130String name;
		value->getName(&name);
		m_message.Assign(reinterpret_cast<const EAStringC &>(name));
		return true;
	}

	if (strcmp(field->m_data->m_text, "name") == 0)
	{
		Rva8CD130String name;
		value->getName(&name);
		m_name.Assign(reinterpret_cast<const EAStringC &>(name));
		return true;
	}

	return false;
}
