// ?gen008CBDF0@@YAXPAX0H0@Z
// partial score=0.847 date=2026-09-28
// ?gen008CBDF0@@YAXPAEPADPAURva008CBDF0Movie@@PAH@Z
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x008CBDF0: Apt serialized-block pointer walker, 1757 bytes, cdecl
// (block, base, movie, serial); the caller at 0x008CC540 forwards (a,b,0,c).
// REWRITE (opus-5.5, 2026-09-28), complete semantics decoded from retail:
// tag byte switch 0x81..0xB8 through a 56-entry byte table into 12 case
// bodies; a null movie means un-relocate (subtract base, release values and
// replace them with serial numbers), otherwise relocate and build Apt values
// from the movie constant table (+0x1C, 8-byte {kind,value}): kind 1 via
// d_008C3C00 on the movie-relative text; 6/7/5 through the inlined pooled
// Float/Integer/Boolean creators (vtables 01136698/01136400/011360A8 over base
// 01135D68, pool heads 013387CC/D0/D4, idle registry 01337810); 8 and 4
// through the matched BfmeDerivedVNF/VN4 constructors; 3 the shared
// g_bfmeFallbackDB value. List cases 0x9B/0x8E stamp 0x98765432/0x12345678
// only when un-relocating. Idle step (d_008A30C0 on the registry) runs every
// 16 values and after every tag. Case bodies are in retail's layout order and
// the align+4 case falls through into the +4 case.
// Measured: code ret at +0x6D8 vs retail +0x6DC; 1487 non-reloc diffs; shape
// 0.847 (prior bank 764B, shape 0.224). Residue: cursor EBX / array EBP where
// retail has cursor EBP / array EBX; the array case's un-relocate block sits
// before the relocate block (retail places it after the kind==1 arm);
// 0x12345678 kept in EBP.
struct AptPoolNode
{
	void *m_vtable;
	unsigned int m_flags;
	union
	{
		AptPoolNode *m_next;
		int m_int;
		float m_float;
		bool m_bool;
	};
};

class BfmeG1211
{
public:
	void bfmeStep1211C();
};

struct Rva00899560Pool
{
	int m_capacity;
	int m_count;
	AptPoolNode **m_items;
	__forceinline void addPooled(AptPoolNode *node)
	{
		int &count = m_count;
		if (count >= m_capacity)
		{
			node->m_flags &= 0xbfffffff;
		}
		else
		{
			m_items[count] = node;
			count++;
		}
	}
	__forceinline void step() { ((BfmeG1211 *)this)->bfmeStep1211C(); }
};

extern Rva00899560Pool *g_rva8CD130IdleHook;
extern void *(*Rva008C5D70Alloc)(unsigned int bytes);
extern AptPoolNode *Rva008D2950Head;
extern AptPoolNode *Rva008D29C0Head;
extern AptPoolNode *Rva008D2A30Head;

class AptValue
{
public:
	virtual void vslot00();
	virtual void release();
	unsigned int m_flags;
	__forceinline int type() const { return m_flags & 0x3f; }
};

extern AptValue *g_bfmeFallbackDB;

struct BfmeNode3AF0;
void bfmeUnlink3AF0(BfmeNode3AF0 *node);
extern void d_008c3c00();

class BfmeDerivedVNF
{
public:
	BfmeDerivedVNF(int value);
};

class BfmeDerivedVN4
{
public:
	BfmeDerivedVN4(int value);
};

static __forceinline AptValue *createFloat(float value)
{
	AptPoolNode *object = Rva008D2950Head;
	if (object != 0)
	{
		Rva008D2950Head = object->m_next;
		g_rva8CD130IdleHook->addPooled(object);
		object->m_float = value;
		return (AptValue *)object;
	}
	object = (AptPoolNode *)Rva008C5D70Alloc(12);
	if (object != 0)
	{
		object->m_vtable = (void *)0x01135D68;
		object->m_flags = (object->m_flags & 0xf0008006) | 0x40008006;
		g_rva8CD130IdleHook->addPooled(object);
		object->m_vtable = (void *)0x01136698;
		object->m_float = value;
		return (AptValue *)object;
	}
	return 0;
}

static __forceinline AptValue *createInteger(int value)
{
	AptPoolNode *object = Rva008D29C0Head;
	if (object != 0)
	{
		Rva008D29C0Head = object->m_next;
		g_rva8CD130IdleHook->addPooled(object);
		object->m_int = value;
		return (AptValue *)object;
	}
	object = (AptPoolNode *)Rva008C5D70Alloc(12);
	if (object != 0)
	{
		object->m_vtable = (void *)0x01135D68;
		object->m_flags = (object->m_flags & 0xf0008007) | 0x40008007;
		g_rva8CD130IdleHook->addPooled(object);
		object->m_vtable = (void *)0x01136400;
		object->m_int = value;
		return (AptValue *)object;
	}
	return 0;
}

