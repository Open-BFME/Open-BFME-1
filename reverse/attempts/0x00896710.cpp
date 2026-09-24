// ?d_00896710@@YAXXZ
// partial score=0.5 date=2026-09-24
// cl: /EHsc /FAsc

class BfmeObj4310;
class BfmeDropObjectA;
class BfmeNodeVMU
{
public:
	void *m_bfmePayload;
	BfmeNodeVMU *m_bfmeNext;
};

class BfmeListVMU
{
public:
	void bfmeEraseVMU(BfmeNodeVMU **it);
	BfmeNodeVMU *m_bfmeHead;
};

class Rva00896710Vector
{
public:
	void Rva00895F30(void *other);
	int size(void) const { return m_count; }
	BfmeDropObjectA **begin(void) { return m_items; }
	int m_count;
	int m_capacity;
	BfmeDropObjectA **m_items;
	BfmeDropObjectA *m_inline[2];
};

class BfmeTracker4310 : public BfmeListVMU
{
public:
	__declspec(noinline) void bfmeDrop(BfmeObj4310 *obj);
	__declspec(noinline) void Rva00896710(void);
	Rva00896710Vector m_rva00896710Vector;
};

class BfmeHolder4310;
extern BfmeTracker4310 *g_bfmeTracker4310;
extern BfmeHolder4310 *g_bfmeHolderBU;
extern int g_bfme1017I;
extern int g_rva00891FA0Ready;
extern int g_rva00891FA0Value;
extern void *(*Rva008C5D70Alloc)(unsigned int bytes);
extern void (*TheBfmeFree)(void *p, unsigned int bytes);

class Rva00893030Manager
{
public:
	void Rva008965B0(void);
};
extern Rva00893030Manager *g_rva00893030Manager;

class Gen_uw_00893e70
{
public:
	bool Rva00892FD0(int first, int second);
	void Rva00895340(void);
};
extern Gen_uw_00893e70 *Rva013377F0;

class Rva008A1940Queue
{
public:
	void flush(void);
};

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
	char m_data[1];
};

class BfmeString3AF0
{
public:
	BfmeStringData3AF0 *m_data;
};

class BfmeDropObjectA
{
public:
	~BfmeDropObjectA(void);
	void operator delete(void *p, unsigned int bytes)
	{
		TheBfmeFree(p, bytes);
	}

	int m_refCount;
	BfmeString3AF0 m_string;
	int m_kind;
	void *m_argument;
	void *m_object;
	void *m_buffer;
};

class BfmeHolderDB
{
public:
	BfmeHolderDB(void) : m_bfmeRef(0) {}
	BfmeHolderDB(const BfmeHolderDB &other) : m_bfmeRef(other.m_bfmeRef)
	{
		if (m_bfmeRef)
			++m_bfmeRef->m_refCount;
	}
	~BfmeHolderDB(void)
	{
		if (m_bfmeRef && --m_bfmeRef->m_refCount == 0)
			delete m_bfmeRef;
	}

	BfmeDropObjectA *m_bfmeRef;
};

class Gen_00895650
{
public:
	BfmeHolderDB bfmeGet(void) const;
};

class Rva008A2BA0Payload
{
public:
	unsigned int m_refs;
	unsigned int m_unmodelled04[3];
	void *m_value10;
	void *getValue(void) const { return m_value10; }
};

class Rva008A2BA0Handle
{
public:
	Rva008A2BA0Handle(void) : m_ptr(0) {}
	Rva008A2BA0Handle(Rva008A2BA0Payload *ptr) : m_ptr(ptr)
	{
		if (m_ptr)
			++m_ptr->m_refs;
	}
	Rva008A2BA0Handle(const Rva008A2BA0Handle &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->m_refs;
	}
	~Rva008A2BA0Handle(void)
	{
		if (m_ptr && --m_ptr->m_refs == 0)
			delete (BfmeDropObjectA *)m_ptr;
	}
	void operator=(const Rva008A2BA0Handle &other)
	{
		if (&other != this)
		{
			if (m_ptr && --m_ptr->m_refs == 0)
				delete (BfmeDropObjectA *)m_ptr;
			m_ptr = other.m_ptr;
			if (m_ptr)
				++m_ptr->m_refs;
		}
	}
	Rva008A2BA0Payload *m_ptr;
};

class Gen_008AC620
{
public:
	Gen_008AC620(void);
	virtual void slot0(void);
	virtual ~Gen_008AC620(void);
	virtual void slot2(void);
	unsigned char m_unmodelled04[8];
	void *m_value0c;
	unsigned char m_unmodelled10[8];
	int m_value18;
	unsigned int m_value1c;
	unsigned char m_unmodelled20[0x10];
};

class Rva008A2C80 : public Gen_008AC620
{
public:
	static void *operator new(unsigned int bytes)
	{
		return Rva008C5D70Alloc(bytes);
	}
	static void operator delete(void *p, unsigned int bytes)
	{
		TheBfmeFree(p, bytes);
	}
	Rva008A2C80(Rva008A2BA0Handle value);
	virtual void slot0(void);
	virtual ~Rva008A2C80(void);
	unsigned int m_value30;
	Rva008A2BA0Handle m_value34;
};

