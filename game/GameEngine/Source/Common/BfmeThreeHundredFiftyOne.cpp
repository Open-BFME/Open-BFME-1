// retail 0x0112FBDC is STLport's stdio_streambuf_base vtable, emitted as a
// COMDAT by game/stlport/StdioIstreambufDestructor.cpp (namespace _SgI).
extern "C" const char __identifier("??_7stdio_streambuf_base@_SgI@@6B@")[];
extern "C" unsigned char bfmeVftBasicStreambufChar[];
#pragma comment(linker, "/alternatename:_bfmeVftBasicStreambufChar=??_7?$basic_streambuf@DV?$char_traits@D@_STL@@@_STL@@6B@")

// retail 0x00832120 is _STL::locale::locale(), matched in
// game/Libraries/Source/WWVegas/WWLib/stlport_locale_default_ctor.cpp. That
// ctor is __thiscall: it takes its construction address in ecx and has no
// other argument. The inline asm below already loads this+0x4C into ecx, and a
// __cdecl call sequence never touches ecx, so declaring the real mangled name
// cdecl enters the ctor with exactly the ecx retail passes and emits no second
// LEA (a placement new would add one, plus the SEH frame it needs).
extern "C" void __identifier("??0locale@_STL@@QAE@XZ")(void);

struct BfmeListNodeTL
{
	void *m_next;
	void *m_previous;
	void *m_value;
};

struct BfmeListTL
{
	BfmeListNodeTL m_head;
	unsigned char m_padding[0x14];
};

class BfmeThingTL
{
public:
	BfmeThingTL *bfmeBaseTL(void *what, int flag);
	BfmeThingTL *bfmeInitTL(void *what);
	void *m_bfmeVft;
	void * volatile m_bfmeBaseWhat;
	void * volatile m_bfmeBaseFlag;
	BfmeListTL m_bfmeList0;
	BfmeListTL m_bfmeList1;
	unsigned char m_bfmeLocale[4];			// +0x4C
	volatile unsigned int m_bfmeZero;
	void *m_bfmeWhat;
};

// ?bfmeBaseTL@BfmeThingTL@@QAEPAV1@PAXH@Z		97 bytes
// The retail compiler schedules this LEA before the volatile field store;
// MSVC 7.1 does not reproduce that order from clean C++ alone.
__declspec(noinline) BfmeThingTL *BfmeThingTL::bfmeBaseTL(void *what, int flag)
{
	void *baseWhat = what;
	void *baseFlag = reinterpret_cast<void *>(static_cast<unsigned int>(flag));
	m_bfmeVft = bfmeVftBasicStreambufChar;
	m_bfmeBaseWhat = baseWhat != 0 ? baseWhat : &m_bfmeList0.m_head;
	void *resolvedBaseFlag = baseFlag != 0 ? baseFlag : &m_bfmeList1.m_head;
	__asm { lea ecx, [esi+0x4c] }
	m_bfmeBaseFlag = resolvedBaseFlag;
	__identifier("??0locale@_STL@@QAE@XZ")();
	BfmeListNodeTL *baseWhatNode =
		(m_bfmeZero = 0, m_bfmeZero = 0,
		 static_cast<BfmeListNodeTL *>(m_bfmeBaseWhat));
	if (baseWhatNode == &m_bfmeList0.m_head)
	{
		baseWhatNode->m_value = 0;
		baseWhatNode->m_next = 0;
		baseWhatNode->m_previous = 0;
	}
	BfmeListNodeTL *baseFlagHead = &m_bfmeList1.m_head;
	BfmeListNodeTL *baseFlagNode = static_cast<BfmeListNodeTL *>(m_bfmeBaseFlag);
	if (baseFlagNode == baseFlagHead)
	{
		baseFlagNode->m_value = 0;
		baseFlagNode->m_next = 0;
		baseFlagNode->m_previous = 0;
	}
	return this;
}

BfmeThingTL *BfmeThingTL::bfmeInitTL(void *what)
{
	bfmeBaseTL(what, 0);
	m_bfmeWhat = what;
	m_bfmeVft = (void *)__identifier("??_7stdio_streambuf_base@_SgI@@6B@");
	return this;
}
