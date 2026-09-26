// cl: /DNDEBUG /MD /EHsc

// Retail 0x003C6070 is an unnamed field helper: add the unsigned argument to
// the dword at +0xA0.  The owner remains address-derived.
struct Rva003C6070AddField
{
	unsigned char m_unmodelled_000[0xA0];
	unsigned int m_value;

	void addField(unsigned int value);
};

void Rva003C6070AddField::addField(unsigned int value)
{
	m_value += value;
}
