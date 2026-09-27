// ?xfer@W3DPropBuffer@@MAEXPAVXfer@@@Z
// partial score=0.941 date=2026-09-27
// cl: /DNDEBUG /MD
// ?xfer@W3DPropBuffer@@MAEXPAVXfer@@@Z

typedef int Int;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	__forceinline Coord3D &operator+=(const Coord3D &other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}


};

struct Matrix3D
{
	Real row0[4];
	Real row1[4];
	Real row2[4];

	Matrix3D(bool identity)
	{
		if (identity) {
			row0[0] = 1.0f;
			row0[1] = 0.0f;
			row0[2] = 0.0f;
			row0[3] = 0.0f;
			row1[0] = 0.0f;
			row1[1] = 1.0f;
			row1[2] = 0.0f;
			row1[3] = 0.0f;
			row2[0] = 0.0f;
			row2[1] = 0.0f;
			row2[2] = 1.0f;
			row2[3] = 0.0f;
		}
	}

	Matrix3D &operator=(const Matrix3D &other)
	{
		row0[0] = other.row0[0];
		row0[1] = other.row0[1];
		row0[2] = other.row0[2];
		row0[3] = other.row0[3];
		row1[0] = other.row1[0];
		row1[1] = other.row1[1];
		row1[2] = other.row1[2];
		row1[3] = other.row1[3];
		row2[0] = other.row2[0];
		row2[1] = other.row2[1];
		row2[2] = other.row2[2];
		row2[3] = other.row2[3];
		return *this;
	}
};

struct Vector3
{
	Real X;
	Real Y;
	Real Z;

	Vector3(Real x, Real y, Real z) : X(x), Y(y), Z(z) {}

	Vector3 &operator+=(const Vector3 &other)
	{
		X += other.X;
		Y += other.Y;
		Z += other.Z;
		return *this;
	}
};

struct SphereClass
{
	Vector3 Center;
	Real Radius;
};

struct XferVersion
{
	unsigned char version;
	unsigned char currentVersion;

	XferVersion(unsigned char value, unsigned char current) :
		version(value), currentVersion(current)
	{
	}

	XferVersion(unsigned char value) : version(value), currentVersion(value) {}
};

class Xfer
{
public:
	virtual void slot00();
	virtual Bool isLoading();
	virtual Bool isSaving();
	virtual Bool isCRC();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion *version);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void xferCoord3D(Coord3D *value);
	virtual void slot25();
	virtual void xferAsciiString(void *value);
	virtual void xferReal(Real *value);
	virtual void slot28();
	virtual void xferUnsignedInt(unsigned int *value);
	virtual void xferInt(Int *value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(Bool *value);
};

class BfmeSeedTarget;
void bfmeHandOver_00001A50(BfmeSeedTarget *target, void *item);
void BfmeParticleSystemXferMatrix(Xfer &xfer, void *value);

class RenderObjClass
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual RenderObjClass *Clone() const;
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void Validate_Transform() const;
	virtual void Set_Transform(const Matrix3D &transform);
	const Matrix3D &Get_Transform() const
	{
		Validate_Transform();
		return m_transform;
	}
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void slot79();
	virtual void slot80();
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual void slot84();
	virtual void slot85();
	virtual void slot86();
	virtual void slot87();
	virtual void slot88();
	virtual void slot89();
	virtual void slot90();
	virtual void slot91();
	virtual void Set_ObjectScale(Real scale);

	char pad04[0x14];
	Matrix3D m_transform;
};

struct PropNameString
{
	void *m_data;

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388b;
	}
};

struct TProp
{
	RenderObjClass *m_robj;
	Int id;
	Coord3D location;
	Int propType;
	Int ss;
	Bool visible;
	SphereClass bounds;
};

struct TPropType
{
	RenderObjClass *m_robj;
	PropNameString m_robjName;
	SphereClass m_bounds;
};

class Snapshot
{
public:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
};

class W3DPropBuffer : public Snapshot
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	TProp m_props[4000];
	Int m_numProps;
	Bool m_anythingChanged;
	Bool m_initialized;
	Bool m_doCull;
	char m_pad2ee0b;
	TPropType m_propTypes[96];
	Int m_numPropTypes;
	void *m_propShroudMaterialPass;
	Int m_bfmeExtraField;
	void *m_light;
};

RenderObjClass *Create_Render_Obj(const char *name);

void W3DPropBuffer::xfer(Xfer *xfer)
{
	if (xfer->isCRC())
		return;

	XferVersion version = 1;
	xfer->xferVersion(&version);

	xfer->xferInt(&m_numPropTypes);
	Int i;
	for (i = 0; i < m_numPropTypes; ++i) {
		bfmeHandOver_00001A50((BfmeSeedTarget *)xfer, &m_propTypes[i].m_bounds.Center);
		xfer->xferReal(&m_propTypes[i].m_bounds.Radius);
		xfer->xferAsciiString(&m_propTypes[i].m_robjName);
		if (xfer->isLoading())
			m_propTypes[i].m_robj = Create_Render_Obj(m_propTypes[i].m_robjName.str());
	}

	xfer->xferInt(&m_numProps);
	for (i = 0; i < m_numProps; ++i) {
		xfer->xferInt(&m_props[i].propType);
		xfer->xferInt(&m_props[i].id);
		xfer->xferCoord3D(&m_props[i].location);
		xfer->xferBool(&m_props[i].visible);
		Matrix3D transform(true);
		Real scale = 1.0f;

		if (!xfer->isLoading()) {
			RenderObjClass *current = m_props[i].m_robj;
			if (current) {
				current->Get_Transform();
				transform = current->m_transform;
			}
		}
		BfmeParticleSystemXferMatrix(*xfer, &transform);
		xfer->xferReal(&scale);

		if (xfer->isLoading()) {
			m_props[i].ss = 0;
			if (m_props[i].propType >= 0 && m_props[i].propType <= m_numPropTypes) {
				RenderObjClass *source = m_propTypes[m_props[i].propType].m_robj;
				if (source) {
					m_props[i].m_robj = source->Clone();
					m_props[i].m_robj->Set_Transform(transform);
					m_props[i].m_robj->Set_ObjectScale(scale);
				} else {
					m_props[i].m_robj = 0;
				}
				m_props[i].bounds = m_propTypes[m_props[i].propType].m_bounds;
			} else {
				m_props[i].m_robj = 0;
				m_props[i].bounds.Center.X = 0.0f;
				m_props[i].bounds.Center.Y = 0.0f;
				m_props[i].bounds.Center.Z = 0.0f;
				m_props[i].bounds.Radius = 1.0f;
			}
			m_props[i].bounds.Center += Vector3(m_props[i].location.x,
				m_props[i].location.y, m_props[i].location.z);
		}
	}

	xfer->xferBool(&m_anythingChanged);
	xfer->xferBool(&m_doCull);
	xfer->xferInt(&m_bfmeExtraField);
}
