namespace _STL
{
template <int Bits>
class bitset
{
public:
	bitset<Bits> &set(unsigned int, int);
};

class Bitset67SetShim
{
public:
	bitset<67> &set(unsigned int pos, int val);
};

template <int Bits>
bitset<Bits> &bitset<Bits>::set(unsigned int pos, int val)
{
	return ((Bitset67SetShim *)this)->set(pos, val);
}

template bitset<67> &bitset<67>::set(unsigned int, int);
}

template <int Bits>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	bool testSetAndClear(const BitFlags<Bits> &, const BitFlags<Bits> &) const;
};

class BitFlags116TestSetAndClearShim
{
public:
	bool testSetAndClear(const BitFlags<116> &a, const BitFlags<116> &b) const;
};

template <int Bits>
bool BitFlags<Bits>::testSetAndClear(const BitFlags<Bits> &a, const BitFlags<Bits> &b) const
{
	return ((BitFlags116TestSetAndClearShim const *)this)->testSetAndClear(
		(const BitFlags<116> &)a, (const BitFlags<116> &)b);
}

template bool BitFlags<116>::testSetAndClear(const BitFlags<116> &, const BitFlags<116> &) const;
