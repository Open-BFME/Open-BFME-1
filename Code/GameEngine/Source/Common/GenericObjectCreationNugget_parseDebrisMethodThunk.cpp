// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: retail-layout C++ conversion of debris nugget parsing.

struct FieldParse;
extern const FieldParse GenericObjectCreationNuggetCommonFields[];
extern const FieldParse GenericObjectCreationNuggetDebrisFields[];

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class MultiIniFieldParse
{
public:
	MultiIniFieldParse()
	{
		Count = 0;
		for (int i = 0; i < 16; ++i) {
			Offsets[i] = 0;
			Fields[i] = 0;
		}
	}
	void add(const FieldParse *, unsigned int = 0);

private:
	const FieldParse *Fields[16];
	unsigned int Offsets[16];
	unsigned int Count;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMulti(void *, const MultiIniFieldParse &);
};

class ObjectCreationNugget {};

class GenericObjectCreationNugget : public ObjectCreationNugget
{
public:
	GenericObjectCreationNugget();
	static void parseDebris(INI *, void *, void *, const void *);

private:
	char BeforeNameAreObjects[0x114];
	bool NameAreObjects;
	char RetailTail[0x33];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ObjectCreationList.h
class ObjectCreationList
{
public:
	void addObjectCreationNugget(ObjectCreationNugget *);
};

void GenericObjectCreationNugget::parseDebris(INI *ini, void *instance, void *, const void *)
{
	MultiIniFieldParse fields;
	fields.add(GenericObjectCreationNuggetCommonFields);
	fields.add(GenericObjectCreationNuggetDebrisFields);

	GenericObjectCreationNugget *nugget = new GenericObjectCreationNugget;
	nugget->NameAreObjects = false;
	ini->initFromINIMulti(nugget, fields);
	((ObjectCreationList *)instance)->addObjectCreationNugget(nugget);
}
