// ?rva00742920@W3DView@@QAEHPAUCoord2D@@@Z
// partial score=0.4904 date=2026-09-27
// BFME camera scroll reconstruction candidate.
// Target: 0x00742920, 726 bytes.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath

typedef float Real;
typedef int Int;
typedef int Bool;

struct Coord2D { Real x, y; };
struct ICoord2D { Int x, y; };
struct Vector2 { Real X, Y; };
struct Vector3 { Real X, Y, Z; };

union RvaScreenSlot
{
	ICoord2D pixels;
	Vector2 direction;
};

struct RvaCameraLocals
{
	Real aspect;
	Vector2 start;
	Vector3 rayStart;
	RvaScreenSlot screen;
	Vector2 end;
	Vector3 rayEnd;
	Vector3 world;
	Vector3 worldStart;
	Vector3 worldEnd;
};

class CameraClass
{
public:
	void Device_To_World_Space(const Vector2 &, Vector3 *);
};

namespace WWMath
{
	Real __fastcall Inv_Sqrt(Real);
}

class RvaZoomLimits
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual Real slot10();
};

class BfmeSubETH
{
public:
	int value;
};

class BfmeViewETH
{
public:
	void bfmeApplyETH(BfmeSubETH *);
};

class Gen_00742DA0
{
public:
	void bfmeFinish();
};

#define RVA_NOTIFY_SLOTS_16(prefix) \
	virtual void prefix##0(); virtual void prefix##1(); virtual void prefix##2(); virtual void prefix##3(); \
	virtual void prefix##4(); virtual void prefix##5(); virtual void prefix##6(); virtual void prefix##7(); \
	virtual void prefix##8(); virtual void prefix##9(); virtual void prefix##a(); virtual void prefix##b(); \
	virtual void prefix##c(); virtual void prefix##d(); virtual void prefix##e(); virtual void prefix##f();

#define RVA_NOTIFY_SLOTS_13(prefix) \
	virtual void prefix##0(); virtual void prefix##1(); virtual void prefix##2(); virtual void prefix##3(); \
	virtual void prefix##4(); virtual void prefix##5(); virtual void prefix##6(); virtual void prefix##7(); \
	virtual void prefix##8(); virtual void prefix##9(); virtual void prefix##a(); virtual void prefix##b(); \
	virtual void prefix##c();

class RvaCameraNotifier
{
public:
	RVA_NOTIFY_SLOTS_16(s0)
	RVA_NOTIFY_SLOTS_16(s1)
	RVA_NOTIFY_SLOTS_16(s2)
	RVA_NOTIFY_SLOTS_16(s3)
	RVA_NOTIFY_SLOTS_16(s4)
	RVA_NOTIFY_SLOTS_16(s5)
	RVA_NOTIFY_SLOTS_16(s6)
	RVA_NOTIFY_SLOTS_16(s7)
	RVA_NOTIFY_SLOTS_13(s8)
	virtual void notify(Int);
};

class RvaGameClient
{
public:
	unsigned char padding[0xbc];
	unsigned char cameraChangeBlocked;
};

class BFMERetailW3DViewInterface
{
public:
	virtual void unused00();
	virtual void unused04();
	virtual void unused08();
	virtual void unused0c();
	virtual void unused10();
	virtual void unused14();
	virtual void unused18();
	virtual void unused1c();
	virtual void unused20();
	virtual void unused24();
	virtual void unused28();
	virtual void unused2c();
	virtual void unused30();
	virtual void unused34();
	virtual void unused38();
	virtual Int getWidth();
	virtual void unused40();
	virtual Int getHeight();
};

class W3DView
{
public:
	virtual void vtableAnchor();
	Bool rva00742920(Coord2D *);

private:
	void getPickRay(const ICoord2D *, Vector3 *, Vector3 *);
	unsigned char padding0004[0x0c - 0x04];
	Vector3 position;
	unsigned char padding0018[0x3c - 0x18];
	Real cameraZoom;
	unsigned char padding0040[0x44 - 0x40];
	unsigned char opaque0044;
	unsigned char padding0045[0x104 - 0x45];
	CameraClass *camera;
	unsigned char padding0108[0x1dc - 0x108];
	unsigned char cameraMovementFlag;
	unsigned char padding01dd[0x23ec - 0x1dd];
	Coord2D scrollAmount;
	unsigned char padding23f4[0x23fc - 0x23f4];
	Real constraintLowX;
	Real constraintLowY;
	Real constraintHighX;
	Real constraintHighY;
	unsigned char padding240c[0x24b8 - 0x240c];
	RvaZoomLimits zoomLimits;
};