static __forceinline AptValue *createBoolean(bool value)
{
	AptPoolNode *object = Rva008D2A30Head;
	if (object != 0)
	{
		Rva008D2A30Head = object->m_next;
		g_rva8CD130IdleHook->addPooled(object);
		object->m_bool = value;
		return (AptValue *)object;
	}
	object = (AptPoolNode *)Rva008C5D70Alloc(12);
	if (object != 0)
	{
		object->m_vtable = (void *)0x01135D68;
		object->m_flags = (object->m_flags & 0xf0008005) | 0x40008005;
		g_rva8CD130IdleHook->addPooled(object);
		object->m_vtable = (void *)0x011360A8;
		object->m_bool = value;
		return (AptValue *)object;
	}
	return 0;
}

inline void *operator new(unsigned int, void *place) { return place; }

struct Rva008CBDF0Constant
{
	int kind;
	union
	{
		int intValue;
		float floatValue;
		char *text;
	};
};

struct Rva008CBDF0Movie
{
	char pad00[0x1c];
	Rva008CBDF0Constant *constants;
};

struct Rva008CBDF0Array
{
	int count;
	AptValue **items;
};

struct Rva008CBDF0PointerPair
{
	char *first;
	char *second;
};

struct Rva008CBDF0List
{
	char *owner;
	int count;
	char **items;
	int pad0c;
	int marker10;
	int marker14;
};

struct Rva008CBDF0PairEntry
{
	int key;
	char *value;
};

struct Rva008CBDF0PairList
{
	char *owner;
	int count;
	int pad08;
	Rva008CBDF0PairEntry *items;
	int pad10;
	int marker14;
	int marker18;
};

struct Rva008CBDF0Flagged
{
	int pad00[3];
	unsigned char flags;
	char pad0d[3];
	char *pointer;
};

static __forceinline unsigned char *align4(unsigned char *cursor)
{
	return (unsigned char *)(((unsigned int)cursor + 3) & ~3u);
}

