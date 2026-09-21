// ?findSorted@Rva002EBF60Owner@@QAEPAUQ2LowerBoundElement20@@PBVAsciiString@@@Z
// partial score=0.45 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: retail 0x002EBF60 (248 B), EH-framed. Lazily sorts an
// inline array of 20-byte key/payload records (this+0x8c/+0x90, flag at
// +0x88), converts the incoming string-like argument through the
// already-landed BfmeThingBUF::bfmeInitBUF (0x002E17C0), lower_bounds
// it against the sorted array (Q2LowerBound002E7EE0, 0x002E7EE0) and,
// on an exact key match (AsciiString::compare, 0x0005FEB0), returns the
// matching record; otherwise 0. The array element type, sort driver and
// lower_bound body are the same ones already landed for the sibling
// 0x002EBEF0/0x002E7EE0 STLport bodies. Cleanup of the local converter
// goes through the already-landed pair destructor Rva002E9E10
// (0x002E9E10), reached via its own ILT pin.

struct Q2LowerBoundStringData
{
	unsigned char m_head[4];
	unsigned short m_length;
	unsigned short m_capacity;
	char m_data[1];
};

class AsciiString
{
public:
	int compare(const AsciiString &other) const;

	Q2LowerBoundStringData *m_data;
};

struct Q2LowerBoundElement20
{
	AsciiString m_key;
	unsigned char m_payload[16];
};

struct S4Cmp002EB8E0
{
	int m_bfmeState;
};

void Rva002EBEF0(Q2LowerBoundElement20 *first, Q2LowerBoundElement20 *last, S4Cmp002EB8E0 comp);

struct Q2LowerBoundLess
{
	bool operator()(const Q2LowerBoundElement20 &left, const AsciiString &right) const;
};

Q2LowerBoundElement20 *Q2LowerBound002E7EE0(
	Q2LowerBoundElement20 *first, Q2LowerBoundElement20 *last,
	const AsciiString &value, Q2LowerBoundLess comp, int *distance);

class BfmeThingBUF
{
public:
	BfmeThingBUF *bfmeInitBUF(void *what);

	unsigned char m_bfmeHead[4];
	AsciiString m_view;
	int m_bfmeB;
	int m_bfmeC;
};

class Mem00887940
{
public:
	~Mem00887940();
};

class Mem002E1260
{
public:
	~Mem002E1260();
};

class Rva002E9E10
{
public:
	~Rva002E9E10();

	Mem00887940 m_head;
	char m_pad[7];
	Mem002E1260 m_tail;
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
	if (param->m_data != 0)
	{
		if (param->m_data->m_length != 0)
		{
			if (!m_sorted)
			{
				S4Cmp002EB8E0 comp;
				comp.m_bfmeState = 0;
				Rva002EBEF0(m_begin, m_end, comp);
				m_sorted = true;
			}

			Rva002E9E10 local;
			((BfmeThingBUF *)&local)->bfmeInitBUF((void *)param);

			Q2LowerBoundLess comp;
			Q2LowerBoundElement20 *found = Q2LowerBound002E7EE0(
				m_begin, m_end, *(AsciiString *)((char *)&local + 4), comp, 0);

			if (found != m_end && found->m_key.compare(*param) == 0)
				return found;
		}
	}

	return 0;
}

// @?findSorted@Rva002EBF60Owner@@QAEPAUQ2LowerBoundElement20@@PBVAsciiString@@@Z 0x002EBF60
