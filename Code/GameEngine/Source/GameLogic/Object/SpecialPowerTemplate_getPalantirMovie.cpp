// cl: /DNDEBUG /MD /EHsc
// SpecialPowerTemplate::getPalantirMovie -- override walk then copy the
// PalantirMovie AsciiString at +0x118. Same two-level unroll as the
// isShortcutPower cluster; the volatile unused local is the by-value
// AsciiString stack slot from Rva001B6070.

#pragma inline_recursion(on)
#pragma inline_depth(2)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other);
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
