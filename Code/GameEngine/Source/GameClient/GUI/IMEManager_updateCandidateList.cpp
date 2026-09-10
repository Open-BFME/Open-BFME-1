// cl: /DNDEBUG /MD /EHsc
// IMEManager::updateCandidateList at retail 0x0048D5C0 (592 bytes).
// Matched openCandidateList(0x0048DCA0)+0x1C calls ILT 0x0000F27C
// directly to this body; ret 4 at 0x0048D80D ends at 0x0048D810.
// IMM32 imports are independently resolved from the PE IAT at
// VA 0x0135955C (CountW) and 0x01359560 (ListW).
//
// The BFME body is the Unicode IMM path from the Generals IME manager.  Its
// candidate fields are kept at their retail offsets: the context is +0x10,
// page start/size/selection/count are +0x3030/+0x3034/+0x3038/+0x303C, the
// UnicodeString array is +0x3040, and the candidate controls are +0x304C
// through +0x305C.

typedef unsigned int UnsignedInt;

void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *memory);

extern "C"
{
	unsigned long __stdcall ImmGetCandidateListCountW(
		void *context, unsigned long *listCount);
	unsigned long __stdcall ImmGetCandidateListW(
		void *context, unsigned long index, void *candidateList,
		unsigned long bufferSize);
	void *memset(void *destination, int value, unsigned int size);
}

template <typename Character>
class StringBase
{
	friend class UnicodeString;

private:
	void *m_data;

public:
	void set(const Character *text);
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString();
	~UnicodeString();

	void set(const unsigned short *text)
	{
		StringBase<unsigned short>::set(text);
	}
};

class GameWindow
{
public:
	int winHide(bool hide);
};

struct CANDIDATELIST
{
	unsigned long dwSize;
	unsigned long dwStyle;
	unsigned long dwCount;
	unsigned long dwSelection;
	unsigned long dwPageStart;
	unsigned long dwPageSize;
};

typedef char CandidateHeaderIs24[(sizeof(CANDIDATELIST) == 24) ? 1 : -1];
typedef char UnicodeStringIs4[(sizeof(UnicodeString) == 4) ? 1 : -1];

class IMEManager
{
public:
	void updateCandidateList(int candidateFlags);

private:
	char m_padding00[0x10];
	void *m_context;
	char m_padding14[0x301C];
	int m_pageStart;
	int m_pageSize;
	int m_selectedIndex;
	int m_candidateCount;
	UnicodeString *m_candidateString;
	char m_padding3044[8];
	GameWindow *m_candidateWindow;
	GameWindow *m_statusWindow;
	GameWindow *m_candidateTextArea;
	GameWindow *m_candidateUpArrow;
	GameWindow *m_candidateDownArrow;
};

// ?updateCandidateList@IMEManager@@QAEXH@Z
void IMEManager::updateCandidateList(int candidateFlags)
{
	if (m_candidateString)
	{
		delete [] m_candidateString;
		m_candidateString = 0;
	}

	m_pageSize = 10;
	m_candidateCount = 0;
	m_pageStart = 0;
	m_selectedIndex = 0;

	if (m_candidateWindow == 0 || m_context == 0 || candidateFlags == 0)
		return;

	int i = 0;
	unsigned int candidate = 1;
	for (; i < 32;
		i++, candidate = candidate << 1)
	{
		if (candidateFlags & candidate)
		{
			unsigned long listCount = 0;
			int size = ImmGetCandidateListCountW(m_context, &listCount);

			char *buffer = new char[size];
			if (buffer == 0)
			{
				return;
			}

			memset(buffer, 0, size);
			CANDIDATELIST *clist = (CANDIDATELIST *)buffer;
			int bytesCopied = ImmGetCandidateListW(
				m_context, i, clist, size);

			if (bytesCopied == 0 || bytesCopied > size)
			{
				delete [] buffer;
				return;
			}

			if (clist->dwStyle == 0 || clist->dwStyle == 2)
			{
				delete [] buffer;
				return;
			}

			if (clist->dwPageStart > clist->dwSelection ||
				clist->dwSelection >= clist->dwPageStart + clist->dwPageSize)
			{
				clist->dwPageStart =
					(clist->dwSelection / clist->dwPageSize) * clist->dwPageSize;
			}

			m_pageSize = clist->dwPageSize;
			m_candidateCount = clist->dwCount;
			m_pageStart = clist->dwPageStart;
			m_selectedIndex = clist->dwSelection;

			if (m_candidateUpArrow)
				m_candidateUpArrow->winHide(m_pageStart == 0);

			if (m_candidateDownArrow)
				m_candidateDownArrow->winHide(
					m_candidateCount - m_pageStart <= m_pageSize);

			if (m_candidateCount > 0)
			{
				m_candidateString = new UnicodeString[m_candidateCount];
				if (m_candidateString)
				{
					for (int j = 0; j < m_candidateCount; j++)
					{
						// dwCount offsets follow the fixed six-DWORD header.
						unsigned long *offsets = reinterpret_cast<unsigned long *>(clist + 1);
						char *string = buffer + offsets[j];
						m_candidateString[j].set((unsigned short *)string);
					}
				}
			}

			delete [] buffer;
			return;
		}
	}
}
