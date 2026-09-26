// cl: /DNDEBUG /MD /EHsc

// Retail 0x003BCB50 is an unnamed field helper.  It adds the unsigned
// argument to the dword at +0xD0; the owner remains address-derived.
struct Rva003BCB50AddField
{
	unsigned char m_unmodelled_000[0xD0];
	unsigned int m_value;

	void addField(unsigned int value);
};

void Rva003BCB50AddField::addField(unsigned int value)
{
	m_value += value;
}
