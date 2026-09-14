// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: LivingWorldPlayerArmy scalar-deleting destructor at retail RVA
// 0x00363E00 (30 bytes). Its exact default and copy constructors, matched
// complete destructor at 0x00362B20, and recovered Living World vector/parser
// paths establish the 0x58-byte object. The wrapper calls its destructor
// through ILT 0x00006C4E before conditionally invoking operator delete.

class LivingWorldPlayerArmy
{
public:
	~LivingWorldPlayerArmy();
};

void forceLivingWorldPlayerArmyDelete(LivingWorldPlayerArmy *army)
{
	delete army;
}
