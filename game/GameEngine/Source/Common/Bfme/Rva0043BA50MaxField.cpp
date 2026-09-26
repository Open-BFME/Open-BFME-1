// cl: /DNDEBUG /MD /EHsc

// Retail 0x0043BA50 is an unnamed unsigned max update.  It retains the
// greater of the argument and the dword at +0x814; the owner is address-derived.
struct Rva0043BA50MaxField
{
	unsigned char m_unmodelled_000[0x814];
	unsigned int m_value;

	void updateMax(unsigned int value);
};

void Rva0043BA50MaxField::updateMax(unsigned int value)
{
	if (value <= m_value)
		return;
	m_value = value;
}
