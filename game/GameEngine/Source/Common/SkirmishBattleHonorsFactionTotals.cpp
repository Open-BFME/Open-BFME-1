// cl: /DNDEBUG /MD /EHsc

// FILE: SkirmishBattleHonorsFactionTotals.cpp
// One SkirmishBattleHonors reader that adds the recorded wins of the four
// BFME sides together.  It keeps a single AsciiString local, rewrites it with
// set() before each lookup and hands a copy to getWins, which is why retail
// builds one string, calls set four times and releases it once.
//
// The side names are the literals at 0x010804D8, 0x010804D0, 0x010804C4 and
// 0x010804BC, read in that order: Gondor, Rohan, Isengard, Mordor.
//
// Retail adds Isengard into the Rohan count, then adds Gondor to that sum,
// then adds Mordor last, and it keeps the Gondor count in ebx across the
// first three calls.  Writing the Gondor step as its own named sum is what
// reproduces that.  Folding it into one four-term expression makes MSVC add
// Isengard and Gondor together first, which costs the same instructions in
// the other order.

typedef int Int;

template <class Type>
class StringBase
{
public:
	void set(const char *s, int len);

private:
	StringBase(const StringBase &that);
	~StringBase();
	friend class AsciiString;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() { m_text = 0; }

	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
	}

	~AsciiString()
	{
		((StringBase<char> *)this)->~StringBase();
	}

	void set(const char *s, int len)
	{
		((StringBase<char> *)this)->set(s, len);
	}

private:
	void *m_text;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SkirmishBattleHonors.h
// getWins is the landed body at 0x0009C650; BFME takes the side name where
// Zero Hour's getWins takes nothing.
class SkirmishBattleHonors
{
public:
	Int getWins(AsciiString name) const;
	Int rva0009c6f0() const;
};

// @?rva0009c6f0@SkirmishBattleHonors@@QBEHXZ 0x0009C6F0
Int SkirmishBattleHonors::rva0009c6f0() const
{
	AsciiString name;

	name.set("Gondor", 6);
	Int gondor = getWins(name);

	name.set("Rohan", 5);
	Int subtotal = getWins(name);

	name.set("Isengard", 8);
	subtotal += getWins(name);
	Int total = subtotal + gondor;

	name.set("Mordor", 6);
	return total + getWins(name);
}
