// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;

extern "C" void * __cdecl memset(void *destination, int value, unsigned int count);
#pragma intrinsic(memset)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other);

private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString &operator=(const UnicodeString &other);

private:
	unsigned short *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	unsigned char m_pad000[4];
	Overridable *m_override;
	unsigned char m_pad008[0x20 - 8];
	AsciiString m_name;
};

struct BfmeExperienceTrackerFields
{
	unsigned char m_pad000[0x0c];
	int m_veterancyLevel;
	unsigned char m_pad010[0x24 - 0x10];
	unsigned char m_flag;
	unsigned char m_pad025[3];
	int m_experience;
};

struct BfmeUpgradeMask
{
	UnsignedInt m_words[6];
};

struct BfmeZeroVector
{
	UnsignedInt x;
	UnsignedInt y;
	UnsignedInt z;

	BfmeZeroVector()
	{
		memset(this, 0, sizeof(*this));
	}
};

struct BfmeObjectInfo
{
	UnsignedInt m_reserved000;
	AsciiString m_templateName;
	int m_veterancyLevel;
	int m_experience;
	BfmeUpgradeMask m_completedUpgrades;
	BfmeZeroVector m_zeroVector;
	unsigned char m_pad034[5];
	unsigned char m_experienceFlag;
	unsigned char m_pad03a[2];
	UnsignedInt m_value03c;
	UnsignedInt m_value040;
	UnsignedInt m_value044;
	UnsignedInt m_value048;
	AsciiString m_commandSetOverride;
	unsigned char m_pad050[0x78 - 0x50];
	UnicodeString m_displayName;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void bfmeBuildObjectInfo(BfmeObjectInfo *info) const;

private:
	const ThingTemplate *getFinalTemplate() const
	{
		const ThingTemplate *thingTemplate = m_template;
		if (thingTemplate && thingTemplate->m_override)
			thingTemplate = reinterpret_cast<const ThingTemplate *>(thingTemplate->m_override->getFinalOverride());
		return thingTemplate;
	}

	unsigned char m_vtable[4];
	ThingTemplate *m_template;
	unsigned char m_pad008[0x210 - 8];
	BfmeExperienceTrackerFields *m_experienceTracker;
	unsigned char m_pad214[0x224 - 0x214];
	BfmeUpgradeMask m_completedUpgrades;
	unsigned char m_pad23c[0x374 - 0x23c];
	UnsignedInt m_value374;
	UnsignedInt m_value378;
	UnsignedInt m_value37c;
	UnsignedInt m_value380;
	unsigned char m_pad384[4];
	UnicodeString m_displayName;
	AsciiString m_commandSetOverride;
};

void Object::bfmeBuildObjectInfo(BfmeObjectInfo *info) const
{
	BfmeExperienceTrackerFields *experienceTracker = m_experienceTracker;
	info->m_templateName = getFinalTemplate()->m_name;
	info->m_veterancyLevel = experienceTracker->m_veterancyLevel;
	info->m_experience = experienceTracker->m_experience;
	info->m_experienceFlag = experienceTracker->m_flag;
	info->m_completedUpgrades = m_completedUpgrades;
	info->m_value03c = m_value374;
	info->m_value044 = m_value37c;
	info->m_value040 = m_value378;
	info->m_value048 = m_value380;
	info->m_displayName = m_displayName;
	info->m_commandSetOverride = m_commandSetOverride;
	info->m_zeroVector = BfmeZeroVector();
}
