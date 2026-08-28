// cl: /DNDEBUG /MD /EHsc
// readable body of ??1MemoryPool@@: Code/GameEngine/Source/Common/System/GameMemory.cpp

// Open-BFME5: MemoryPool's destructor, retail 0x001F84C0, 115 bytes. The body
// carried only a machine byte-dump row; the symbols.csv pin names it, and the
// two members it calls on the AI sub-object are pinned with this row.
//
// A flag at +0x3C guards the whole thing -- a pool that was never opened does
// nothing at all. Otherwise six slots at +0x24 are walked. A live slot whose
// own flag at +0x48 is set and whose kind at +0x60 is one of four values is
// first dropped from the sub-object at +0x0C of _TheAIParseDefinitionAI, then
// deleted through slot 0 of its table and the slot cleared. The slot is re-read
// between the two, so the drop is allowed to have changed it.
//
// After the loop the same sub-object is flushed once and the flag comes down.

typedef int Int;

class BfmePoolEntry
{
public:
	virtual ~BfmePoolEntry();				// slot 0

	char m_bfmeHeadA[0x48 - 0x04];
	bool m_bfmeTracked;					// +0x48
	char m_bfmeHeadB[0x60 - 0x49];
	Int m_bfmeKind;						// +0x60
};

class Rva003D8530Owner
{
public:
	void bfmeDrop(void *entry);				// ILT 0x00016DB0
	void bfmeFlush(void);					// ILT 0x00009787
};

class BfmeAIRoot
{
public:
	char m_bfmeHead[0x0C];
	Rva003D8530Owner *m_bfmeOwner;				// +0x0C
};

extern "C" BfmeAIRoot *TheAIParseDefinitionAI;			// 0x012EF214

class MemoryPool
{
public:
	~MemoryPool();

private:
	char m_bfmeHead[0x24];
	BfmePoolEntry *m_bfmeSlots[6];				// +0x24
	bool m_bfmeOpen;					// +0x3C
};

// ??1MemoryPool@@QAE@XZ
MemoryPool::~MemoryPool()
{
	if (!m_bfmeOpen)
		return;

	for (Int i = 0; i < 6; ++i)
	{
		BfmePoolEntry *entry = m_bfmeSlots[i];

		if (entry)
		{
			if (entry->m_bfmeTracked)
			{
				Int kind = entry->m_bfmeKind;

				if (kind == 1 || kind == 2 || kind == 3 || kind == 4)
					TheAIParseDefinitionAI->m_bfmeOwner->bfmeDrop(entry);
			}

			delete m_bfmeSlots[i];

			m_bfmeSlots[i] = 0;
		}
	}

	TheAIParseDefinitionAI->m_bfmeOwner->bfmeFlush();

	m_bfmeOpen = false;
}
