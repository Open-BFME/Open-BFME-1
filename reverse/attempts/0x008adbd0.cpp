// ?bfmeEmit1236@BfmeB1236@@QAEXPAXH0@Z
// partial score=0.2 date=2026-09-21
// cl: /O2 /Oy /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?bfmeEmit1236@BfmeB1236@@QAEXPAXH0@Z
//
// Identity is proven by the matched BfmeA1236 callers at 0x008BDA00 and
// 0x008BDA70, and by the existing symbols.csv pin.  The three generic Apt
// helpers remain address-qualified because callees.py reports their dump
// names; no new semantic pin is claimed here.

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
	void (__cdecl *free)(void *storage);
};

extern const float g_bfmeK1253;
extern float g_bfmeDefaultBU;

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

extern "C" void __cdecl bfmeNotify1209(void *a);
__declspec(dllimport) void __cdecl bfmeCallVJU(void *a, int b);

struct BfmeQ1206
{
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
};

extern "C" BfmeQ1206 g_bfmeD1206;

class Rva00899770
{
public:
	virtual void addRef(void);
	virtual void release(void);

	unsigned m_flags;
	union
	{
		bool m_boolean;
		int m_integer;
		float m_float;
		BfmeStringData3AF0 *m_string;
	};
	char m_gap0c[0x14];
	void *m_indirect;
};

typedef Rva00899770 AptValue;

class BfmeTab1024
{
public:
	int bfmeFind1024(int key);
};

class BfmeStrVKI
{
};

class Rva008AE770Stack
{
public:
	Rva00899770 *createString(void *value, int unused, BfmeStrVKI *name,
		int one, int another, int zero);
};

extern Rva008AE770Stack Rva008AE770TheStack;

struct BfmeReturnedString1236
{
	BfmeStringData3AF0 *m_data;
};

struct BfmeStringSlot1236
{
	BfmeStringData3AF0 *m_data;

	BfmeStringSlot1236(BfmeStringData3AF0 *data)
		: m_data(data)
	{
		if (data != 0)
			++data->m_refCount;
	}

