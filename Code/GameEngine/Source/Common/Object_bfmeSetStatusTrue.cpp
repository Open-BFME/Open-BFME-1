// ?bfmeSetStatusTrue@Object@@QAEXV?$BitFlags@$0CN@@@@Z
template <int Bits>
class BitFlags
{
	unsigned int m_bits[(Bits + 31) / 32];
};

class Object
{
public:
	void setStatus(BitFlags<45>, bool);
	void bfmeSetStatusTrue(BitFlags<45>);
};

void Object::bfmeSetStatusTrue(BitFlags<45> flags)
{
	setStatus(flags, true);
}
