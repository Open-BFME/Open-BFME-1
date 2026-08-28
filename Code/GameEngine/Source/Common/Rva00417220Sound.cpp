// cl: /O2 /Ob0

class AudioEventRTS;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
	const AudioEventRTS *bfmeLookupSound(int index) const;

public:
	int hasSound95() const;
};

int ThingTemplate::hasSound95() const
{
	return bfmeLookupSound(0x5F) != 0;
}
