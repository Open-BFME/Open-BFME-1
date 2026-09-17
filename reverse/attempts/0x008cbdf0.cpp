// ?gen008CBDF0@@YAXPAX0H0@Z
// partial score=0.3 date=2026-09-17
// ?gen008CBDF0@@YAXPAX0H0@Z
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x008CBDF0 is the Apt serialized-record walker.  The caller at
// 0x008CC540 proves the four-argument cdecl ABI and passes a null third
// argument.  The record dispatch bytes, the 0x01337828 allocator, the Apt
// free-list heads, and the two registry constructors are all read directly
// from the retail body.  The routine keeps its address-derived name because
// no evidence proves a source class or method name for the whole walker.

struct Rva00899560Value
{
	void *m_vtable;
	unsigned int m_flags;
	unsigned int m_payload;
};

struct Rva00899560Pool
{
	int m_capacity;
	int m_count;
	Rva00899560Value **m_items;
};

struct Rva008D2950Node
{
	void *m_vtable;
	unsigned int m_flags;
	Rva008D2950Node *m_next;
};

struct Rva008D29C0Node
{
	void *m_vtable;
	unsigned int m_flags;
	Rva008D29C0Node *m_next;
};

struct Rva008D2A30Node
{
	void *m_vtable;
	unsigned int m_flags;
	Rva008D2A30Node *m_next;
};

struct AptValue
{
	virtual void slot0();
	virtual void release();
	unsigned int m_flags;
};

struct BfmeNode3AF0
{
	unsigned char m_bytes[4];
};

struct BfmeDerivedVNF
{
	BfmeDerivedVNF(int value);
};

struct BfmeDerivedVN4
{
	BfmeDerivedVN4(int value);
};

struct Rva008CBDF0Array
{
	int m_count;
	unsigned int *m_items;
};

struct Rva008CBDF0Pair
{
	int m_kind;
	int m_value;
};

struct Rva008CBDF0Table
{
	unsigned char m_gap[0x1c];
	Rva008CBDF0Pair *m_pairs;
};

extern Rva00899560Pool *g_rva8CD130IdleHook;
extern void *(*Rva008C5D70Alloc)(unsigned int bytes);
extern Rva008D2950Node *Rva008D2950Head;
extern Rva008D29C0Node *Rva008D29C0Head;
extern Rva008D2A30Node *Rva008D2A30Head;
extern AptValue *g_bfmeFallbackDB;

extern void d_008a30c0();
extern void d_008c3c00();
extern void bfmeUnlink3AF0(BfmeNode3AF0 *node);

inline void *operator new(unsigned int, void *place)
{
	return place;
}

static __forceinline void idleStep(Rva00899560Pool *pool)
{
	// MSVC 7.1 spells the ECX-only member call through __fastcall.
	typedef void (__fastcall *Call)(Rva00899560Pool *);
	(reinterpret_cast<Call>(d_008a30c0))(pool);
}

static __forceinline void addToIdlePool(Rva00899560Value *value)
{
	Rva00899560Pool *pool = g_rva8CD130IdleHook;
	int index = pool->m_count;
	if (index >= pool->m_capacity)
	{
		value->m_flags &= 0xbfffffff;
	}
	else
	{
		pool->m_items[index] = value;
		pool->m_count = index + 1;
	}
}

static __forceinline unsigned char *align4(unsigned char *cursor)
{
	return reinterpret_cast<unsigned char *>(
		(reinterpret_cast<unsigned int>(cursor) + 3) & ~3u);
}

static __forceinline bool valueIsDefined(unsigned int flags)
{
	return ((flags >> 15) & 1) != 0;
}

static __forceinline void adjustWord(unsigned int *word, unsigned int delta,
	bool subtract)
{
	if (*word != 0)
		*word = subtract ? *word - delta : *word + delta;
}

static __forceinline Rva00899560Value *makeFloat(int value)
{
	Rva008D2950Node *node = Rva008D2950Head;
	if (node != 0)
	{
		Rva008D2950Head = node->m_next;
		addToIdlePool(reinterpret_cast<Rva00899560Value *>(node));
		reinterpret_cast<Rva00899560Value *>(node)->m_payload =
			static_cast<unsigned int>(value);
		return reinterpret_cast<Rva00899560Value *>(node);
	}

	Rva00899560Value *object = reinterpret_cast<Rva00899560Value *>(
		Rva008C5D70Alloc(12));
	if (object == 0)
		return 0;
	object->m_vtable = reinterpret_cast<void *>(0x01135d68);
	object->m_flags = (object->m_flags & 0xf0008006) | 0x40008006;
	addToIdlePool(object);
	object->m_vtable = reinterpret_cast<void *>(0x01136698);
	object->m_payload = static_cast<unsigned int>(value);
	return object;
}

