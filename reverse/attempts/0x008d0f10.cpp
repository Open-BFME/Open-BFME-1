// ?d_008d0f10@@YAXXZ
// partial score=0.34 date=2026-09-20
// ?run@Rva008D0F10@@SAXPAVRva008D0F10State@@PAURva008D0F10Context@@@Z
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x008D0F10 is shared by the 1212A, 1214A and 1216A entry points.
// Those callers prove the state/context pair, but do not prove a semantic
// owner for the body, so the owner remains address-derived here.

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
};

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

class BfmeStrVKI
{
public:
	BfmeStrVKI(const char *text)
	{
		bfmeSetVKI(text);
	}

	void __declspec(nothrow) bfmeSetVKI(const char *text);

	~BfmeStrVKI()
	{
		BfmeStringData3AF0 *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	BfmeStringData3AF0 *m_data;
};

class Rva8CD130String
{
public:
	Rva8CD130String()
	{
		m_data = &g_bfmeDefaultString1284;
		++m_data->m_refCount;
	}

	~Rva8CD130String()
	{
		BfmeStringData3AF0 *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	void assign(BfmeStringData3AF0 *data)
	{
		++data->m_refCount;
		BfmeStringData3AF0 *old = m_data;
		if (--old->m_refCount == 0)
			g_bfmeStringPool1284->free(old);
		m_data = data;
	}

	void assign(const BfmeStrVKI &text)
	{
		assign(text.m_data);
	}

	BfmeStringData3AF0 *m_data;
};

class Rva8CD130Value
{
public:
	virtual void addRef();
	virtual void release();
	void getName(Rva8CD130String *name);
};

class AptValue
{
public:
	int toInteger() const;
};

extern AptValue *g_bfmeFallbackDB;

int bfmeCompareVSC(const char *left, const char *right);

class Rva008D0F10Value
{
public:
	virtual void addRef();
	virtual void release();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual Rva008D0F10Value *slot18();
	virtual int slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual int slot4c();

	union
	{
		unsigned m_flags;
		struct
		{
			unsigned short m_lowFlags;
			unsigned short m_highFlags;
		};
	};
	void *m_link;
	unsigned char m_pad0c[0x0c];
	Rva008D0F10Value *m_field18;
	unsigned m_state1c;
	void *m_field20;
	int m_field24;
	int m_count28;
	unsigned char m_pad2c[0x20];
	Rva008D0F10Value *m_field4c;

	bool isUndefined() const
	{
		return ((m_flags >> 15) & 1) == 0;
	}

	bool maxRefCountHit() const
	{
		return ((m_flags >> 30) & 1) != 0;
	}

	unsigned type() const
	{
		return m_flags & 0x3f;
	}
};

class Rva008D0F10State
{
public:
	void invoke(void *first, void *second, int count);

