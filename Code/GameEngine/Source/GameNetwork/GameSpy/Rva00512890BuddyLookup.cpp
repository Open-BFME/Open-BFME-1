// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/peerdefs /Ireference/shims/stringinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _BFME_RETAIL_PLAYER_INFO_LAYOUT
#define __PLACEMENT_VEC_NEW_INLINE
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>

typedef int Int;
typedef int GPProfile;
typedef int GPEnum;

template <typename T> class StringBase
{
	friend class UnicodeString;

	private:
	void releaseBuffer();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	void translate(const AsciiString &src);

	void clear(void)
	{
		StringBase<unsigned short>::releaseBuffer();
	}
};

class BuddyInfo
{
public:
	~BuddyInfo(void);

	GPProfile m_id;
	AsciiString m_name;
	AsciiString m_email;
	AsciiString m_countryCode;
	GPEnum m_status;
	UnicodeString m_statusString;
	UnicodeString m_locationString;
};

class Gen_004E9FD0
{
public:
	Gen_004E9FD0(const Gen_004E9FD0 &other);
	~Gen_004E9FD0(void)
	{
		reinterpret_cast<BuddyInfo *>(this)->~BuddyInfo();
	}

	GPProfile m_id;
	AsciiString m_name;
	AsciiString m_email;
	AsciiString m_countryCode;
	GPEnum m_status;
	UnicodeString m_statusString;
	UnicodeString m_locationString;
};

typedef std::map<GPProfile, Gen_004E9FD0> BuddyInfoMap;

class GameSpyInfo
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual BuddyInfoMap *getBuddyMap(void) = 0;
	virtual BuddyInfoMap *getBuddyRequestMap(void) = 0;
};

extern GameSpyInfo *TheGameSpyInfo;

// ?Rva00512890@@YGHHAAVUnicodeString@@@Z
int __stdcall Rva00512890(Int profileID, UnicodeString &result)
{
	BuddyInfoMap *buddies = TheGameSpyInfo->getBuddyMap();
	for (BuddyInfoMap::const_iterator it = buddies->begin(); it != buddies->end(); ++it)
	{
		Gen_004E9FD0 info = it->second;
		if (info.m_id == profileID)
		{
			result.translate(info.m_name);
			if (!info.m_status)
				return 2;
			return 1;
		}
	}

	buddies = TheGameSpyInfo->getBuddyRequestMap();
	for (BuddyInfoMap::const_iterator it = buddies->begin(); it != buddies->end(); ++it)
	{
		Gen_004E9FD0 info = it->second;
		if (info.m_id == profileID)
		{
			result.translate(info.m_name);
			return 4;
		}
	}

	result.clear();
	return 0x1000;
}
