// cl: /O2 /Ob0 /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ conversion of the positional TerrainScorch dispatch.

struct Coord3D
{
	float x, y, z;
};

class Matrix3D;

int GetGameClientRandomValue(int, int, char *, int);

#define BFME_GAMECLIENT_SLOT( name ) virtual void name();
class GameClient
{
public:
	BFME_GAMECLIENT_SLOT(v00) BFME_GAMECLIENT_SLOT(v04)
	BFME_GAMECLIENT_SLOT(v08) BFME_GAMECLIENT_SLOT(v0C)
	BFME_GAMECLIENT_SLOT(v10) BFME_GAMECLIENT_SLOT(v14)
	BFME_GAMECLIENT_SLOT(v18) BFME_GAMECLIENT_SLOT(v1C)
	BFME_GAMECLIENT_SLOT(v20) BFME_GAMECLIENT_SLOT(v24)
	BFME_GAMECLIENT_SLOT(v28) BFME_GAMECLIENT_SLOT(v2C)
	BFME_GAMECLIENT_SLOT(v30) BFME_GAMECLIENT_SLOT(v34)
	BFME_GAMECLIENT_SLOT(v38) BFME_GAMECLIENT_SLOT(v3C)
	BFME_GAMECLIENT_SLOT(v40)
	virtual void addScorch(const Coord3D *, float, int);
};
#undef BFME_GAMECLIENT_SLOT

extern GameClient *TheGameClient;

class TerrainScorchFXNugget
{
public:
	virtual void v00();
	virtual void doFXPos(const Coord3D *, const Matrix3D *, float, const Coord3D *) const;

private:
	unsigned char m_unmodelled[0xB0];
	int m_scorch;
	float m_radius;
};

// ?doFXPos@TerrainScorchFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z
void TerrainScorchFXNugget::doFXPos(const Coord3D *primary, const Matrix3D *,
	float, const Coord3D *) const
{
	if (primary)
	{
		int scorch = m_scorch;
		if (scorch < 0)
			scorch = GetGameClientRandomValue(0, 3,
				"F:\\bfme\\Code\\gameengine\\Source\\GameClient\\FXList.cpp", 0x4C5);
		TheGameClient->addScorch(primary, m_radius, scorch);
	}
}
