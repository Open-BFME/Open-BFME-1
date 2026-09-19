// ?getField10@Rva00337950Owner@@QAEHXZ
// Retail 0x00337950 returns the first dword plus 0x10.

class Rva00337950Owner
{
public:
	int getField10();

private:
	int m_field0;
};

int Rva00337950Owner::getField10()
{
	return m_field0 + 0x10;
}