	~BfmeStringSlot1236()
	{
		BfmeStringData3AF0 *data = m_data;
		if (data != 0 && --data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	__forceinline BfmeStringSlot1236 &operator=(const BfmeReturnedString1236 &other)
	{
		BfmeStringData3AF0 *data = other.m_data;
		++data->m_refCount;
		BfmeStringData3AF0 *old = m_data;
		if (old != 0 && --old->m_refCount == 0)
			g_bfmeStringPool1284->free(old);
		m_data = data;
		return *this;
	}
};

class Rva00898F60Owner1236
{
public:
	BfmeReturnedString1236 *getString(BfmeStringData3AF0 **out);
};

#pragma comment(linker, "/alternatename:?getString@Rva00898F60Owner1236@@QAEPAVBfmeReturnedString1236@@PAPAVBfmeStringData3AF0@@@Z=?d_00898f60@@YAXXZ")

class Gen_008D2B50
{
public:
	void bfmePush(void);
};

class Gen_008D2B80
{
public:
	void bfmePop(void);
};

class Gen_008D2C80
{
public:
	void bfmePush(void);
	void bfmePop1210(void);
};

struct BfmeS1209
{
	float m_bfme00;
	float m_bfme04;
	float m_bfme08;
	float m_bfme0c;
	float m_bfme10;
	float m_bfme14;
	float m_bfme18;
	float m_bfme1c;
};

class BfmeA1209
{
public:
	void bfmeOp1209(const BfmeS1209 *a);
};

class BfmeA1206
{
public:
	void bfmeGet1206(BfmeQ1206 *out);
};

class BfmeThingDXH
{
public:
	void bfmeGoDXH(void *a);
};

struct BfmeDataLI
{
	int m_bfmeWords[6];
};

class BfmeItemLI
{
public:
	virtual void bfmeDoLI(void) = 0;
};

class BfmeThingLI
{
public:
	void bfmeAddLI(BfmeItemLI *item, const BfmeDataLI *data);
};

extern char *Rva008A5380Holder;

class Rva008A0F20Header
{
public:
	int isKind0C(void) const;
	int isKind11(void) const;
};

class BfmeSubF1038
{
public:
	void *m_owner;
	void bfmeAdd1038(int a, int b);
};

struct RvaEmitOwnerTable1236
{
	char m_gap00[0x58];
	void *m_context;
};

struct RvaEmitOwner1236
{
	RvaEmitOwnerTable1236 *m_table;
};

struct RvaEmitRef1236
{
	int m_refCount;
	char m_gap04[0x14];
	void *m_value;
};

struct RvaEmitRecord1236
{
	int m_bfme00;
	BfmeS1209 m_bfme04;
	float m_bfme24;
	float m_bfme28;
	float m_bfme2c;
	int m_bfme30;
	struct
	{
		short m_index;
		short m_value;
	} m_bfme34[1];
};

struct RvaEmitSequence1236
{
	char m_gap00[4];
	void **m_table;
	RvaEmitRef1236 *m_ref08;
	RvaEmitRef1236 *m_ref0c;
	char m_gap10[0x20];
	int m_count;
	RvaEmitRecord1236 *m_records;
};

struct RvaEmitState1236
{
	char m_gap00[0x0c];
	RvaEmitSequence1236 *m_sequence;
	void *m_bfme10;
	int m_bfme14;
	float m_bfme18;
	unsigned m_bfme1c;
	BfmeSubF1038 m_bfme20;
	BfmeSubF1038 m_bfme24;
};

struct RvaEmitTail1236
{
	char m_gap00[0x0c];
	RvaEmitRef1236 *m_ref0c;
};

struct RvaEmitTailRef1236
{
	char m_gap00[0x18];
	void *m_value;
};

struct RvaEmitContext1236
{
	char m_gap00[0x50];
	RvaEmitTail1236 *m_tail;
};

typedef RvaEmitContext1236 BfmeA1236;

struct RvaEmitItem1236
{
	char m_gap00[0x10];
	void **m_values;
};

struct RvaEmitValue1236
{
	int m_refCount;
	char m_gap04[0x14];
	void *m_value;
};

struct RvaEmitLerp1236
{
	char m_gap00[0x2c];
	float m_factor;
};

typedef void (__cdecl *RvaEmitSink1236)(void *, void *, void *, void *);
typedef void (__cdecl *RvaEmitNotify1236)(void *, void *);

class BfmeB1236 : public Rva00899770
{
public:
	void bfmeEmit1236(void *a, int unused, void *c);

	char m_gap24[0x24];
	void *m_bfme48;
	void *m_bfme4c;
	RvaEmitState1236 *m_bfme50;
};

void BfmeB1236::bfmeEmit1236(void *a, int unused, void *c)
{
	RvaEmitLerp1236 *lerp = (RvaEmitLerp1236 *)m_bfme48;
	if (lerp != 0 && lerp->m_factor < g_bfmeK1253)
		return;

	unsigned flags = m_flags;
	unsigned kind = flags;
	kind &= 0x3f;

	if (kind == 0x0d)
	{
		unsigned bit = flags >> 15;
		bit = ~bit;
		if (((unsigned char)bit & 1) == 0)
			goto emit_state;
	}

	if (kind == 0x12)
	{
		unsigned bit = flags >> 15;
		bit = ~bit;
		if (((unsigned char)bit & 1) == 0)
			goto emit_state;
	}
	goto check_kind_e;

	emit_state:
	{
		RvaEmitContext1236 *context;
		AptValue *found = 0;
		RvaEmitState1236 *state = m_bfme50;
		if ((state->m_bfme1c & 0x0c000000) == 0)
		{
			if (state->m_bfme10 != (void *)found)
			{
				found = (AptValue *)((BfmeTab1024 *)state->m_bfme10)->bfmeFind1024(
					(int)0x013384c8);
			}

			if (found != (AptValue *)0)
				state->m_bfme1c = (state->m_bfme1c & 0xf7ffffff) | 0x04000000;
			else
				state->m_bfme1c = (state->m_bfme1c & 0xfbffffff) | 0x08000000;
		}

		if ((state->m_bfme1c & 0x0c000000) == 0x04000000)
		{
			if (state->m_bfme10 != (void *)found)
			{
				found = (AptValue *)((BfmeTab1024 *)state->m_bfme10)->bfmeFind1024(
					(int)0x013384c8);
			}

			context =
				(RvaEmitContext1236 *)((RvaEmitOwnerTable1236 *)
					((RvaEmitOwner1236 *)state->m_bfme24.m_owner)->m_table)->m_context;
			if (context == (RvaEmitContext1236 *)0)
				return;

			Rva00899770 *created = Rva008AE770TheStack.createString(
				(void *)this, 0, (BfmeStrVKI *)0x013384c0, 1, 1, 0);
			created->addRef();

			BfmeStringSlot1236 first(&g_bfmeDefaultString1284);
			{
				BfmeStringSlot1236 second(0);
				BfmeReturnedString1236 *returned =
					((Rva00898F60Owner1236 *)this)->getString(
						&second.m_data);
				first = *returned;
			}

			AptValue *left = created;
			if ((created->m_flags & 0x3f) != 1)
				left = (AptValue *)created->m_indirect;

			AptValue *right = found;
			if ((found->m_flags & 0x3f) != 1)
				right = (AptValue *)found->m_indirect;

			RvaEmitTailRef1236 *tailRef =
				(RvaEmitTailRef1236 *)context->m_tail->m_ref0c;
			RvaEmitSink1236 sink = (RvaEmitSink1236)0x013378ac;
			sink((char *)right->m_string + 8,
				(char *)left->m_string + 8,
				tailRef->m_value,
				(char *)first.m_data + 8);

			created->release();
			return;
		}
		else
		{
			state->m_bfme24.bfmeAdd1038((int)a, (int)c);
			return;
		}
	}

check_kind_e:
	if (kind == 0x0e)
	{
		unsigned bit = flags >> 15;
		bit = ~bit;
		if (((unsigned char)bit & 1) == 0)
		{
			BfmeQ1206 data;
			((BfmeA1206 *)a)->bfmeGet1206(&data);
			((BfmeThingLI *)Rva008A5380Holder)->bfmeAddLI(
				(BfmeItemLI *)this, (const BfmeDataLI *)&data);
			this->m_bfme50->m_bfme20.bfmeAdd1038((int)a, (int)c);
			return;
		}
	}

	if (kind == 0x0f)
	{
		unsigned bit = flags >> 15;
		bit = ~bit;
		if (((unsigned char)bit & 1) == 0)
		{
			void *value = this->m_bfme50->m_bfme20.m_owner;
			if (value != 0 && value != (void *)0x012d5598)
			{
				RvaEmitNotify1236 notify = (RvaEmitNotify1236)0x01337878;
				notify(value, c);
			}
			return;
		}
	}

	if (kind == 0x10)
	{
		unsigned bit = flags >> 15;
		bit = ~bit;
		if (((unsigned char)bit & 1) == 0)
		{
			RvaEmitState1236 *state = m_bfme50;
			Gen_008D2C80 *stack = (Gen_008D2C80 *)a;
			stack->bfmePush();
			((BfmeThingDXH *)a)->bfmeGoDXH(
				(char *)state->m_sequence + 0x18);

			BfmeQ1206 data = g_bfmeD1206;
			int outer = 0;
			float accumulator = 0.0f;
			RvaEmitItem1236 *item = 0;

			if (state->m_sequence->m_count > 0)
			{
				while (outer < state->m_sequence->m_count)
				{
					stack->bfmePush();
					RvaEmitRecord1236 *record =
						(RvaEmitRecord1236 *)((char *)state->m_sequence->m_records + outer * 0x38);
					((BfmeA1209 *)a)->bfmeOp1209(&record->m_bfme04);

					if (record->m_bfme24 != -100000000.0f ||
						record->m_bfme28 != -100000000.0f)
						accumulator = 0.0f;

					float value24 = record->m_bfme24;
					float value28 = record->m_bfme28;
					float value2c = record->m_bfme2c;
					int index = 0;
					if (record->m_bfme30 > 0)
					{
						item = (RvaEmitItem1236 *)state->m_sequence->m_table[record->m_bfme00];
						do
						{
							int valueIndex = record->m_bfme34[index].m_index;
							RvaEmitValue1236 *value =
								(RvaEmitValue1236 *)item->m_values[valueIndex];

							stack->bfmePush();
							data.m_bfme00 = *(int *)&value2c;
							data.m_bfme0c = *(int *)&value2c;
							data.m_bfme14 = *(int *)&value28;
							float next = accumulator + value24;
							data.m_bfme10 = *(int *)&next;
							((BfmeThingDXH *)a)->bfmeGoDXH(&data);

							if (--value->m_refCount == 0)
								bfmeCallVJU(value->m_value, (int)c);
							stack->bfmePop1210();

							accumulator += (float)record->m_bfme34[index].m_value *
								(*(const float *)0x010ba670);
							++index;
						}
						while (index < record->m_bfme30);
					}

					((Gen_008D2B80 *)a)->bfmePop();
					++outer;
				}
			}

			stack->bfmePop1210();
			return;
		}
	}

	if (((Rva008A0F20Header *)this)->isKind11())
	{
		BfmeA1236 *context = (BfmeA1236 *)a;
		RvaEmitState1236 *state = m_bfme50;
		((Gen_008D2B50 *)context)->bfmePush();
		*(float *)context = g_bfmeDefaultBU - state->m_bfme18;
		bfmeNotify1209(context);

		RvaEmitRef1236 *first = state->m_sequence->m_ref08;
		if (--first->m_refCount == 0)
			bfmeCallVJU(first->m_value, (int)c);
		RvaEmitRef1236 *second = state->m_sequence->m_ref0c;
		*(float *)context = state->m_bfme18;
		bfmeNotify1209(context);
		if (--second->m_refCount == 0)
			bfmeCallVJU(second->m_value, (int)c);
		((Gen_008D2B80 *)context)->bfmePop();
		return;
	}

	if (((Rva008A0F20Header *)this)->isKind0C())
	{
		RvaEmitState1236 *state = m_bfme50;
		RvaEmitRef1236 *value = state->m_sequence->m_ref08;
		if (--value->m_refCount == 0)
			bfmeCallVJU(value->m_value, (int)c);
	}
}
