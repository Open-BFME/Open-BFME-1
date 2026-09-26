// cl: /DNDEBUG /MD /EHsc

// Two of ThingTemplate's sound accessors:
//
//   getSound   0x00416FA0  one sound by index, empty event if the slot is unfilled
//   hasSound95 0x00417220  is slot 0x5F filled
//
// Both call one private helper through the same ILT (0x0000286A), and they sat in
// two files in two different directories describing that helper and the class
// twice.
//
// The two declarations of the helper agreed on everything, including that it is
// private (ABE) -- the part a merge can quietly get wrong. They spelled it two
// ways that happen to mean the same thing: hasSound95 declared it before any
// access specifier and relied on `class` defaulting to private, while getSound
// wrote `private:`. One declaration now.
//
// A THIRD accessor, bfmeGetAudioEventInfo57 (0x004172E0), belongs to this group
// by every other measure -- it is 0x340 away in the image, calls the same helper
// through the same ILT, and falls back to the same global at 0x012F1318 that
// getSound does -- and it is deliberately NOT here. It returns an
// AudioEventInfoRef by value, and building that value needs a constructor that
// retains the event info. Any spelling of that constructor makes MSVC emit an
// out-of-line COMDAT copy of ??0AudioEventInfoRef@@QAE@PBVAudioEventInfo@@@Z
// beside the body, and the ledger declares no row for it, so the commit hook
// refuses a TU that carries it -- correctly. __forceinline does not suppress the
// copy. Writing the retain out in the body instead, as an aggregate, does avoid
// the extra symbol but changes the bytes: retail stores the pointer into the
// return slot BEFORE testing it, and the aggregate form tests first and stores
// last. Its own file predates that hook check and is grandfathered, so it stays
// where it is rather than have its body reshaped to fit a merge.

typedef int Int;

class AudioEventRTS;

// Slot index. hasSound95's name is this number in decimal (0x5F == 95); the
// sibling accessor named ...57 uses the hex spelling of a different slot, so the
// two names are not in the same base. Nothing recovers what the slots mean.
enum { BFME_SOUND_SLOT_5F = 0x5F };

// The shared empty event at 0x012F1318, which getSound's fallback returns and
// which bfmeGetAudioEventInfo57 falls back to as well.
extern AudioEventRTS BfmeTheEmptyAudioEvent;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	const AudioEventRTS *getSound(Int index) const;
	Int hasSound95() const;

private:
	const AudioEventRTS *bfmeLookupSound(Int index) const;	// ILT 0x0000286A
};

// ?getSound@ThingTemplate@@QBEPBVAudioEventRTS@@H@Z
//
// The body carried only a machine byte-dump row; targets/game/reverse/reloc_names.csv holds
// the name with identity=real.
const AudioEventRTS *ThingTemplate::getSound(Int index) const
{
	const AudioEventRTS *sound = bfmeLookupSound(index);
	if (!sound)
		sound = &BfmeTheEmptyAudioEvent;
	return sound;
}

// ?hasSound95@ThingTemplate@@QBEHXZ
//
// The neg/sbb/neg is what this compiler emits turning a pointer test into an Int.
Int ThingTemplate::hasSound95() const
{
	return bfmeLookupSound(BFME_SOUND_SLOT_5F) != 0;
}
