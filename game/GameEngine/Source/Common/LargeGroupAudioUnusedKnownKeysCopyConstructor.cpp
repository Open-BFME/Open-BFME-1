// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: LargeGroupAudioUnusedKnownKeys' copy constructor, retail
// 0x003CD590, 87 bytes. The body carried only a machine byte-dump row; the
// symbols.csv pin names it, and the base constructor, the member constructor
// and the vtable are all pinned with this row.
//
// Three steps and nothing else: the base is copy-constructed from the source,
// the class's own vtable goes over the base one, and the member at +0x0C is
// copy-constructed from the source's. The source pointer is used twice, once as
// itself for the base and once biased by twelve for the member.
//
// The unwind slot is written once, for the base, just before the member's
// constructor -- the only call here that can throw once something is standing.

class LargeGroupAudioKeyMap
{
public:
	LargeGroupAudioKeyMap(const LargeGroupAudioKeyMap &other);	// ILT 0x0002F06D
	~LargeGroupAudioKeyMap();

private:
	void *m_bfmeData;
};

class LargeGroupAudioUnusedKnownKeysBase
{
public:
	LargeGroupAudioUnusedKnownKeysBase(
			const LargeGroupAudioUnusedKnownKeysBase &other); // ILT 0x0001DE26
	~LargeGroupAudioUnusedKnownKeysBase();

	virtual void bfmeSlot0(void);

private:
	char m_bfmePad[0x0C - 0x04];
};

class LargeGroupAudioUnusedKnownKeys : public LargeGroupAudioUnusedKnownKeysBase
{
public:
	LargeGroupAudioUnusedKnownKeys(const LargeGroupAudioUnusedKnownKeys &other);

	virtual void bfmeSlot0(void);

private:
	LargeGroupAudioKeyMap m_bfmeKeys;			// +0x0C
};

// ??0LargeGroupAudioUnusedKnownKeys@@QAE@ABV0@@Z
LargeGroupAudioUnusedKnownKeys::LargeGroupAudioUnusedKnownKeys(
		const LargeGroupAudioUnusedKnownKeys &other) :
	LargeGroupAudioUnusedKnownKeysBase(other),
	m_bfmeKeys(other.m_bfmeKeys)
{
}
