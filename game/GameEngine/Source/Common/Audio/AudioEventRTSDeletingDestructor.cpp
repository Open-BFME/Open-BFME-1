// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Open-BFME: AudioEventRTS scalar-deleting destructor at retail RVA
// 0x000B33C0 (30 bytes).  The AudioEventRTS ctor family and vtable
// 0x01081D40 identify the object; its matched 162-byte destructor at
// 0x000B31F0 is called through ILT 0x00026F35 by this deleting wrapper.

class AudioEventRTS
{
public:
	__declspec(noinline) ~AudioEventRTS();
};

void Force_AudioEventRTS_Deleting_Destructor(AudioEventRTS *event)
{
	delete event;
}
