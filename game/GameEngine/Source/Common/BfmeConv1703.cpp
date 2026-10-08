class BfmeSubFU;

class BfmeAudioFU
{
public:
	virtual void bfmeSlot00FU(void);
	virtual void bfmeSlot01FU(void);
	virtual void bfmeSlot02FU(void);
	virtual void bfmeSlot03FU(void);
	virtual void bfmeSlot04FU(void);
	virtual void bfmeSlot05FU(void);
	virtual void bfmeSlot06FU(void);
	virtual void bfmeSlot07FU(void);
	virtual void bfmeSlot08FU(void);
	virtual void bfmeSlot09FU(void);
	virtual void bfmeSlot10FU(void);
	virtual void bfmeSlot11FU(void);
	virtual void bfmeSlot12FU(void);
	virtual void bfmeSlot13FU(void);
	virtual void bfmeSlot14FU(void);
	virtual void bfmeSlot15FU(void);
	virtual void bfmeSlot16FU(void);
	virtual void *bfmeMakeFU(BfmeSubFU *sub);
};

// Retail's AudioManager singleton (0x012ED668); the TU-local view above only
// names the slot this body calls.
class AudioManager;

extern AudioManager *TheAudio;

static inline BfmeAudioFU *localBfmeAudioFU()
{
	return (BfmeAudioFU *)TheAudio;
}

enum ObjectID {};

// retail ILTs 0x0001F753 -> 0x000B2690, 0x00019A6A -> 0x000B2250 and
// 0x00040A52 -> 0x000B2200 are the matched AudioEventRTS::operator=,
// setObjectID and setPlayingHandle rows
class AudioEventRTS
{
public:
	AudioEventRTS &operator=(const AudioEventRTS &other);
	void setObjectID(ObjectID objID);
	void setPlayingHandle(unsigned int handle);
};

class BfmeSubFU
{
public:
	unsigned char m_bfmeDataFU[4];
};

class BfmeOwnerFU
{
public:
	void bfmeGoFU(void *first, void *second);

	unsigned char m_bfmeHeadFU[0xe8];
	BfmeSubFU m_bfmeSubFU;
};

void BfmeOwnerFU::bfmeGoFU(void *first, void *second)
{
	BfmeSubFU *sub = &m_bfmeSubFU;
	AudioEventRTS *event = (AudioEventRTS *)sub;

	*event = *(const AudioEventRTS *)first;
	event->setObjectID((ObjectID)(int)second);
	event->setPlayingHandle((unsigned int)localBfmeAudioFU()->bfmeMakeFU(sub));
}
