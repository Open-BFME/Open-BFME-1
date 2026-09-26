// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x001B2040 (25 bytes).

class Rva001B2040
{
public:
	void copyFields(void *source);

private:
	unsigned char m_padding[0x0C];
	void *m_first;
	unsigned char m_gap[0x0C];
	void *m_second;
};

void Rva001B2040::copyFields(void *source)
{
	unsigned char *nested = *reinterpret_cast<unsigned char **>(
		reinterpret_cast<unsigned char *>(source) + 0x210);
	m_second = *reinterpret_cast<void **>(nested + 0x1C);
	m_first = *reinterpret_cast<void **>(nested + 0x0C);
}
