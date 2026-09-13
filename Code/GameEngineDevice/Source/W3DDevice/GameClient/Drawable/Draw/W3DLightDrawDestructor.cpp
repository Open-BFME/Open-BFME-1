// cl: /DNDEBUG /MD /EHsc
// W3DLightDraw::~W3DLightDraw, retail RVA 0x00758580.
//
// The primary vtable at VA 0x01122B20 has 59 entries.  Its slot-zero
// deleting destructor (RVA 0x00758860) reaches this complete-object
// destructor through ILT 0x0004B62D.  DrawModule's 59-entry primary table is
// VA 0x01121BA8.  The declarations below are TU-local ABI reconciliation for
// those complete tables; unresolved lexical identities stay RVA-derived.

typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

class ChunkLoadClass;
class ChunkSaveClass;
class Coord3D;
class Matrix3D;
class MemoryPool;
class PersistFactoryClass;
class Xfer;

// The light hierarchy is RefCountClass -> RenderObjClass -> LightClass ->
// W3DDynamicLight.  RenderObjClass's two secondary bases are material here:
// they keep RefCountClass (and therefore NumRefs at +4) as the primary base.
class RefCountClass
{
public:
	virtual void Delete_This();

	void Release_Ref() const
	{
		--m_numRefs;
		if (m_numRefs == 0)
			const_cast<RefCountClass *>(this)->Delete_This();
	}

protected:
	virtual ~RefCountClass();

private:
	mutable int m_numRefs;                 // +0x04
};

class PostLoadableClass
{
public:
	virtual ~PostLoadableClass();
	virtual void On_Post_Load();

private:
	Bool m_isPostLoadRegistered;
};

class PersistClass : public PostLoadableClass
{
public:
	virtual const PersistFactoryClass &Get_Factory() const = 0;
	virtual Bool Save(ChunkSaveClass &save);
	virtual Bool Load(ChunkLoadClass &load);
};

class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass();

private:
	void *m_listNode;
};

class RenderObjClass : public RefCountClass, public PersistClass, public MultiListObjectClass
{
protected:
	virtual ~RenderObjClass();
};

class LightClass : public RenderObjClass
{
protected:
	virtual ~LightClass();
	char m_renderAndLightState[0x124 - sizeof(RenderObjClass)];
};

typedef char LightClass_size_must_be_0x124[(sizeof(LightClass) == 0x124) ? 1 : -1];

class W3DDynamicLight : public LightClass
{
public:
	virtual ~W3DDynamicLight();

	void setEnabled(Bool enabled)
	{
		m_enabled = enabled;
		m_decayRange = false;
		m_decayFrameCount = 0;
		m_decayColor = false;
		m_increaseFrameCount = 0;
	}

private:
	Bool m_priorEnable;                    // +0x124
	Bool m_processMe;                      // +0x125
	int m_prevMinX;                        // +0x128
	int m_prevMinY;
	int m_prevMaxX;
	int m_prevMaxY;
	int m_minX;
	int m_minY;
	int m_maxX;
	int m_maxY;
	Bool m_enabled;                        // +0x148
	Bool m_decayRange;                     // +0x149
	Bool m_decayColor;                     // +0x14A
	UnsignedInt m_curDecayFrameCount;      // +0x14C
	UnsignedInt m_curIncreaseFrameCount;   // +0x150
	UnsignedInt m_decayFrameCount;         // +0x154
	UnsignedInt m_increaseFrameCount;      // +0x158
};

typedef char W3DDynamicLight_enabled_must_be_0x148[
	(sizeof(W3DDynamicLight) >= 0x15C) ? 1 : -1];

// The primary DrawModule table is indexed explicitly below.  Each neutral
// name records the retail implementation RVA, and each argument records only
// an observed four-byte ABI word where its public type is not yet proved.
class MemoryPoolObject
{
protected:
	virtual ~MemoryPoolObject();                                      // 00 -> 0x00750350
	virtual MemoryPool *getObjectMemoryPool();                        // 01 -> 0x001139D0
	virtual const char *rva0074FF70() const;                          // 02 -> 0x0074FF70
};

class Module : public MemoryPoolObject
{
protected:
	virtual void rva001139A0(Xfer *xfer);                             // 03 -> 0x001139A0

public:
	virtual UnsignedInt getModuleNameKey() const = 0;                 // 04 -> purecall
	virtual void rva00113B40();                                      // 05 -> 0x00113B40
	virtual void rva00113B50();                                      // 06 -> 0x00113B50
	virtual void rva00113B60();                                      // 07 -> 0x00113B60
	virtual void rva00113B70();                                      // 08 -> 0x00113B70

protected:
	const void *m_moduleData;                                         // +0x04
};

class DrawableModule : public Module
{
protected:
	virtual ~DrawableModule();
	void *m_drawable;                                                  // +0x08
};

