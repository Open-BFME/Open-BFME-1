// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /MD /EHsc /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring8 /ICode/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Retail 0x0076D850, 909 bytes: W3DModelDraw's public-bone name resolver.
// The BFME string wrapper is kept local: its one-pointer StringBase layout and
// releaseBuffer cleanup are the layout witnessed by the retail body.

#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE 1

#include "WWMath/matrix3d.h"
#include "WW3D2/RendObj.h"
#include <map>

typedef int Int;
typedef bool Bool;

template <typename T>
struct Rva0076D850StringData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	Rva0076D850StringData<T> *m_data;

public:
	void toLower();
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other)
		: StringBase<char>(*(const StringBase<char> *)&other) {}
	~AsciiString() { releaseBuffer(); }

	Bool isNone() const;
	Bool isEmpty() const
	{
		return m_data == 0 || m_data->m_length == 0;
	}
	const char *str() const
	{
		return m_data ? m_data->m_text : (const char *)0x0107388B;
	}
	void toLower() { StringBase<char>::toLower(); }
	void format(AsciiString format, ...);

private:
	void releaseBuffer();
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

inline NameKeyType NAMEKEY(const AsciiString &name)
{
	return TheNameKeyGenerator->nameToKey(name.str());
}

struct PristineBoneInfo
{
	Matrix3D mtx;
	Int boneIndex;
};

typedef std::map<NameKeyType, PristineBoneInfo, std::less<NameKeyType> >
	PristineBoneInfoMap;

extern void setFPMode();

static Bool findSingleBone(RenderObjClass *robj, const AsciiString &boneName,
	Matrix3D &mtx, Int &boneIndex)
{
	if (boneName.isNone() || boneName.isEmpty())
		return false;

	boneIndex = robj->Get_Bone_Index(boneName.str());
	if (boneIndex != 0)
	{
		mtx = robj->Get_Bone_Transform(boneIndex);
		return true;
	}
	else
	{
		return false;
	}
}

static Bool findSingleSubObj(RenderObjClass *robj, const AsciiString &boneName,
	Matrix3D &mtx, Int &boneIndex)
{
	if (boneName.isNone() || boneName.isEmpty())
		return false;

	RenderObjClass *childObject = robj->Get_Sub_Object_By_Name(boneName.str());
	if (childObject)
	{
		mtx = childObject->Get_Transform();
		for (Int subObj = 0; subObj < robj->Get_Num_Sub_Objects(); ++subObj)
		{
			RenderObjClass *test = robj->Get_Sub_Object(subObj);
			if (test == childObject)
				boneIndex = robj->Get_Sub_Object_Bone_Index(0, subObj);
			if (test)
				test->Release_Ref();
		}
		childObject->Release_Ref();
		return true;
	}
	else
	{
		return false;
	}
}

// ?doSingleBoneName@@YA_NPAVRenderObjClass@@ABVAsciiString@@AAV?$map@W4NameKeyType@@UPristineBoneInfo@@U?$less@W4NameKeyType@@@_STL@@V?$allocator@U?$pair@$$CBW4NameKeyType@@UPristineBoneInfo@@@_STL@@@4@@_STL@@@Z
static __declspec(noinline) Bool doSingleBoneName(RenderObjClass *robj, const AsciiString &boneName,
	PristineBoneInfoMap &map)
{
	Bool foundAsBone = false;
	Bool foundAsSubObj = false;

	PristineBoneInfo info;
	AsciiString tmp;

	AsciiString boneNameTmp = boneName;
	boneNameTmp.toLower();

	setFPMode();

	if (findSingleBone(robj, boneNameTmp, info.mtx, info.boneIndex))
	{
		map[NAMEKEY(boneNameTmp)].PristineBoneInfo::PristineBoneInfo(info);
		foundAsBone = true;
	}

	for (Int i = 1; i <= 99; ++i)
	{
		tmp.format(AsciiString("%s%02d"), boneNameTmp.str(), i);
		if (findSingleBone(robj, tmp, info.mtx, info.boneIndex))
		{
			map[NAMEKEY(tmp)].PristineBoneInfo::PristineBoneInfo(info);
			foundAsBone = true;
		}
		else
		{
			break;
		}
	}

	if (!foundAsBone)
	{
		if (findSingleSubObj(robj, boneNameTmp, info.mtx, info.boneIndex))
		{
			map[NAMEKEY(boneNameTmp)].PristineBoneInfo::PristineBoneInfo(info);
			foundAsSubObj = true;
		}

		for (Int i = 1; i <= 99; ++i)
		{
			tmp.format(AsciiString("%s%02d"), boneNameTmp.str(), i);
			if (findSingleSubObj(robj, tmp, info.mtx, info.boneIndex))
			{
				map[NAMEKEY(tmp)].PristineBoneInfo::PristineBoneInfo(info);
				foundAsSubObj = true;
			}
			else
			{
				break;
			}
		}
	}

	return foundAsBone || foundAsSubObj;
}

// ?rva0076D850Anchor@@YA_NPAVRenderObjClass@@ABVAsciiString@@AAV?$map@W4NameKeyType@@UPristineBoneInfo@@U?$less@W4NameKeyType@@@_STL@@V?$allocator@U?$pair@$$CBW4NameKeyType@@UPristineBoneInfo@@@_STL@@@4@@_STL@@@Z
__declspec(noinline) Bool rva0076D850Anchor(RenderObjClass *robj,
	const AsciiString &boneName, PristineBoneInfoMap &map)
{
	return doSingleBoneName(robj, boneName, map);
}
