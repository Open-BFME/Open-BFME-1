// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
class AptValue; class Rva00899F00Base;
struct Rva008B4370Owner; struct Rva008B4420Owner; struct Owner008B4700; struct Owner008B4480;
AptValue *aptSetPackedChannels008B4370(Rva008B4370Owner *,int);
AptValue *aptPackedChannels008B4420(Rva008B4420Owner *,int);
Rva00899F00Base *aptGetChannels008B4700(Owner008B4700 *,int);
AptValue *aptApplyChannels008B4480(Owner008B4480 *,int);

extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int bytes);
class BfmeItemDX;
void bfmePush(BfmeItemDX *block);
extern "C" int __cdecl _strcmpi(const char *a,const char *b);
extern "C" void *bfmeVft1029A[];


class BfmeA1029
{
public:
	BfmeA1029 *bfmeGo1029A(int a);
	void bfmeBase1029(int n, int m);

	void	*m_bfmeVfptr;
	char	m_bfmePad[0x1c];
	int		m_bfmeVal;
};


class BfmeS1082
{
public:
	virtual void bfmeSlot1082S_0(void);
	virtual void bfmeSlot1082S_1(void);
};

extern BfmeS1082 *g_bfmeS1082_4;
extern BfmeS1082 *g_bfmeS1082_5;
extern BfmeS1082 *g_bfmeS1082_6;
extern BfmeS1082 *g_bfmeS1082_7;


struct BfmeCandidateDataDX
{
	const void	*m_head;
	const void	*m_reserved;
	char		m_name[1];
};


struct BfmeCandidateDX
{
	const BfmeCandidateDataDX *m_tag;
};

#define g_bfmeCandidate0 g_Va013386A0
#define g_bfmeCandidate1 g_Va01338594
#define g_bfmeCandidate2 g_Va013385A4
#define g_bfmeCandidate3 g_Va013386AC
extern BfmeCandidateDX g_bfmeCandidate0;
extern BfmeCandidateDX g_bfmeCandidate1;
extern BfmeCandidateDX g_bfmeCandidate2;
extern BfmeCandidateDX g_bfmeCandidate3;

// ?bfmeSetRegisteredFlag@@YAXPAVBfmeS1082@@@Z absent-from-retail
static void bfmeSetRegisteredFlag(BfmeS1082 *obj)
{
	unsigned int *bits = (unsigned int *)((char *)obj + 4);
	*bits = (*bits & 0xffffc07f) | 0x40;
}


// ?bfmeSameCandidate@@YA_NPBUBfmeCandidateDataDX@@0@Z absent-from-retail
static __forceinline bool bfmeSameCandidate(const BfmeCandidateDataDX *x, const BfmeCandidateDataDX *y)
{
	int result = x == y ? 0 : _strcmpi(x->m_name, y->m_name);
 return !result;
}



class Rva00897670HeaderedDelete { public: static void operator delete(void *,unsigned); };
class Rva00899FC0 : public BfmeA1029, public Rva00897670HeaderedDelete
{
public:
	static void *operator new(unsigned int n)
	{
		char *raw = (char *)Rva008C5D70Alloc(n + 8);
		char *block = raw + 8;
		bfmePush((BfmeItemDX *)block);
		return block;
	}


	Rva00899FC0(int value)
	{
		bfmeBase1029(9, 8);
		m_bfmeVfptr = bfmeVft1029A;
		m_bfmeVal = value;
	}
};

typedef Rva00899FC0 BfmeCandidateSingleton0;

class Rva01136AB8Owner
{
public:
	void *Rva008B4DA0(void *unused, const BfmeCandidateDX *desc);
};


// Open BFME 2: Code/Libraries/Source/Apt/AptObject/AptFactoryConstructors.cpp
// ?Rva008B4DA0@Rva01136AB8Owner@@QAEPAXPAXPBUBfmeCandidateDX@@@Z
void *Rva01136AB8Owner::Rva008B4DA0(void *unused, const BfmeCandidateDX *desc)
{
	if (bfmeSameCandidate(desc->m_tag, g_bfmeCandidate0.m_tag))
	{
		if (g_bfmeS1082_4 == 0)
		{
			g_bfmeS1082_4 = (BfmeS1082 *)new BfmeCandidateSingleton0((int)&aptSetPackedChannels008B4370);
			bfmeSetRegisteredFlag(g_bfmeS1082_4);
			g_bfmeS1082_4->bfmeSlot1082S_0();
		}
		return g_bfmeS1082_4;
	}
	if (bfmeSameCandidate(desc->m_tag, g_bfmeCandidate1.m_tag))
	{
		if (g_bfmeS1082_5 == 0)
		{
			g_bfmeS1082_5 = (BfmeS1082 *)new BfmeCandidateSingleton0((int)&aptPackedChannels008B4420);
			bfmeSetRegisteredFlag(g_bfmeS1082_5);
			g_bfmeS1082_5->bfmeSlot1082S_0();
		}
		return g_bfmeS1082_5;
	}
	if (bfmeSameCandidate(desc->m_tag, g_bfmeCandidate2.m_tag))
	{
		if (g_bfmeS1082_6 == 0)
		{
			g_bfmeS1082_6 = (BfmeS1082 *)new BfmeCandidateSingleton0((int)&aptGetChannels008B4700);
			bfmeSetRegisteredFlag(g_bfmeS1082_6);
			g_bfmeS1082_6->bfmeSlot1082S_0();
		}
		return g_bfmeS1082_6;
	}
	if (bfmeSameCandidate(desc->m_tag, g_bfmeCandidate3.m_tag))
	{
		if (g_bfmeS1082_7 == 0)
		{
			g_bfmeS1082_7 = (BfmeS1082 *)new BfmeCandidateSingleton0((int)&aptApplyChannels008B4480);
			bfmeSetRegisteredFlag(g_bfmeS1082_7);
			g_bfmeS1082_7->bfmeSlot1082S_0();
		}
		return g_bfmeS1082_7;
	}
	return 0;
}
