// cl: /DNDEBUG /MD /EHsc
// Address-derived Glo012F1024Type indexed entry selection at retail 0x003B39C0.

class AsciiString;
class Glo012F1024Item;

class Glo012F1024Entry
{
public:
	Glo012F1024Item *select(AsciiString *key);

	char m_bfmeBody[0x20];
};

class BfmeEntryVector
{
public:
	int bfmeSize(void) const { return (int)(m_bfmeFinish - m_bfmeStart); }

	Glo012F1024Entry *m_bfmeStart;
	Glo012F1024Entry *m_bfmeFinish;
};

class Glo012F1024Type
{
public:
	Glo012F1024Item *selectEntry(AsciiString *key);

private:
	char m_pad00[0x0C];
	int m_bfmeIndex;
	BfmeEntryVector m_bfmeEntries;
};

// ?selectEntry@Glo012F1024Type@@QAEPAVGlo012F1024Item@@PAVAsciiString@@@Z
Glo012F1024Item *Glo012F1024Type::selectEntry(AsciiString *key)
{
	if (m_bfmeIndex >= 0
		&& (unsigned int)m_bfmeIndex < (unsigned int)m_bfmeEntries.bfmeSize())
	{
		Glo012F1024Entry *start = m_bfmeEntries.m_bfmeStart;
		return start[m_bfmeIndex].select(key);
	}

	return 0;
}