static __forceinline Rva00899560Value *makeInteger(int value)
{
	Rva008D29C0Node *node = Rva008D29C0Head;
	if (node != 0)
	{
		Rva008D29C0Head = node->m_next;
		addToIdlePool(reinterpret_cast<Rva00899560Value *>(node));
		reinterpret_cast<Rva00899560Value *>(node)->m_payload =
			static_cast<unsigned int>(value);
		return reinterpret_cast<Rva00899560Value *>(node);
	}

	Rva00899560Value *object = reinterpret_cast<Rva00899560Value *>(
		Rva008C5D70Alloc(12));
	if (object == 0)
		return 0;
	object->m_vtable = reinterpret_cast<void *>(0x01135d68);
	object->m_flags = (object->m_flags & 0xf0008007) | 0x40008007;
	addToIdlePool(object);
	object->m_vtable = reinterpret_cast<void *>(0x01136400);
	object->m_payload = static_cast<unsigned int>(value);
	return object;
}

static __forceinline Rva00899560Value *makeBoolean(bool value)
{
	Rva008D2A30Node *node = Rva008D2A30Head;
	if (node != 0)
	{
		Rva008D2A30Head = node->m_next;
		addToIdlePool(reinterpret_cast<Rva00899560Value *>(node));
		reinterpret_cast<Rva00899560Value *>(node)->m_payload = value ? 1 : 0;
		return reinterpret_cast<Rva00899560Value *>(node);
	}

	Rva00899560Value *object = reinterpret_cast<Rva00899560Value *>(
		Rva008C5D70Alloc(12));
	if (object == 0)
		return 0;
	object->m_vtable = reinterpret_cast<void *>(0x01135d68);
	object->m_flags = (object->m_flags & 0xf0008005) | 0x40008005;
	addToIdlePool(object);
	object->m_vtable = reinterpret_cast<void *>(0x011360a8);
	object->m_payload = value ? 1 : 0;
	return object;
}

static __forceinline Rva00899560Value *makeFromPair(int kind, int value)
{
	switch (kind)
	{
	case 6:
		return makeFloat(value);
	case 7:
		return makeInteger(value);
	case 5:
		return makeBoolean(value != 0);
	case 8:
	{
		void *raw = Rva008C5D70Alloc(12);
		return raw == 0 ? 0 : reinterpret_cast<Rva00899560Value *>(
			new (raw) BfmeDerivedVNF(value));
	}
	case 4:
	{
		void *raw = Rva008C5D70Alloc(12);
		return raw == 0 ? 0 : reinterpret_cast<Rva00899560Value *>(
			new (raw) BfmeDerivedVN4(value));
	}
	case 3:
		return reinterpret_cast<Rva00899560Value *>(g_bfmeFallbackDB);
	default:
		return 0;
	}
}

static __forceinline void callC3C00(unsigned int value)
{
	typedef void (__cdecl *Call)(unsigned int);
	(reinterpret_cast<Call>(d_008c3c00))(value);
}

static void cleanSerializedValues(Rva008CBDF0Array *array, unsigned int *state)
{
	int count = array->m_count;
	for (int index = 0; index < count; ++index)
	{
		AptValue *value = reinterpret_cast<AptValue *>(array->m_items[index]);
		unsigned int flags = value->m_flags;
		unsigned int kind = flags & 0x3f;

		if (kind == 42 && valueIsDefined(flags))
		{
			BfmeNode3AF0 *node = reinterpret_cast<BfmeNode3AF0 *>(
				*reinterpret_cast<unsigned int *>(
					reinterpret_cast<unsigned char *>(value) + 0x20));
			bfmeUnlink3AF0(node);
		}
		else
		{
			value->release();
		}

		array->m_items[index] = *state;
		++*state;
		if ((index & 0x8000000f) == 0)
			idleStep(g_rva8CD130IdleHook);
	}
}

static void processModeTable(Rva008CBDF0Array *array, unsigned int *base,
	int mode, unsigned int *state)
{
	Rva008CBDF0Table *table = reinterpret_cast<Rva008CBDF0Table *>(
		static_cast<unsigned int>(mode));
	if (array->m_items != 0)
		array->m_items = reinterpret_cast<unsigned int *>(
			reinterpret_cast<unsigned int>(array->m_items) +
			reinterpret_cast<unsigned int>(base));

	for (int index = 0; index < array->m_count; ++index)
	{
		unsigned int slot = array->m_items[index];
		Rva008CBDF0Pair *pair = table->m_pairs + slot;
		++*state;
		if (pair->m_kind == 1 && pair->m_value != 0)
		{
			unsigned int *pointer = reinterpret_cast<unsigned int *>(
				reinterpret_cast<unsigned char *>(pair) + 4);
			*pointer += reinterpret_cast<unsigned int>(table);
			callC3C00(*pointer);
			*pointer -= reinterpret_cast<unsigned int>(table);
		}
		else
		{
			Rva00899560Value *value = makeFromPair(pair->m_kind, pair->m_value);
			if (value != 0)
				array->m_items[index] = reinterpret_cast<unsigned int>(value);
		}
	}
}

