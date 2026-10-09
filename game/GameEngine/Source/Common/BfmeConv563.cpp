struct Elem003B6FD0;
class LivingWorldPlayerArmy;
namespace _STL
{
template <class Value> class allocator;
template <class Value, class Alloc> class vector
{
public:
    Value *erase(Value *, Value *);
};
}

struct BfmePairCAC
{
	int m_bfmeX;
	int m_bfmeY;
	unsigned char m_bfmeTail[8];
};

class BfmeThingCAC
{
public:
	void bfmeGoCAC();
	unsigned char m_bfmeHead[0x10];
	BfmePairCAC m_bfmeA;
	BfmePairCAC m_bfmeB;
};

void BfmeThingCAC::bfmeGoCAC()
{
	reinterpret_cast<_STL::vector<Elem003B6FD0, _STL::allocator<Elem003B6FD0> > *>(&m_bfmeA)
        ->erase((Elem003B6FD0 *)m_bfmeA.m_bfmeX, (Elem003B6FD0 *)m_bfmeA.m_bfmeY);
	reinterpret_cast<_STL::vector<LivingWorldPlayerArmy, _STL::allocator<LivingWorldPlayerArmy> > *>(&m_bfmeB)
        ->erase((LivingWorldPlayerArmy *)m_bfmeB.m_bfmeX, (LivingWorldPlayerArmy *)m_bfmeB.m_bfmeY);
}
