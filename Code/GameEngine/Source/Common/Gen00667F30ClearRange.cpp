// Open-BFME5 conversion for the complete 91-byte body at 0x00667F30.
// The owner remains address-derived: the matched caller at 0x006688D0 uses
// this body on a 65536-bit command-ID filter, and the retail body proves the
// word-array layout through its indexed load/store and full 16-bit window.

class Gen_00667F30
{
public:
	void bfmeClearRange(unsigned short commandID);

private:
	unsigned int m_bfmeBits[0x800];
};

// ?bfmeClearRange@Gen_00667F30@@QAEXG@Z
void Gen_00667F30::bfmeClearRange(unsigned short commandID)
{
	unsigned int *bits = m_bfmeBits;
	int last = commandID + 0x800A;
	int first = commandID + 0x7FF6;

	if (first >= last)
		return;

	int index = first + 0x10000;
	int count = last - first;

	do {
		int normalized = index % 0x10000;
		unsigned int mask = 1u << (normalized & 0x1F);
		unsigned int wordIndex = ((unsigned int)normalized) >> 5;
		unsigned int *word = &bits[wordIndex];

		*word &= ~mask;
		++index;
		--count;
	} while (count != 0);
}
