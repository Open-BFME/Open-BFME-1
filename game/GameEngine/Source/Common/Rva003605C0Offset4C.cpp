// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva003605C0Offset4C
{
private:
	unsigned char m_pad[0x4c];

public:
	void *getOffset4C();
};

void *Rva003605C0Offset4C::getOffset4C()
{
	return reinterpret_cast<unsigned char *>(this) + 0x4c;
}
