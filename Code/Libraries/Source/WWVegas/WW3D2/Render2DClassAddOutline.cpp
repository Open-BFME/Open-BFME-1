// cl: /DNDEBUG /MD /EHsc
// readable body of ?Add_Outline@Render2DClass@@: Code/Libraries/Source/WWVegas/WW3D2/render2d.cpp

// BFME emits the three-argument outline overload directly instead of routing
// it through the UV overload found in the Zero Hour source.  The four line
// endpoints and their one-pixel bias are otherwise the original Render2D
// implementation.

typedef unsigned long uint32;

class Vector2
{
public:
	Vector2(float x, float y) : X(x), Y(y) {}

	float X;
	float Y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/rect.h
class RectClass
{
public:
	float Left;
	float Top;
	float Right;
	float Bottom;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2d.h
class Render2DClass
{
public:
	void Add_Line(const Vector2 &a, const Vector2 &b, float width, uint32 color);
	void Add_Outline(const RectClass &rect, float width, uint32 color);
};

// ?Add_Outline@Render2DClass@@QAEXABVRectClass@@MK@Z
void Render2DClass::Add_Outline(const RectClass &rect, float width, uint32 color)
{
	Add_Line(Vector2(rect.Left + 1, rect.Bottom),
		Vector2(rect.Left + 1, rect.Top + 1), width, color);
	Add_Line(Vector2(rect.Left, rect.Top + 1),
		Vector2(rect.Right - 1, rect.Top + 1), width, color);
	Add_Line(Vector2(rect.Right, rect.Top),
		Vector2(rect.Right, rect.Bottom - 1), width, color);
	Add_Line(Vector2(rect.Right, rect.Bottom),
		Vector2(rect.Left + 1, rect.Bottom), width, color);
}
