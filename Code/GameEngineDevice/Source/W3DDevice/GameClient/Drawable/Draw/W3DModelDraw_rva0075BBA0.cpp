// cl: /DNDEBUG /MD /EHsc /O2
// Retail 0x0075BBA0, 154 bytes.  The sole direct caller is
// W3DModelDraw::setAnimationFrame through ObjectDrawInterface slot 18 at
// 0x00760600.  It passes an Int and the validated RenderObjClass transform at
// render-object +0x18, restoring the complete draw-module pointer by -0x0C.

typedef int Int;

class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;

	Vector4 &operator=(const Vector4 &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		return *this;
	}
};

class Matrix3D
{
public:
	Vector4 row[3];

	Matrix3D &operator=(const Matrix3D &other)
	{
		row[0] = other.row[0];
		row[1] = other.row[1];
		row[2] = other.row[2];
		return *this;
	}
};

// The call at retail 0x0075BC20 uses ILT 0x000361CE, which routes to the
// 257-byte Thing body at 0x00132200.  Named Thing::setPosition,
// Thing::setPositionZ, and Drawable::loadPostProcess callers prove its owner.
// Its surviving lexical identity does not: keep the RVA-derived name distinct
// from Thing::setTransformMatrix at 0x00132350 (via ILT 0x00023D49).
class Thing
{
public:
	void rva00132200(const Matrix3D *transform);
};

class Drawable : public Thing
{
};

// The global operand is retail VA 0x012F1464.  The virtual call at +0x68 is
// GameClient::getFrame, independently backed by the same global and frame
// accessor family in GameClientFrameAccessors.cpp.
class GameClient
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual unsigned int getFrame();
};

extern GameClient *TheGameClient;

// W3DModelDraw installs its ObjectDrawInterface secondary vtable at complete
// object +0x0C.  The slot thunk reaches 0x00760600, which restores the complete
// pointer with -0x0C before calling this body.  No surviving name proves this
// method's original spelling, so retain a truthful RVA-derived member name.
class W3DModelDraw
{
public:
	void rva0075BBA0(Int value, const Matrix3D *transform);

private:
	unsigned char m_unmodelled00[0x08];
	Drawable *m_drawable;                          // +0x008
	unsigned char m_unmodelled0C[0x234 - 0x0C];
	Matrix3D m_rva0075BBA0Transform;               // +0x234
	Int m_rva0075BBA0Value;                        // +0x264
	unsigned int m_rva0075BBA0ClientFrame;         // +0x268
};

void W3DModelDraw::rva0075BBA0(Int value, const Matrix3D *transform)
{
	m_rva0075BBA0Value = value;
	m_rva0075BBA0Transform = *transform;
	m_drawable->rva00132200(transform);
	m_rva0075BBA0ClientFrame = TheGameClient->getFrame();
}
