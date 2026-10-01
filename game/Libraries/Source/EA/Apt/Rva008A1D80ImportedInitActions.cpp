// Retail 0x008A1D80 (102 bytes, thiscall, ret 8): scans the owner's +0x04
// entry list for the first type-8 entry carrying the given key, runs that
// entry's action stream on the Apt interpreter with the caller's argument
// (the same BfmeR1226::bfmeAdd1226 / bfmeLine1226 pair BfmeConv1226.cpp
// uses) under the "Imported Init Actions" label, then negates the entry's
// key so it cannot fire again.  No named caller reaches it, so the owner
// keeps the address.

class BfmeR1226
{
public:
	void bfmeAdd1226(void *a, void *b, int c);
	void bfmeLine1226(char *a);
};

// Retail's object at 0x01338748 is the Apt stack, defined by Rva00C6DCC0StaticInit.cpp
// as `struct Rva008AE770Stack` and exported as ?Rva008AE770TheStack@@3U....  MSVC 7.1
// mangles a global's class type 3V for `class` but 3U for `struct`, so the global is
// declared under its defining type.  The members called here
// (?bfmeAdd1226@BfmeR1226@@ / ?bfmeLine1226@BfmeR1226@@, retail 0x008CCED0 and
// 0x008A0F40) are retail's own names for them, so the object is still reached through
// the BfmeR1226 view and only the address-of spelling changes.
struct Rva008AE770Stack;
extern struct Rva008AE770Stack Rva008AE770TheStack;

struct Rva008A1D80Entry
{
	int m_type;
	int m_key;
	void *m_stream;
};

struct Rva008A1D80List
{
	int m_count;
	Rva008A1D80Entry **m_entries;
};

class Rva008A1D80Owner
{
public:
	void runImportedInitActions(void *arg, int key);

	int m_bfme00;
	Rva008A1D80List *m_list;
};

void Rva008A1D80Owner::runImportedInitActions(void *arg, int key)
{
	for (int i = 0; i < m_list->m_count; ++i)
	{
		Rva008A1D80Entry *entry = m_list->m_entries[i];
		if (entry->m_type == 8 && entry->m_key == key)
		{
			((BfmeR1226 *)&Rva008AE770TheStack)->bfmeAdd1226(m_list->m_entries[i]->m_stream, arg, -1);
			((BfmeR1226 *)&Rva008AE770TheStack)->bfmeLine1226("Imported Init Actions");
			entry->m_key = -entry->m_key;
			return;
		}
	}
}
