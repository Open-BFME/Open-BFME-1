// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME: address-derived storage selector at 0x000B56F0.

struct Rva000B56F0Object
{
	unsigned char m_prefix[8];
	unsigned char m_inlineStorage[0x90];
	unsigned int m_flags;
	unsigned char m_externalStorage[1];

	void *selectStorage();
};

void *Rva000B56F0Object::selectStorage()
{
	void *result = m_externalStorage;
	if ((m_flags & 1) == 0) {
		result = m_inlineStorage;
	}
	return result;
}
