// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// BfmeSinkBL::bfmeSubmitBL is reached through ILT 0x00039333. The two report
// senders prove the name, count, and four BfmeBlobBL arguments. The body copies
// the four blocks into the sink record, then submits a by-value name and count.

struct Rva004488B0Block
{
	void *first;
	void *second;
	void *third;
};

class StringBaseNarrowBL
{
protected:
	StringBaseNarrowBL(const StringBaseNarrowBL &other);
	~StringBaseNarrowBL(void);

	char *m_bfmeNarrowBL;
};

class AsciiStringBL : public StringBaseNarrowBL
{
public:
	AsciiStringBL(const AsciiStringBL &other) : StringBaseNarrowBL(other)
	{
	}

	~AsciiStringBL(void)
	{
	}
};

class BfmeBlobBL
{
public:
	char m_bfmePadBBL[12];
};

class Rva004488B0FourBlockRecord
{
public:
	void copy(const Rva004488B0Block &a, const Rva004488B0Block &b,
		const Rva004488B0Block &c, const Rva004488B0Block &d);
	void rva004498d0(AsciiStringBL name, int count);
};

class BfmeSinkBL
{
public:
	void bfmeSubmitBL(AsciiStringBL name, int count, BfmeBlobBL *first,
		BfmeBlobBL *second, BfmeBlobBL *third, BfmeBlobBL *fourth);

private:
	char m_bfmePad[0x12c8];
	Rva004488B0FourBlockRecord m_bfmeRecord;
};

#pragma comment(linker, "/alternatename:?copy@Rva004488B0FourBlockRecord@@QAEXABURva004488B0Block@@000@Z=?j_0002825e@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva004498d0@Rva004488B0FourBlockRecord@@QAEXVAsciiStringBL@@H@Z=?j_00043603@@YAXXZ")

void BfmeSinkBL::bfmeSubmitBL(AsciiStringBL name, int count,
	BfmeBlobBL *first, BfmeBlobBL *second,
	BfmeBlobBL *third, BfmeBlobBL *fourth)
{
	m_bfmeRecord.copy(
		*(const Rva004488B0Block *)first,
		*(const Rva004488B0Block *)second,
		*(const Rva004488B0Block *)third,
		*(const Rva004488B0Block *)fourth);
	m_bfmeRecord.rva004498d0(name, count);
}
