// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: retail 0x003CD4B0, 168 bytes. Placement between the exact
// default and copy constructors, plus their shared +0x04/+0x08/+0x0C layout,
// proves the owner. The method name remains behavior-derived because the
// executable carries no surviving spelling for this return-by-value collector.

class LargeGroupAudioKeyMap
{
public:
	LargeGroupAudioKeyMap(void);
	LargeGroupAudioKeyMap(const LargeGroupAudioKeyMap &other);
	~LargeGroupAudioKeyMap(void);

	void bfmeMerge(const LargeGroupAudioKeyMap &other);

private:
	void *m_bfmeData[3];
};

class Rva003CD390KeySource
{
public:
	LargeGroupAudioKeyMap bfmeCollectKeyMap(void);
};

class LargeGroupAudioUnusedKnownKeys
{
public:
	LargeGroupAudioKeyMap bfmeCollectKeyMap(void);

private:
	void *m_bfmeVtable;					// +0x00
	LargeGroupAudioUnusedKnownKeys *m_next;			// +0x04
	bool m_isOverride;					// +0x08
	Rva003CD390KeySource **m_keysBegin;			// +0x0C
	Rva003CD390KeySource **m_keysEnd;			// +0x10
	Rva003CD390KeySource **m_keysCapacity;			// +0x14
};

// ?bfmeCollectKeyMap@LargeGroupAudioUnusedKnownKeys@@QAE?AVLargeGroupAudioKeyMap@@XZ
LargeGroupAudioKeyMap LargeGroupAudioUnusedKnownKeys::bfmeCollectKeyMap(void)
{
	LargeGroupAudioKeyMap result;

	Rva003CD390KeySource **it = m_keysBegin;
	Rva003CD390KeySource **end = m_keysEnd;

	for (; it != end; ++it)
		result.bfmeMerge((*it)->bfmeCollectKeyMap());

	return result;
}
