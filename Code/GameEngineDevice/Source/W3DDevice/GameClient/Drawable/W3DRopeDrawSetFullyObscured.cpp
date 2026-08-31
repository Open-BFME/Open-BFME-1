// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;

class W3DRopeDraw
{
public:
	virtual void setFullyObscuredByShroud(Bool fullyObscured);
};

// W3DRopeDraw's primary vtable slot points through ILT 0x00013D1D to
// 0x0074FFC0. Rope rendering does not retain a separate shroud state.
void W3DRopeDraw::setFullyObscuredByShroud(Bool fullyObscured)
{
}
