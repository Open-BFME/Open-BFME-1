// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail's CritterEmitterUpdateModuleData vtable at 0x010A39F0 names this
// scalar deleting destructor in slot zero. Its call target is the separately
// matched destructor body at 0x001FA750.

#include <vector>

struct CritterEmitterPod { int data[2]; };

class AsciiString
{
public:
	~AsciiString();
private:
	char *m_data;
};

class CritterEmitterUpdateModuleDataInner
{
public:
	~CritterEmitterUpdateModuleDataInner();
private:
	unsigned char m_pad[0x9c];
};

class CritterEmitterUpdateModuleDataUnknownB4
{
public:
	~CritterEmitterUpdateModuleDataUnknownB4();
private:
	unsigned char m_pad[12];
};

class CritterEmitterUpdateModuleDataRootBase
{
public:
	virtual ~CritterEmitterUpdateModuleDataRootBase() {}
private:
	void *m_04;
};

class CritterEmitterUpdateModuleDataBase : public CritterEmitterUpdateModuleDataRootBase
{
public:
	virtual ~CritterEmitterUpdateModuleDataBase() {}
private:
	CritterEmitterUpdateModuleDataInner m_08;
};

class CritterEmitterUpdateModuleData : public CritterEmitterUpdateModuleDataBase
{
public:
	virtual ~CritterEmitterUpdateModuleData();
private:
	AsciiString m_a4;
	_STL::vector<CritterEmitterPod> m_a8;
	CritterEmitterUpdateModuleDataUnknownB4 m_b4;
	AsciiString m_c0;
};

CritterEmitterUpdateModuleData::~CritterEmitterUpdateModuleData()
{
}
