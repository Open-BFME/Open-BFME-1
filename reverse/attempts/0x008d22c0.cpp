// ?d_008d22c0@@YAXXZ
// partial score=0.16 date=2026-09-17
// cl: /O2 /Oy /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// The matched callers identify this as BfmeNodeDX::bfmeEmit1281.  The
// receiver and the node-detail offsets are witnessed by the callers and by
// the retail body.  The remaining Apt node/value owners use names derived from
// their addresses, so no semantic class name is asserted for them.

extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int bytes);
extern void (__cdecl *TheBfmeFree)(void *storage, unsigned int bytes) throw();

class BfmeItemDX
{
public:
	int m_body[4];
};

extern void __cdecl bfmePush(BfmeItemDX *item);
extern void __cdecl bfmeRemove(BfmeItemDX *item);

class Rva8CBC80Derived
{
public:
	virtual ~Rva8CBC80Derived();

	static void *operator new(unsigned int)
	{
		char *storage = (char *)Rva008C5D70Alloc(0x20);
		storage += 8;
		bfmePush((BfmeItemDX *)storage);
		return storage;
	}

	static void operator delete(void *storage, unsigned int bytes);

	Rva8CBC80Derived();
	unsigned int m_flags;
	char m_payload[0x18];
};

class BfmeB1055
{
public:
	BfmeB1055 *bfmeGo1055B(int a, int b, int c, int d);
	BfmeB1055 *bfmeGo1055C(int a, int b, int c, int d);

	void *m_vtable;
	unsigned int m_flags;
	char m_padding08[0x30 - 0x08];
	int m_argument30;
};

void *Rva008BA7D0(unsigned int bytes);
void *Rva008BA840(unsigned int bytes);

class Rva008D22C0B1055
{
public:
	static __forceinline void *operator new(unsigned int) throw()
	{
		return Rva008BA7D0(0x34);
	}

	static void operator delete(void *storage, unsigned int bytes)
	{
		bfmeRemove((BfmeItemDX *)storage);
		TheBfmeFree((char *)storage - 8, bytes + 8);
	}

	__forceinline Rva008D22C0B1055(int a, int b, int c, int d)
	{
		((BfmeB1055 *)this)->bfmeGo1055B(a, b, c, d);
	}

	void *m_vtable;
	unsigned int m_flags;
	char m_padding08[0x30 - 0x08];
	int m_argument30;
};

class Rva008D22C0C1055
{
public:
	static __forceinline void *operator new(unsigned int) throw()
	{
		return Rva008BA840(0x34);
	}

	static void operator delete(void *storage, unsigned int bytes)
	{
		bfmeRemove((BfmeItemDX *)storage);
		TheBfmeFree((char *)storage - 8, bytes + 8);
	}

	__forceinline Rva008D22C0C1055(int a, int b, int c, int d)
	{
		((BfmeB1055 *)this)->bfmeGo1055C(a, b, c, d);
	}

	void *m_vtable;
	unsigned int m_flags;
	char m_padding08[0x30 - 0x08];
};

class AptValue
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual AptValue *slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual int slot19();

	unsigned int m_flags;
	AptValue *m_chain08;
	AptValue *m_chain0c;
	char m_padding10[0x20 - 0x10];
	void *m_argument20;
	void *m_argument24;
	void *m_owner28;
	char m_padding2c[4];
	void *m_argument30;
};

class BfmeNodeDX
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual AptValue *slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();

	bool bfmeEmit1281(int mode, void *tail, int enabled);

	unsigned int m_flags;
	char m_padding08[0x50 - 0x08];
	void *m_detail;
};

struct Rva008D22C0FlagEntry
{
	unsigned int m_flags;
	int m_argument04;
	int m_argument08;
};

struct Rva008D22C0FlagList
{
	int m_count;
	Rva008D22C0FlagEntry *m_entries;
};

struct Rva008D22C0Detail
{
	char m_padding00[0x20];
	Rva008D22C0FlagList *m_flags;
};

struct Rva008D22C0Route
{
	unsigned int m_flags;
	int m_index;
};

class BfmeA1232
{
public:
	void bfmePop1232(int count);
};

