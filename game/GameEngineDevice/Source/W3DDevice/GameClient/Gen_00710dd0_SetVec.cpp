// cl: /DNDEBUG /MD /EHsc

// Retail 0x00710DD0. Copy three dwords from arg to this+0x164.

struct Gen_00710dd0_Vec
{
	int x;
	int y;
	int z;
};

class Gen_00710dd0
{
public:
	void set(const Gen_00710dd0_Vec *v);

private:
	unsigned char m_pad[0x164];
	int m_164;
	int m_168;
	int m_16c;
};

// ?set@Gen_00710dd0@@QAEXPBUGen_00710dd0_Vec@@@Z
void Gen_00710dd0::set(const Gen_00710dd0_Vec *v)
{
	m_164 = v->x;
	m_168 = v->y;
	m_16c = v->z;
}
