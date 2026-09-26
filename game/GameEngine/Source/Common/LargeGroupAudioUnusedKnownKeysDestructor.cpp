// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: LargeGroupAudioUnusedKnownKeys' destructor, retail 0x003CDED0,
// 95 bytes. The derived vftable at 0x010EE0FC points through the scalar
// deleting destructor at 0x003CDEA0 to this body. Retail destroys the +0x0C
// key-map member, installs the base vftable, deletes the chained override at
// +0x04 through its virtual destructor, and clears the link.

class LargeGroupAudioKeyMap
{
public:
	~LargeGroupAudioKeyMap(void);

private:
	void *m_bfmeData[3];
};

class LargeGroupAudioUnusedKnownKeysBase
{
public:
	virtual ~LargeGroupAudioUnusedKnownKeysBase(void)
	{
		if (m_nextOverride)
			delete m_nextOverride;

		m_nextOverride = 0;
	}

private:
	LargeGroupAudioUnusedKnownKeysBase *m_nextOverride;
	bool m_isOverride;
};

class __declspec(novtable) LargeGroupAudioUnusedKnownKeys :
	public LargeGroupAudioUnusedKnownKeysBase
{
public:
	virtual ~LargeGroupAudioUnusedKnownKeys(void);

private:
	LargeGroupAudioKeyMap m_bfmeKeys;
};

// ??1LargeGroupAudioUnusedKnownKeys@@UAE@XZ
LargeGroupAudioUnusedKnownKeys::~LargeGroupAudioUnusedKnownKeys(void)
{
}
