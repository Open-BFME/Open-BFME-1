// stlport

// Address-derived reconstruction of the four-byte vector append at 0x006F2890.
// The owner is otherwise unidentified; its vector storage begins at +0x29C.

#include <vector>

struct Gen_t_006f2820_m4pod
{
	int value;
};

class Gen006F2890
{
public:
	void append(Gen_t_006f2820_m4pod value);

private:
	char m_head[0x29C];
	_STL::vector<Gen_t_006f2820_m4pod> m_values;
};

void Gen006F2890::append(Gen_t_006f2820_m4pod value)
{
	m_values.push_back(value);
}
