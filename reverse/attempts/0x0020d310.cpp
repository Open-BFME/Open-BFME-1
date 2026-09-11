// ?update@SpawnUnitBehavior@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.9 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;
typedef bool Bool;

enum UpdateSleepTime
{
	UPDATE_SLEEP_5 = 5
};

template <typename T>
struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T>
class StringBase
{
	protected:
	StringBase() : m_data(0) {}

public:
	void releaseBuffer();

	private:
	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	~AsciiString() {}
};

class Player;
class ProductionUpdateInterface;
class CommandButton;

class Object
{
public:
	Player *getControllingPlayer() const;
	ProductionUpdateInterface *getProductionUpdateInterface();
	void doCommandButton(const CommandButton *button, int source, int extra);
};

class Rva00367E30Logic
{
public:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
};

#define TheBfmeGameLogic (*(Rva00367E30Logic **)0x012F0898)

struct Rva0020AA00Target
{
};

class Rva0020AA00Registry
{
public:
	Rva0020AA00Target *lookup(const int &key);
};

#define Rva0020AA00TheRegistry (*(Rva0020AA00Registry **)0x012EF1D8)

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
};

#define TheControlBar (*(ControlBar **)0x012F33F8)

class Rva000C7CD0Obj
{
};

class Rva000C7CD0
{
public:
	Bool ok(Rva000C7CD0Obj *object, int flags);
};

class BfmeThingDNA
{
public:
	virtual AsciiString *bfmeGoDNA(AsciiString *other);
};

class ProductionEntry
{
public:
	unsigned char m_pad00[0x08];
	Rva000C7CD0Obj *m_value08;
	AsciiString m_name0c;
	void *m_value10;
};

class ProductionUpdateInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void process(void *value);
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual UnsignedInt count();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual ProductionEntry *entry();
};

bool operator==(const StringBase<char> &left, const StringBase<char> &right);

class SpawnUnitBehavior
{
public:
	virtual UpdateSleepTime update();
};

#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?getProductionUpdateInterface@Object@@QAEPAVProductionUpdateInterface@@XZ=?j_00003b52@@YAXXZ")
#pragma comment(linker, "/alternatename:?lookup@Rva0020AA00Registry@@QAEPAURva0020AA00Target@@ABH@Z=?j_00028560@@YAXXZ")
#pragma comment(linker, "/alternatename:?ok@Rva000C7CD0@@QAEEPAURva000C7CD0Obj@@H@Z=?j_00022336@@YAXXZ")
#pragma comment(linker, "/alternatename:?findCommandButton@ControlBar@@QAEPBVCommandButton@@ABVAsciiString@@@Z=?j_0003b59d@@YAXXZ")
#pragma comment(linker, "/alternatename:?doCommandButton@Object@@QAEXPBVCommandButton@@HH@Z=?j_000063cf@@YAXXZ")

// ?update@SpawnUnitBehavior@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime SpawnUnitBehavior::update()
{
	volatile AsciiString name;
	Object *object = *reinterpret_cast<Object **>(reinterpret_cast<unsigned char *>(this) - 0x08);
	void *moduleData = *reinterpret_cast<void **>(reinterpret_cast<unsigned char *>(this) - 0x0c);
	unsigned char *rawThis = reinterpret_cast<unsigned char *>(this);
	volatile Bool matched;
	Player *player = object->getControllingPlayer();
	UpdateSleepTime result = UPDATE_SLEEP_5;

	if (player == 0 || TheBfmeGameLogic->m_frame < result ||
		*reinterpret_cast<unsigned char *>(reinterpret_cast<char *>(player) + 0x681) == 0 ||
		(*reinterpret_cast<unsigned char *>(reinterpret_cast<char *>(object) + 0x118) & 0x14) != 0)
		return result;

	ProductionUpdateInterface *production = object->getProductionUpdateInterface();
	if (production != 0 && production->count() > 0)
	{
		if (production->count() <= 1)
			return result;

		ProductionEntry *entry = production->entry();
		Rva000C7CD0Obj *item = entry->m_value08;
		if (item != 0)
		{
			AsciiString *copiedName = reinterpret_cast<BfmeThingDNA *>(rawThis + 0x10)->bfmeGoDNA(
				const_cast<AsciiString *>(&name));
			if (*reinterpret_cast<StringBase<char> *>(copiedName) ==
				*reinterpret_cast<StringBase<char> *>(reinterpret_cast<char *>(item) + 0x20))
				matched = true;
			else
				matched = false;
		}
		else
			matched = false;
		if ((*reinterpret_cast<unsigned int *>(const_cast<AsciiString *>(&name)) & 1) != 0)
			((StringBase<char> *)const_cast<AsciiString *>(&name))->releaseBuffer();
		if (matched)
			production->process((*(ProductionEntry **)&entry)->m_value10);
		return result;
	}

	Rva000C7CD0 *availability = reinterpret_cast<Rva000C7CD0 *>(
		reinterpret_cast<char *>(player) + 0x30);
	if (availability == 0)
		return result;
	Rva0020AA00Target *target = Rva0020AA00TheRegistry->lookup(
		*reinterpret_cast<const int *>(reinterpret_cast<char *>(moduleData) + 0x08));
	if (target == 0 || !availability->ok(reinterpret_cast<Rva000C7CD0Obj *>(target), 0))
		return result;
	const CommandButton *button = TheControlBar->findCommandButton(
		*reinterpret_cast<AsciiString *>(reinterpret_cast<char *>(moduleData) + 0x0c));
	if (*reinterpret_cast<unsigned char *>(reinterpret_cast<char *>(moduleData) + 0x1c) != 0 &&
		*reinterpret_cast<unsigned char *>(rawThis + 0x14) == 0)
		return result;
	if (button != 0)
		object->doCommandButton(button, 2, 0);
	*reinterpret_cast<unsigned char *>(rawThis + 0x14) = 0;
	return result;
}
