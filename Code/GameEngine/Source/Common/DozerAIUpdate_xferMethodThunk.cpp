// cl: /DNDEBUG /MD /EHsc
// readable body of ?xfer@DozerAIUpdate@@MAEXPAVXfer@@@Z: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdate.cpp
// Open-BFME5: retail-layout C++ conversion of the dozer snapshot transfer.

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

// BFME's Xfer dispatch keeps xferVersion at slot 10, xferSnapshot at slot 12,
// xferUser at slot 9, and the typed transfers at their retail slots.  The
// unnamed slots are retained so the calls use the original vtable offsets.
class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual Bool isLightCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void xferUser(void *, int);
	virtual void xferVersion(XferVersion *);
	virtual void slot11();
	virtual void xferSnapshot(void *);
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
	virtual void xferCoord3D(float *);
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void xferUnsignedInt(UnsignedInt *);
	virtual void xferInt(int *);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(UnsignedInt *);
};

class DozerRootBase
{
public:
	virtual ~DozerRootBase();

private:
	unsigned char m_pad[8];
};

class DozerIface1 { public: virtual void vslot(); };
class DozerIface2 { public: virtual void vslot(); private: unsigned char m_pad[0xC]; };
class DozerIface3 { public: virtual void vslot(); };
class DozerIface4 { public: virtual void vslot(); };

class BfmeSeedTarget;
class Gen_002B3190
{
private:
	void bfmeAccept(BfmeSeedTarget *);
	friend void invokeDozerBaseXfer(Gen_002B3190 *, BfmeSeedTarget *);
};

static void invokeDozerBaseXfer(Gen_002B3190 *base, BfmeSeedTarget *xfer)
{
	base->bfmeAccept(xfer);
}

class AIUpdateInterface : public DozerRootBase, public DozerIface1,
	public DozerIface2, public DozerIface3, public DozerIface4
{
public:
	virtual ~AIUpdateInterface();
	virtual void xfer(Xfer *);

private:
	unsigned char m_pad[0x318];
};

class DozerAIInterface { public: virtual void vslot(); };

class DozerPrimaryStateMachine
{
public:
	virtual ~DozerPrimaryStateMachine();
};

class AudioEventRTS
{
public:
	virtual ~AudioEventRTS();
	void xfer(Xfer *);

private:
	unsigned char m_pad[0x6C];
};

class BfmeSubAccept_0002C41C
{
public:
	void bfmeAccept(BfmeSeedTarget *);
};

class DozerAIUpdate : public AIUpdateInterface, public DozerAIInterface
{
protected:
	virtual void xfer(Xfer *);

private:
	struct DozerTaskInfo
	{
		ObjectID m_targetObjectID;
		UnsignedInt m_taskOrderFrame;
	};

	struct DozerDockPointInfo
	{
		UnsignedInt m_valid;
		float m_location[3];
	};

	DozerTaskInfo m_task[3];
	DozerPrimaryStateMachine *m_dozerMachine;
	UnsignedInt m_currentTask;
	AudioEventRTS m_buildingSound;
	UnsignedInt m_isRebuild;
	DozerDockPointInfo m_dockPoint[3][3];
	UnsignedInt m_buildSubTask;
};

struct BfmeFormattedText
{
	char *m_text;
	int m_tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(BfmeFormattedText *, int, const char *, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *, void *);
extern void friend_xferObjectID(Xfer *, ObjectID *);

// ?xfer@DozerAIUpdate@@MAEXPAVXfer@@@Z
void DozerAIUpdate::xfer(Xfer *xfer)
{
	invokeDozerBaseXfer(reinterpret_cast<Gen_002B3190 *>(this), reinterpret_cast<BfmeSeedTarget *>(xfer));

	if (xfer->isLightCRC())
		return;

	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	int numTasks = 3;
	xfer->xferInt(&numTasks);
	if (numTasks != 3)
	{
		BfmeFormattedText error;
		bfmeFormatText(&error, 5, 0);
		_CxxThrowException(&error, (void *)0x011DFE5C);
	}

	UnsignedInt *taskOrderFrame = &m_task[0].m_taskOrderFrame;
	for (int i = 0; i < 3; ++i)
	{
		friend_xferObjectID(xfer, reinterpret_cast<ObjectID *>(taskOrderFrame - 1));
		xfer->xferUnsignedInt(taskOrderFrame);
		taskOrderFrame += 2;
	}

	xfer->xferSnapshot(m_dozerMachine);
	xfer->xferUser(&m_currentTask, sizeof(m_currentTask));

	int dockPoints = 3;
	xfer->xferInt(&dockPoints);
	if (dockPoints != 3)
	{
		BfmeFormattedText error;
		bfmeFormatText(&error, 5, 0);
		_CxxThrowException(&error, (void *)0x011DFE5C);
	}

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			xfer->xferBool(&m_dockPoint[i][j].m_valid);
			xfer->xferCoord3D(m_dockPoint[i][j].m_location);
		}
	}

	xfer->xferUser(&m_buildSubTask, sizeof(m_buildSubTask));
	reinterpret_cast<BfmeSubAccept_0002C41C *>(&m_buildingSound)->bfmeAccept(reinterpret_cast<BfmeSeedTarget *>(xfer));
	xfer->xferBool(&m_isRebuild);
}
