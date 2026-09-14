// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Open-BFME5: PlayingAudio scalar-deleting destructor at retail
// 0x006BA0E0 (30 bytes).  The constructor at 0x006B9F70, vtable
// 0x0111C8C4, and matched complete destructor at 0x006BA030 establish
// the identity.

class PlayingAudio
{
public:
	virtual ~PlayingAudio();
};

void forcePlayingAudioDeletingDestructor()
{
	PlayingAudio value;
}
