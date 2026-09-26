// Retail RVA 0x003A4E30 is BfmeHostCB::bfmePopCB.  The named caller, the
// element destructor, and the vector shift helper establish this owner and
// the 20-byte element layout.
extern const float BfmeZeroRange;
extern "C" const float _bfmeScaleCB;

struct BfmeUniBufCB
{
	unsigned char m_bfmeHeadCB[4];
	unsigned short m_bfmeChCB;
};

class UnicodeString
{
public:
	void set(const UnicodeString &o);
};

class AsciiString
{
};

class Rva003A5450
{
public:
	void setAscii(const AsciiString &s);
};

struct BfmeUnicodeHandleCB
{
	BfmeUniBufCB *m_bfmeDataCB;
};

class Open2Rec3A4420
{
	public:
	Open2Rec3A4420(const Open2Rec3A4420 &o);
	~Open2Rec3A4420();

	int m_bfme00CB;
	int m_bfme04CB;
	BfmeUnicodeHandleCB m_bfme08CB;
	BfmeUnicodeHandleCB m_bfme0CCB;
	float m_bfme10CB;
};

typedef Open2Rec3A4420 BfmeElemCB;

struct ModuleInfo
{
	struct Nugget
	{
	};
};

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class T, class U, class V>
	::ModuleInfo::Nugget *__copy(::ModuleInfo::Nugget *first, ::ModuleInfo::Nugget *last,
		::ModuleInfo::Nugget *dst, const random_access_iterator_tag &tag, int *flag);
}

struct BfmeScaleCB
{
	__forceinline float multiply(const volatile float &value) const
	{
		return *m_bfmeScaleCB * value;
	}

	const float *m_bfmeScaleCB;
};

struct BfmeVectorCB
{
	BfmeElemCB *begin() { return m_bfmeBeginCB; }
	BfmeElemCB *end() { return m_bfmeEndCB; }
	unsigned int size() { return (unsigned int)(m_bfmeEndCB - m_bfmeBeginCB); }

	BfmeElemCB *m_bfmeBeginCB;
	BfmeElemCB *m_bfmeEndCB;
};

class BfmeHostCB
{
public:
	char bfmePopCB();

	unsigned char m_bfmeHeadCB[0x14];
	int m_bfme14CB;
	int m_bfme18CB;
	unsigned char m_bfme1CCB;
	unsigned char m_bfmeGapCB[3];
	float m_bfme20CB;
	unsigned char m_bfmeGap2CB[4];
	BfmeVectorCB m_bfmeItemsCB;
	unsigned char m_bfmeGap3CB[4];
	BfmeUnicodeHandleCB m_bfme34CB;
};

char BfmeHostCB::bfmePopCB()
{
	BfmeElemCB *begin = m_bfmeItemsCB.begin();

	if (m_bfmeItemsCB.size() != 0)
	{
		BfmeElemCB *source = m_bfmeItemsCB.begin();
		BfmeElemCB e(*source);

		m_bfme14CB = e.m_bfme00CB;
		m_bfme18CB = e.m_bfme04CB;

		if (e.m_bfme08CB.m_bfmeDataCB != 0 && e.m_bfme08CB.m_bfmeDataCB->m_bfmeChCB != 0)
		{
			UnicodeString *destination = reinterpret_cast<UnicodeString *>(&m_bfme34CB);
			const UnicodeString *source_string = reinterpret_cast<const UnicodeString *>(&e.m_bfme08CB);
			destination->set(*source_string);
		}

		if (e.m_bfme0CCB.m_bfmeDataCB != 0 && e.m_bfme0CCB.m_bfmeDataCB->m_bfmeChCB != 0)
			reinterpret_cast<Rva003A5450 *>(this)->setAscii(*reinterpret_cast<const AsciiString *>(&e.m_bfme0CCB));

		if (e.m_bfme10CB != BfmeZeroRange)
		{
			BfmeScaleCB scale = { &_bfmeScaleCB };
			m_bfme20CB = scale.multiply(e.m_bfme10CB);
		}

		BfmeElemCB *first = m_bfmeItemsCB.begin();
		BfmeElemCB *last = m_bfmeItemsCB.end();

		if (first + 1 != last)
		{
			_STL::random_access_iterator_tag tag;

			_STL::__copy<ModuleInfo::Nugget *, ModuleInfo::Nugget *, int>(
				reinterpret_cast<ModuleInfo::Nugget *>(first + 1),
				reinterpret_cast<ModuleInfo::Nugget *>(last),
				reinterpret_cast<ModuleInfo::Nugget *>(first), tag, 0);
		}

		--m_bfmeItemsCB.m_bfmeEndCB;

		m_bfmeItemsCB.m_bfmeEndCB->~BfmeElemCB();

		m_bfme1CCB = 1;

		return 1;
	}

	return 0;
}
