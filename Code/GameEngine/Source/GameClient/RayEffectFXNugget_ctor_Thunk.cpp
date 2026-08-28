// cl: /DNDEBUG /MD /EHsc
// Clean C++ reconstruction of the BFME ray-effect FX nugget constructor.

typedef float Real;

class AsciiString
{
public:
	AsciiString() : m_text(0) {}
	~AsciiString();
	void clear();

private:
	char *m_text;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class FXNugget
{
public:
	FXNugget();
	virtual ~FXNugget();

protected:
	int m_nuggetType;

private:
	unsigned char m_bfmeBaseData[0xAC];
};

class RayEffectFXNugget : public FXNugget
{
public:
	RayEffectFXNugget();
	virtual ~RayEffectFXNugget();

private:
	AsciiString m_templateName;
	Coord3D m_primaryOffset;
	Coord3D m_secondaryOffset;
};

RayEffectFXNugget::RayEffectFXNugget()
{
	m_templateName.clear();
	m_primaryOffset.x = m_primaryOffset.y = m_primaryOffset.z = 0;
	m_secondaryOffset.x = m_secondaryOffset.y = m_secondaryOffset.z = 0;
	m_nuggetType = 2;
}
