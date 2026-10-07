// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: LargeGroupAudio scalar-deleting destructor at retail RVA
// 0x003D1350 (30 bytes). Its exact constructor at 0x003CEF00 and complete
// destructor at 0x003D0D70 share the recovered dual-vptr subsystem layout.
// The destructor ILT is 0x000139FD.

class LargeGroupAudio
{
public:
	LargeGroupAudio();	// matched at 0x003CEF00 in INILargeGroupAudioUnusedKnownKeys.cpp
	virtual ~LargeGroupAudio();
};

// The implicit copy constructor (no retail twin) is what makes MSVC emit the
// vftable and with it ??_G; the default constructor stays declared so this TU
// does not emit a second copy of the retail one.
void forceLargeGroupAudioDeletingDestructor(const LargeGroupAudio &that)
{
	LargeGroupAudio value(that);
}
