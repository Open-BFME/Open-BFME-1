// cl: /DNDEBUG /MD /EHsc
// readable body of ?setName@User@@: Code/GameEngine/Source/GameNetwork/User.cpp
// Open-BFME5: User::setName, retail 0x00685420, zh_sweep packet 00685420.
//
// The Zero Hour body is one line -- m_name = name -- and everything retail
// emits around it is the by-value UnicodeString parameter: assign through
// UnicodeString::set, then destroy the parameter, with an SEH frame so the
// destruction still happens if set throws. `ret 4` and that single dword of
// argument are also what rule out the packet's other ICF candidate,
// GameSpyInfo::setCachedLocalPlayerStats, which takes a PSPlayerStats.
//
// The one thing the bytes settle: m_name is at [this+0x4C], not at the front
// of the class as the reference User declares it. So it gets its own TU with
// the offset spelled locally rather than a change to the shared header.
//
// Both callees are inline in the reference and so appear as direct calls:
// UnicodeString::operator= forwards to set (0x008891F0), and ~UnicodeString
// forwards to releaseBuffer (0x00887940, one of the many bodies folded onto
// that address).

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	~UnicodeString() { releaseBuffer(); }

	void set(const UnicodeString &stringSrc);						///< 0x008891F0

	UnicodeString &operator=(const UnicodeString &stringSrc)
	{
		set(stringSrc);
		return *this;
	}

protected:
	void releaseBuffer(void);										///< 0x00887940

private:
	void *m_data;
};

class User
{
public:
	void setName(UnicodeString name);

private:
	unsigned char m_unreconstructed_00[0x4C];
	UnicodeString m_name;											///< +0x4C
};

// ?setName@User@@QAEXVUnicodeString@@@Z
void User::setName(UnicodeString name)
{
	m_name.set(name);
}
