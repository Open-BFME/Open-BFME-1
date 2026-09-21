// ?rva003c12a0@Gen_003C12A0Owner@@QAEXPAVGen_003C12A0Iface@@@Z
// partial score=0.38 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x003C12A0, 443 bytes. This body operates on the same
// _STL::list<T> at this+0xC0 that the sized-list constructor at 0x003C15C0
// (Rva003C15C0LivingWorldListCtor.cpp, "neutral physical owner at 0x003C2FC0
// loads this+0xC0") builds: same 12-byte payload {wide StringBase handle,
// int, int(=3 default)}, same circular sentinel walk shape counted here via
// _STL::distance(begin(),end()) for size(). No owner class identity (not
// LivingWorldLogic, not proven) is claimed -- only the +0xC0 list member and
// its element shape are read out of the retail bytes, matching the sibling.
//
// The single stack argument (thiscall, ret 4) is a pointer to an interface
// with unresolved virtuals; only the vtable slots this body actually calls
// are named (by offset), the rest are unused placeholders that exist purely
// to keep later slots at the right index. Call shapes read out of the bytes:
//   slot01 (vtbl+4):  bool ()                          -- gates rebuild vs report
//   slot09 (vtbl+0x24): void (int *, int)               -- pushed (ptr, 4)
//   slot25 (vtbl+0x64): void (Rva003C12A0Element *)      -- fills text+word4+word8
//   slot30 (vtbl+0x78): void (int *)                     -- in/out int, called twice
//
// When slot01() is true: the list is cleared (thunk 0x0002AF95 -> 0x003C0060,
// pinned _List_base<Gen_t_003c0c70_p12cd>::clear -- same 12-byte
// nontrivial-dtor payload shape) and rebuilt with `count` (size(), possibly
// updated in place by the first slot30 call) freshly-constructed elements.
// When false: the existing elements are left untouched but each one's copy is
// still round-tripped through slot25/slot30/slot09 (a "report existing
// entries" pass), matching the retail second block at +0x13e.

#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"
#include <list>

class UnicodeString
{
public:
	UnicodeString() : m_text(0) {}
	UnicodeString(const UnicodeString &that)
	{
		((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(
			*(const StringBase<wchar_t> *)&that);
	}
	~UnicodeString()
	{
		((StringBase<wchar_t> *)this)->releaseBuffer();
	}

private:
	void *m_text;
};

struct Rva003C12A0Element
{
	UnicodeString m_text;
	int m_word4;
	int m_word8;

	Rva003C12A0Element()
		: m_text()
		, m_word4(0)
		, m_word8(3)
	{
	}

	~Rva003C12A0Element() {}
};

bool operator==(const Rva003C12A0Element &, const Rva003C12A0Element &);
bool operator<(const Rva003C12A0Element &, const Rva003C12A0Element &);

class Gen_003C12A0Iface
{
public:
	virtual void slot00();
	virtual bool slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09(int *value, int tag);
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
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25(Rva003C12A0Element *elem);
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30(int *value);
};

class Gen_003C12A0Owner
{
public:
	void rva003c12a0(Gen_003C12A0Iface *iface);

private:
	unsigned char m_unmodelled00[0xC0];
	_STL::list<Rva003C12A0Element> m_list;
};

// ?rva003c12a0@Gen_003C12A0Owner@@QAEXPAVGen_003C12A0Iface@@@Z
void Gen_003C12A0Owner::rva003c12a0(Gen_003C12A0Iface *iface)
{
	int count = (int)m_list.size();
	iface->slot30(&count);
	bool proceed = iface->slot01();

	if (proceed)
	{
		m_list.clear();
		for (int i = 0; i < count; ++i)
		{
			Rva003C12A0Element tmp;
			iface->slot25(&tmp);
			iface->slot30(&tmp.m_word4);
			int extra;
			iface->slot09(&extra, 4);
			m_list.push_back(tmp);
		}
		return;
	}

	_STL::list<Rva003C12A0Element>::iterator it = m_list.begin();
	_STL::list<Rva003C12A0Element>::iterator end = m_list.end();
	for (; it != end; ++it)
	{
		Rva003C12A0Element tmp2(*it);
		iface->slot25(&tmp2);
		iface->slot30(&tmp2.m_word4);
		int extra2;
		iface->slot09(&extra2, 4);
	}
}
