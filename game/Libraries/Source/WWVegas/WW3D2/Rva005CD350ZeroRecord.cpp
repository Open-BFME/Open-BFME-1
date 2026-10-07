// cl: /DNDEBUG /MD /EHsc

// Two opaque retail twins (?dup_005cd350, ?dup_005cd6d0): a constructor that
// zeroes eight dwords and returns this. Their rows used to sit on the pristine
// Zero Hour hrawanim.cpp under its NodeMotionStruct constructor; BFME's own
// NodeMotionStruct constructor (game hrawanim.cpp) is longer, so the owning
// class is unproven and keeps an address-derived name.

class Rva005CD350Record
{
public:
	Rva005CD350Record();

	void *m_field00;
	void *m_field04;
	void *m_field08;
	void *m_field0C;
	void *m_field10;
	void *m_field14;
	void *m_field18;
	void *m_field1C;
};

Rva005CD350Record::Rva005CD350Record() :
	m_field00(0),
	m_field04(0),
	m_field08(0),
	m_field0C(0),
	m_field10(0),
	m_field14(0),
	m_field18(0),
	m_field1C(0)
{
}
