// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x0049A540, 755 bytes through RET 0x10 at +0x2F0: slot 3 (+0x0C) of
// the six-slot table 0x010EDAD8 (reached only through ILT 0x0000CB2B). The
// table belongs to the object built by 0x003BD700 (UnicodeString at +4, int
// at +8); that object is the owner the matched BannerThingCounter::add
// (0x0049A8F0) runs on: this body binds `this` and a local counts record into
// the functor wrapper whose table 0x010FA348 (dir32:
// Rva0049A120FunctorSingleWrapper) has slot +4 = 0x0049AB20, the forwarder
// that calls add(counts, name, count). The method name keeps its address.
//
// The body gathers the counts of army m_at08 through TheGameLogic (ILT
// 0x00008AA8 -> the this+0x170 tail thunk 0x00383940 -> 0x00362760, which
// visits each army record with the functor), copies m_at04 into the first
// output string, clears the next two, and fills the fourth with the display
// names of unmatched templates (", " separated) followed by one
// "BANNERUI:SummaryUnitQuantity" line per banner entry with a positive count
// (singular label for one unit, plural label otherwise).
#include "ascii_string.h"
#include "unicode_string.h"

template <> inline bool StringBase<unsigned short>::isEmpty() const
{
	return !m_data || m_data->length == 0;
}
template <> inline void StringBase<unsigned short>::concat(const unsigned short *s)
{
	concat(s, wcslen(s));
}
template <> inline void StringBase<unsigned short>::concat(const StringBase<unsigned short> &s)
{
	const int n = s.m_data ? s.m_data->length : 0;
	const unsigned short *p = s.m_data ? s.m_data->data : (const unsigned short *)L"";
	concat(p, n);
}

inline UnicodeString::UnicodeString(const wchar_t *s)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(s);
}
inline UnicodeString::~UnicodeString()
{
	((StringBase<unsigned short> *)this)->releaseBuffer();
}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &s)
{
	((StringBase<unsigned short> *)this)->set(*(const StringBase<unsigned short> *)&s);
	return *this;
}
inline UnicodeString &UnicodeString::operator+=(const wchar_t *s)
{
	((StringBase<unsigned short> *)this)->concat(s);
	return *this;
}
inline UnicodeString &UnicodeString::operator+=(const UnicodeString &s)
{
	((StringBase<unsigned short> *)this)->concat(*(const StringBase<unsigned short> *)&s);
	return *this;
}

typedef int Int;
typedef bool Bool;

// Slot order as in the matched SkirmishScreenStateRva005294F0.cpp: the two
// fetch overloads land at +0x24 (AsciiString) and +0x28 (const char *).
class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;

class ThingTemplate
{
public:
	const UnicodeString &getDisplayName() const { return m_displayName; }

private:
	unsigned char m_unmodelled00[0x0c];
	UnicodeString m_displayName;
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern BfmeThingFactory *TheThingFactory;

// Banner entries as BannerThingCounterAdd.cpp lays them out (12 bytes, filter
// at +8); this body copies +0 or +4 as an AsciiString label.
struct BannerThingEntry
{
	AsciiString m_first;
	AsciiString m_second;
	Int m_filter;
};

class BannerThingEntryVector
{
public:
	BannerThingEntry *begin() { return m_begin; }
	unsigned size() { return (unsigned)(m_end - m_begin); }

private:
	BannerThingEntry *m_begin;
	BannerThingEntry *m_end;
};

class BannerUI
{
public:
	char m_fields[0x1c];
	Int m_defaultFilter;
	BannerThingEntryVector m_entries;
};
extern BannerUI *TheBannerUI;

// The counts record BannerThingCounter::add fills (its BannerThingCounts):
// unmatched template names, then one count per banner entry. Its constructor
// and destructor are the matched 0x0049A430 / 0x0049A4B0, reached through
// ILTs 0x0000F592 / 0x000327D6, and the ledger names them Gen_0049A4B0 (the
// constructor's one word is the entry count, declared there as a pointer).
class Gen_0049A4B0
{
public:
	Gen_0049A4B0(void *entryCount);
	~Gen_0049A4B0();

