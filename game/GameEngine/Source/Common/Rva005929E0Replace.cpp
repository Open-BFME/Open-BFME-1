// cl: /DNDEBUG /MD /EHsc

// Rva005929E0::replace, retail 0x00592920, 144 bytes.
//
// Companion to the already-matched Rva005929E0::release at 0x005929E0, which
// destroys the owned pointer at +8. This body `new`s the four-UnicodeString
// record whose constructor is already landed at 0x00590010 (ILT 0x0004B2B3)
// and, when the pointer changes, runs the same non-virtual dtor + ??3 pair
// as release (ILT 0x0003FA7B -> UpgradeMuxData / Gen0003FA7B).

class UnicodeString;

class Rva00590010FourString
{
public:
	Rva00590010FourString(
		const UnicodeString &first,
		const UnicodeString &second,
		const UnicodeString &third,
		const UnicodeString &fourth );

private:
	char m_body[0x14];
};

// The record's destructor call goes through ILT 0x0003FA7B to 0x0058C4C0,
// matched as ??1UpgradeMuxData@@QAE@XZ (UpgradeMuxData_dtor_Thunk.cpp: four
// wide-string releases at +0x0C..+0x00); S2DeleteHeldObject.cpp reaches the
// same body the same way.
class UpgradeMuxData
{
public:
	~UpgradeMuxData();
};

class Rva005929E0
{
public:
	void replace(
		const UnicodeString &first,
		const UnicodeString &second,
		const UnicodeString &third,
		const UnicodeString &fourth );

private:
	char m_lead[8];
	Rva00590010FourString *m_owned;
};

// ?replace@Rva005929E0@@QAEXABVUnicodeString@@000@Z
void Rva005929E0::replace(
	const UnicodeString &first,
	const UnicodeString &second,
	const UnicodeString &third,
	const UnicodeString &fourth )
{
	Rva00590010FourString *p = new Rva00590010FourString(
		first, second, third, fourth );
	if (p != m_owned)
	{
		if (m_owned)
			delete (UpgradeMuxData *)m_owned;
		m_owned = p;
	}
}
