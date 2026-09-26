// cl: /DNDEBUG /MD /EHsc

// W3DSupplyDraw is a W3DModelDraw-family module with the secondary model-draw
// interface vptr at +0x0C.  Its empty destructor re-seats both vptrs and then
// tail-calls the matched W3DModelDraw destructor.

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

class W3DSupplyDraw : public W3DModelDraw, public W3DModelDrawInterface
{
protected:
	virtual ~W3DSupplyDraw();
};

W3DSupplyDraw::~W3DSupplyDraw()
{
}
