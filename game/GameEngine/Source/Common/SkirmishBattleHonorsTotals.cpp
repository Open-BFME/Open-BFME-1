// cl: /DNDEBUG /MD /EHsc

// SkirmishBattleHonors totals across the four BFME factions.

typedef int Int;


template <class Type>
class StringBase
{
private:
	void set(const Type *text, int length);
	StringBase(const StringBase &other);
	~StringBase();
	friend class AsciiString;
};

class AsciiString
{
public:
	AsciiString() : m_text(0) {}

	void set(const char *text, int length)
	{
		((StringBase<char> *)this)->set(text, length);
	}

	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}

	~AsciiString()
	{
		((StringBase<char> *)this)->~StringBase();
	}

private:
	void *m_text;
};

class SkirmishBattleHonors
{
public:
	Int getWins(AsciiString side) const;
	Int getLosses(AsciiString side) const;
	Int getLosses(void) const;
};

Int SkirmishBattleHonors::getLosses(void) const
{
	AsciiString side;
	Int total = 0;
	side.set("Gondor", 6);
	total += getLosses(side);

	side.set("Rohan", 5);
	total += getLosses(side);
	side.set("Isengard", 8);
	total += getLosses(side);
	side.set("Mordor", 6);
	total += getLosses(side);

	return total;
}
