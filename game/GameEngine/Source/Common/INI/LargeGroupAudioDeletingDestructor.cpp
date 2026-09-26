// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: LargeGroupAudio scalar-deleting destructor at retail RVA
// 0x003D1350 (30 bytes). Its exact constructor at 0x003CEF00 and complete
// destructor at 0x003D0D70 share the recovered dual-vptr subsystem layout.
// The destructor ILT is 0x000139FD.

class LargeGroupAudio
{
public:
	virtual ~LargeGroupAudio();
};

void forceLargeGroupAudioDeletingDestructor()
{
	LargeGroupAudio value;
}
