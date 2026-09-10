// ?buildCameraTransform@W3DView@@AAEXPAVMatrix3D@@@Z
// partial score=0.45 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BFME W3DView::buildCameraTransform, retail 0x00741D30 (1322 bytes).
// The 0x007423B0 and 0x00743640 callers name this as W3DView's private
// camera-transform builder.  The primary W3DView table is 0x011217A0; the
// offsets below are the slots used by the complete retail body.

typedef float Real;
typedef int Int;
typedef bool Bool;

struct Coord2D
{
	Real x;
	Real y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Region2D
{
	Coord2D lo;
	Coord2D hi;
};

class Matrix3D;

// The two strings are the four-byte StringBase payloads used by the real
// context destructor at 0x00740C80.  This declaration supplies only the
// existing UnicodeString::set call; it does not manufacture string storage.
class UnicodeString
{
public:
	void set(const UnicodeString &other);

private:
	void *m_data;
};

// Matched at 0x006DFC60.  The field types here reflect the context uses in
// this wrapper while retaining the exact 0xD8 layout of the matched reset.
class Gen_006DFC60
{
public:
	Gen_006DFC60(void);

	Matrix3D *m_bfme00;
	Int m_bfme04;
	Real m_bfme08;
	Real m_bfme0c;
	Real m_bfme10;
	Real m_bfme14;
	Real m_bfme18;
	Real m_bfme1c;
	Real m_bfme20;
	Real m_bfme24;
	Real m_bfme28;
	Real m_bfme2c;
	Real m_bfme30;
	Real m_bfme34;
	Real m_bfme38;
	Real m_bfme3c;
	Real m_bfme40;
	Int m_bfme44;
	Real m_bfme48;
	Real m_bfme4c;
	Real m_bfme50;
	Real m_bfme54;
	Real m_bfme58;
	Real m_bfme5c;
	Real m_bfme60;
	Real m_bfme64;
	Real m_bfme68;
	Real m_bfme6c;
	Int m_bfme70;
	Int m_bfme74;
	unsigned char m_bfme78;
	unsigned char m_bfmeGap79[3];
	Real m_bfme7c;
	Real m_bfme80;
	Real m_bfme84;
	Real m_bfme88;
	unsigned char m_bfme8c;
	unsigned char m_bfmeGap8d[3];
	Real m_bfme90;
	Real m_bfme94;
	Real m_bfme98;
	unsigned char m_bfme9c;
	unsigned char m_bfmeGap9d[3];
	Real m_bfmea0;
	Int m_bfmea4;
	unsigned char m_bfmea8;
	unsigned char m_bfmea9;
	unsigned char m_bfmeaa;
	unsigned char m_bfmeGapab[1];
	UnicodeString m_bfmeac;
	UnicodeString m_bfmeb0;
	Int m_bfmeb4;
	Int m_bfmeb8;
	Int m_bfmebc;
	Int m_bfmec0;
	Int m_bfmec4;
	Int m_bfmec8;
	Int m_bfmecc;
	unsigned char m_bfmed0;
	unsigned char m_bfmed1;
	unsigned char m_bfmed2;
	unsigned char m_bfmed3;
	Int m_bfmed4;
};

struct Rva00367E30Logic;
extern Rva00367E30Logic *TheBfmeGameLogic;

class ClientRoot4120
{
	char m_padding00[0xbc];

public:
	Bool m_cameraSlaveActive;
	Bool m_cameraSlaveGuard;
};

extern ClientRoot4120 *TheGameClient;

class BfmeMapObjectExtra
{
};

extern BfmeMapObjectExtra BfmeTheMapObjectExtra;

#define BFME_DWORD(address) (*reinterpret_cast<volatile Int *>(address))
#define BFME_REAL(address) (*reinterpret_cast<volatile Real *>(address))
#define BfmeZeroRange BFME_REAL(0x01075350)
#define BfmeK1266A BFME_REAL(0x01075338)
#define BfmeScaleBK BFME_REAL(0x01075C70)
#define BfmeKTHE BFME_REAL(0x0109ECC0)
#define BfmeK12730 BFME_REAL(0x01121730)

// CameraClass::unused050 is slot 20; the raw transform begins at +0x18.
#define CAMERA_UNUSED(n) virtual void unused##n() = 0;
class CameraClass
{
public:
	CAMERA_UNUSED(00) CAMERA_UNUSED(01) CAMERA_UNUSED(02)
	CAMERA_UNUSED(03) CAMERA_UNUSED(04) CAMERA_UNUSED(05)
	CAMERA_UNUSED(06) CAMERA_UNUSED(07) CAMERA_UNUSED(08)
	CAMERA_UNUSED(09) CAMERA_UNUSED(10) CAMERA_UNUSED(11)
	CAMERA_UNUSED(12) CAMERA_UNUSED(13) CAMERA_UNUSED(14)
	CAMERA_UNUSED(15) CAMERA_UNUSED(16) CAMERA_UNUSED(17)
	CAMERA_UNUSED(18) CAMERA_UNUSED(19) CAMERA_UNUSED(20)

