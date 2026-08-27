// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: retail-layout C++ conversion of the AttackNugget parser.

class INI;
typedef void (*INIFieldParseProc)(INI *, void *, void *, const void *);

struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class INI
{
public:
	void initFromINI(void *, const FieldParse *);
	static void parseInt(INI *, void *, void *, const void *);
	static void parseLookupList(INI *, void *, void *, const void *);
	static void parseReal(INI *, void *, void *, const void *);
};

class RadiusDecalTemplate
{
public:
	static void parseRadiusDecalTemplate(INI *, void *, void *, const void *);

private:
	unsigned char m_retailLayout[0x30];
};

class ObjectCreationNugget
{
public:
	virtual void create();
};

class ObjectCreationList
{
public:
	void addObjectCreationNugget(ObjectCreationNugget *);
};

extern "C" const char TheWeaponSlotTypeNamesLookupList;

class AttackNugget : public ObjectCreationNugget
{
public:
	AttackNugget();
	virtual void create();

	static void parse(INI *, void *, void *, const void *);

private:
	RadiusDecalTemplate m_deliveryDecalTemplate;
	float m_deliveryDecalRadius;
	int m_numberOfShots;
	int m_weaponSlot;
};

// ?parse@AttackNugget@@SAXPAVINI@@PAX1PBX@Z
// dup_59eb90 absent-from-retail
void AttackNugget::parse(INI *ini, void *instance, void *, const void *)
{
	static const FieldParse myFieldParse[] =
	{
		{ "NumberOfShots", INI::parseInt, 0, 0x38 },
		{ "WeaponSlot", INI::parseLookupList, &TheWeaponSlotTypeNamesLookupList, 0x3c },
		{ "DeliveryDecal", RadiusDecalTemplate::parseRadiusDecalTemplate, 0, 0x04 },
		{ "DeliveryDecalRadius", INI::parseReal, 0, 0x34 },
		{ 0, 0, 0, 0 }
	};

	AttackNugget *nugget = new AttackNugget;
	ini->initFromINI(nugget, myFieldParse);
	((ObjectCreationList *)instance)->addObjectCreationNugget(nugget);
}
