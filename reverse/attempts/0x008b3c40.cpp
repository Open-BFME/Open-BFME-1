// ?bfmeFallback1015@Rva008B38D0@@QAEPAVRva8CD130Value@@PAV2@PAURva8CD130String@@@Z
// partial score=0.58 date=2026-09-23
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Rva008B38D0 vtable 0x00D36A40 slot 10: named-member lookup. Falls back to
// the Rva008B2EF0 slot 10 lookup first, then resolves the member name through
// the R4 perfect hash and builds the value for ids 100..112.

struct R4Word
{
	const char *name;
	int value;
};

const R4Word *Rva008D5DC0(const char *str, unsigned int len);

struct AptStringBlock
{
	unsigned short m_refs;
	unsigned short m_length;
	unsigned int m_reserved;
	char m_chars[4];
};

struct Rva8CD130String
{
	AptStringBlock *m_data;
};

class Rva8CD130Value
{
public:
	virtual void addRef();
	unsigned int m_flags;
};

struct Rva00899560Pool
{
	int m_capacity;
	int m_count;
	Rva8CD130Value **m_items;

	__forceinline void addPooled(Rva8CD130Value *value)
	{
		int &count = m_count;
		if (count >= m_capacity)
		{
			value->m_flags &= 0xbfffffff;
		}
		else
		{
			m_items[count] = value;
			count++;
		}
	}
};

extern Rva00899560Pool *g_rva8CD130IdleHook;
extern void *(*Rva008C5D70Alloc)(unsigned int bytes);
extern void (*Rva008C5D70Free)(void *block, unsigned int bytes);

class BfmeStrVKK
{
public:
	void bfmeTruncVKK(unsigned int length);
};

extern AptStringBlock g_bfmeDefaultString1284;

class Rva008B2EA0Node : public Rva8CD130Value
{
public:
	void *operator new(unsigned int bytes)
	{
		return Rva008C5D70Alloc(bytes);
	}

	void operator delete(void *block, unsigned int bytes)
	{
		Rva008C5D70Free(block, bytes);
	}

	Rva008B2EA0Node();
	void append(void *text);

	AptStringBlock *m_string;
	Rva008B2EA0Node *m_next;

	static Rva008B2EA0Node *create();
};

extern Rva008B2EA0Node *Rva008C3B60Head;

__forceinline Rva008B2EA0Node *Rva008B2EA0Node::create()
{
	Rva008B2EA0Node *node = Rva008C3B60Head;
	if (node)
	{
		Rva008C3B60Head = node->m_next;
		g_rva8CD130IdleHook->addPooled(node);
		if (node->m_string != &g_bfmeDefaultString1284)
			((BfmeStrVKK *)&node->m_string)->bfmeTruncVKK(0);
	}
	else
	{
		node = new Rva008B2EA0Node;
	}
	return node;
}

class AptBoolean : public Rva8CD130Value
{
public:
	union
	{
		AptBoolean *m_next;
		bool m_value;
	};

	static AptBoolean *create(bool value);
};

extern AptBoolean *Rva008D2A30Head;

__forceinline AptBoolean *AptBoolean::create(bool value)
{
	AptBoolean *object = Rva008D2A30Head;
	if (object != 0)
	{
		Rva008D2A30Head = object->m_next;
		g_rva8CD130IdleHook->addPooled(object);
		object->m_value = value;
		return object;
	}
	object = (AptBoolean *)Rva008C5D70Alloc(12);
	if (object != 0)
	{
		*(void **)object = (void *)0x01135D68;
		object->m_flags = (object->m_flags & 0xf0008005) | 0x40008005;
		g_rva8CD130IdleHook->addPooled(object);
		*(void **)object = (void *)0x011360A8;
		object->m_value = value;
		return object;
	}
	return 0;
}

class AptInteger : public Rva8CD130Value
{
public:
	union
	{
		AptInteger *m_next;
		int m_value;
	};

	static AptInteger *create(int value);
};

extern AptInteger *Rva008D29C0Head;

__forceinline AptInteger *AptInteger::create(int value)
{
	AptInteger *object = Rva008D29C0Head;
	if (object != 0)
	{
		Rva008D29C0Head = object->m_next;
		g_rva8CD130IdleHook->addPooled(object);
		object->m_value = value;
		return object;
	}
	object = (AptInteger *)Rva008C5D70Alloc(12);
	if (object != 0)
	{
		*(void **)object = (void *)0x01135D68;
		object->m_flags = (object->m_flags & 0xf0008007) | 0x40008007;
		g_rva8CD130IdleHook->addPooled(object);
		*(void **)object = (void *)0x01136400;
		object->m_value = value;
		return object;
	}
	return 0;
}

