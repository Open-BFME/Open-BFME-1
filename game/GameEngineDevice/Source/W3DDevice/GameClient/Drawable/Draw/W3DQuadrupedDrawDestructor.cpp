// cl: /DNDEBUG /MD /EHsc

// W3DQuadrupedDraw has W3DModelDraw's primary polymorphic base and the
// W3DModelDrawInterface secondary vptr at +0x0C.  Its empty destructor therefore
// re-seats both vptrs and tail-calls W3DModelDraw's destructor.

class W3DModelDraw
{
protected:
	virtual ~W3DModelDraw();

private:
	unsigned int m_data[ 2 ];
};

class W3DModelDrawInterface
{
public:
	virtual void w3dModelDrawInterfaceAnchor();
};

class W3DQuadrupedDraw : public W3DModelDraw, public W3DModelDrawInterface
{
public:
	virtual ~W3DQuadrupedDraw();
};

W3DQuadrupedDraw::~W3DQuadrupedDraw()
{
}
