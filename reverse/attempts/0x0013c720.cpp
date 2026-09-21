// ?dump@Rva0013C720Owner@@QAEXPBD@Z
// partial score=0.1 date=2026-09-18
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x0013C720, 1344 bytes.  The boundary is the contiguous 0x540-byte
// body ending in ret 4.  The caller proves only a thiscall body with one stack
// argument; the address-qualified owner below deliberately makes no class or
// semantic claim beyond that ABI.

typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

extern const Real g_bfmeDefaultBU;
extern const Real BfmeZeroRange;

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) {}
	~BFMERetailAsciiString() { releaseBuffer(); }
	void releaseBuffer();
	const char *str() const
	{
		return m_data != 0 ? (const char *)m_data + 8 :
			(const char *)0x0107388B;
	}

	void *m_data;
};

// The dump helper's 0x48-byte record is witnessed by its constructor, dump
// method, and the adjacent copy/assignment bodies.  The member meanings stay
// opaque here; only the field widths and offsets used by those bodies are
// represented.
class Rva0013C720Record
{
public:
	void *m_00;
	void *m_04;
	void *m_08;
	void *m_0c;
	void *m_10;
	int m_14;
	int m_18;
	void *m_1c;
	void *m_20;
	int m_24;
	void *m_28;
	int m_2c;
	int m_30;
	int m_34;
	int m_38;
	void *m_3c;
	int m_40;
	void *m_44;
};

class BfmeD1191 : public Rva0013C720Record
{
public:
	BfmeD1191(const char *filename);
	void bfmeDump1191();
	char *m_bfme48;
};

class Rva0013A0C0 : public Rva0013C720Record
{
public:
	void assign(const Rva0013A0C0 &other);
};

class Rva0013A1A0 : public Rva0013C720Record
{
public:
	void copyTo(Rva0013A1A0 &dest) const;
};

class Rva0013C720RegistryItem;

class Rva0013C720RegistryNode
{
public:
	char m_pad00[0x2a0];
	Rva0013C720RegistryItem *m_begin;
	Rva0013C720RegistryItem *m_end;
	char m_pad2a8[0xe4];
	Rva0013C720RegistryNode *m_next;
};

class Rva0013C720Registry
{
public:
	char m_pad00[8];
	Rva0013C720RegistryNode *m_first;
};

#define Rva0013C720TheRegistry (*(Rva0013C720Registry **)0x012EF1D8)

class Rva0013C720RegistryItem
{
public:
	char m_pad00[8];
	void *m_value;
	char m_tail[0xc];
};

class Rva0013C720Element
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10();
	virtual void *slot11();
};

class Rva0013C720Asset
{
public:
	virtual void release();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual int slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual int slot10();
	virtual int slot11();
	int m_refCount;
};

class Rva0013C720VectorCopy
{
public:
	void copyFrom(const void *source);
};

class Rva0013C720VectorDestroy
{
public:
	void destroy();
};

class Rva0013C720SmallDestroy
{
public:
	void destroy();
};

class Rva0013C720Open2Destroy
{
public:
	void destroy();
};

class Rva0013C720Owner
{
public:
	void dump(const char *filename);
	Bool build(Rva0013A1A0 *out, Rva0013C720RegistryNode *node,
		Rva0013C720RegistryItem *item, int index);
	void attach(Rva0013A1A0 *record, int index);
};

class UnicodeString
{
public:
	UnicodeString() : m_data(0) {}
	~UnicodeString() { releaseBuffer(); }
	void set(const UnicodeString &other);
	void releaseBuffer();
	void *m_data;
};

class Rva0013C720HAnim
{
public:
	virtual void release();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual int slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11();
};

extern void *Create_Render_Obj(const char *name);
extern Rva0013C720HAnim *Get_HAnim(const char *name);
extern "C" int __cdecl fclose(void *stream);