void __cdecl gen008CBDF0(void *serialized, void *base, int mode, void *state)
{
	int modeIsNull = mode == 0;
	idleStep(g_rva8CD130IdleHook);

	unsigned char *cursor = reinterpret_cast<unsigned char *>(serialized);
	unsigned int record = *cursor++;
	if (record == 0)
		return;

	for (;;)
	{
		unsigned int code = record - 0x81;
		switch (code)
		{
		case 0:
		case 6:
		case 24:
		case 28:
		case 30:
		case 55:
			cursor = align4(cursor + 3);
			cursor += 4;
			break;

		case 2:
		{
			cursor = align4(cursor + 3);
			Rva008CBDF0Array *array = reinterpret_cast<Rva008CBDF0Array *>(cursor);
			cursor += 8;
			if (array->m_items != 0 && modeIsNull)
			{
				cleanSerializedValues(array,
					reinterpret_cast<unsigned int *>(state));
			}
			else if (array->m_items != 0)
			{
				processModeTable(array, reinterpret_cast<unsigned int *>(base),
					mode, reinterpret_cast<unsigned int *>(state));
			}
		if (array->m_items != 0)
			array->m_items = reinterpret_cast<unsigned int *>(
				reinterpret_cast<unsigned int>(array->m_items) +
				(modeIsNull ? -reinterpret_cast<unsigned int>(base)
					: reinterpret_cast<unsigned int>(base)));
			break;
		}

		case 10:
		case 11:
		case 32:
		case 35:
		case 36:
		case 37:
		case 38:
			cursor = align4(cursor + 3);
			adjustWord(reinterpret_cast<unsigned int *>(cursor),
				reinterpret_cast<unsigned int>(base), modeIsNull);
			cursor += 4;
			break;

		case 13:
			cursor = align4(cursor + 3);
		{
			unsigned int *object = reinterpret_cast<unsigned int *>(cursor);
			cursor += 0x1c;
			adjustWord(object, reinterpret_cast<unsigned int>(base), modeIsNull);
			adjustWord(object + 3, reinterpret_cast<unsigned int>(base), modeIsNull);
			if (object[3] != 0)
			{
				unsigned int count = object[1];
				for (unsigned int index = 0; index < count; ++index)
					adjustWord(reinterpret_cast<unsigned int *>(object[3]) + index * 2,
						reinterpret_cast<unsigned int>(base), modeIsNull);
			}
		}
			break;

		case 19:
			cursor = align4(cursor + 3);
		{
			unsigned int *object = reinterpret_cast<unsigned int *>(cursor);
			cursor += 4;
			adjustWord(object, reinterpret_cast<unsigned int>(cursor), modeIsNull);
		}
			break;

		case 26:
			cursor = align4(cursor + 3);
		{
			unsigned int *object = reinterpret_cast<unsigned int *>(cursor);
			cursor += 0x18;
			adjustWord(object, reinterpret_cast<unsigned int>(base), modeIsNull);
			adjustWord(object + 2, reinterpret_cast<unsigned int>(base), modeIsNull);
			if (object[2] != 0)
			{
				unsigned int count = object[1];
				for (unsigned int index = 0; index < count; ++index)
					adjustWord(reinterpret_cast<unsigned int *>(object[2]) + index,
						reinterpret_cast<unsigned int>(base), modeIsNull);
			}
		}
			break;

		case 14:
			cursor = align4(cursor + 3);
		{
			unsigned char *object = cursor;
			unsigned char flags = object[0x0c];
			cursor += 0x14;
			if ((flags & 4) == 0)
				adjustWord(reinterpret_cast<unsigned int *>(object + 0x10),
					reinterpret_cast<unsigned int>(base), modeIsNull);
		}
			break;

		case 33:
		case 45:
		case 46:
		case 47:
		case 48:
		case 49:
		case 50:
		case 52:
			++cursor;
			break;

		case 34:
		case 53:
			cursor += 2;
			break;

		case 51:
		case 54:
			cursor += 4;
			break;

		case 7:
		case 21:
		{
			cursor = align4(cursor + 3);
			Rva008CBDF0Array *array = reinterpret_cast<Rva008CBDF0Array *>(cursor);
			cursor += 8;
			if (modeIsNull)
			{
				cleanSerializedValues(array,
					reinterpret_cast<unsigned int *>(state));
			}
			else
			{
				processModeTable(array, reinterpret_cast<unsigned int *>(base),
					mode, reinterpret_cast<unsigned int *>(state));
			}
			break;
		}

		default:
			idleStep(g_rva8CD130IdleHook);
			break;
		}

		idleStep(g_rva8CD130IdleHook);
		record = *cursor++;
		if (record == 0)
			break;
	}
}
