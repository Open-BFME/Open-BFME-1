// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ivendor/stlport /Ireference/shims/stringbaseascii /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib

#include <hash_map>
#include "string_base.h"

class AsciiString
{
public:
	AsciiString();
	AsciiString(const char *text);
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString();
	AsciiString &operator=(const AsciiString &that)
	{
		((StringBase<char> *)this)->set(
			*(const StringBase<char> *)&that);
		return *this;
	}
	static const AsciiString TheEmptyString;

	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
	};

	bool isEmpty() const
	{
		return m_data == 0 || m_data->m_length == 0;
	}

	int compareNoCase(const AsciiString &that) const;

private:
	Header *m_data;
};

namespace rts
{
	template <typename T> struct hash;
	template <typename T> struct equal_to;

	template <> struct hash<AsciiString>
	{
		size_t operator()(AsciiString value) const;
	};

	template <> struct equal_to<AsciiString>
	{
		bool operator()(const AsciiString &left,
			const AsciiString &right) const;
	};
}

struct DataChunkInfo;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkInput
{
public:
	typedef bool (*Parser)(DataChunkInput &, DataChunkInfo *, void *);

	float readReal();
	AsciiString readAsciiString();
	void registerParser(const AsciiString &label, const AsciiString &parentLabel,
		Parser parser, void *userData);
	bool parse(void *userData);
};

struct Vector3
{
	Vector3() {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

	float X;
	float Y;
	float Z;
};

#define SKYBOX_SLOT(n) virtual void slot##n();

class SkyBoxRenderObject
{
public:
	SKYBOX_SLOT(0) SKYBOX_SLOT(1) SKYBOX_SLOT(2) SKYBOX_SLOT(3)
	SKYBOX_SLOT(4) SKYBOX_SLOT(5) SKYBOX_SLOT(6) SKYBOX_SLOT(7)
	SKYBOX_SLOT(8) SKYBOX_SLOT(9) SKYBOX_SLOT(10) SKYBOX_SLOT(11)
	SKYBOX_SLOT(12) SKYBOX_SLOT(13) SKYBOX_SLOT(14) SKYBOX_SLOT(15)
	SKYBOX_SLOT(16) SKYBOX_SLOT(17) SKYBOX_SLOT(18) SKYBOX_SLOT(19)
	SKYBOX_SLOT(20) SKYBOX_SLOT(21)
	virtual void setPosition(const Vector3 &position);
};

#undef SKYBOX_SLOT

class SkyboxTextureSet
{
public:
	virtual ~SkyboxTextureSet();

	AsciiString m_morningN;
	AsciiString m_morningE;
	AsciiString m_morningS;
	AsciiString m_morningW;
	AsciiString m_morningT;
};

typedef std::hash_map<AsciiString, SkyboxTextureSet *,
	rts::hash<AsciiString>, rts::equal_to<AsciiString> > SkyboxTextureSetMap;

extern SkyboxTextureSetMap TheSkyboxTextureSets;

class WaterRenderObjClass
{
public:
	void replaceSkyboxTexture(const AsciiString &oldTexture,
		const AsciiString &newTexture);
};

class WaterSkyBoxSettingsOwner
{
public:
	void setSkyBoxPosition(float x, float y, float z)
	{
		m_skyBox->setPosition(Vector3(x, y, z));
	}

	void setSkyBoxScale(const float *scale);
	void setSkyBoxRotation007A15A0(const float *rotation);
	void setSkyBoxTexture007A58C0(const AsciiString *texture);
	void loadSkyBoxSettings007A6120(DataChunkInput &file);

	unsigned char m_beforeSkyBox[0x250];
	SkyBoxRenderObject *volatile m_skyBox;
	unsigned char m_beforeSkyBoxTextureName[0x74];
	AsciiString m_skyBoxTextureName;
	AsciiString m_skyBoxTextureNames[5];
};

extern WaterSkyBoxSettingsOwner *TheWaterRenderObj;

void WaterSkyBoxSettingsOwner::setSkyBoxTexture007A58C0(
	const AsciiString *texture)
{
	AsciiString textureName(*texture);
	if (textureName.isEmpty())
		((StringBase<char> *)&textureName)->set("DefaultSky", 10);
	SkyboxTextureSetMap::iterator set = TheSkyboxTextureSets.find(textureName);
	if (set == TheSkyboxTextureSets.end())
		return;

	StringBase<char> *skyBoxTextureName =
		(StringBase<char> *)&m_skyBoxTextureName;
	const StringBase<char> *textureNameBase =
		(const StringBase<char> *)&textureName;
	skyBoxTextureName->set(*textureNameBase);
	AsciiString skyBoxTextures[5];
	skyBoxTextures[0] = set->second->m_morningN;
	skyBoxTextures[1] = set->second->m_morningE;
	skyBoxTextures[2] = set->second->m_morningS;
	skyBoxTextures[3] = set->second->m_morningW;
	skyBoxTextures[4] = set->second->m_morningT;

	for (int index = 0; index < 5; ++index) {
		AsciiString *oldTexture = &m_skyBoxTextureNames[index];
		AsciiString *newTexture = &skyBoxTextures[index];
		if (!oldTexture->isEmpty() &&
			oldTexture->compareNoCase(*newTexture) != 0) {
			reinterpret_cast<WaterRenderObjClass *>(this)->replaceSkyboxTexture(
				*oldTexture, *newTexture);
			((StringBase<char> *)oldTexture)->set(
				*(const StringBase<char> *)newTexture);
		}
	}
}

bool parseSkyBoxSettings007A5BA0(DataChunkInput &file, DataChunkInfo *, void *)
{
	Vector3 position;
	position.X = file.readReal();
	position.Y = file.readReal();
	position.Z = file.readReal();
	float scale = file.readReal();
	float rotation = file.readReal();
	AsciiString texture = file.readAsciiString();

	if (TheWaterRenderObj->m_skyBox != 0) {
		TheWaterRenderObj->setSkyBoxPosition(position.X, position.Y, position.Z);
	}

	TheWaterRenderObj->setSkyBoxScale(&scale);
	TheWaterRenderObj->setSkyBoxRotation007A15A0(&rotation);
	TheWaterRenderObj->setSkyBoxTexture007A58C0(&texture);
	return true;
}

void WaterSkyBoxSettingsOwner::loadSkyBoxSettings007A6120(DataChunkInput &file)
{
	{
		AsciiString label("SkyboxSettings");
		file.registerParser(label, AsciiString::TheEmptyString,
			parseSkyBoxSettings007A5BA0, 0);
	}
	if (!file.parse(this))
		throw 0xDEAD0005;
}
