class BfmeFoundAKB
{
public:
	virtual void bfmeSpareAKB0();
	virtual bool bfmeTestAKB();
};

enum SpecialPowerType {};
class SpecialPowerModuleInterface;
struct AICommandParms;

// retail ILT 0x0001B185 -> 0x001C3920 is the matched
// Object::findSpecialPowerModuleInterface row
class Object
{
public:
	SpecialPowerModuleInterface *findSpecialPowerModuleInterface(SpecialPowerType type) const;
};

// retail ILT 0x00006EF1 -> 0x0027C1A0 is the matched (non-virtual call of the)
// AIUpdateInterface::isAllowedToRespondToAiCommands row
class AIUpdateInterface
{
	friend class BfmeThingAKB;
protected:
	virtual bool isAllowedToRespondToAiCommands(const AICommandParms *parms) const;
};

class BfmeSubAKB;

class BfmeThingAKB
{
public:
	bool bfmeAskAKB(int *what);
	unsigned char m_bfmeHead[8];
	BfmeSubAKB *m_bfmeSub;
};

bool BfmeThingAKB::bfmeAskAKB(int *what)
{
	if (!((AIUpdateInterface *)this)->AIUpdateInterface::isAllowedToRespondToAiCommands((const AICommandParms *)what))
		return false;
	BfmeFoundAKB *found = (BfmeFoundAKB *)((Object *)m_bfmeSub)->findSpecialPowerModuleInterface((SpecialPowerType)0x2e);
	if (found != 0 && !found->bfmeTestAKB())
		return *what == 0x1b;
	return true;
}