class DrawModule : public DrawableModule
{
protected:
	// The authentic DrawModule destructor is empty and inline; its compiler-
	// generated vptr transition is the retail store at RVA 0x007585E8.
	virtual ~DrawModule() {}

public:
	virtual void doDrawModule(const Matrix3D *transform) = 0;          // 09 -> purecall
	virtual void setShadowsEnabled(Bool enabled) = 0;                  // 10 -> purecall
	virtual void releaseShadows() = 0;                                // 11 -> purecall
	virtual void allocateShadows() = 0;                               // 12 -> purecall
	virtual void rva0074FF80();                                       // 13 -> 0x0074FF80
	virtual void setHidden(Bool hidden);                              // 14 -> 0x0074FF90
	virtual Bool rva0074FFA0() const;                                 // 15 -> 0x0074FFA0
	virtual void rva0074FFC0(UnsignedInt);                            // 16 -> 0x0074FFC0
	virtual void rva0074FFB0(UnsignedInt);                            // 17 -> 0x0074FFB0
	virtual void rva0074FFD0(UnsignedInt, UnsignedInt);               // 18 -> 0x0074FFD0
	virtual void setTerrainDecalOpacity(Real opacity);                 // 19 -> 0x0074FFE0
	virtual void rva0074FFF0(UnsignedInt);                            // 20 -> 0x0074FFF0
	virtual void rva00750000(UnsignedInt);                            // 21 -> 0x00750000
	virtual void rva00750010(UnsignedInt, UnsignedInt);               // 22 -> 0x00750010
	virtual void rva00750020(UnsignedInt);                            // 23 -> 0x00750020
	virtual void rva00750030(UnsignedInt, UnsignedInt);               // 24 -> 0x00750030
	virtual void rva00750040();                                       // 25 -> 0x00750040
	virtual void rva00750050(UnsignedInt);                            // 26 -> 0x00750050
	virtual void rva00750060(UnsignedInt);                            // 27 -> 0x00750060
	virtual void rva00750070(UnsignedInt);                            // 28 -> 0x00750070
	virtual void rva00750080(UnsignedInt);                            // 29 -> 0x00750080
	virtual void rva00750090(UnsignedInt, UnsignedInt, UnsignedInt);  // 30 -> 0x00750090
	virtual void rva007500A0();                                       // 31 -> 0x007500A0
	virtual void setFullyObscuredByShroud(Bool obscured) = 0;         // 32 -> purecall
	virtual void rva007500B0();                                       // 33 -> 0x007500B0
	virtual Bool isVisible() const;                                   // 34 -> 0x007500C0
	virtual void reactToTransformChange(const Matrix3D *oldTransform,
		const Coord3D *oldPosition, Real oldAngle) = 0;                 // 35 -> purecall
	virtual void reactToGeometryChange() = 0;                         // 36 -> purecall
	virtual Bool isLaser() const;                                     // 37 -> 0x007500D0
	virtual void *rva007500F0();                                      // 38 -> 0x007500F0
	virtual void *getObjectDrawInterface();                           // 39 -> 0x007500E0
	virtual void *rva00750110();                                      // 40 -> 0x00750110
	virtual void *rva00750100();                                      // 41 -> 0x00750100
	virtual void *rva00750130();                                      // 42 -> 0x00750130
	virtual void *rva00750120();                                      // 43 -> 0x00750120
	virtual void *rva00750150();                                      // 44 -> 0x00750150
	virtual void *rva00750140();                                      // 45 -> 0x00750140
	virtual void *rva00750160();                                      // 46 -> 0x00750160
	virtual Real rva00750170() const;                                 // 47 -> 0x00750170
	virtual void rva00750180(UnsignedInt);                            // 48 -> 0x00750180
	virtual void rva00750190(UnsignedInt, UnsignedInt);               // 49 -> 0x00750190
	virtual Bool rva007501A0() const;                                 // 50 -> 0x007501A0
	virtual void rva007501B0(UnsignedInt);                            // 51 -> 0x007501B0
	virtual void rva007501C0();                                       // 52 -> 0x007501C0
	virtual void rva007501D0(UnsignedInt, UnsignedInt);               // 53 -> 0x007501D0
	virtual void rva007501E0();                                       // 54 -> 0x007501E0
	virtual void rva007501F0(UnsignedInt);                            // 55 -> 0x007501F0
	virtual void rva00750200(UnsignedInt);                            // 56 -> 0x00750200
	virtual Bool rva00750210() const;                                 // 57 -> 0x00750210
	virtual void bfmeCondition4Callback();                            // 58 -> 0x00750220
};

class W3DLightDraw : public DrawModule
{
public:
	virtual ~W3DLightDraw();                                          // 00 -> 0x00758860

protected:
	virtual MemoryPool *getObjectMemoryPool();                        // 01 -> 0x001139D0
	virtual const char *rva0074FF70() const;                          // 02 -> 0x00758520
	virtual void rva001139A0(Xfer *xfer);                             // 03 -> 0x00758670

public:
	virtual UnsignedInt getModuleNameKey() const;                     // 04 -> 0x007586F0
	virtual void doDrawModule(const Matrix3D *transform);             // 09 -> 0x00758890
	virtual void setShadowsEnabled(Bool enabled);                     // 10 -> 0x00758530
	virtual void releaseShadows();                                    // 11 -> 0x00758560
	virtual void allocateShadows();                                   // 12 -> 0x00758570
	virtual void setHidden(Bool hidden);                              // 14 -> 0x00758630
	virtual void setFullyObscuredByShroud(Bool obscured);             // 32 -> 0x00758540
	virtual void reactToTransformChange(const Matrix3D *oldTransform,
		const Coord3D *oldPosition, Real oldAngle);                     // 35 -> 0x00758AC0
	virtual void reactToGeometryChange();                             // 36 -> 0x00758550

private:
	W3DDynamicLight *m_light;                                         // +0x0C
};

typedef char W3DLightDraw_light_must_be_at_0x0C[(sizeof(DrawModule) == 0x0C) ? 1 : -1];

W3DLightDraw::~W3DLightDraw()
{
	m_light->setEnabled(false);
	if (m_light)
	{
		m_light->Release_Ref();
		m_light = 0;
	}
}