	int m_count;
	int m_unused04;
	Rva008D0F10Value **m_stack;
	unsigned char m_gap0c[0x0c];
	int m_count18;
	int m_unused1c;
	Rva008D0F10Value **m_stack20;
	unsigned char m_gap24[0x0c];
	int m_count30;
	int m_unused34;
	Rva008D0F10Value **m_stack38;
};

struct Rva008D0F10Context
{
	void *m_unused00;
	void *m_value04;
	void *m_unused08;
	void *m_unused0c;
	void *m_field10;
};

class Rva008D0F10
{
public:
	static void run(Rva008D0F10State *state, Rva008D0F10Context *context);
};

// The generated ledger row at 0x008CF740 is an address-only placeholder. Its
// retail call contract is thiscall(state, first, second, count); keep the
// source declaration typed locally and route its decorated name to the live
// address-only body.
#pragma comment(linker, "/alternatename:?invoke@Rva008D0F10State@@QAEXPAX0H@Z=?d_008cf740@@YAXXZ")

class Rva00899770;
class Rva008AE770Stack
{
public:
	Rva00899770 *createString(void *value, int unused, BfmeStrVKI *name,
		int one, int another, int zero);
};

class Rva00899C20Node
{
public:
	int rva00899C20();
};

class BfmeA1232
{
public:
	void bfmePop1232(int count);
};

static Rva008D0F10Value *d0(AptValue *value)
{
	return reinterpret_cast<Rva008D0F10Value *>(value);
}

static AptValue *apt(Rva008D0F10Value *value)
{
	return reinterpret_cast<AptValue *>(value);
}

void Rva008D0F10::run(Rva008D0F10State *state,
	Rva008D0F10Context *context)
{
	Rva008D0F10Value *top = state->m_stack[state->m_count - 1];
	Rva008D0F10Value *under = state->m_stack[state->m_count - 3];
	Rva008D0F10Value *current = state->m_stack[state->m_count - 2];
	Rva8CD130String name;
	Rva008D0F10Value *result;
	Rva008D0F10Value *value;
	int count;
	bool cleanSecondary;
	bool releaseCurrent;

	result = 0;
	cleanSecondary = false;
	releaseCurrent = false;

	if (top == d0(g_bfmeFallbackDB))
	{
		BfmeStrVKI text((const char *)0x01135e30);
		name.assign(text);
	}
	else
	{
		reinterpret_cast<Rva8CD130Value *>(top)->getName(&name);
	}

	count = apt(under)->toInteger();
	if (current->isUndefined())
		goto invoke_result;

	state->m_stack38[state->m_count30] =
		reinterpret_cast<Rva008D0F10Value *>(context->m_value04);
	++state->m_count30;
	state->m_stack38[state->m_count30 - 1]->addRef();

	value = state->m_stack[state->m_count - 1];
	if (!value->maxRefCountHit())
		value->release();
	--state->m_count;
	value = state->m_stack[state->m_count - 1];
	if (!value->maxRefCountHit())
		value->release();
	--state->m_count;
	value = state->m_stack[state->m_count - 1];
	if (!value->maxRefCountHit())
		value->release();
	--state->m_count;

	if (current->type() == 0x1c && !current->isUndefined())
		result = current->m_field18;
	else
		result = current;

	if (result == 0 || result == d0(g_bfmeFallbackDB))
	{
		result = reinterpret_cast<Rva008D0F10Value *>(
			reinterpret_cast<Rva008AE770Stack *>(state)->createString(
				current, 0, reinterpret_cast<BfmeStrVKI *>(&name), 1, 1, 0));
	}

	if (result != 0 && !result->isUndefined())
		goto dispatch_result;

	if (bfmeCompareVSC((const char *)name.m_data + 8,
		(const char *)0x01137314) != 0
		&& bfmeCompareVSC((const char *)name.m_data + 8,
		(const char *)0x0113730c) != 0)
		goto dispatch_result;

	result = current;
	if (current->type() == 7)
	{
		if (!current->isUndefined())
			goto after_arguments;
	}
	if (current->type() == 6 && !current->isUndefined())
		goto after_arguments;

	count = apt(state->m_stack[state->m_count - 1])->toInteger();
	if (count > 1)
	{
		value = state->m_stack[state->m_count - 2];
		if (value != 0 && !value->isUndefined())
			current = value;

		value = state->m_stack[state->m_count - 1];
		if (!value->maxRefCountHit())
			value->release();
		--state->m_count;
		--count;

		value = state->m_stack[state->m_count - 1];
		if (!value->maxRefCountHit())
			value->release();
		--state->m_count;
	}

after_arguments:
	if (count > 0)
	{
		while (count > 0)
		{
			value = state->m_stack[state->m_count - 1];
			if (value->isUndefined())
				current = d0(g_bfmeFallbackDB);
			else
				current = value;
			if (!value->maxRefCountHit())
				value->release();
			--state->m_count;
			--count;
		}
	}
	else
	{
		current = d0(g_bfmeFallbackDB);
	}

	if (bfmeCompareVSC((const char *)name.m_data + 8,
		(const char *)0x01137314) != 0)
		goto dispatch_result;

	if (state->m_count > 0 &&
		state->m_stack[state->m_count - 1] != d0(g_bfmeFallbackDB))
	{
		Rva008D0F10Value *last = state->m_stack[state->m_count - 1];
		if (last->type() == 0x16 && !last->isUndefined())
		{
			if (!last->maxRefCountHit())
				last->release();
			--state->m_count;
			int i = last->m_count28 - 1;
			if (i >= 0)
			{
				do
				{
					Rva008D0F10Value *item =
						reinterpret_cast<Rva008D0F10Value *>(
							((unsigned int)(reinterpret_cast<Rva008D0F10Value **>(
								last->m_field20))[i]) & ~1u);
					state->m_stack[state->m_count] = item;
					++state->m_count;
					if (!item->maxRefCountHit())
						item->addRef();
					--i;
				} while (i >= 0);
			}
		}
	}

dispatch_result:
	if (current->slot1c() != 0)
	{
		if (state->m_count18 == 0 &&
			current == reinterpret_cast<Rva008D0F10Value *>(context->m_field10))
		{
			BfmeStrVKI text((const char *)0x01132714);
			result = reinterpret_cast<Rva008D0F10Value *>(
				reinterpret_cast<Rva008AE770Stack *>(state)->createString(
					context->m_value04, 0, &text, 1, 1, 0));
		}
		else if (state->m_count18 != 0)
		{
			Rva008D0F10Value *cursor =
				state->m_stack20[state->m_count18 - 1];
			unsigned kind = current->type();
			if (kind >= 0x0c && kind <= 0x13 && !current->isUndefined()
				&& cursor != current->m_field4c && cursor != current)
			{
				Rva008D0F10Value *owner = cursor->slot18();
				while (owner != 0)
				{
					owner = reinterpret_cast<Rva008D0F10Value *>(
						((unsigned int)owner->m_link) & ~1u);
					if (owner == 0 || owner == current)
						break;
					owner = owner->slot18();
				}
			}
		}

		cleanSecondary = true;
		if (result->type() == 0x1b && !result->isUndefined())
		{
			result->m_state1c |= 0x200;
			state->m_stack20[state->m_count18] = result;
			++state->m_count18;
			result->addRef();
		}
	}

	if ((current->m_highFlags & 0x0fff) == 1)
	{
		current->addRef();
		releaseCurrent = true;
	}

	invoke_result:
	if (reinterpret_cast<Rva00899C20Node *>(current)->rva00899C20() != 0)
	{
		Rva008D0F10Value *pending =
			state->m_stack38[state->m_count30 - 2];
		current = pending;
		if (pending == reinterpret_cast<Rva008D0F10Value *>(context->m_field10)
			&& result->type() == 0x0a && !result->isUndefined())
		{
			int oldCount = result->m_count28;
			if (result->slot4c() == 1)
			{
				result->m_count28 = (int)context->m_value04;
				state->invoke(current, result, count);
				result->m_count28 = oldCount;
			}
			else
			{
				state->invoke(current, result, count);
			}
		}
		else
		{
			state->invoke(current, result, count);
		}
	}
	else
	{
		state->invoke(current, result, count);
	}

	if (cleanSecondary)
	{
		value = state->m_stack20[state->m_count18 - 1];
		if (value->type() == 0x1b && !value->isUndefined())
		{
			value->m_state1c &= ~0x200u;
			value->release();
			--state->m_count18;
		}
	}

	if (releaseCurrent)
		current->release();

	if (state->m_count > 0 &&
		state->m_stack[state->m_count - 1] != d0(g_bfmeFallbackDB)
		&& current->type() == 0x16 && !current->isUndefined()
		&& (bfmeCompareVSC((const char *)name.m_data + 8,
			(const char *)0x01136d54) == 0
			|| bfmeCompareVSC((const char *)name.m_data + 8,
				(const char *)0x01136d44) == 0))
	{
		value = state->m_stack[state->m_count - 1];
		if (!value->maxRefCountHit())
			value->release();
		--state->m_count;
		value = state->m_stack38[state->m_count30 - 1];
		value->release();
		--state->m_count30;
	}

	goto done;

undefined_middle:
	reinterpret_cast<BfmeA1232 *>(state)->bfmePop1232(count + 3);
	state->m_stack[state->m_count++] = d0(g_bfmeFallbackDB);
	if (!d0(g_bfmeFallbackDB)->maxRefCountHit())
		d0(g_bfmeFallbackDB)->addRef();

	done:
	return;
}
