// Retail 0x000F9820 (143 bytes).
// The address-derived owner uses the matched BfmeVecVLH accessor and the
// matched BfmeThingFactory::findTemplate lookup.

struct Rva000F9820Record
{
	char pad00[0x30];
	int value30;
	int value34;
};

struct BfmeElemVLH
{
};

class BfmeVecVLH
{
public:
	BfmeElemVLH *bfmeAtVLH(int index);
	int value00;
	Rva000F9820Record *begin;
	Rva000F9820Record *end;
	int value0c;
	int value10;
};

class Rva000F9270FactoryLookup
{
public:
	void *evaluate(void *argument);
};

class AsciiString;
class ThingTemplate;

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &record);
};

class BfmeUseB980
{
public:
	void *bfmeApply980B(int first, int second);
};

struct BfmeGameLogic
{
	char pad00[0x3c];
	int frame;
};

// Retail's global at 0x012EF1D8 is EA's `ThingFactory *TheThingFactory` (name
// from ?findByTemplateID@ThingFactory@@QAEPBVThingTemplate@@, class declared in
// common/System/game_engine_subsystems.h).  This TU keeps the address-derived
// BfmeOtherBN view for the member call and casts the singleton to it.
class ThingFactory;
extern ThingFactory *TheThingFactory;
class GameLogic;

// retail 0x012F0898; the TU-local view above is BfmeGameLogic
extern GameLogic *TheGameLogic;

class Rva000F9820 : public BfmeVecVLH
{
public:
	float getValue(int divisor, int *out);
};

float Rva000F9820::getValue(int divisor, int *out)
{
	Rva000F9820Record *record;
	void *key;
	BfmeUseB980 *product;
	int value;

	record = (Rva000F9820Record *)bfmeAtVLH(divisor);
	if (record)
	{
		if (record->value30 == -1)
		{
			if (out)
				*out = (int)((Rva000F9270FactoryLookup *)record)->evaluate((void *)value10);
			return 1.0f;
		}

		key = (void *)value10;
		product = (BfmeUseB980 *)((BfmeThingFactory *)TheThingFactory)->findTemplate(*reinterpret_cast<const AsciiString *>(record));
		if (product)
		{
			value = (int)product->bfmeApply980B((int)key, record->value34);
			if (value > 0)
			{
				BfmeGameLogic *logic = (BfmeGameLogic *)TheGameLogic;
				return ((float)(unsigned int)logic->frame - (float)record->value30) / value;
			}
		}
	}
	return 0.0f;
}
