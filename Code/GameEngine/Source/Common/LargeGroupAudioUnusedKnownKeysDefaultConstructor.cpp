// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: LargeGroupAudioUnusedKnownKeys' default constructor, retail
// 0x003CD450, 73 bytes. The matched copy constructor at 0x003CD590 supplies
// the class identity and member layout. Retail clears the base override link
// and flag, installs the derived vtable, then constructs the key map at +0x0C.

class LargeGroupAudioKeyMap
{
public:
	LargeGroupAudioKeyMap(void);
	~LargeGroupAudioKeyMap(void);

private:
	void *m_bfmeData[3];
};

class LargeGroupAudioUnusedKnownKeysBase
{
public:
	LargeGroupAudioUnusedKnownKeysBase(void) :
		m_nextOverride(0),
		m_isOverride(false)
	{
	}

	~LargeGroupAudioUnusedKnownKeysBase(void);

	virtual void bfmeSlot0(void);

private:
	LargeGroupAudioUnusedKnownKeysBase *m_nextOverride;
	bool m_isOverride;
};

class LargeGroupAudioUnusedKnownKeys : public LargeGroupAudioUnusedKnownKeysBase
{
public:
	LargeGroupAudioUnusedKnownKeys(void);

	virtual void bfmeSlot0(void);

private:
	LargeGroupAudioKeyMap m_bfmeKeys;
};

// ??0LargeGroupAudioUnusedKnownKeys@@QAE@XZ
LargeGroupAudioUnusedKnownKeys::LargeGroupAudioUnusedKnownKeys(void)
{
}
