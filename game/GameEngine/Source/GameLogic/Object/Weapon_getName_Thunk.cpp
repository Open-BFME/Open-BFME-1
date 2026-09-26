// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: Weapon::getName, retail 0x001C2DC0.
//
// A forwarding accessor returning AsciiString by value, so most of the body is
// the return-slot protocol: reserve four bytes, clear the unwind state slot,
// and hand the hidden return pointer to WeaponTemplate::getName with the
// template as `this`.
//
// The one fact in it: m_template at Weapon+0x30. Spelled locally because
// Weapon.cpp's WeaponTemplate layout is already known not to be BFME's -- see
// ?getMinimumAttackRange@WeaponTemplate@@QBEMXZ at 0x001E15D0, whose field sits
// 0x24 away from where that file puts it.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// Retail's AsciiString derives from StringBase<char>: its own copy ctor is the
// forwarder at 0x0005EE50 and it holds nothing of its own, so a caller that
// copies a string encodes the base body at 0x00887B60 directly. The delegation
// has to be visible here for this TU to encode the same call.
template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase<T> &src);

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString
{
public:
	// Retail inlines this forwarder, so the call site encodes
	// StringBase<char>'s copy ctor at 0x00887B60 directly.
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString();

	static AsciiString TheEmptyString;

private:
	void *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponTemplate
{
public:
	AsciiString getName(void) const;				///< ILT 0x0002D70E
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
public:
	AsciiString getName(void) const;

private:
	char m_unreconstructed_00[0x30];
	const WeaponTemplate *m_template;				///< retail this+0x30
};

// ?getName@Weapon@@QBE?AVAsciiString@@XZ
AsciiString Weapon::getName(void) const
{
	return m_template->getName();
}

AsciiString WeaponTemplate::getName(void) const
{
	return AsciiString::TheEmptyString;
}
