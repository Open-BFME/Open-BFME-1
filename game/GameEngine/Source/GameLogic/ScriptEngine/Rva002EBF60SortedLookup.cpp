// cl: /DNDEBUG /MD /EHsc
// Retail 0x002EBF60 (248 bytes): address-derived owner; no semantic class claim.
// Constructor 0x002E17C0 writes 20 bytes. The search key is at local offset 0
// (retail LEA accounting), not +4. Both comparator temporaries are empty
// value-initialized objects. Cached end/begin match retail's call-time snapshot.
// Lower-bound and StringBase comparison only read data/compare bytes and cannot
// throw C++ exceptions. This preserves retail's frame without a state-0 store.

struct Q2LowerBoundStringData
{
	unsigned char m_head[4];
	unsigned short m_length;
	unsigned short m_capacity;
	char m_data[1];
};

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
template<> int StringBase<char>::compare(const StringBase<char> &) const throw();
static __forceinline int compare002EBF60(const AsciiString &a,const AsciiString &b) throw()
{
 return ((const StringBase<char> &)a).compare((const StringBase<char> &)b);
}
struct Q2LowerBoundString { Q2LowerBoundStringData *m_data; };

struct Q2LowerBoundElement20
{
	Q2LowerBoundString m_key;
	unsigned char m_payload[16];
};

struct S4Cmp002EB8E0
{
	
};

struct S4SortElem20;
void Rva002EBEF0(S4SortElem20 *first, S4SortElem20 *last, S4Cmp002EB8E0 comp);

struct Q2LowerBoundLess
{
	bool operator()(const Q2LowerBoundElement20 &left, const AsciiString &right) const;
};

Q2LowerBoundElement20 *__lower_bound(
	Q2LowerBoundElement20 *first, Q2LowerBoundElement20 *last,
	const Q2LowerBoundString &value, Q2LowerBoundLess comp, int *distance) throw();

class BfmeThingBUF
{
public:
	BfmeThingBUF *bfmeInitBUF(void *what);


};

class Rva002E9E10
{
public:
 Rva002E9E10(const AsciiString *p) { ((BfmeThingBUF *)this)->bfmeInitBUF((void *)p); }
 ~Rva002E9E10();
 unsigned char storage[20];
};

class Rva002EBF60Owner
{
public:
	Q2LowerBoundElement20 *findSorted(const AsciiString *param);

private:
	unsigned char m_pad00[0x88];
	bool m_sorted;
	unsigned char m_pad89[3];
	Q2LowerBoundElement20 *m_begin;
	Q2LowerBoundElement20 *m_end;
};

Q2LowerBoundElement20 *Rva002EBF60Owner::findSorted(const AsciiString *param)
{
	if (((const Q2LowerBoundString *)param)->m_data != 0)
	{
		if (((const Q2LowerBoundString *)param)->m_data->m_length != 0)
		{
			if (!m_sorted)
			{
				Q2LowerBoundElement20 *end = m_end;
                Q2LowerBoundElement20 *begin = m_begin;
                Rva002EBEF0((S4SortElem20 *)begin, (S4SortElem20 *)end, S4Cmp002EB8E0());
				m_sorted = true;
			}

			Rva002E9E10 local(param);

			Q2LowerBoundElement20 *last = m_end;
            Q2LowerBoundElement20 *first = m_begin;
			Q2LowerBoundElement20 *found = __lower_bound(
				first, last, *(Q2LowerBoundString *)&local, Q2LowerBoundLess(), 0);

			if (found != last && compare002EBF60(*(const AsciiString *)&found->m_key,*param) == 0)
				return found;
		}
	}

	return 0;
}


