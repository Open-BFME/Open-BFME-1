// cl: /DNDEBUG /MD /EHsc

// BFME W3DPropDraw::reactToTransformChange, retail 0x00759560.
// The implementation is the upstream W3DPropDraw.cpp body.  The adjacent
// matched constructor at 0x007592C0, W3DPropDraw name getter at 0x007592F0,
// and destructor at 0x00759350 establish the owner.  The final call is the
// matched BaseHeightMapRenderObjClass::addProp body at 0x006C8C20.

enum DrawableID
{
	INVALID_DRAWABLE_ID = 0
};
typedef float Real;

struct Coord3D
{
	// BFME's by-value ABI treats this record as compiler-nontrivial in this
	// call.  The force-inlined copy is the three retail word moves; the
	// callee owns destruction of the argument.
	__forceinline Coord3D(const Coord3D &that)
		: x(that.x), y(that.y), z(that.z) {}
	~Coord3D();

	Real x;
	Real y;
	Real z;
};

class Matrix3D;

class AsciiString
{
public:
	void *m_data;
};

class Drawable
{
public:
	const Coord3D *getPosition() const;
	__declspec(noinline) Real getScale() const;
	DrawableID getID() const;
	__forceinline Real getOrientation() const { return m_orientation; }

private:
	unsigned char m_pad[0x44];
	Real m_orientation;
	unsigned char m_padAfterOrientation[0x1B0];
	Real m_scale;
};

Real Drawable::getScale() const
{
	return m_scale;
}

class W3DPropDrawModuleData
{
public:
	unsigned char m_pad[8];
	AsciiString m_modelName;
};

class BaseHeightMapRenderObjClass
{
public:
	void addProp(int id, Coord3D location, Real angle, Real scale,
		const AsciiString &modelName);
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
extern const Real BfmeZeroRange;

class W3DPropDraw
{
public:
	virtual void reactToTransformChange(const Matrix3D *oldMtx,
		const Coord3D *oldPos, Real oldAngle);

private:
	W3DPropDrawModuleData *m_moduleData;
	Drawable *m_drawable;
	bool m_propAdded;
};

void W3DPropDraw::reactToTransformChange(
	const Matrix3D *, const Coord3D *, Real)
{
	Drawable *draw = m_drawable;
	if (m_propAdded)
		return;

	if (draw->getPosition()->x == BfmeZeroRange
		&& draw->getPosition()->y == BfmeZeroRange)
		return;

	m_propAdded = true;
	W3DPropDrawModuleData *moduleData = m_moduleData;
	if (moduleData == 0)
		return;

	Real scale = draw->getScale();
	TheTerrainRenderObject->addProp((int)draw->getID(), *draw->getPosition(),
		draw->getOrientation(), scale, moduleData->m_modelName);
}