#pragma comment(linker, "/alternatename:?assign@Rva0013A0C0@@QAEXABV1@@Z=?j_0002257f@@YAXXZ")
#pragma comment(linker, "/alternatename:?copyTo@Rva0013A1A0@@QBEXAAV1@@Z=?j_0002f7b6@@YAXXZ")
#pragma comment(linker, "/alternatename:?copyFrom@Rva0013C720VectorCopy@@QAEXPAX@Z=?j_0003ea13@@YAXXZ")
#pragma comment(linker, "/alternatename:?destroy@Rva0013C720VectorDestroy@@QAEXXZ=?j_000395d1@@YAXXZ")
#pragma comment(linker, "/alternatename:?destroy@Rva0013C720SmallDestroy@@QAEXXZ=?j_00003b6b@@YAXXZ")
#pragma comment(linker, "/alternatename:?destroy@Rva0013C720Open2Destroy@@QAEXXZ=?j_0000b488@@YAXXZ")
#pragma comment(linker, "/alternatename:?set@UnicodeString@@QAEXABV1@@Z=?j_00087c90@@YAXXZ")
#pragma comment(linker, "/alternatename:?build@Rva0013C720Owner@@QAE_NPAVRva0013A1A0@@PAVRva0013C720RegistryNode@@PAVRva0013C720RegistryItem@@H@Z=?j_00020be9@@YAXXZ")
#pragma comment(linker, "/alternatename:?attach@Rva0013C720Owner@@QAEXPAVRva0013A1A0@@H@Z=?j_00038ef1@@YAXXZ")

void Rva0013C720Owner::dump(const char *filename)
{
	BfmeD1191 report(filename);
	Rva0013C720Registry *registry = Rva0013C720TheRegistry;
	Rva0013C720RegistryNode *first = registry != 0 ? registry->m_first : 0;
	Real nodeCount = BfmeZeroRange;
	Rva0013C720RegistryNode *walk = first;
	while (walk != 0)
	{
		nodeCount += g_bfmeDefaultBU;
		walk = walk->m_next;
	}

	if (registry != 0)
	{
		Rva0013C720RegistryNode *node = first;
		while (node != 0)
		{
			Rva0013C720RegistryItem *begin = node->m_begin;
			Rva0013C720RegistryItem *end = node->m_end;
			int count = (int)(end - begin);
			for (int index = 0; index < count; ++index)
			{
				Rva0013C720RegistryItem *item = begin + index;
				Rva0013C720Element *element =
					(Rva0013C720Element *)item->m_value;
				if (element == 0)
					continue;

				Rva0013C720Asset *asset =
					(Rva0013C720Asset *)element->slot11();
				if (asset == 0)
					continue;

				Rva0013C720VectorCopy firstCopy;
				Rva0013C720VectorCopy secondCopy;
				firstCopy.copyFrom((char *)asset + 0x18);
				secondCopy.copyFrom((char *)asset + 0x24);

				Rva0013A1A0 built;
				if (build(&built, node, item, index))
				{
					const char *name = built.m_00 != 0 ?
						(const char *)built.m_00 + 8 :
						(const char *)0x0107388B;
					Rva0013C720Asset *render =
						(Rva0013C720Asset *)Create_Render_Obj(name);
					if (render != 0)
					{
						int firstValue = render->slot10();
						int secondValue = render->slot11();
						(void)firstValue;
						(void)secondValue;
						attach(&built, index);
						if (--render->m_refCount == 0)
							render->release();
					}
				}

				Rva0013A1A0 copied;
				built.copyTo(copied);
				report.bfmeDump1191();
				((BFMERetailAsciiString *)&built)->releaseBuffer();
				((BFMERetailAsciiString *)&copied)->releaseBuffer();
				((BFMERetailAsciiString *)&firstCopy)->releaseBuffer();
				((BFMERetailAsciiString *)&secondCopy)->releaseBuffer();
			}
			node = node->m_next;
		}
	}

	Rva0013A0C0 assigned;
	assigned.assign((const Rva0013A0C0 &)report);
	UnicodeString firstName;
	UnicodeString secondName;
	secondName.set(firstName);
	firstName.set(secondName);
	Rva0013C720HAnim *animation = Get_HAnim(firstName.m_data != 0 ?
		(const char *)firstName.m_data + 8 : (const char *)0x0107388B);
	if (animation != 0)
	{
		int value = animation->slot04();
		(void)value;
		animation->release();
	}

	Rva0013C720VectorDestroy vectorDestroy;
	Rva0013C720SmallDestroy smallDestroy;
	Rva0013C720Open2Destroy open2Destroy;
	vectorDestroy.destroy();
	smallDestroy.destroy();
	open2Destroy.destroy();
	fclose(report.m_bfme48);
}
