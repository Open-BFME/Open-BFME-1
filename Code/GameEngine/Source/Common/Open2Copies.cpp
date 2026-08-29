// cl: /DNDEBUG /MD /EHsc
//
// Four instances of STLport's random-access `copy` over records whose
// members include an AsciiString.  Each walks two pointers by the element
// size; the one that is LOADED from is the source and the one STORED to is the
// result, which is how the layouts below were read off the loop bodies.
//
// The element assignment is memberwise in declaration order and its string arm
// is `set(const StringBase &)`, not operator=, so the record's own assignment
// is the implicit one over an AsciiString whose operator= forwards to set.
// The count is computed once and counted DOWN -- STLport's
// `for (Distance n = last - first; n > 0; --n)`.
//
// The element size, taken from the loop's own pointer increment, is what fixes
// the trailing padding: the members below account for every byte the copy
// touches, and the record is padded out to the stride the loop walks.

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	void set( const StringBase<T> &src );		// retail 0x00887C90

private:
	~StringBase();					// retail 0x00887940

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString() {}

	AsciiString &operator=( const AsciiString &other )
	{
		m_string.set( other.m_string );
		return *this;
	}

	StringBase<char> m_string;
};

// -------------------------------------------------------------------------
// 0x003A4270 -- 101 bytes, element 0x14
class Open2Elem3A4270
{
public:
	int m_at00;
	int m_at04;
	AsciiString m_at08;
	AsciiString m_at0c;
	int m_at10;
};

// @?Open2Copy3A4270@@YAPAVOpen2Elem3A4270@@PAV1@00@Z 0x003A4270
Open2Elem3A4270 *Open2Copy3A4270( Open2Elem3A4270 *first, Open2Elem3A4270 *last,
	Open2Elem3A4270 *result )
{
	for( int n = last - first; n > 0; --n )
	{
		*result = *first;
		++first;
		++result;
	}
	return result;
}

// -------------------------------------------------------------------------
// 0x003AEDF0 -- 92 bytes, element 0xc
class Open2Elem3AEDF0
{
public:
	AsciiString m_at00;
	AsciiString m_at04;
	AsciiString m_at08;
};

// @?Open2Copy3AEDF0@@YAPAVOpen2Elem3AEDF0@@PAV1@00@Z 0x003AEDF0
Open2Elem3AEDF0 *Open2Copy3AEDF0( Open2Elem3AEDF0 *first, Open2Elem3AEDF0 *last,
	Open2Elem3AEDF0 *result )
{
	for( int n = last - first; n > 0; --n )
	{
		*result = *first;
		++first;
		++result;
	}
	return result;
}

// -------------------------------------------------------------------------
// 0x003B3880 -- 92 bytes, element 0xc
class Open2Elem3B3880
{
public:
	AsciiString m_at00;
	AsciiString m_at04;
	AsciiString m_at08;
};

// @?Open2Copy3B3880@@YAPAVOpen2Elem3B3880@@PAV1@00@Z 0x003B3880
Open2Elem3B3880 *Open2Copy3B3880( Open2Elem3B3880 *first, Open2Elem3B3880 *last,
	Open2Elem3B3880 *result )
{
	for( int n = last - first; n > 0; --n )
	{
		*result = *first;
		++first;
		++result;
	}
	return result;
}

// -------------------------------------------------------------------------
// 0x007655A0 -- 95 bytes, element 0x14
class Open2Elem7655A0
{
public:
	int m_at00;
	int m_at04;
	int m_at08;
	AsciiString m_at0c;
	int m_at10;
};

// @?Open2Copy7655A0@@YAPAVOpen2Elem7655A0@@PAV1@00@Z 0x007655A0
Open2Elem7655A0 *Open2Copy7655A0( Open2Elem7655A0 *first, Open2Elem7655A0 *last,
	Open2Elem7655A0 *result )
{
	for( int n = last - first; n > 0; --n )
	{
		*result = *first;
		++first;
		++result;
	}
	return result;
}
