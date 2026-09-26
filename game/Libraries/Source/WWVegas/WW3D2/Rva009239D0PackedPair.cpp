// cl: /O2 /Ob0

struct Rva009239D0Pair
{
	unsigned int low;
	unsigned int high;
};

class Rva009239D0
{
public:
	unsigned int packed(const Rva009239D0Pair *pair) const;
};

unsigned int Rva009239D0::packed(const Rva009239D0Pair *pair) const
{
	return (pair->high << 16) + pair->low;
}
