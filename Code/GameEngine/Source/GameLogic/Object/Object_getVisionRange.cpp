// cl: /DNDEBUG /MD /EHsc
// readable body of ?getVisionRange@Object@@QBEMXZ: Code/GameEngine/Source/GameLogic/Object/Object.cpp

// Open-BFME5: Object::getVisionRange, retail 0x001C17C0, 71 bytes. The body
// carried only a machine byte-dump row; reverse/reloc_names.csv holds the name
// with identity=real.
//
// The stored range at +0x194 is copied out through an integer register, a zero
// bonus is set up beside it, and the bonus source -- when there is one -- is
// asked for bonus number 14. A yes scales the range by one plus what came back;
// anything else hands the stored range straight over.
//
// The two floats are one array rather than two locals. That is what puts the
// range in the lower slot and the address-taken bonus in the upper one: as
// separate locals MSVC always places the address-taken one lower, whichever
// order they are declared or initialised in, which is the single thing that
// kept this body from matching before.

typedef int Int;
typedef bool Bool;
typedef float Real;

class BfmeVisionBonusSource
{
public:
	Bool bfmeGetBonus(Int which, Real *out);		// ILT 0x000282D6
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Real getVisionRange(void) const;

private:
	BfmeVisionBonusSource *bfmeGetBonusSource(void) const;	// ILT 0x000202ED

	char m_bfmeHead[0x194];
	Real m_bfmeVisionRange;					// +0x194
};

// ?getVisionRange@Object@@QBEMXZ
Real Object::getVisionRange(void) const
{
	Real slot[2];

	slot[0] = m_bfmeVisionRange;
	slot[1] = 0.0f;

	BfmeVisionBonusSource *source = bfmeGetBonusSource();

	if (source && source->bfmeGetBonus(14, &slot[1]))
		return (slot[1] + 1.0f) * slot[0];

	return slot[0];
}