void *Rva00897640(unsigned int bytes);
void Rva00897670(void *block, unsigned int bytes);

class BfmeA1029 : public Rva8CD130Value
{
public:
	void *operator new(unsigned int bytes)
	{
		return Rva00897640(bytes);
	}

	void operator delete(void *block, unsigned int bytes)
	{
		Rva00897670(block, bytes);
	}

	BfmeA1029(int callback);

	char m_pad[0x18];
	int m_callback;
};

extern BfmeA1029 *g_bfmeS1082_0;
extern BfmeA1029 *g_bfmeS1082_1;
extern BfmeA1029 *g_bfmeS1082_2;
extern BfmeA1029 *g_bfmeS1082_3;

int Rva008B3A40(int);
int Rva008B3A70(int);
int Rva008B3AA0(int);
int Rva008B3B70(int);

class Rva008B38D0Target
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21();
	virtual void *rva58();
	virtual void v23(); virtual void v24(); virtual void v25();
	virtual void *rva68();
	virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30();
	virtual int rva7C();
	virtual void v32();
	virtual int rva84();
	virtual void v34(); virtual void v35(); virtual void v36();
	virtual int rva94();
};

extern AptStringBlock *g_rva01338608;

class Rva008B2EF0
{
public:
	Rva8CD130Value *bfmeFallback1015(Rva8CD130Value *context, Rva8CD130String *name);

	void *m_vtable;
	unsigned int m_flags;
	char m_pad08[0x18];
	Rva008B38D0Target *m_target;
	unsigned int m_value24;
};

class Rva008B38D0 : public Rva008B2EF0
{
public:
	Rva8CD130Value *bfmeFallback1015(Rva8CD130Value *context, Rva8CD130String *name);
};

Rva8CD130Value *Rva008B38D0::bfmeFallback1015(Rva8CD130Value *context, Rva8CD130String *name)
{
	context->m_flags = (context->m_flags & ~0x3f) | 0x20;
	Rva8CD130Value *found = Rva008B2EF0::bfmeFallback1015(context, name);
	context->m_flags = (context->m_flags & ~0x3f) | 0x21;
	if (found != 0 && (found->m_flags & 0x8000))
		return found;

	const R4Word *word = Rva008D5DC0(name->m_data->m_chars, name->m_data->m_length);
	if (word == 0)
		return 0;

	Rva008B38D0Target *target = m_target;
	switch (word->value)
	{
	case 100:
	{
		Rva008B2EA0Node *text = Rva008B2EA0Node::create();
		text->append(g_rva01338608->m_chars);
		if (m_target)
		{
			void *extra = target->rva58();
			if (extra)
				text->append(extra);
		}
		return text;
	}
	case 103:
	{
		Rva008B2EA0Node *text = Rva008B2EA0Node::create();
		text->append(g_rva01338608->m_chars);
		if (m_target)
		{
			void *extra = target->rva68();
			if (extra)
				text->append(extra);
		}
		return text;
	}
	case 104:
		if (g_bfmeS1082_0 == 0)
		{
			g_bfmeS1082_0 = new BfmeA1029((int)Rva008B3A40);
			g_bfmeS1082_0->m_flags = (g_bfmeS1082_0->m_flags & 0xffffc03f) | 0x40;
			g_bfmeS1082_0->addRef();
		}
		return g_bfmeS1082_0;
	case 105:
		if (g_bfmeS1082_1 == 0)
		{
			g_bfmeS1082_1 = new BfmeA1029((int)Rva008B3A70);
			g_bfmeS1082_1->m_flags = (g_bfmeS1082_1->m_flags & 0xffffc03f) | 0x40;
			g_bfmeS1082_1->addRef();
		}
		return g_bfmeS1082_1;
	case 106:
		return AptBoolean::create(target->rva7C() != 0);
	case 107:
		if (g_bfmeS1082_2 == 0)
		{
			g_bfmeS1082_2 = new BfmeA1029((int)Rva008B3AA0);
			g_bfmeS1082_2->m_flags = (g_bfmeS1082_2->m_flags & 0xffffc03f) | 0x40;
			g_bfmeS1082_2->addRef();
		}
		return g_bfmeS1082_2;
	case 108:
		return AptBoolean::create(target->rva84() != 0);
	case 109:
		if (g_bfmeS1082_3 == 0)
		{
			g_bfmeS1082_3 = new BfmeA1029((int)Rva008B3B70);
			g_bfmeS1082_3->m_flags = (g_bfmeS1082_3->m_flags & 0xffffc03f) | 0x40;
			g_bfmeS1082_3->addRef();
		}
		return g_bfmeS1082_3;
	case 112:
		return AptInteger::create(target->rva94());
	}
	return 0;
}