	char m_padding04[0x18 - 4];
	unsigned m_transform[12];
};
#undef CAMERA_UNUSED

class W3DViewVtable
{
public:
#define W3D_VOID(n) virtual void w3d##n() = 0;
	W3D_VOID(00) W3D_VOID(01) W3D_VOID(02) W3D_VOID(03)
	W3D_VOID(04) W3D_VOID(05) W3D_VOID(06) W3D_VOID(07)
	W3D_VOID(08) W3D_VOID(09) W3D_VOID(10) W3D_VOID(11)
	W3D_VOID(12) W3D_VOID(13) W3D_VOID(14)
	virtual Int w3d15() = 0;
	W3D_VOID(16)
	virtual Int w3d17() = 0;
	W3D_VOID(18) W3D_VOID(19) W3D_VOID(20) W3D_VOID(21)
	W3D_VOID(22) W3D_VOID(23) W3D_VOID(24) W3D_VOID(25)
	W3D_VOID(26) W3D_VOID(27) W3D_VOID(28) W3D_VOID(29)
	W3D_VOID(30) W3D_VOID(31) W3D_VOID(32) W3D_VOID(33)
	W3D_VOID(34) W3D_VOID(35) W3D_VOID(36) W3D_VOID(37)
	W3D_VOID(38) W3D_VOID(39) W3D_VOID(40) W3D_VOID(41)
	W3D_VOID(42) W3D_VOID(43)
	virtual void w3d44(Int) = 0;
	W3D_VOID(45)
	virtual void w3d46(Int) = 0;
	W3D_VOID(47) W3D_VOID(48) W3D_VOID(49) W3D_VOID(50)
	W3D_VOID(51) W3D_VOID(52) W3D_VOID(53) W3D_VOID(54)
	W3D_VOID(55) W3D_VOID(56) W3D_VOID(57) W3D_VOID(58)
	W3D_VOID(59) W3D_VOID(60) W3D_VOID(61) W3D_VOID(62)
	virtual Real w3d63() = 0;
	W3D_VOID(64)
	virtual Real w3d65() = 0;
	W3D_VOID(66)
	virtual Real w3d67() = 0;
	W3D_VOID(68) W3D_VOID(69) W3D_VOID(70) W3D_VOID(71)
	virtual Real w3d72() = 0;
	W3D_VOID(73) W3D_VOID(74) W3D_VOID(75) W3D_VOID(76)
	W3D_VOID(77) W3D_VOID(78) W3D_VOID(79) W3D_VOID(80)
	W3D_VOID(81) W3D_VOID(82) W3D_VOID(83) W3D_VOID(84)
	W3D_VOID(85) W3D_VOID(86) W3D_VOID(87) W3D_VOID(88)
	W3D_VOID(89) W3D_VOID(90) W3D_VOID(91) W3D_VOID(92)
	W3D_VOID(93) W3D_VOID(94) W3D_VOID(95) W3D_VOID(96)
	W3D_VOID(97) W3D_VOID(98) W3D_VOID(99) W3D_VOID(100)
	W3D_VOID(101) W3D_VOID(102) W3D_VOID(103) W3D_VOID(104)
	W3D_VOID(105) W3D_VOID(106) W3D_VOID(107) W3D_VOID(108)
	W3D_VOID(109) W3D_VOID(110) W3D_VOID(111) W3D_VOID(112)
	W3D_VOID(113)
	virtual Bool w3d114() = 0;
	W3D_VOID(115)
	virtual Int w3d116() = 0;
#undef W3D_VOID
};

class W3DView : public W3DViewVtable
{
private:
	void buildCameraTransform(Matrix3D *transform);

