// cl: /DNDEBUG /MD /EHsc

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;

struct XferVersion
{
	UnsignedByte current;
	UnsignedByte minimum;
};

class Xfer
{
public:
	virtual void unused00();
	virtual bool isLoading() const;
	virtual bool isSaving() const;
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void xferVersion(XferVersion *version);
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void xferUnsignedInt(UnsignedInt *value);
	virtual void unused30();
	virtual void xferUnsignedShort(UnsignedShort *value);
};

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);
extern int g_rva005c5100ThrowInfo;
extern void __cdecl bfmeCalcTGC(void *xfer, int *value);

class UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);
};

class ObjectTracker
{
public:
	ObjectTracker() : objectID(0), next(0) {}
	virtual ~ObjectTracker() {}

	int objectID;
	ObjectTracker *next;
};

class PropagandaTowerBehavior : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_padding04[0x20];
	UnsignedInt m_lastScanFrame;
	ObjectTracker *m_insideList;
};

union XferLocal
{
	XferVersion version;
	XferException error;
};

// ?xfer@PropagandaTowerBehavior@@MAEXPAVXfer@@@Z
void PropagandaTowerBehavior::xfer(Xfer *xfer)
{
	XferLocal local;
	local.version.current = 1;
	local.version.minimum = 1;
	xfer->xferVersion(&local.version);
	UpdateModule::xfer(xfer);
	xfer->xferUnsignedInt(&m_lastScanFrame);

	UnsignedShort insideCount = 0;
	for (ObjectTracker *tracker = m_insideList;
		tracker != 0; tracker = tracker->next)
		++insideCount;
	xfer->xferUnsignedShort(&insideCount);

	if (xfer->isSaving())
	{
		ObjectTracker *tracker = m_insideList;
		while (tracker != 0)
		{
			bfmeCalcTGC(xfer, &tracker->objectID);
			tracker = tracker->next;
		}
	}
	else
	{
		if (m_insideList != 0)
		{
			bfmeFormatText(&local.error, 5, 0);
			_CxxThrowException(&local.error, &g_rva005c5100ThrowInfo);
		}

		for (UnsignedShort i = 0; i < insideCount; ++i)
		{
			ObjectTracker *tracker = new ObjectTracker;
			tracker->next = m_insideList;
			m_insideList = tracker;
			bfmeCalcTGC(xfer, &tracker->objectID);
		}
	}
}