	AsciiString *m_unmatchedNames;
	AsciiString *m_unmatchedNamesEnd;
	AsciiString *m_unmatchedNamesCapacity;
	Int *m_counts;
	Int *m_countsEnd;
	Int *m_countsCapacity;
};

class BannerThingCounter;

// The single-inheritance functor wrapper of FunctorBindSingleWrapperCtors.cpp
// (reference count at +4, eight bound bytes at +8); for this table the bound
// words are the owner and the counts record.
struct FunctorBindingSingle
{
	BannerThingCounter *m_target;
	Gen_0049A4B0 *m_param;
};

class FunctorSingleWrapperHead
{
public:
	FunctorSingleWrapperHead() : m_refCount(0) {}
	virtual ~FunctorSingleWrapperHead();
	virtual void invoke(const AsciiString &name, Int count) = 0;

	// Retail keeps the wrapper in ECX across the store and deletes it with no
	// null test: the release is the wrapper's own inline member.
	void releaseReference()
	{
		if (--m_refCount <= 0)
			delete this;
	}

	Int m_refCount;
};

class Rva0049A120FunctorSingleWrapper : public FunctorSingleWrapperHead
{
public:
	Rva0049A120FunctorSingleWrapper(const FunctorBindingSingle &binding) : m_binding(binding) {}
	~Rva0049A120FunctorSingleWrapper();
	void invoke(const AsciiString &name, Int count);

	FunctorBindingSingle m_binding;
};

class Rva0049A2E0FunctorSingleHolder
{
public:
	Rva0049A2E0FunctorSingleHolder(const FunctorBindingSingle &binding)
	{
		m_ptr = new Rva0049A120FunctorSingleWrapper(binding);
		if (m_ptr != 0)
			m_ptr->m_refCount++;
	}
	~Rva0049A2E0FunctorSingleHolder()
	{
		if (m_ptr != 0)
			m_ptr->releaseReference();
	}

	Rva0049A120FunctorSingleWrapper *m_ptr;
};

// TheGameLogic's member at 0x00383940 (ILT 0x00008AA8): `add ecx,0x170; jmp
// 0x00362760`, which walks the army records of `index` and calls the visitor
// for each (identity_evidence/0x00383940-tail-thunk-two-arguments.md).
class Rva00383940
{
public:
	void invoke(Int index, void *item);
};
class GameLogic;
extern GameLogic *TheGameLogic;

class BannerThingCounter
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void rva0049A540(UnicodeString *nameOut, UnicodeString *clearedA, UnicodeString *clearedB,
		UnicodeString *summaryOut);
	virtual void slot10();
	virtual void slot14();

private:
	UnicodeString m_at04;
	Int m_at08;
};

void BannerThingCounter::rva0049A540(UnicodeString *nameOut, UnicodeString *clearedA, UnicodeString *clearedB,
	UnicodeString *summaryOut)
{
	Gen_0049A4B0 counts((void *)TheBannerUI->m_entries.size());
	{
		FunctorBindingSingle binding;
		binding.m_target = this;
		binding.m_param = &counts;
		Rva0049A2E0FunctorSingleHolder visitor(binding);
		reinterpret_cast<Rva00383940 *>(TheGameLogic)->invoke(m_at08, &visitor);
	}

	*nameOut = m_at04;
	((StringBase<unsigned short> *)clearedA)->clear();
	((StringBase<unsigned short> *)clearedB)->clear();
	((StringBase<unsigned short> *)summaryOut)->clear();

	if (counts.m_unmatchedNames != counts.m_unmatchedNamesEnd)
	{
		Int nameCount = counts.m_unmatchedNamesEnd - counts.m_unmatchedNames;
		for (Int i = 0; i < nameCount; ++i)
		{
			const AsciiString &name = counts.m_unmatchedNames[i];
			const ThingTemplate *thing = TheThingFactory->findTemplate(name);
			if (!summaryOut->isEmpty())
				*summaryOut += L", ";
			*summaryOut += thing->getDisplayName();
		}
	}

	Int entryCount = counts.m_countsEnd - counts.m_counts;
	for (Int index = 0; index < entryCount; ++index)
	{
		Int count = counts.m_counts[index];
		if (count > 0)
		{
			const BannerThingEntry &entry = TheBannerUI->m_entries.begin()[index];
			UnicodeString line = TheGameText->fetch("BANNERUI:SummaryUnitQuantity");
			line.format(line.str(), TheGameText->fetch(count == 1 ? entry.m_first : entry.m_second).str());
			line.format(line.str(), count);
			if (!summaryOut->isEmpty())
				*summaryOut += L"\n";
			*summaryOut += line;
		}
	}
}