class BfmeR1226
{
public:
	void bfmeLine1226(char *text);
};

class BfmeOtherLP;

class BfmeThingLP
{
public:
	void bfmePushLP(void *value, BfmeOtherLP *owner, int tail);
};

class BfmeRingRef0890;

class BfmeRing008A0890
{
public:
	void insert(int value, BfmeRingRef0890 *owner, int tail);
};

class BfmeN1034;

class BfmeRouteManager1282
{
public:
	void bfmeSubmit1282(void *owner, BfmeN1034 *value, int zero, int tail);
	void produce(void *owner, BfmeN1034 *value, int zero, int tail);
};

extern BfmeRouteManager1282 *g_bfmeHolderBU;
extern void *g_bfmeExtra1282;
extern AptValue **g_bfmeArr1233;
extern int g_bfmeRouteKeys1282[];

extern void d_0089cef0(void);
extern void d_008cced0(void);

class Gen_008A0D60
{
public:
	Gen_008A0D60() {}

	__forceinline ~Gen_008A0D60()
	{
		if (m_buffer != 0)
			TheBfmeFree(m_buffer, m_count * 4);
	}

	char m_head[4];
	int m_count;
	AptValue **m_buffer;
};

static __forceinline void bfmeAdd1226Opaque(void *value, void *owner, int mode)
{
	typedef void (BfmeR1226::*Call)(void *, void *, int);
	union
	{
		void (*raw)(void);
		Call typed;
	} thunk;
	thunk.raw = d_008cced0;
	(((BfmeR1226 *)0x01338748)->*thunk.typed)(value, owner, mode);
}

static __forceinline AptValue *bfmeLookupOpaque(AptValue *value, void *key)
{
	typedef AptValue *(AptValue::*Call)(void *);
	union
	{
		void (*raw)(void);
		Call typed;
	} thunk;
	thunk.raw = d_0089cef0;
	return (value->*thunk.typed)(key);
}

