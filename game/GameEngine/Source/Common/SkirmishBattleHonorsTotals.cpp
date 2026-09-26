// cl: /DNDEBUG /MD /EHsc

// SkirmishBattleHonors totals across the four BFME factions.

typedef int Int;

extern char g_bfmeSideNameA1294[];
extern char g_bfmeSideNameB1294[];
extern char g_bfmeSideNameC1294[];
extern char g_bfmeSideNameD1294[];

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
	side.set(g_bfmeSideNameA1294, 6);
	total += getLosses(side);

	side.set(g_bfmeSideNameB1294, 5);
	total += getLosses(side);
	side.set(g_bfmeSideNameD1294, 8);
	total += getLosses(side);
	side.set(g_bfmeSideNameC1294, 6);
	total += getLosses(side);

	return total;
}
