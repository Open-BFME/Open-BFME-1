// ?rva0024e990@Rva0024E990Owner@@QAEXPAVObject@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Retail RVA 0x0024E990, 163 bytes. The helper is called by the
// SlaughterHordeContain accounting path; the owner remains address-derived.
// Layout evidence: creator Object +0x08, count +0x9bc, AsciiString +0x9c0.

class Player;
class ThingTemplate;

template <typename T>
struct StringBufferData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_padding;
	T m_text[1];
};

#include "string_base.h"

class AsciiString : public StringBase<char>
{

public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	StringBufferData<char> *bufferData() const { return (StringBufferData<char> *)m_data; }
	void releaseBuffer() { StringBase<char>::releaseBuffer(); }
};

#define OBJECT_TU_MEMBERS \
	Player *getControllingPlayer() const;
#include "../object.h"
#undef OBJECT_TU_MEMBERS

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class ScoreKeeper
{
public:
	void addObjectCount(const ThingTemplate *tmpl, int count);
	void addObjectDestroyedCount(const ThingTemplate *tmpl, const Player *byPlayer, int count);
};

static __forceinline Player *controllingPlayerOf(const Object *object)
{
	return object->getControllingPlayer();
}

extern BfmeThingFactory *TheThingFactory;

#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?findTemplate@BfmeThingFactory@@QAEPBVThingTemplate@@ABVAsciiString@@@Z=?j_00028560@@YAXXZ")
#pragma comment(linker, "/alternatename:?addObjectCount@ScoreKeeper@@QAEXPBVThingTemplate@@H@Z=?j_000385fa@@YAXXZ")
#pragma comment(linker, "/alternatename:?addObjectDestroyedCount@ScoreKeeper@@QAEXPBVThingTemplate@@PBVPlayer@@H@Z=?j_00031359@@YAXXZ")

class __declspec(novtable) Rva0024E8E0PrimaryBase
{
public:
	virtual ~Rva0024E8E0PrimaryBase();

protected:
	unsigned char m_objectPrefix[4];
	Object *m_creatorObj;
};

template <int Number>
class __declspec(novtable) Rva0024E8E0SecondaryBase
{
public:
	virtual ~Rva0024E8E0SecondaryBase();
};

class __declspec(novtable) Rva0024E8E0WideSecondaryBase
{
public:
	virtual ~Rva0024E8E0WideSecondaryBase();

private:
	unsigned char m_pad[12];
};

class __declspec(novtable) Rva0024E8E0OpenContainLike
	: public Rva0024E8E0PrimaryBase,
	  public Rva0024E8E0SecondaryBase<1>,
	  public Rva0024E8E0WideSecondaryBase,
	  public Rva0024E8E0SecondaryBase<2>,
	  public Rva0024E8E0SecondaryBase<3>,
	  public Rva0024E8E0SecondaryBase<4>,
	  public Rva0024E8E0SecondaryBase<5>,
	  public Rva0024E8E0SecondaryBase<6>,
	  public Rva0024E8E0SecondaryBase<7>
{
public:
	virtual ~Rva0024E8E0OpenContainLike();

protected:
	unsigned char m_pad[0x3c4];
};

class __declspec(novtable) SlaughterHordeContainBase : public Rva0024E8E0OpenContainLike
{
public:
	virtual ~SlaughterHordeContainBase();

protected:
	unsigned char m_gap[0x9bc - sizeof(Rva0024E8E0OpenContainLike)];
	int m_count;
	AsciiString m_name;
};

class __declspec(novtable) Rva0024E990Owner : public SlaughterHordeContainBase
{
public:
	void rva0024e990(Object *other);
};

// ?rva0024e990@Rva0024E990Owner@@QAEXPAVObject@@@Z
void Rva0024E990Owner::rva0024e990(Object *other)
{
	if ((unsigned int)m_count <= 0)
		return;

	const AsciiString &name = m_name;
	StringBufferData<char> *buffer = name.bufferData();
	if (buffer == 0)
		return;
	if (buffer->m_length == 0)
		return;

	Object *self = other;
	if (self == 0)
		return;

	Player *creatorPlayer;
	Player *otherPlayer;
	const ThingTemplate *tmpl;
	creatorPlayer = controllingPlayerOf(m_creatorObj);
	otherPlayer = controllingPlayerOf(self);
	tmpl = TheThingFactory->findTemplate(name);
	if (creatorPlayer == otherPlayer)
		goto release;
	if (tmpl == 0)
		goto release;

	((ScoreKeeper *)((char *)creatorPlayer + 0x348))->addObjectCount(tmpl, m_count);
	((ScoreKeeper *)((char *)otherPlayer + 0x348))->addObjectDestroyedCount(tmpl, creatorPlayer, m_count);

release:
	m_count = 0;
	m_name.releaseBuffer();
}
