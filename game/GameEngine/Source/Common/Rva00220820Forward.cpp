// Retail 0x00220820 forwards the second argument's dword at +4 to the first.
class BfmeItem1005
{
public:
	void bfmeDoD1005(int value);
};

struct Rva00220820Pair
{
	int first;
	int second;
};

void __cdecl rva00220820Forward(BfmeItem1005 *receiver, const Rva00220820Pair *value)
{
	receiver->bfmeDoD1005(value->second);
}
