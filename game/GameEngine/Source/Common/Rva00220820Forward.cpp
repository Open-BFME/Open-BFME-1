// Retail 0x00220820 forwards the second argument's dword at +4 to the first.
class BfmeItem1005;

class BfmeThing916D
{
public:
	void bfmeGo916D(void *value);
};

struct Rva00220820Pair
{
	int first;
	int second;
};

void __cdecl rva00220820Forward(BfmeItem1005 *receiver, const Rva00220820Pair *value)
{
	((BfmeThing916D *)receiver)->bfmeGo916D((void *)value->second);
}
