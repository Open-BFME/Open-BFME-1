// cl: /O2 /MD /DNDEBUG
// Two-table key lookup walked up the object chain (retail 0x008ACCF0, 203 B).
// Shape follows BFME 2 Code/Libraries/Source/Apt/Rva006ED490Walk.cpp (rev 2bac16a6):
// one counter serves both table scans, and no dead first-count local. Its only caller
// is the Apt dispatch at 0x008AE490 (direct rel32 call). Handoff:
// targets/game/reverse/attempt_support/20261110-008accf0-shared-counter.md

// Retail 009F6FA0 jumps through the MSVCR71._strcmpi IAT slot.
extern "C" int __cdecl _strcmpi(const char *a, const char *b);

struct BfmeLookupString008ACCF0Header
{
	char m_padding00[8];
	char m_text[1];
};

struct BfmeLookupString008ACCF0
{
	BfmeLookupString008ACCF0Header *m_header;
	bool matches(const char *p) const { return _strcmpi(m_header->m_text, p) == 0; }
};

struct BfmeLookupTableView008ACCF0
{
	char m_padding00[0x10];
	int *m_resultValues;
	char m_padding14[0x0C];
	int m_secondCount;
	int *m_secondValues;
	int m_firstCount;
	int *m_firstValues;
};

struct BfmeLookupTableHolder008ACCF0
{
	char m_padding00[4];
	char *m_table;
};

struct BfmeLookupOwner008ACCF0
{
	char m_padding00[0x0C];
	BfmeLookupTableHolder008ACCF0 *m_holder;
};

struct BfmeLookupObject008ACCF0
{
	char m_padding00[0x4C];
	BfmeLookupObject008ACCF0 *m_next;
	BfmeLookupOwner008ACCF0 *m_owner;
};

int bfmeLookup008ACCF0(BfmeLookupObject008ACCF0 *object,
	BfmeLookupString008ACCF0 *key, unsigned char include)
{
	BfmeLookupString008ACCF0 *needle = key;
	unsigned char useSecond = include;
	for (;;)
	{
		BfmeLookupTableView008ACCF0 *view = (BfmeLookupTableView008ACCF0 *)
			((char *)object->m_owner->m_holder->m_table + 8);
		int i;
		for (i = 0; i < view->m_firstCount; ++i)
		{
			if (needle->matches((const char *)view->m_firstValues[i * 2]))
				return view->m_resultValues[view->m_firstValues[i * 2 + 1]];
		}

		if (useSecond != 0)
		{
			i = 0;
			if (view->m_secondCount > 0)
			{
				do
				{
					if (needle->matches((const char *)view->m_secondValues[i * 4 + 1]))
						return view->m_resultValues[view->m_secondValues[i * 4 + 2]];
					++i;
				} while (i < view->m_secondCount);
			}
		}

		BfmeLookupObject008ACCF0 *next = object->m_next;
		if (next == 0)
			return 0;
		useSecond = 0;
		object = next;
	}
}
