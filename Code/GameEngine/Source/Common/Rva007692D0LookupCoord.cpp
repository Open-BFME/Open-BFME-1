// ?rva007692D0LookupCoord@Rva00769260Owner@@QAE_NPAXPAURva007692D0Coord@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Retail 0x007692D0 shares the flag and tree layout of the byte-matched
// Rva00769260Owner::lookup at 0x00769260. The slot at node+0x14 holds
// three coordinate components at +0x0C/+0x1C/+0x2C. The address-derived
// method name does not assert an unproved original declaration.
typedef bool Bool;

struct Rva00769260Node
{
	char m_pad00[0x14];
	char m_result[0x30];
	int m_value;
};

struct Rva00769260Iterator
{
	Rva00769260Iterator(const Rva00769260Iterator &);
	Rva00769260Node *m_node;
};

class Rva00769260Tree
{
public:
	Rva00769260Iterator find(void *const &key);
	Rva00769260Node *m_end;
};

struct Rva007692D0Coord
{
	float x, y, z;
};

class Rva00769260Owner
{
public:
	Bool rva007692D0LookupCoord(void *key, Rva007692D0Coord *coord);

private:
	char m_pad00[0x70];
	Rva00769260Tree m_tree;
	char m_pad74[0xAC - 0x74];
	unsigned char m_flags;
};

Bool Rva00769260Owner::rva007692D0LookupCoord(void *key, Rva007692D0Coord *coord)
{
	Bool active = (m_flags & 1) != 0;
	void *candidate = key;
	*(void *volatile *)&key = candidate;
	if (active && candidate != 0)
	{
		Rva00769260Iterator found = m_tree.find(key);
		if (found.m_node != m_tree.m_end)
		{
			char *result = found.m_node->m_result;
			if (result != 0)
			{
				// Volatile reads retain the three x87 loads before the output stores.
				float x = *(volatile float *)(result + 0x0c);
				float y = *(volatile float *)(result + 0x1c);
				float z = *(volatile float *)(result + 0x2c);
				coord->x = x; coord->y = y; coord->z = z;
				return true;
			}
		}
	}
	coord->x = 0;
	coord->y = 0;
	coord->z = 0;
	return false;
}
