// ??1W3DRadar@@UAE@XZ
//
// BFME stores four Coord2D view-box entries with destructors and five counted
// texture references in the W3DRadar tail.  The public Zero Hour header uses
// POD ICoord2D entries, so this TU keeps the BFME layout local to the
// destructor that proves it.

class Snapshot
{
public:
	virtual ~Snapshot();
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
};

class Radar : public Snapshot, public SubsystemInterface
{
public:
	virtual ~Radar();
};

class Coord2D
{
public:
	Coord2D();
	~Coord2D();

	float x;
	float y;
};

class TextureClass
{
public:
	void Release_Ref();
};

class TextureRef
{
public:
	TextureRef() : m_texture(0) {}

	~TextureRef()
	{
		if (m_texture)
		{
			m_texture->Release_Ref();
		}
	}

	TextureClass *m_texture;
};

class W3DRadar : public Radar
{
public:
	virtual ~W3DRadar();

private:
	char m_pad1470[0x1470];
	TextureRef m_texture1478;
	TextureRef m_texture147c;
	char m_pad1480[8];
	TextureRef m_texture1488;
	char m_pad148c[8];
	TextureRef m_texture1494;
	char m_pad1498[8];
	TextureRef m_texture14a0;
	char m_pad14a4[0x44];
	Coord2D m_viewBox[4];
};

extern void j_00011207();

W3DRadar::~W3DRadar()
{
	j_00011207();
}
