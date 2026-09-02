// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva00249C50HordeContain
{
public:
	void resetContainState();
	void resetPair(void *first, void *second);
	void finishReset();

private:
	unsigned char unused_000[0xEC];
	unsigned char m_first[0x0C];
	unsigned char m_second[0x0C];
};

// ?resetContainState@Rva00249C50HordeContain@@QAEXXZ
void Rva00249C50HordeContain::resetContainState()
{
	resetPair(m_first, m_second);
	finishReset();
}