static RvaGameClient *gameClient()
{
	return *(RvaGameClient **)0x012f1464;
}

static RvaCameraNotifier *cameraNotifier()
{
	return *(RvaCameraNotifier **)0x012f7fe0;
}

static const Real &globalReal(unsigned address)
{
	return *(const Real *)address;
}

Bool W3DView::rva00742920(Coord2D *delta)
{
	if (gameClient()->cameraChangeBlocked && opaque0044)
		return 0;
	Bool result = 0;
	if (delta && !(delta->x == globalReal(0x01075350) && delta->y == globalReal(0x01075350)))
	{
		scrollAmount = *delta;
		RvaCameraLocals locals;
		locals.start.X = (Real)(reinterpret_cast<BFMERetailW3DViewInterface *>(this)->getWidth() / 2);
		locals.start.Y = (Real)(reinterpret_cast<BFMERetailW3DViewInterface *>(this)->getHeight() / 2);
		locals.aspect = (Real)(reinterpret_cast<BFMERetailW3DViewInterface *>(this)->getWidth() /
			reinterpret_cast<BFMERetailW3DViewInterface *>(this)->getHeight());
		locals.end.X = locals.start.X + delta->x * globalReal(0x01121744);
		locals.end.Y = (locals.aspect * delta->y) * globalReal(0x01121744) + locals.start.Y;

		locals.screen.pixels.x = (Int)locals.start.X;
		locals.screen.pixels.y = (Int)locals.start.Y;
		((W3DView *)this)->getPickRay(&locals.screen.pixels, &locals.rayStart, &locals.rayEnd);
		locals.rayEnd.X -= locals.rayStart.X;
		locals.rayEnd.Z = 0.0f;
		volatile Real *rayEndY = &locals.rayEnd.Y;
		*rayEndY = locals.rayEnd.Y - locals.rayStart.Y;
		Real lengthSquared = locals.rayEnd.Y * locals.rayEnd.Y + locals.rayEnd.X * locals.rayEnd.X;
		if (lengthSquared != globalReal(0x01075350))
		{
			Real inverseLength = WWMath::Inv_Sqrt(lengthSquared);
			locals.rayEnd.X *= inverseLength;
			locals.rayEnd.Y *= inverseLength;
			locals.rayEnd.Z *= inverseLength;
		}

		camera->Device_To_World_Space(locals.start, &locals.worldStart);
		camera->Device_To_World_Space(locals.end, &locals.worldEnd);
		locals.screen.direction.X = -locals.rayEnd.X;
		locals.screen.direction.Y = -locals.rayEnd.Y;
		locals.rayStart.Y = -locals.rayEnd.Y;
		locals.rayStart.X = locals.rayEnd.Y;
		locals.world.Z = position.Z;
		locals.world.X = position.X;
		locals.world.Y = position.Y;
		volatile Real scale = zoomLimits.slot10() * (cameraZoom * globalReal(0x01083b6c));
		Real horizontal = locals.rayStart.X * delta->x;
		horizontal += locals.screen.direction.X * delta->y;
		locals.world.X += horizontal * scale;
		locals.world.Y += (locals.rayStart.Y * delta->x * locals.aspect + locals.screen.direction.Y * delta->y) * scale;
		if (opaque0044)
			((BfmeViewETH *)this)->bfmeApplyETH((BfmeSubETH *)&locals.world);
		position = locals.world;

		if (locals.world.X >= constraintLowX)
			result |= 1;
		if (locals.world.X <= constraintHighX)
			result |= 2;
		if (locals.world.Y >= constraintLowY)
			result |= 4;
		if (locals.world.Y <= constraintHighY)
			result |= 8;
		cameraMovementFlag = 0;
		((Gen_00742DA0 *)this)->bfmeFinish();
		RvaCameraNotifier *notifier = cameraNotifier();
		if (notifier)
			notifier->notify(1);
	}
	return result;
}
