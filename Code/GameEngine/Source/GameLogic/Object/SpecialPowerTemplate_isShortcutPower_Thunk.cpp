// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: the SpecialPowerTemplate accessors that are nothing but an
// inlined override walk -- four of them, at 0x00268890, 0x002688C0,
// 0x00268920 and 0x00268980. They share every byte except the offset each
// one reaches at the end, which is what makes them cheap to land together and
// what pins four members of the class.
//
// Same shape ?isSupplySourceSafe@AIPlayer@@QAE_NH@Z at 0x00166A10 carries. Overridable::friend_getFinalOverride is defined recursively and inline
// in the header, so MSVC unrolls two levels and leaves the rest to the
// out-of-line copy:
//
//   eax = this->m_nextOverride;  if null, answer is `this`
//   ecx = eax->m_nextOverride;   if null, answer is eax
//   otherwise call the out-of-line copy and take its result
//
// The offsets each one pins:
//
//   0x00268890  getInitiateSound          &m_initiateSound          +0x024
//   0x002688C0  getInitiateAtTargetSound  &m_initiateAtTargetSound  +0x094
//   0x00268980  getRadiusCursorRadius      m_radiusCursorRadius     +0x10c
//   0x00268920  isShortcutPower            m_shortcutPower          +0x115
//
// The two sounds are 0x70 apart, which sizes AudioEventRTS at 112 bytes.
// m_nextOverride is at +0x04, so Overridable is a vtable pointer and that one
// member.
//
// The call goes to the NON-const overload -- retail's target resolves through
// ILT 0x00048C61 to 0x00097880, which the ledger carries as
// ?friend_getFinalOverride@Overridable@@QAEPAV1@XZ -- so the const walk is
// reached by casting rather than by a second const overload.

// MSVC does not expand a recursive inline at all unless inline_recursion is on;
// with it off the walk unrolls once and calls. Retail unrolls exactly twice, so
// the depth is pinned here rather than left to the default.
#pragma inline_recursion(on)
#pragma inline_depth(2)

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
	Overridable *m_nextOverride;					///< retail this+0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
	char m_unreconstructed_00[0x94 - 0x24];			///< 0x70, the gap between the two sounds
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate : public Overridable
{
public:
	bool isShortcutPower(void) const;
	const AudioEventRTS *getInitiateSound(void) const;
	const AudioEventRTS *getInitiateAtTargetSound(void) const;
	float getRadiusCursorRadius(void) const;

private:
	char m_unreconstructed_08[0x24 - 8];
	AudioEventRTS m_initiateSound;					///< retail this+0x024
	AudioEventRTS m_initiateAtTargetSound;			///< retail this+0x094
	char m_unreconstructed_104[0x10c - 0x104];
	float m_radiusCursorRadius;						///< retail this+0x10c
	char m_unreconstructed_110[0x115 - 0x110];
	bool m_shortcutPower;							///< retail this+0x115
};

// ?isShortcutPower@SpecialPowerTemplate@@QBE_NXZ
bool SpecialPowerTemplate::isShortcutPower(void) const
{
	const SpecialPowerTemplate *self = (const SpecialPowerTemplate *)
		const_cast<SpecialPowerTemplate *>(this)->friend_getFinalOverride();
	return self->m_shortcutPower;
}

// ?getInitiateSound@SpecialPowerTemplate@@QBEPBVAudioEventRTS@@XZ
const AudioEventRTS *SpecialPowerTemplate::getInitiateSound(void) const
{
	const SpecialPowerTemplate *self = (const SpecialPowerTemplate *)
		const_cast<SpecialPowerTemplate *>(this)->friend_getFinalOverride();
	return &self->m_initiateSound;
}

// ?getInitiateAtTargetSound@SpecialPowerTemplate@@QBEPBVAudioEventRTS@@XZ
const AudioEventRTS *SpecialPowerTemplate::getInitiateAtTargetSound(void) const
{
	const SpecialPowerTemplate *self = (const SpecialPowerTemplate *)
		const_cast<SpecialPowerTemplate *>(this)->friend_getFinalOverride();
	return &self->m_initiateAtTargetSound;
}

// ?getRadiusCursorRadius@SpecialPowerTemplate@@QBEMXZ
float SpecialPowerTemplate::getRadiusCursorRadius(void) const
{
	const SpecialPowerTemplate *self = (const SpecialPowerTemplate *)
		const_cast<SpecialPowerTemplate *>(this)->friend_getFinalOverride();
	return self->m_radiusCursorRadius;
}
