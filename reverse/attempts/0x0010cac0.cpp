// ?d_0010cac0@@YAXPAURva0010CAC0Param@@@Z
// partial score=0.25 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef bool Bool;
typedef int Int;
#define NULL 0
#define TRUE true
#define FALSE false

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
extern "C" __declspec(dllimport) void __stdcall Rva01358E54(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() { m_text = 0; }
	~AsciiString();

private:
	char *m_text;
};

// alias of ??0?$StringBase@D@@AAE@ABV0@@Z (0x00887B60)
class GameSpyGroupRoom
{
public:
	GameSpyGroupRoom(const GameSpyGroupRoom &other);

private:
	void *m_item;
};

// alias of ?releaseBuffer@?$StringBase@D@@AAEXXZ (0x00887940)
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	char *m_data;
};

class Counted
{
public:
	void *vtable;
	long m_refCount;
};

class CountedPtr
{
public:
	void bind(const AsciiString &name);

	Counted *m_ptr;
};

struct Rva0010CAC0Param
{
	Counted *m_head;
	void *m_field04;
};

// address-derived: caller/owner unidentified; body ports GameSpyGroupRoom /
// BFMERetailAsciiString / CountedPtr::bind construction observed in the retail
// disassembly at 0x0010CAC0 (dump d_00104e40.asm)
void d_0010cac0(Rva0010CAC0Param *param)
{
	Counted *head = param->m_head;

	if (head)
		InterlockedIncrement(&head->m_refCount);

	const GameSpyGroupRoom *src = head
		? (const GameSpyGroupRoom *)((char *)head + 8)
		: (const GameSpyGroupRoom *)0x01336E50;

	GameSpyGroupRoom room(*src);
	(void)room;

	AsciiString name;
	{
		BFMERetailAsciiString empty((const char *)0x0107388B);
		(void)empty;
	}

	CountedPtr *eventInfo = (CountedPtr *)param;
	eventInfo->bind(name);

	if (head)
		Rva01358E54(&head->m_refCount);
}
