// Open-BFME: address-derived field getter reconstructed from retail RVA 0x0037A7F0.

class Rva0037A7F0Object
{
public:
	int getField14();

private:
	char m_pad0[0x14];
};

int Rva0037A7F0Object::getField14()
{
	return *(int *)((char *)this + 0x14);
}
