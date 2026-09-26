// Open-BFME: GenericObjectCreationNugget asset collection, retail 0x001D7F90.
// The adjacent constructor fixes the vector, string, FX, and particle fields.

template <typename T>
class StringBase
{
friend class AsciiString;

private:
	StringBase() {}
	StringBase(const StringBase<T> &that);
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text);
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString();
	bool isEmpty() const
	{
		return m_data == 0 || *(const unsigned short *)(m_data + 4) == 0;
	}

	char *m_data;
};

AsciiString operator+(AsciiString left, const AsciiString &right);

class AssetList
{
public:
	AssetList &operator<<(const AsciiString &name);
};

class Gen_002DDCC0Target
{
public:
	void bfmeForward(void *first, void *second);
};

class Rva0020AA00Target
{
public:
	void notify(int first, int second);
};

class ThingTemplate;

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern BfmeThingFactory *Rva0020AA00TheRegistry;

class Rva003392B0TemplateStore
{
public:
	void *findTemplate(const AsciiString &name);
};

class ParticleSystemManager
{
};

struct GenericObjectCreationNuggetAnimSet
{
	AsciiString m_initial;
	AsciiString m_flying;
	AsciiString m_final;
};

struct GenericObjectCreationNuggetStringVector
{
	AsciiString *m_begin;
	AsciiString *m_end;
	AsciiString *m_capacity;
};

struct GenericObjectCreationNuggetAnimSetVector
{
	GenericObjectCreationNuggetAnimSet *m_begin;
	GenericObjectCreationNuggetAnimSet *m_end;
	GenericObjectCreationNuggetAnimSet *m_capacity;
};

class GenericObjectCreationNugget
{
public:
	void GetAssetList(AssetList &assets, void *context) const;

private:
	char m_vftable[4];
	GenericObjectCreationNuggetStringVector m_names;
	AsciiString m_putInContainer;
	GenericObjectCreationNuggetAnimSetVector m_animSets;
	Gen_002DDCC0Target *m_fxFinal;
	AsciiString m_particleSysName;
};

void GenericObjectCreationNugget::GetAssetList(AssetList &assets, void *context) const
{
	if (m_fxFinal)
		m_fxFinal->bfmeForward(&assets, context);

	if (!m_putInContainer.isEmpty())
	{
		Rva0020AA00Target *container = (Rva0020AA00Target *)Rva0020AA00TheRegistry->findTemplate(m_putInContainer);
		if (container)
			container->notify((int)&assets, (int)context);
	}

	for (AsciiString *name = m_names.m_begin; name != m_names.m_end; ++name)
	{
		Rva0020AA00Target *prototype = (Rva0020AA00Target *)Rva0020AA00TheRegistry->findTemplate(*name);
		if (prototype)
			prototype->notify((int)&assets, (int)context);
	}

	if (m_particleSysName.m_data != 0 &&
		*(const unsigned short *)(m_particleSysName.m_data + 4) != 0)
	{
		(*(Rva003392B0TemplateStore **)0x012F64BC)->findTemplate(m_particleSysName);
	}

	for (GenericObjectCreationNuggetAnimSet *animSet = m_animSets.m_begin;
		animSet != m_animSets.m_end; ++animSet)
	{
		AsciiString prefix("a*");
		if (!animSet->m_initial.isEmpty())
			assets << prefix + animSet->m_initial;
		if (!animSet->m_flying.isEmpty())
			assets << prefix + animSet->m_flying;
		if (!animSet->m_final.isEmpty())
			assets << prefix + animSet->m_final;
	}
}
