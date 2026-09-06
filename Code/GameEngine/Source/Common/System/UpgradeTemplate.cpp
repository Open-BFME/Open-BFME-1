// cl: /DNDEBUG /MD /EHsc
// readable body of ??0UpgradeTemplate@@QAE@XZ: Code/GameEngine/Source/Common/System/Upgrade.cpp
// readable body of ?cacheButtonImage@UpgradeTemplate@@QAEXXZ: Code/GameEngine/Source/Common/System/Upgrade.cpp
// readable body of ?calcTimeToBuild@UpgradeTemplate@@QBEHPAVPlayer@@@Z: Code/GameEngine/Source/Common/System/Upgrade.cpp

// UpgradeTemplate is built, and two accessors read one field each.
//
//   UpgradeTemplate()   zero the scalars, -1 the classification
//   cacheButtonImage    resolve the button image name once, then drop it
//   calcTimeToBuild     the build time in frames
//
// They used to sit in three files with three accounts of the class: the
// constructor named every field, the two accessors padded to the single field
// each reads. The merged layout is the constructor's, which is the only one
// that names the whole object, and the other two agree with it field for
// field -- m_buildTime at +0x18, m_buttonImageName at +0x110 and the image it
// resolves into at +0x114.
//
// The names come from retail's INI field table at 0x00C88B60 joined to
// upstream's m_upgradeFieldParseTable on the key: retail supplies the offset,
// upstream only the name. Fields the table does not reach keep their offset for
// a name.
//
// Two more bodies for this class stay out, each for a reason worth recording.
// UpgradeCenter::newUpgrade calls the field at +0x20 m_upgradeMaskIndex where
// the constructor calls it m_academyClassificationType, and nothing in these
// three bodies settles which name it should carry. The destructor is stranger:
// it byte-matches only while its two sound members are declared as a private
// class of its own, because retail's member-destructor calls there do NOT go to
// the address ??1AudioEventRTS@@UAE@XZ is pinned to, while this constructor's
// member-construction calls do go to ??0AudioEventRTS@@QAE@PAXH@Z. One of those
// two pins is naming the wrong address; until that is settled the destructor
// cannot share a declaration with the constructor, and folding it in here made
// exactly that call site come out five bytes different.

class Player;
class Image;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();

	bool isNotEmpty() const
	{
		return m_data && *(unsigned short *)(m_data + 4) != 0;
	}

	void clear();

private:
	char *m_data;
};

class MappedImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern MappedImageCollection *TheMappedImageCollection;

extern int g_bfmeDefaultBG;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	AudioEventRTS(void *event = &g_bfmeDefaultBG, int value = 0);
	virtual ~AudioEventRTS();

private:
	unsigned char m_data[0x6c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeTemplate
{
public:
	UpgradeTemplate();

	void cacheButtonImage();
	int calcTimeToBuild(Player *player) const;

protected:
	virtual ~UpgradeTemplate();				// vptr at this+0x00

private:
	unsigned int m_type;					// this+0x04
	AsciiString m_member08;					// this+0x08
	unsigned int m_nameKey;					// this+0x0C
	AsciiString m_displayNameLabel;				// this+0x10
	AsciiString m_member14;					// this+0x14
	float m_buildTime;					// this+0x18
	int m_cost;						// this+0x1C
	int m_academyClassificationType;			// this+0x20
	AsciiString m_member24;					// this+0x24
	AudioEventRTS m_researchSound;				// this+0x28
	AudioEventRTS m_unitSpecificSound;			// this+0x98
	UpgradeTemplate *m_next;				// this+0x108
	UpgradeTemplate *m_prev;				// this+0x10C
	AsciiString m_buttonImageName;				// this+0x110
	const Image *m_buttonImage;				// this+0x114
	AsciiString m_member118;				// this+0x118
	bool m_flag11c;						// this+0x11C
	bool m_flag11d;						// this+0x11D
};

// ??0UpgradeTemplate@@QAE@XZ
// BFME constructs both sound members with the shared default object at
// 0x01336E50.
UpgradeTemplate::UpgradeTemplate()
{
	m_cost = 0;
	m_type = 0;
	m_nameKey = 0;
	m_buildTime = 0.0f;
	m_next = 0;
	m_prev = 0;
	m_buttonImage = 0;
	m_flag11c = false;
	m_flag11d = false;
	m_academyClassificationType = -1;
}

// ?cacheButtonImage@UpgradeTemplate@@QAEXXZ
void UpgradeTemplate::cacheButtonImage()
{
	if (m_buttonImageName.isNotEmpty())
	{
		m_buttonImage =
			TheMappedImageCollection->findImageByName(m_buttonImageName);
		m_buttonImageName.clear();
	}
}

// ?calcTimeToBuild@UpgradeTemplate@@QBEHPAVPlayer@@@Z
int UpgradeTemplate::calcTimeToBuild(Player *) const
{
	return m_buildTime * 30.0f;
}
