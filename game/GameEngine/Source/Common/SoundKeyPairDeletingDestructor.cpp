// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: SoundKeyPair scalar-deleting destructor at retail
// 0x003D2190 (30 bytes).  The matched constructor at 0x003CFB00 and complete
// destructor at 0x003D18E0 establish the class identity; LargeGroupAudioMap
// owns and destroys these four-pointer sound records.

class SoundKeyPair
{
public:
	~SoundKeyPair();
};

void Force_SoundKeyPair_Deleting_Destructor(SoundKeyPair *value)
{
	delete value;
}
