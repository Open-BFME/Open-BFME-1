class BfmeThingDSB;

class SpecialAbilityUpdate
{
protected:
	bool continuePreparation();
	friend class BfmeThingDSB;
};

class BfmeThingDSB
{
public:
	bool bfmeGoDSB();
	char m_bfmeHead[0xf8];
	char m_bfmeFlag;
};

bool BfmeThingDSB::bfmeGoDSB()
{
	if (m_bfmeFlag)
		return false;
	return ((SpecialAbilityUpdate *)this)->continuePreparation();
}
