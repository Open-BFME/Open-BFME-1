// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: ThingTemplate::getSound, retail 0x00416FA0, 22 bytes. The body
// carried only a machine byte-dump row; reverse/reloc_names.csv holds the name
// with identity=real.
//
// A lookup by index with a fallback: when the lookup returns null the result is
// the shared empty audio event at 0x012F1318, which is the same global the
// getPerUnitSound body two functions along falls back to.

typedef int Int;

class AudioEventRTS;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	const AudioEventRTS *getSound(Int index) const;

private:
	const AudioEventRTS *bfmeLookupSound(Int index) const;	// ILT 0x0000286A
};

extern AudioEventRTS BfmeTheEmptyAudioEvent;			// 0x012F1318

// ?getSound@ThingTemplate@@QBEPBVAudioEventRTS@@H@Z
const AudioEventRTS *ThingTemplate::getSound(Int index) const
{
	const AudioEventRTS *sound = bfmeLookupSound(index);
	if (!sound)
		sound = &BfmeTheEmptyAudioEvent;
	return sound;
}
