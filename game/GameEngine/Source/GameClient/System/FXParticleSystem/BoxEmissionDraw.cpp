// Box volume callback recovered from the complete retail body at
// retail RVA 0x005F8770 (224 bytes).  Box createModule installs this callback
// in primary vtable 0x01112360 slot 4.  This shape keeps the proven
// upper-to-lower endpoint order and assigns the upper local before the lower
// local at every later edge update.
// cl: /DNDEBUG /MD /GX- /O2 /Ob2

struct Rva005F8770Coord3D
{
	float x;
	float y;
	float z;
};

// Slot +0x2C takes two coordinate pointers and two scalar words. Its retail
// implementation is a ret 0x10 no-op; the historical method name is unknown.
class View
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28();
	virtual void Rva0045BA00Slot(const Rva005F8770Coord3D *from,
		const Rva005F8770Coord3D *to, unsigned int colour,
		unsigned int flags);
};

extern View *TheTacticalView;

class Rva005F8770BoxCallbackView
{
	char opaquePrefix[0x20];
	float extentX;
	float extentY;
	float extentZ;

public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void Rva005F8770Draw(float x, float y, float z);
};

void Rva005F8770BoxCallbackView::Rva005F8770Draw(float x, float y, float z)
{
	Rva005F8770Coord3D upper;
	Rva005F8770Coord3D lower;

	upper.x = x + extentX;
	upper.y = y + extentY;
	upper.z = z + extentZ;
	lower.x = x + extentX;
	lower.y = y + extentY;
	lower.z = z - extentZ;
	TheTacticalView->Rva0045BA00Slot(&upper, &lower, 0xCCAAFFFF, 0);

	upper.x = x - extentX;
	lower.x = x - extentX;
	TheTacticalView->Rva0045BA00Slot(&upper, &lower, 0xCCAAFFFF, 0);

	upper.y = y - extentY;
	lower.y = y - extentY;
	TheTacticalView->Rva0045BA00Slot(&upper, &lower, 0xCCAAFFFF, 0);

	upper.x = x + extentX;
	lower.x = x + extentX;
	TheTacticalView->Rva0045BA00Slot(&upper, &lower, 0xCCAAFFFF, 0);
}
