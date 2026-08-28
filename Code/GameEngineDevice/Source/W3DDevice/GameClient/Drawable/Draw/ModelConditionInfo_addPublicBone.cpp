// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?addPublicBone@ModelConditionInfo@@QBEXABVAsciiString@@@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw.cpp
// Open-BFME: ModelConditionInfo::addPublicBone, retail 0x00772BF0, 161 bytes.
//
// The reference's body unchanged: skip an empty or none name, lower-case a copy
// of it, and append it to the public bone list unless it is already there.
//
// isEmpty() is inline -- a null data pointer or a zero length word at data+4 --
// while isNone(), the copy constructor, toLower(), the search and the append are
// all out of line, which is what makes the body this short. The list is the
// reference's vector at this+0x40, mutable because the method is const.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <algorithm>

typedef int Int;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &src);			// 0x00887B60
	~AsciiString();						// 0x00887940

	Bool isEmpty(void) const { return m_data == 0 || m_data->length == 0; }
	Bool isNone(void) const;				// 0x008881A0
	void toLower(void);					// 0x00887DA0

	Bool operator==(const AsciiString &other) const;

private:
	struct Header {
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	Header *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class ModelConditionInfo
{
public:
	void addPublicBone(const AsciiString& boneName) const;

private:
	unsigned char m_unmodelled_000[0x40];
	mutable _STL::vector<AsciiString> m_publicBones;	// this+0x40
};

void ModelConditionInfo::addPublicBone(const AsciiString& boneName) const
{
	if (boneName.isEmpty() || boneName.isNone())
		return;

	AsciiString tmp = boneName;
	tmp.toLower();
	if (_STL::find(m_publicBones.begin(), m_publicBones.end(), tmp) == m_publicBones.end())
	{
		m_publicBones.push_back(tmp);
	}
}
