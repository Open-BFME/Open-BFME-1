// ?bfmeLookup008ACCF0@@YAHPAUBfmeLookupObject008ACCF0@@PAUBfmeLookupString008ACCF0@@E@Z
// partial score=0.55 date=2026-09-03
// Open-BFME5 conversion.

int bfmeCompareVSC(const char *a, const char *b);

struct BfmeLookupString008ACCF0Header
{
	char m_padding00[8];
	char m_text[1];
};

struct BfmeLookupString008ACCF0
{
	BfmeLookupString008ACCF0Header *m_header;
};

struct BfmeLookupTable008ACCF0
{
	char m_padding00[0x18];
	int *m_resultValues;
	char m_padding1c[0x0C];
	int m_secondCount;
	int *m_secondValues;
	int m_firstCount;
	int *m_firstValues;
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
	BfmeLookupTable008ACCF0 *m_table;
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
	register unsigned char useSecond = include;
	for (;;)
	{
		BfmeLookupTable008ACCF0 *table = object->m_owner->m_holder->m_table;
		int firstCount = table->m_firstCount;
		BfmeLookupTableView008ACCF0 *view =
			(BfmeLookupTableView008ACCF0 *)((char *)table + 8);
		int i = 0;
		if (firstCount > 0)
		{
			do
			{
				if (bfmeCompareVSC((const char *)view->m_firstValues[i * 2],
					(const char *)((char *)needle->m_header + 8)) == 0)
					return view->m_resultValues[view->m_firstValues[i * 2 + 1]];
				++i;
			} while (i < view->m_firstCount);
		}

		if (useSecond != 0)
		{
			int j = 0;
			if (view->m_secondCount > 0)
			{
				do
				{
					if (bfmeCompareVSC((const char *)view->m_secondValues[j * 4 + 1],
						(const char *)((char *)needle->m_header + 8)) == 0)
						return view->m_resultValues[view->m_secondValues[j * 4 + 2]];
					++j;
				} while (j < view->m_secondCount);
			}
		}

		object = object->m_next;
		if (object == 0)
			return 0;
	}
}
