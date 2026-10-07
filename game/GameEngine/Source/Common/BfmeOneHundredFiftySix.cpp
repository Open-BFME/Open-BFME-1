// A reading chosen by the sort of thing asked about, a flag taken away with a
// side effect when it is the tenth one, and a search that marks the first cell
// carrying a given key.

struct BfmeSlotYX
{
	int m_bfmeFirst;			// 0x00
	int m_bfmeSecond;			// 0x04
	unsigned char m_bfmeBody[0x38];		// 0x08
};

struct BfmeItemYX
{
	unsigned char m_bfmeHead[8];		// 0x0
	int m_bfmeValue;			// 0x8
	int m_bfmeKind;				// 0xc
};

struct BfmeBoxYX
{
	BfmeItemYX *m_bfmeItem;			// 0x0
};

class BfmeThingYX
{
public:
	int bfmePickYX(BfmeBoxYX *box) const;

private:
	unsigned char m_bfmeHead[0xb44];	// 0x000
	BfmeSlotYX *m_bfmeTable;		// 0xb44
};

int BfmeThingYX::bfmePickYX(BfmeBoxYX *box) const
{
	BfmeItemYX *item = box->m_bfmeItem;

	switch (item->m_bfmeKind)
	{
		case 1:
			return item->m_bfmeValue;

		case 2:
			return m_bfmeTable[item->m_bfmeValue].m_bfmeSecond;

		case 4:
			return 0;
	}

	return 0;
}

class BfmeJobYY
{
public:
	unsigned char m_bfmeHead[0x34];		// 0x00
	int m_bfmeDelay;			// 0x34
	unsigned char m_bfmeState;		// 0x38
};

class BfmeThingYY
{
public:
	void bfmeClearYY(unsigned int bit);

private:
	unsigned char m_bfmeHead[0x68];		// 0x000
	BfmeJobYY *m_bfmeJob;			// 0x068
	unsigned char m_bfmeGap[0xa8];		// 0x06c
	unsigned int m_bfmeFlags;		// 0x114
};

void BfmeThingYY::bfmeClearYY(unsigned int bit)
{
	m_bfmeFlags &= ~bit;

	if (bit == 0x10)
	{
		BfmeJobYY *job = m_bfmeJob;

		if (job != 0)
		{
			job->m_bfmeDelay = 10;
			m_bfmeJob->m_bfmeState = 2;
		}
	}
}

// ScriptEngine::setSequentialTimer(Object *, Int) (retail 0x00339980, ILT
// 0x00044A1C; ilt_oracle CONFIRMED exact): the first sequential script whose
// object ID matches gets its frames-to-wait. TU-local layout view.
class Object
{
public:
	unsigned char m_bfmeHead[0x74];		// 0x00
	int m_bfmeID;				// 0x74
};

struct SequentialScript
{
	unsigned char m_bfmeHead[8];		// 0x00
	int m_objectID;				// 0x08
	unsigned char m_bfmeBody[0x14];		// 0x0c
	int m_framesToWait;			// 0x20
};

class ScriptEngine
{
public:
	void setSequentialTimer(Object *obj, int frameCount);

private:
	unsigned char m_bfmeHead[0xc];		// 0x00
	SequentialScript **m_bfmeBegin;		// 0x0c
	SequentialScript **m_bfmeEnd;		// 0x10
};

void ScriptEngine::setSequentialTimer(Object *obj, int frameCount)
{
	if (obj == 0)
		return;

	SequentialScript **end = m_bfmeEnd;
	int key = obj->m_bfmeID;
	SequentialScript **at = m_bfmeBegin;

	while (at != end)
	{
		SequentialScript *seq = *at;

		if (seq != 0 && seq->m_objectID == key)
		{
			seq->m_framesToWait = frameCount;
			return;
		}

		++at;
	}
}
