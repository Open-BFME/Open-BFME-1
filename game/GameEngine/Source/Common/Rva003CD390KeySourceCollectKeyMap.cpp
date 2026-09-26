// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: retail 0x003CD390, 142 bytes. The owner and method names are
// behavior-derived because no symbol-bearing xref survives; the address-based
// class name keeps that uncertainty explicit. The byte-proven body walks the
// key-map pointer range at +0x18/+0x1C and merges every entry.

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

private:
	unsigned char m_bfmeUnmodelled[0x18];
	LargeGroupAudioKeyMap **m_mapsBegin;			// +0x18
	LargeGroupAudioKeyMap **m_mapsEnd;			// +0x1C
	LargeGroupAudioKeyMap **m_mapsCapacity;			// +0x20
};

// ?bfmeCollectKeyMap@Rva003CD390KeySource@@QAE?AVLargeGroupAudioKeyMap@@XZ
LargeGroupAudioKeyMap Rva003CD390KeySource::bfmeCollectKeyMap(void)
{
	LargeGroupAudioKeyMap result;

	LargeGroupAudioKeyMap **it = m_mapsBegin;
	LargeGroupAudioKeyMap **end = m_mapsEnd;

	for (; it != end; ++it)
		result.bfmeMerge(**it);

	return result;
}
