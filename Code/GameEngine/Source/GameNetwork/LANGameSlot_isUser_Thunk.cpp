// cl: /DNDEBUG /MD /EHsc
// readable body of ?isUser@LANGameSlot@@: Code/GameEngine/Source/GameNetwork/LANGameInfo.cpp
// Open-BFME5: LANGameSlot::isUser(UnicodeString) as clean C++ in its own TU.
//
// The body is one line of LANGameInfo.cpp, but it cannot be converted there:
// any edit to that file renumbers its $L labels, and the gen-funclet row
// uw_00c46f00 names one of THREE byte-identical eight-byte funclets in its
// parent group, so build.py (correctly) refuses to re-pick it from an
// ambiguous field. Compiling the member in a TU of its own leaves
// LANGameInfo.cpp -- and therefore its label numbering -- untouched.
//
// Retail shape at 0x0068E8D0: /EHsc frame, m_state at this+0x04 compared to
// SLOT_PLAYER (5), an out-of-line GameSlot::getName() whose returned temporary
// feeds StringBase<unsigned short>::compareNoCase, and ebx doing double duty
// as the boolean TRUE and as the "temporary is live" unwind flag. Both callees
// are reached through their incremental-link thunks: getName at 0x0003A20B and
// compareNoCase at 0x0001609F.
//
// StringBase is declared, never defined, so that:
//   * compareNoCase mangles as ?compareNoCase@?$StringBase@G@@QBEHABV1@@Z --
//     retail reaches the compare as a StringBase member, not a UnicodeString
//     one, so the string must be spelled through the base;
//   * the destructor mangles private, ??1?$StringBase@G@@AAE@XZ, which is the
//     folded releaseBuffer body at 0x008881D0;
//   * throw() on compareNoCase matters: it is the only call between the
//     getName temporary's construction and its destruction, so without it MSVC
//     bumps the unwind state around it and the frame gains five bytes.
// unsigned short rather than wchar_t because this TU declares no wchar_t and
// compiles with the default /Zc:wchar_t-, which is what makes the template
// argument G.

class UnicodeString;

template <class T>
class StringBase
{
public:
	int compareNoCase(const StringBase<T> &that) const throw();

private:
	friend class UnicodeString;

	StringBase();
	~StringBase();

	T *m_str;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString(const UnicodeString &that);
	~UnicodeString() {}

	int compareNoCase(const UnicodeString &that) const throw()
	{
		return ((const StringBase<unsigned short> *)this)->compareNoCase(
			*(const StringBase<unsigned short> *)&that);
	}
};

enum SlotState
{
	SLOT_OPEN,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_PLAYER
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	virtual void reset(void) = 0;	// vptr, so m_state lands at this+0x04
	UnicodeString getName(void) const;

protected:
	SlotState m_state;
	char m_unrecovered[0x20];
	UnicodeString m_name;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameSlot : public GameSlot
{
public:
	bool isUser(UnicodeString userName);
};

// ?isUser@LANGameSlot@@QAE_NVUnicodeString@@@Z
bool LANGameSlot::isUser(UnicodeString userName)
{
	return (m_state == SLOT_PLAYER && !userName.compareNoCase(getName()));
}

UnicodeString GameSlot::getName(void) const
{
	return m_name;
}
