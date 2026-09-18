// ?getField4@Rva00255A70Owner@@QAEPAXXZ
// Retail 0x00255A70 returns the owner field at offset +0x4.

class Rva00255A70Owner
{
public:
	void *getField4();

private:
	void *m_field0;
	void *m_field4;
};

void *Rva00255A70Owner::getField4()
{
	return m_field4;
}
