// cl: /DNDEBUG /MD /EHsc
//
// Retail's FadeAndDieOrnamentUpdateModuleData vtable at 0x0108E838 names
// this scalar deleting destructor in slot zero. Its call target is the
// separately matched destructor body at 0x00126E70.

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
};

class FadeAndDieOrnamentUpdateModuleDataBase
{
public:
	virtual ~FadeAndDieOrnamentUpdateModuleDataBase() {}

private:
	unsigned char m_pad[0x4];
};

class FadeAndDieOrnamentUpdateModuleData
	: public FadeAndDieOrnamentUpdateModuleDataBase
{
public:
	virtual ~FadeAndDieOrnamentUpdateModuleData();

private:
	BFMERetailAsciiString m_buffer;
};

FadeAndDieOrnamentUpdateModuleData::~FadeAndDieOrnamentUpdateModuleData()
{
}