class Gen_008A12A0
{
public:
	int bfmeDigit(void) const;
};

class Rva008C3F10Value
{
public:
	virtual void slot00(void);
	virtual void slot04(int);
	virtual void slot08(void);
	virtual void slot0C(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1C(void);
	virtual void slot20(int);
	unsigned int field04;
	char gap08[4];
	char *field0C;
	char gap10[0x40];
	void *field50;
	void cleanup(char mode);
};

class BfmeNode1236
{
public:
	void bfmeActivate1236(void);
};

class BfmeElemCU
{
public:
	BfmeElemCU(void);
	~BfmeElemCU(void);
	int m_unmodelled00;
};

extern int Rva00892370Get(void);
class Rva00892360
{
public:
	static void store(int value);
};

class Gen_t_00894a10_p12cd
{
public:
	Gen_t_00894a10_p12cd(void)
	{
		m_pad0 = 0;
		m_pad4 = 0;
		m_data = m_inline;
	}
	~Gen_t_00894a10_p12cd(void);

	unsigned int m_pad0;
	unsigned int m_pad4;
	BfmeElemCU *m_data;
	BfmeElemCU m_inline[2];
};

struct Rva00891FA0Record
{
	int m_value;
	char m_kind;
	char m_text[256];
};

extern "C" __declspec(dllimport) void __cdecl Rva00891FA0SendRecord(
	Rva00891FA0Record *record, int count);
extern void (__cdecl *Rva01337854Callback)(void *first, void *second);

void BfmeTracker4310::Rva00896710(void)
{
	Rva00893030Manager *manager = g_rva00893030Manager;
	int zero = 0;
	manager->Rva008965B0();

	if (g_bfme1017I == zero ||
		((Gen_uw_00893e70 *)Rva013377F0)->Rva00892FD0(3, 2))
	{
	int itemCount = m_rva00896710Vector.size();
	BfmeDropObjectA **item = m_rva00896710Vector.begin();

		if (item != item + itemCount)
		{
			do
			{
				BfmeDropObjectA *outer = *item;
				if (outer)
					++outer->m_refCount;

				BfmeNodeVMU *node = m_bfmeHead;
				while (node != 0)
				{
					BfmeDropObjectA *inner = (BfmeDropObjectA *)node->m_bfmePayload;
					if (inner)
						++inner->m_refCount;

					bool shouldProcess;
					{
						BfmeHolderDB holder = ((Gen_00895650 *)inner)->bfmeGet();
						if (holder.m_bfmeRef == (BfmeDropObjectA *)outer)
						{
							shouldProcess = true;
							if (((unsigned char *)inner)[0x0c] != 0)
								shouldProcess = false;
						}
						else
							shouldProcess = false;
					}
					if (shouldProcess)
					{
						Rva008A2BA0Handle handle((Rva008A2BA0Payload *)outer);
						Rva008A2C80 *attached = new Rva008A2C80(handle);
						Rva008C3F10Value *state = *(Rva008C3F10Value **)((char *)inner + 8);
						if (Rva00892370Get() == zero)
						{
							int digit = ((Gen_008A12A0 *)attached)->bfmeDigit();
							Rva00892360::store(digit);
						}

						state->cleanup(1);
						unsigned int flags = state->field04;
						flags &= 0xffffffd2;
						flags |= 0x8012;
						state->field50 = attached;
						state->field04 = flags;
						attached->m_value18 = -1;
						((Gen_008AC620 *)state->field50)->m_value1c |= 0x01000000;
						((BfmeNode1236 *)state)->bfmeActivate1236();
						((unsigned char *)inner)[0x0c] = 1;

						void (__cdecl *callback)(void *, void *) = Rva01337854Callback;
						if (callback)
							callback(((BfmeStringData3AF0 *)outer->m_string.m_data)->m_data,
								state->field0C + 8);

					if (g_rva00891FA0Ready != 0)
					{
						Rva00891FA0Record record;
						int length =
							((BfmeStringData3AF0 *)outer->m_string.m_data)->m_length + 6;
						record.m_value = g_rva00891FA0Value;
						record.m_kind = 6;
						const char *source =
							((BfmeStringData3AF0 *)outer->m_string.m_data)->m_data;
						char *destination = record.m_text;
						while ((*destination++ = *source++) != 0)
							;
						Rva00891FA0SendRecord(&record, length);
				}
						((unsigned char *)inner)[0x0c] = 0;
						if (inner && --inner->m_refCount == 0)
							delete inner;
			}
				else if (inner && --inner->m_refCount == 0)
					delete inner;

				node = node->m_bfmeNext;
				}

				if (outer && --outer->m_refCount == 0)
					delete outer;
				++item;
			}
			while (item != m_rva00896710Vector.begin() +
				m_rva00896710Vector.size());
		}
	}

	if (g_bfme1017I != 0)
	{
		((Gen_uw_00893e70 *)Rva013377F0)->Rva00895340();
		if (m_rva00896710Vector.size() > zero)
		{
			Gen_t_00894a10_p12cd temporary;
			m_rva00896710Vector.Rva00895F30(&temporary);
			((Rva008A1940Queue *)g_bfmeHolderBU)->flush();
		}
	}
}
