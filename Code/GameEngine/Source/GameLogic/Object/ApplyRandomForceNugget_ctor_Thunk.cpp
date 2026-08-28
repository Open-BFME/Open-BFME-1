// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME5: ApplyRandomForceNugget::ApplyRandomForceNugget, retail
// 0x003B7610, zh_sweep packet 003b7610.
//
// The reference constructor zeroes five Reals, +0x04 through +0x14. Retail
// zeroes six, out to +0x18, and then a byte at +0x1C. So BFME's nugget carries
// two more fields; only their offsets, widths and initial values are proven, so
// they are named for what the bytes show rather than guessed at.
//
// It gets its own TU even though the class is local to ObjectCreationList.cpp.
// Adding the two members there is byte-correct for this body but renumbers the
// compiland's $L labels, and that file has EH funclet rows keyed on them --
// uw_00c09bd3 and uw_00c09be9 both go red. This is the trap that makes a
// thunk TU the default answer for any layout change.
//
// The base contributes nothing: retail stamps exactly one vtable and calls no
// base constructor, so the vptr belongs to this class and the base subobject is
// empty.

typedef float Real;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ObjectCreationList.h
class ObjectCreationNugget
{
};

class ApplyRandomForceNugget : public ObjectCreationNugget
{
public:
	ApplyRandomForceNugget();

	virtual ~ApplyRandomForceNugget() {}					///< places the vptr at +0x00

private:
	Real											m_spinRate;			///< +0x04
	Real											m_minMag, m_maxMag;	///< +0x08, +0x0C
	Real											m_minPitch, m_maxPitch;	///< +0x10, +0x14
	Real											m_unreconstructed_18;	///< +0x18
	Bool											m_unreconstructed_1C;	///< +0x1C
};

// ??0ApplyRandomForceNugget@@QAE@XZ
ApplyRandomForceNugget::ApplyRandomForceNugget() : 
	m_spinRate(0.0f),
	m_minMag(0.0f),
	m_maxMag(0.0f),
	m_minPitch(0.0f),
	m_maxPitch(0.0f),
	m_unreconstructed_18(0.0f),
	m_unreconstructed_1C(false)
{
}
