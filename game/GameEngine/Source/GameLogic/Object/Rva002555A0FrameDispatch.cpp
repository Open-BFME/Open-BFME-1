class SpecialPowerTemplate;
class SpecialPowerModuleInterface;

class Object
{
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *power) const;
};

class Rva002555A0Module
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0c(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1c(); virtual void slot20();
	virtual void slot24(unsigned int frame);
};

struct GameLogic
{
	char pad[0x3c];
	unsigned int m_frame;
};
extern GameLogic *TheBfmeGameLogic;

int __cdecl rva002555a0FrameDispatch(const Object *object, const SpecialPowerTemplate *power)
{
	if (object && power)
	{
		SpecialPowerModuleInterface *module = object->getSpecialPowerModule(power);
		if (module)
			((Rva002555A0Module *)module)->slot24(TheBfmeGameLogic->m_frame);
	}
	return 1;
}
