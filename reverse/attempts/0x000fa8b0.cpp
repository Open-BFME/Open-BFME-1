// ?findIndex@Rva000FA8B0List@@QAEHPAVRva000FA8B0Query@@H@Z
// partial score=0.2 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME5: retail 0x000FA8B0 (188B).
// Scans a 0x60-byte-stride record list bounded by [this+4]/[this+8] (the
// same begin/end shape as the landed Rva000FA830PortraitList neighbour,
// Rva000FA830PortraitEntry.cpp) for a counted-string name match (decoded
// the same way as Rva006A16B0Empty's other call sites: m_data ? data+8 :
// the shared empty string, length word at m_data+4) plus an optional key,
// returning the matching record's index or -1. Owner is address-derived:
// this exact 0x60-stride/0x3C-key shape also reaches AIPlayer::findFactory
// and two still-carved dumps, which does not fit a portrait-only identity,
// so the record/list layout below models only the bytes this body proves
// and does not claim the PortraitList class.
//
// PARTIAL: retail inlines every comparison (memcmp with a runtime length
// compiles to rep cmpsb here too; no real CALL anywhere in this body) and
// this source reproduces that, the shared-tail control flow (empty-list and
// loop-exhausted both fall into one `return -1`), and the signed length
// compare (jl, matched once entryLen/queryLen were plain `int` locals
// instead of `unsigned short`). The remaining residue is pure register
// allocation: retail keeps the entry cursor in eax (caller-saved, free
// because nothing in the body makes a real call) the whole function, while
// this source's compile keeps choosing ebx (callee-saved, pushed up front)
// for the same role, which changes the encoding of nearly every
// instruction even though the instruction sequence is otherwise the same
// shape. Tried plain/char* cursor typing and a `register` hint; neither
// changed the allocation. Best score: 38/188 matching bytes (0.20).

extern "C" int memcmp(const void *, const void *, unsigned int);
extern const char Rva006A16B0Empty[];

class Rva000FA8B0Entry
{
public:
	void *m_namePtr;
	char m_pad1[0x3c - 4];
	int m_key;
	char m_pad2[0x60 - 0x40];
};

class Rva000FA8B0Query
{
public:
	char m_pad[0x20];
	void *m_namePtr;
};

class Rva000FA8B0List
{
	void *m_vtable;
	Rva000FA8B0Entry *m_begin;
	Rva000FA8B0Entry *m_end;

public:
	int findIndex(Rva000FA8B0Query *query, int key);
};

int Rva000FA8B0List::findIndex(Rva000FA8B0Query *query, int key)
{
	Rva000FA8B0Entry *cur = m_begin;
	Rva000FA8B0Entry *end = m_end;
	int index = 0;
	if (cur != end)
	{
		void *queryName = query->m_namePtr;
		do
		{
			int queryLen = queryName ? *(unsigned short *)((char *)queryName + 4) : 0;
			const char *queryData = queryName ? (const char *)queryName + 8 : Rva006A16B0Empty;

			void *entryName = cur->m_namePtr;
			int entryLen = entryName ? *(unsigned short *)((char *)entryName + 4) : 0;
			const char *entryData = entryName ? (const char *)entryName + 8 : Rva006A16B0Empty;

			int minLen = entryLen < queryLen ? entryLen : queryLen;
			if (memcmp(entryData, queryData, minLen) == 0 && entryLen == queryLen)
			{
				if (key == -1 || key == cur->m_key)
					return index;
			}
			++index;
			cur = (Rva000FA8B0Entry *)((char *)cur + 0x60);
		} while (cur != end);
	}
	return -1;
}
