// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: MiscAudio scalar-deleting destructor at retail RVA 0x00699F00
// (30 bytes).  MiscAudio's matched constructor at 0x00694E60 establishes the
// BFME 0xE00-byte object with 32 embedded AudioEventRTS values, while the
// matched complete destructor at 0x006952F0 performs their exact teardown.
// The retail vtable's deleting slot therefore belongs to MiscAudio, not to the
// generated address-only placeholder in game/gen_small/dtors_008.cpp.

class MiscAudio
{
public:
	virtual ~MiscAudio();
};

// The retail scalar wrapper calls the existing ILT at 0x00009048, which
// reaches MiscAudio's matched complete destructor at 0x006952F0.
#pragma comment(linker, "/alternatename:??1MiscAudio@@UAE@XZ=?j_00009048@@YAXXZ")

void forceMiscAudioDeletingDestructor()
{
	MiscAudio value;
}
