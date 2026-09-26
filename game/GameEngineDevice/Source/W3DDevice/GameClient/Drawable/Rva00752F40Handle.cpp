// cl: /O2 /Ob2 /GR- /EHsc /MD /DNDEBUG

typedef int Int;

class GameLODLevelState00752F40
{
public:
	char m_pad[0x170c];
	Int m_level;
};

extern GameLODLevelState00752F40 *TheGameLODManager;
extern Int GetGameClientRandomValue(Int low, Int high, char *file, Int line);

struct Gen00752F40Row
{
	Int m_value;
	Int m_pad[4];
};

class Gen00752F40
{
public:
	Int handle(Int upperBound);

private:
	char m_pad[0x16c];
	Gen00752F40Row m_rows[3];
};

__forceinline Int gen00752F40Scale(Int value, const Gen00752F40Row &row)
{
	return value * row.m_value;
}

Int Gen00752F40::handle(Int upperBound)
{
	Int level = TheGameLODManager->m_level - 1;

	if (level < 0)
		level = 0;
	else if (level > 2)
		level = 2;

	return m_rows[level].m_value * GetGameClientRandomValue(0, upperBound - 1,
		(char *)0x011225a8, 0x272) / 100;
}
