// ?rva006EBD20@W3DDisplay@@UAEXMMMMK@Z
// partial score=0.8 date=2026-09-04
// ?rva006EBD20@W3DDisplay@@UAEXMMMMK@Z

// cl: /DNDEBUG /MD /EHsc

typedef unsigned long UnsignedInt;

struct BfmeV1207
{
	BfmeV1207() {}
	BfmeV1207(float x, float y) : X(x), Y(y) {}
	float X;
	float Y;
};

typedef BfmeV1207 BfmeVector2;

struct BfmeFloatRect
{
	BfmeFloatRect(float left, float top, float right, float bottom)
		: Left(left), Top(top), Right(right), Bottom(bottom) {}
	float Left;
	float Top;
	float Right;
	float Bottom;
};

class BfmeRender2D
{
private:
	unsigned char m_unmodelled_00[0x54];
	unsigned char m_texturingEnabled;

public:
	void disableTexturing() { m_texturingEnabled = 0; }
	void addRect006e(const BfmeFloatRect &rect, int color);
};

class BfmeA1207 : public BfmeRender2D
{
public:
	void bfmeDo1207(const BfmeV1207 &a1, const BfmeV1207 &a2,
		const BfmeV1207 &a3, const BfmeV1207 &a4,
		const BfmeV1207 &a5, const BfmeV1207 &a6, int color);
};

class W3DDisplay
{
private:
	unsigned char m_unmodelled_04[0x160];
	BfmeA1207 *m_render2D;

public:
	virtual void rva006EBD20(float x, float y, float width, float height, UnsignedInt color);
};


extern "C" __declspec(dllimport) double __cdecl ceil(double);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
#pragma intrinsic(sin, cos)
// Retail vtable VA 0x0111EE94 -> ILT RVA 0x6F00 -> RVA 0x6EBD20.
// Address-qualified identity: filled ellipse fan; Display ownership from adjacent verified rect methods.
// WWMath::Float_To_Long(float), original WWMath/wwmath.h compiler helper.
// Normal casts call _ftol; /QIfist emits qword FISTP instead of this original dword rounding helper.
inline long floatToLong(float f) { long i; __asm { fld [f] } __asm { fistp [i] } return i; }
void W3DDisplay::rva006EBD20(float x, float y, float width, float height, UnsignedInt color)
{
 m_render2D->disableTexturing();
 float rx=width/2, ry=height/2;
 float cx=x+rx, cy=y+ry;
 BfmeVector2 previous(rx,0);
 int count=floatToLong((float)ceil((rx>ry?rx:ry)*4));
 float step=6.28318530717958647692f/count;
 float angle=0;
 for(int i=0;i<count;){
  BfmeVector2 next;
  if(++i<count){
   angle+=step;
   next.X=rx*(float)cos(angle);
   next.Y=ry*(float)sin(angle);
  } else { next.X=rx; next.Y=0; }
  m_render2D->bfmeDo1207(BfmeVector2(cx,cy), BfmeVector2(cx+previous.X,cy+previous.Y), BfmeVector2(cx+next.X,cy+next.Y),BfmeVector2(0,0),BfmeVector2(0,0),BfmeVector2(0,0),color);
  previous=next;
 }
}
