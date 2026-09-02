// cl: /DNDEBUG /MD
//
// Retail 0x006AAC20: thiscall returning a 9-byte pair-shaped result.  Calls
// grow(m_count+1) at +0x10 then a helper that fills a local {dword dword byte}
// and copies it to the hidden return slot.  Same outline as STLport
// hashtable::insert_unique (resize then insert_unique_noresize).

struct Rva006AAC20Iter
{
	int a;
	int b;
};

struct Rva006AAC20Result
{
	Rva006AAC20Iter first;
	char second;
	Rva006AAC20Result() {}
	Rva006AAC20Result(const Rva006AAC20Result &other)
		: first(other.first), second(other.second) {}
};

class Rva006AAC20
{
public:
	Rva006AAC20Result go(void *arg);

private:
	void grow(int n);
	void makeInto(Rva006AAC20Result *dest, void *arg);

	char m_lead[0x10];
	int m_count;
};

Rva006AAC20Result Rva006AAC20::go(void *arg)
{
	grow(m_count + 1);
	Rva006AAC20Result tmp;
	makeInto(&tmp, arg);
	return tmp;
}