bool BfmeNodeDX::bfmeEmit1281(int mode, void *tail, int enabled)
{
	bool changed = false;
	BfmeNodeDX *self = this;
	unsigned int flags = self->m_flags;
	if ((flags & 0x3f) == 0xf)
	{
		flags >>= 15;
		if ((((unsigned char)~flags) & 1) == 0)
			return changed;
	}

	Rva008D22C0Detail *detail = (Rva008D22C0Detail *)self->m_detail;
	if (detail->m_flags != 0)
	{
		int index = 0;
		int offset = 0;
		if (detail->m_flags->m_count > 0)
		{
			do
			{
			Rva008D22C0FlagEntry *entry =
				(Rva008D22C0FlagEntry *)
					((char *)detail->m_flags->m_entries + offset);
			if ((entry->m_flags & (unsigned int)mode) != 0)
			{
				if (mode > 0x200)
				{
					if (mode != 0x20000)
					{
						((BfmeThingLP *)g_bfmeHolderBU)->bfmePushLP(
							(char *)entry + 8, (BfmeOtherLP *)self, (int)tail);
						changed = 1;
					}
					else if (entry->m_argument04 == (mode >> 17))
					{
						((BfmeRing008A0890 *)g_bfmeHolderBU)->insert(
							(int)((char *)entry + 8),
							(BfmeRingRef0890 *)self, (int)tail);
						changed = 1;
					}
				}
				else
				{
					switch (mode)
					{
					case 0x200:
					case 4:
					{
						AptValue *created = (AptValue *)new Rva8CBC80Derived;

						AptValue **createdValues =
							*(AptValue ***)0x0133875c;
						int createdCount = *(int *)0x01338754;
						createdValues[createdCount] = created;
						++*(int *)0x01338754;
						created->slot00();

						AptValue **ownerValues =
							*(AptValue ***)0x01338780;
						int ownerCount = *(int *)0x01338778;
						ownerValues[ownerCount] = (AptValue *)self;
						++*(int *)0x01338778;
						self->slot00();

						Gen_008A0D60 saved;
						saved.m_count = *(int *)0x0133874c;
							saved.m_buffer = (AptValue **)Rva008C5D70Alloc(
									saved.m_count * 4);
							register AptValue **buffer = saved.m_buffer;

						int stackCount = *(int *)0x01338748;
						int copied = 0;
						for (int reverse = 0; reverse < stackCount; ++reverse)
						{
							AptValue *value =
								g_bfmeArr1233[*(int *)0x01338748 - reverse - 1];
							buffer[copied] = value;
							++copied;
							value->slot00();
						}

						((BfmeA1232 *)0x01338748)->bfmePop1232(stackCount);
						bfmeAdd1226Opaque((void *)entry->m_argument08,
							(void *)self, -1);
						((BfmeR1226 *)0x01338748)->bfmeLine1226(
							(char *)0x0113731c);

						for (int remaining = copied; remaining > 0; --remaining)
						{
							AptValue *value = buffer[remaining - 1];
							int count = *(int *)0x01338748;
							g_bfmeArr1233[count] = value;
							++*(int *)0x01338748;
							if ((value->m_flags & 0x40000000) == 0)
								value->slot00();
							value->slot01();
						}

						ownerCount = *(int *)0x01338778;
						ownerValues = *(AptValue ***)0x01338780;
						ownerValues[ownerCount - 1]->slot01();
						--*(int *)0x01338778;

						createdCount = *(int *)0x01338754;
						createdValues = *(AptValue ***)0x0133875c;
						createdValues[createdCount - 1]->slot01();
						--*(int *)0x01338754;
						changed = 1;
					}
						break;

					case 2:
						((BfmeRing008A0890 *)g_bfmeHolderBU)->insert(
							(int)((char *)entry + 8),
							(BfmeRingRef0890 *)self, (int)g_bfmeExtra1282);
						changed = 1;
						break;
					}
				}
			}

			++index;
			offset += 0xc;
			}
			while (index < detail->m_flags->m_count);
		}
	}

	if (enabled != 0)
	{
		for (struct Rva008D22C0Route *route =
				(struct Rva008D22C0Route *)0x012d5d50;
			route < (struct Rva008D22C0Route *)0x012d5dc0; ++route)
		{
			if ((route->m_flags & (unsigned int)mode) == 0)
				continue;

			AptValue *current = self->slot06();
			void *key = (void *)&g_bfmeRouteKeys1282[route->m_index];
			AptValue *found = bfmeLookupOpaque(current, key);
			if (found == 0)
			{
				AptValue *search =
					(AptValue *)((unsigned int)current->m_chain0c & ~1u);
				AptValue *chain =
					(AptValue *)((unsigned int)current->m_chain08 & ~1u);
				while (search != 0)
				{
					found = bfmeLookupOpaque(search, key);
					if (found != 0)
						break;
					search = chain;
					if (search == 0)
						break;
					AptValue *link = search->slot06();
					chain = (AptValue *)((unsigned int)link->m_chain08 & ~1u);
				}
			}

			if (found == 0 || (found->m_flags & 0x8000) == 0)
				continue;

			if (found->m_owner28 != self)
			{
				if (found->slot19() == 1)
				{
					Rva008D22C0B1055 *created =
						new Rva008D22C0B1055(
							(int)found->m_argument30,
							(int)found->m_argument20,
							(int)found->m_argument24, (int)self);
					created->m_flags =
						(created->m_flags & 0xffffc07f) | 0x40;
					found = (AptValue *)created;
				}
				else
				{
					Rva008D22C0C1055 *created =
						new Rva008D22C0C1055(
							(int)found->m_argument30,
							(int)found->m_argument20,
							(int)found->m_argument24, (int)self);
					created->m_flags =
						(created->m_flags & 0xffffc07f) | 0x40;
					found = (AptValue *)created;
				}
			}

			if (route->m_flags == 0x4000 || route->m_flags == 0x2000)
			{
				g_bfmeHolderBU->produce((void *)self,
					(BfmeN1034 *)found, 0, (int)tail);
				changed = 1;
			}
			else
			{
				g_bfmeHolderBU->bfmeSubmit1282((void *)self,
					(BfmeN1034 *)found, 0, (int)tail);
				changed = 1;
			}
		}
	}

	return changed;
}
