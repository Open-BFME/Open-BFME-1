// cl: /DNDEBUG /MD /EHsc
// BFME2 GenericObjectCreationNugget::parseObject reconstruction.

struct FieldParse
{
	const char *token;
	void *parse;
	const void *userData;
	int offset;
};

class MultiIniFieldParse
{
public:
	MultiIniFieldParse()
	{
		m_count = 0;
		for (int i = 0; i < 16; ++i)
		{
			m_extraOffset[i] = 0;
			m_fieldParse[i] = 0;
		}
	}

	void add(const FieldParse *, unsigned int = 0);

private:
	const FieldParse *m_fieldParse[16];
	unsigned int m_extraOffset[16];
	int m_count;
};

class INI
{
public:
	void initFromINIMulti(void *, const MultiIniFieldParse &);
};

class ObjectCreationNugget
{
};

class GenericObjectCreationNugget : public ObjectCreationNugget
{
public:
	GenericObjectCreationNugget();

	static void parseObject(INI *, void *, void *, const void *);

	char m_beforeNameAreObjects[0x114];
	bool m_nameAreObjects;
	char m_retailTail[0x33];
};

class ObjectCreationList
{
public:
	void addObjectCreationNugget(ObjectCreationNugget *);
};

static const FieldParse s_commonFieldParse[] =
{
	{ 0, 0, 0, 0 }
};

static const FieldParse s_objectFieldParse[] =
{
	{ 0, 0, 0, 0 }
};

void GenericObjectCreationNugget::parseObject(INI *ini, void *instance,
	void *, const void *)
{
	MultiIniFieldParse fields;
	fields.add(s_commonFieldParse);
	fields.add(s_objectFieldParse);

	GenericObjectCreationNugget *nugget = new GenericObjectCreationNugget;
	nugget->m_nameAreObjects = true;

	ini->initFromINIMulti(nugget, fields);
	((ObjectCreationList *)instance)->addObjectCreationNugget(nugget);
}