	char m_padding04[0x0c - 4];
	Coord3D m_pos;
	char m_padding18[0x20 - 0x18];
	Real m_field20;
	Real m_field24;
	Real m_field28;
	char m_padding2c[0x6c - 0x2c];
	Real m_field6c;
	Real m_field70;
	char m_padding74[0xb4 - 0x74];
	char m_buildState[4];
	char m_paddingb8[0x104 - 0xb8];
	CameraClass *m_3DCamera;
	char m_padding108[0x10c - 0x108];
	Int m_field10c;
	Int m_field110;
	char m_padding114[0x118 - 0x114];
	Int m_field118;
	Int m_field11c;
	char m_padding120[0x12c - 0x120];
	Real m_field12c;
	Real m_field130;
	Real m_field134;
	Real m_field138;
	char m_padding13c[0x1cc - 0x13c];
	Int m_field1cc;
	char m_padding1d0[0x1dc - 0x1d0];
	Bool m_cameraSlaveObject;
	char m_padding1dd[0x2354 - 0x1dd];
	Int m_cameraMovementMode;
	char m_padding2358[0x23b8 - 0x2358];
	Bool m_cameraState23b8;
	char m_padding23b9[0x23d8 - 0x23b9];
	Coord3D m_cameraOffset;
	char m_padding23e4[0x23f8 - 0x23e4];
	Real m_groundLevel;
	Region2D m_cameraConstraint;
	Bool m_cameraConstraintValid;
	char m_padding240d[0x2410 - 0x240d];
	Real m_field2410;
	Real m_field2414;
	Real m_field2418;
	Real m_field241c;
	Real m_field2420;
	Real m_field2424;
	unsigned char m_field2428;
	unsigned char m_field2429;
	unsigned char m_field242a;
	unsigned char m_padding242b;
	UnicodeString m_field242c;
	UnicodeString m_field2430;
	char m_padding2434[8];
	Coord3D m_cameraPoint243c;
};

extern void j_000035b7(void);
extern void j_000084ea(void);
extern void j_00009304(void);
extern void j_0001f253(void);
extern void j_00048fa4(void);

class BuildStateCall
{
};

class LogicQueryCall
{
};

class CameraSlaveCall
{
};

class MapObjectExtraCall
{
};

class ContextDestructorCall
{
};

void W3DView::buildCameraTransform(Matrix3D *transform)
{
	if (TheBfmeGameLogic != 0 && m_cameraMovementMode == 3)
	{
		CameraClass *camera = m_3DCamera;
		camera->unused20();
		unsigned *destination = reinterpret_cast<unsigned *>(transform);
		for (Int i = 0; i < 12; ++i)
			destination[i] = camera->m_transform[i];
		return;
	}

	Gen_006DFC60 context;
	context.m_bfme00 = transform;
	context.m_bfme04 = BFME_DWORD(0x012BB214);
	context.m_bfme08 = m_field2410;
	context.m_bfme0c = m_field2414;
	context.m_bfme10 = m_field2418;
	context.m_bfme14 = m_field241c;
	context.m_bfme18 = m_field2420;
	context.m_bfme1c = m_field2424;
	context.m_bfme20 = m_field12c;
	context.m_bfme24 = m_field130;
	context.m_bfme28 = m_field134;
	context.m_bfme2c = m_groundLevel;
	context.m_bfme30 = w3d72();
	context.m_bfme34 = w3d63();
	context.m_bfme38 = w3d65();
	context.m_bfme3c = w3d67();
	context.m_bfme40 = m_field6c;
	context.m_bfme44 = BFME_DWORD(0x012F9DBC);
	context.m_bfme4c = m_pos.x;
	context.m_bfme50 = m_pos.y;
	context.m_bfme54 = m_pos.z;
	context.m_bfme58 = m_pos.x;
	context.m_bfme5c = m_pos.y;
	context.m_bfme60 = m_pos.z;
	context.m_bfme70 = m_field118;
	context.m_bfme74 = m_field11c;
	context.m_bfme78 = m_cameraConstraintValid;

	if (m_cameraConstraintValid)
	{
		context.m_bfme7c = m_cameraConstraint.lo.x;
		context.m_bfme80 = m_cameraConstraint.lo.y;
		context.m_bfme84 = m_cameraConstraint.hi.x;
		context.m_bfme88 = m_cameraConstraint.hi.y;
		context.m_bfme8c = m_field242a;
		context.m_bfme90 = m_cameraOffset.x;
		context.m_bfme94 = m_cameraOffset.y;
		context.m_bfme98 = m_cameraOffset.z;
		context.m_bfme9c = w3d114();
		context.m_bfmea0 = m_field70;
		context.m_bfmea4 = w3d116();
		context.m_bfmea8 = m_field2428;
		context.m_bfmea9 = m_cameraSlaveObject;
		context.m_bfmeaa = m_field2429;
		context.m_bfmeac.set(m_field242c);
		context.m_bfmeb0.set(m_field2430);
	}

	context.m_bfmeb4 = m_field10c;
	context.m_bfmeb8 = m_field110;
	context.m_bfmebc = w3d15();
	context.m_bfmec0 = w3d17();
	context.m_bfmed4 = m_cameraMovementMode;

	// The first x87 compare selects the existing height unless the camera is
	// not already slaved; the following two compares implement the BFME scale
	// guard and retain the retail single-precision state update.
	if (m_field138 == BfmeZeroRange)
	{
		context.m_bfme50 = m_field138;
	}
	else if (m_cameraSlaveObject)
	{
		context.m_bfme50 = m_field138;
	}
	else if (m_field138 * BfmeScaleBK < BfmeK1266A)
	{
		if (m_field138 < BfmeK12730)
			m_field138 = BfmeZeroRange;
		else
			m_field138 += BfmeK12730;
		context.m_bfme50 = m_field138;
	}
	else if (m_field138 > BfmeZeroRange)
	{
		m_field138 -= BfmeK1266A;
		context.m_bfme50 = m_field138;
	}

	if (m_cameraState23b8)
	{
		context.m_bfme64 = m_cameraPoint243c.x;
		context.m_bfme68 = m_cameraPoint243c.y;
		context.m_bfme6c = m_cameraPoint243c.z;
	}
	else if (m_cameraSlaveObject)
	{
		LogicQueryCall *logic = reinterpret_cast<LogicQueryCall *>(TheBfmeGameLogic);
		typedef void *(LogicQueryCall::*Query)(void *);
		union
		{
			void (*function)(void);
			Query member;
		} query;
		query.function = j_0001f253;
		void *result = (logic->*query.member)(reinterpret_cast<char *>(this) + 0x1cc);
		if (result != 0)
		{
			Coord3D *point = reinterpret_cast<Coord3D *>(reinterpret_cast<char *>(result) + 0x38);
			context.m_bfme64 = point->x;
			context.m_bfme68 = point->y;
			context.m_bfme6c = point->z + context.m_bfme50;
		}
	}

	BuildStateCall *state = reinterpret_cast<BuildStateCall *>(reinterpret_cast<char *>(this) + 0xb4);
	typedef void (BuildStateCall::*Build)(Gen_006DFC60 *);
	union
	{
		void (*function)(void);
		Build member;
	} build;
	build.function = j_000035b7;
	(state->*build.member)(&context);

	w3d44(context.m_bfmebc);
	w3d46(context.m_bfmec0);
	m_pos.x = context.m_bfme58;
	m_pos.y = context.m_bfme5c;
	m_pos.z = context.m_bfme60;

	if (TheGameClient != 0 && !TheGameClient->m_cameraSlaveGuard &&
		TheGameClient->m_cameraSlaveActive)
	{
		CameraSlaveCall *slaveObject = reinterpret_cast<CameraSlaveCall *>(0x012A79D0);
		typedef void *(CameraSlaveCall::*Lookup)(void);
		union
		{
			void (*function)(void);
			Lookup member;
		} lookupCall;
		lookupCall.function = j_00009304;
		void *lookup = (slaveObject->*lookupCall.member)();

		MapObjectExtraCall *map = reinterpret_cast<MapObjectExtraCall *>(&BfmeTheMapObjectExtra);
		typedef void (MapObjectExtraCall::*Notify)(void *, Real);
		union
		{
			void (*function)(void);
			Notify member;
		} notify;
		notify.function = j_00048fa4;
		(map->*notify.member)(lookup, m_field28 * BfmeKTHE);
	}

	ContextDestructorCall *destructor = reinterpret_cast<ContextDestructorCall *>(&context);
	typedef void (ContextDestructorCall::*Destroy)(void);
	union
	{
		void (*function)(void);
		Destroy member;
	} destroy;
	destroy.function = j_000084ea;
	(destructor->*destroy.member)();
}

#undef BFME_DWORD
#undef BFME_REAL
#undef BfmeZeroRange
#undef BfmeK1266A
#undef BfmeScaleBK
#undef BfmeKTHE
#undef BfmeK12730
