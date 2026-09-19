// cl: /DNDEBUG /MD /O2 /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct XferVersion
{
	unsigned char m_version;
	unsigned char m_currentVersion;
	unsigned short m_padding;
};

class BfmeSeedTarget;
class BroadcastStealthUpdate;

class Gen_001ED0C0
{
	friend class BroadcastStealthUpdate;

private:
	void bfmeAccept(BfmeSeedTarget *target);
};

class BfmeSubAccept_00029DAC
{
public:
	void bfmeAccept(BfmeSeedTarget *target);

private:
	unsigned char m_pad[8];
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual bool isLoading();
	virtual bool isSaving();
	virtual bool isCRC();
	virtual bool isLightCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(XferVersion *version);
	virtual Xfer &xferTypeName(const char *const &name);
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual Xfer &xferUnsignedInt(unsigned int *value);
	virtual Xfer &xferInt(int *value);
};

struct BfmeFormattedText
{
	char *text;
	int tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(
	BfmeFormattedText *result, int tag, const char *format, ...);
extern void __cdecl bfmeCalcTGC(void *xfer, int *value);
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);

class BroadcastStealthUpdate
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad[0x1c];
	BfmeSubAccept_00029DAC m_bfmeSub0;
	_STL::list<void *> m_broadcastObjects;
	unsigned int m_broadcastObjectCount;
	_STL::list<int> m_pendingObjects;
};

// ?xfer@BroadcastStealthUpdate@@MAEXPAVXfer@@@Z
void BroadcastStealthUpdate::xfer(Xfer *xfer)
{
	((Gen_001ED0C0 *)this)->bfmeAccept((BfmeSeedTarget *)xfer);
	if (xfer->isLightCRC())
		return;

	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 2;
	xfer->xferVersion(&version);
	if (version.m_currentVersion >= 2)
		m_bfmeSub0.bfmeAccept((BfmeSeedTarget *)xfer);

	int value;
	if (xfer->isSaving())
	{
		xfer->xferInt((int *)&m_broadcastObjectCount);
		_STL::list<void *>::_Node *node =
			(_STL::list<void *>::_Node *)m_broadcastObjects._M_node._M_data->_M_next;
		while (node != m_broadcastObjects._M_node._M_data)
		{
			value = *(int *)((char *)node->_M_data + 0x74);
			bfmeCalcTGC(xfer, &value);
			node = (_STL::list<void *>::_Node *)node->_M_next;
		}
	}
	else
	{
		if (!m_broadcastObjects.empty())
		{
			BfmeFormattedText error;
			bfmeFormatText(&error, 5, 0);
			_CxxThrowException(&error, (void *)0x011DFE5C);
		}

		xfer->xferInt((int *)&m_broadcastObjectCount);
		for (unsigned int i = 0; i < m_broadcastObjectCount; ++i)
		{
			bfmeCalcTGC(xfer, &value);
			m_pendingObjects.push_back(value);
		}
	}
}
