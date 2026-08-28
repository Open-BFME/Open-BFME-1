// cl: /DNDEBUG /MD /EHsc
// readable body of ??1TerrainRoadType@@MAE@XZ: Code/GameEngine/Source/GameClient/Terrain/TerrainRoads.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/TerrainRoads.h
class TerrainRoadType
{
protected:
	virtual ~TerrainRoadType();

private:
	AsciiString m_name;
	bool m_isBridge;
	char m_pad09[3];
	unsigned int m_id;
	TerrainRoadType *m_next;
	float m_roadWidth;
	float m_roadWidthInTexture;
	float m_bridgeScale;
	AsciiString m_scaffoldObjectName;
	AsciiString m_scaffoldSupportObjectName;
	float m_radarColor[3];
	AsciiString m_bridgeModelName;
	AsciiString m_texture;
	AsciiString m_bridgeModelNameDamaged;
	AsciiString m_textureDamaged;
	AsciiString m_bridgeModelNameReallyDamaged;
	AsciiString m_textureReallyDamaged;
	AsciiString m_bridgeModelNameBroken;
	AsciiString m_textureBroken;
	AsciiString m_towerObjectName[4];
	AsciiString m_damageToSoundString[4];
	AsciiString m_damageToOCLString[12];
	AsciiString m_damageToFXString[12];
	AsciiString m_repairedToSoundString[4];
	AsciiString m_repairedToOCLString[12];
	AsciiString m_repairedToFXString[12];
	float m_transitionEffectsHeight;
	int m_numFXPerType;
};

TerrainRoadType::~TerrainRoadType()
{
}
