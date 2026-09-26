// ?updateObjectReference@BfmeObjectReferenceStore@@QAEXPAVObject@@_N@Z
// partial score=0.85 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef unsigned short UnsignedShort;

class AsciiString
{
public:
	struct Header
	{
		int m_references;
		unsigned short m_length;
	};

	Header *m_data;
};

class PlayerTemplate
{
public:
	char m_pad00[0x118];
	Bool m_isActive;
};

class Player
{
public:
	char m_pad00[4];
	PlayerTemplate *m_template;
};

class Object;

class ObjectReferenceFilter
{
public:
	Bool accepts(Object *object, Player *player);
};

class Object
{
public:
	Player *getControllingPlayer() const;
	void addObjectReference(const AsciiString *name);
	void removeObjectReference(const AsciiString *name, int value);
	void *getVisionBonusSource() const;
};

class PlayerList
{
public:
	Player *getPlayer(UnsignedShort index);
};

class VisionBonusSource
{
public:
	void apply(int value, int mode);
};

extern PlayerList *ThePlayers;

class BfmeObjectReferenceStore
{
public:
	void updateObjectReference(Object *object, Bool adding);

private:
	char m_pad00[0x14];
	int m_mode;
	ObjectReferenceFilter m_filter;
	AsciiString m_name;
	int m_value;
	UnsignedShort m_mask;
};

#pragma comment(linker, "/alternatename:?getControllingPlayer@ObjectReferenceObject@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?accepts@ObjectReferenceFilter@@QAE_NPAVObject@@PAVPlayer@@@Z=?j_0001da34@@YAXXZ")
#pragma comment(linker, "/alternatename:?addObjectReference@ObjectReferenceObject@@QAEXPBVAsciiString@@@Z=?j_0001ef9c@@YAXXZ")
#pragma comment(linker, "/alternatename:?removeObjectReference@ObjectReferenceObject@@QAEXPBVAsciiString@@H@Z=?j_00037a56@@YAXXZ")
#pragma comment(linker, "/alternatename:?getVisionBonusSource@ObjectReferenceObject@@QBEPAXXZ=?j_000202ed@@YAXXZ")
#pragma comment(linker, "/alternatename:?getPlayer@PlayerList@@QAEPAVPlayer@@G@Z=?j_0001dde5@@YAXXZ")
#pragma comment(linker, "/alternatename:?apply@VisionBonusSource@@QAEXHH@Z=?j_0001c0da@@YAXXZ")

// ?updateObjectReference@BfmeObjectReferenceStore@@QAEXPAVObject@@_N@Z
void BfmeObjectReferenceStore::updateObjectReference(Object *rawObject,
	Bool adding)
{
	Object *object = rawObject;
	if (object == 0)
		return;

	if (m_mode == 0)
		return;

	if (m_mode == 2)
	{
		if (object->getControllingPlayer() != 0)
		{
			PlayerTemplate *playerTemplate =
				object->getControllingPlayer()->m_template;
			if (playerTemplate == 0)
				return;
			if (!playerTemplate->m_isActive)
				return;
		}
	}

	if (m_mode == 3)
	{
		if (object->getControllingPlayer() != 0)
		{
			PlayerTemplate *playerTemplate =
				object->getControllingPlayer()->m_template;
			if (playerTemplate != 0 && playerTemplate->m_isActive)
				return;
		}
	}

	Player *player = 0;
	if (m_mask != 0)
		player = ThePlayers->getPlayer(m_mask);
	if (!m_filter.accepts(object, player))
		return;

	if (m_name.m_data != 0 && m_name.m_data->m_length != 0)
	{
		if (adding)
			object->addObjectReference(&m_name);
		else
			object->removeObjectReference(&m_name, -1);
	}

	if (m_value != 0)
	{
		VisionBonusSource *source =
			reinterpret_cast<VisionBonusSource *>(object->getVisionBonusSource());
		if (source == 0)
			return;
		if (adding)
			source->apply(m_value, 0);
		else
			source->apply(m_value, 0x3b9ac9ff);
	}
}
