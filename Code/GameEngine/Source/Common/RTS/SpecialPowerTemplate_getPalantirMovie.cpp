// cl: /DNDEBUG /MD /EHsc
// SpecialPowerTemplate::getPalantirMovie -- override walk then copy the
// PalantirMovie AsciiString at +0x118. Same two-level unroll as the
// isShortcutPower cluster; the volatile unused local is the by-value
// AsciiString stack slot from Rva001B6070.

#pragma inline_recursion(on)
#pragma inline_depth(2)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	Overridable *friend_getFinalOverride(void)
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

protected:
	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate : public Overridable
{
public:
	AsciiString getPalantirMovie(void) const;

private:
	char m_unreconstructed_08[0x118 - 8];
	AsciiString m_palantirMovie;
};

// ?getPalantirMovie@SpecialPowerTemplate@@QBE?AVAsciiString@@XZ
AsciiString SpecialPowerTemplate::getPalantirMovie(void) const
{
	const SpecialPowerTemplate *volatile unused = 0;
	const SpecialPowerTemplate *self = (const SpecialPowerTemplate *)
		const_cast<SpecialPowerTemplate *>(this)->friend_getFinalOverride();
	return self->m_palantirMovie;
}