void __cdecl gen008CBDF0(unsigned char *block, char *base, Rva008CBDF0Movie *movie, int *serial)
{
	int unrelocate = movie == 0;
	g_rva8CD130IdleHook->step();
	int tag = *block;
	unsigned char *cursor = block + 1;
	if (tag == 0)
		return;
	do
	{
		switch (tag)
		{
		case 0xa2: case 0xae: case 0xaf: case 0xb0: case 0xb1: case 0xb2: case 0xb3: case 0xb5:
			cursor += 1;
			break;
		case 0xa3: case 0xb6:
			cursor += 2;
			break;
		case 0x88: case 0x96:
		{
			cursor = align4(cursor);
			Rva008CBDF0Array *array = (Rva008CBDF0Array *)cursor;
			cursor += sizeof(Rva008CBDF0Array);
			if (unrelocate)
			{
				for (int i = 0; i < array->count; ++i)
				{
					AptValue *value = array->items[i];
					unsigned int flags = value->m_flags;
					int kind = flags & 0x3f;
					if ((kind == 1 || kind == 0x2a) && !(~(flags >> 15) & 1))
					{
						bfmeUnlink3AF0(kind == 1 ? (BfmeNode3AF0 *)value : *(BfmeNode3AF0 **)((char *)value + 0x20));
					}
					else
					{
						value->release();
					}
					array->items[i] = (AptValue *)*serial;
					++*serial;
					if (i % 16 == 0)
						g_rva8CD130IdleHook->step();
				}
				if (array->items)
					array->items = (AptValue **)((char *)array->items - (unsigned int)base);
			}
			else
			{
				if (array->items)
					array->items = (AptValue **)((char *)array->items + (unsigned int)base);
				for (int i = 0; i < array->count; ++i)
				{
					int index = (int)array->items[i];
					++*serial;
					Rva008CBDF0Constant *constant = &movie->constants[index];
					AptValue *value = 0;
					if (constant->kind == 1)
					{
						if (movie->constants[index].text)
							movie->constants[index].text += (unsigned int)movie;
						value = ((AptValue *(__cdecl *)(char *))d_008c3c00)(movie->constants[index].text);
						if (movie->constants[index].text)
							movie->constants[index].text -= (unsigned int)movie;
					}
					else if (constant->kind == 6)
						value = createFloat(constant->floatValue);
					else if (constant->kind == 7)
						value = createInteger(constant->intValue);
					else if (constant->kind == 8)
						{ void *raw = Rva008C5D70Alloc(12); value = raw ? (AptValue *)new (raw) BfmeDerivedVNF(movie->constants[index].intValue) : 0; }
					else if (constant->kind == 5)
						value = createBoolean(constant->intValue != 0);
					else if (constant->kind == 4)
						{ void *raw = Rva008C5D70Alloc(12); value = raw ? (AptValue *)new (raw) BfmeDerivedVN4(movie->constants[index].intValue) : 0; }
					else if (constant->kind == 3)
						value = g_bfmeFallbackDB;
					array->items[i] = value;
					unsigned int flags = value->m_flags;
					int kind = flags & 0x3f;
					if (!((kind == 1 || kind == 0x2a) && !(~(flags >> 15) & 1)))
						value->vslot00();
					if (i % 16 == 0)
						g_rva8CD130IdleHook->step();
				}
			}
			break;
		}
		case 0x83:
		{
			cursor = align4(cursor);
			Rva008CBDF0PointerPair *pair = (Rva008CBDF0PointerPair *)cursor;
			cursor += sizeof(Rva008CBDF0PointerPair);
			if (unrelocate)
			{
				if (pair->first) pair->first -= (unsigned int)base;
				if (pair->second) pair->second -= (unsigned int)base;
			}
			else
			{
				if (pair->first) pair->first += (unsigned int)base;
				if (pair->second) pair->second += (unsigned int)base;
			}
			break;
		}
		case 0x8b: case 0x8c: case 0xa1: case 0xa4: case 0xa5: case 0xa6: case 0xa7:
		{
			cursor = align4(cursor);
			char **pointer = (char **)cursor;
			cursor += sizeof(char *);
			if (unrelocate)
			{
				if (*pointer) *pointer -= (unsigned int)base;
			}
			else
			{
				if (*pointer) *pointer += (unsigned int)base;
			}
			break;
		}
		case 0x9b:
		{
			cursor = align4(cursor);
			Rva008CBDF0List *list = (Rva008CBDF0List *)cursor;
			cursor += sizeof(Rva008CBDF0List);
			if (unrelocate)
			{
				if (list->owner) list->owner -= (unsigned int)base;
			}
			else
			{
				if (list->owner) list->owner += (unsigned int)base;
				if (list->items) list->items = (char **)((char *)list->items + (unsigned int)base);
			}
			for (int i = 0; i < list->count; ++i)
			{
				if (unrelocate)
				{
					if (list->items[i]) list->items[i] -= (unsigned int)base;
				}
				else
				{
					if (list->items[i]) list->items[i] += (unsigned int)base;
				}
			}
			if (unrelocate)
			{
				if (list->items) list->items = (char **)((char *)list->items - (unsigned int)base);
				list->marker10 = 0x98765432;
				list->marker14 = 0x12345678;
			}
			break;
		}
		case 0x81: case 0x87: case 0x99: case 0x9d: case 0x9f: case 0xb8:
			cursor = align4(cursor);
		case 0xb4: case 0xb7:
			cursor += 4;
			break;
		case 0x94:
		{
			cursor = align4(cursor);
			int *offset = (int *)cursor;
			cursor += sizeof(int);
			if (unrelocate)
				*offset -= (int)cursor;
			else
				*offset += (int)cursor;
			break;
		}
		case 0x8e:
		{
			cursor = align4(cursor);
			Rva008CBDF0PairList *list = (Rva008CBDF0PairList *)cursor;
			cursor += sizeof(Rva008CBDF0PairList);
			if (unrelocate)
			{
				if (list->owner) list->owner -= (unsigned int)base;
			}
			else
			{
				if (list->owner) list->owner += (unsigned int)base;
				if (list->items) list->items = (Rva008CBDF0PairEntry *)((char *)list->items + (unsigned int)base);
			}
			for (int i = 0; i < list->count; ++i)
			{
				if (unrelocate)
				{
					if (list->items[i].value) list->items[i].value -= (unsigned int)base;
				}
				else
				{
					if (list->items[i].value) list->items[i].value += (unsigned int)base;
				}
			}
			if (unrelocate)
			{
				if (list->items) list->items = (Rva008CBDF0PairEntry *)((char *)list->items - (unsigned int)base);
				list->marker14 = 0x98765432;
				list->marker18 = 0x12345678;
			}
			break;
		}
		case 0x8f:
		{
			cursor = align4(cursor);
			Rva008CBDF0Flagged *flagged = (Rva008CBDF0Flagged *)cursor;
			cursor += sizeof(Rva008CBDF0Flagged);
			if (!(flagged->flags & 4))
			{
				if (unrelocate)
				{
					if (flagged->pointer) flagged->pointer -= (unsigned int)base;
				}
				else
				{
					if (flagged->pointer) flagged->pointer += (unsigned int)base;
				}
			}
			break;
		}
		}
		g_rva8CD130IdleHook->step();
		tag = *cursor++;
	} while (tag != 0);
}
