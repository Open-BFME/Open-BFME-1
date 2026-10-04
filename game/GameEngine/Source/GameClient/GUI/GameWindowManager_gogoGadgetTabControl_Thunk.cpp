// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BFME's gadget factory dispatch reaches this vtable-slot-18 body through
// Rva0078F730Owner::selectFactory.  The BFME dispatch ABI is the reduced
// `(factory-record, TabControlData *, GameFont *, bool)` form below rather
// than the larger upstream source declaration.  The record's owner and
// instance-data offsets are shared with the matched BFME progress-bar sibling.
// The emitted reduced-ABI spelling below is the true identity retained in the
// ledger; the canonical upstream method supplies the matching gadget logic.

class GameWindow;
class GameFont;

class WinInstanceData
{
public:
	char m_gap00[0xc];
	unsigned int m_style;
};

struct Rva0047D090FactoryRecord
{
	GameWindow *m_owner;
	char m_gap04[0x2c];
	WinInstanceData *m_instanceData;
};

struct Rva0047D090TabControlData
{
	char m_data[0x54];
};

// GameWindow needs a complete type here so that the union's member-pointer
// spelling of the ?j_00002e69 thunk does not disturb codegen.
class GameWindow
{
};

extern void j_00002e69();
extern void j_00048365();
extern void j_0004b501();
extern void j_00008936();
extern void j_00047230();
class RouteWinSetOwner {};

class GameWindowManager
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual GameWindow *gogoGadgetTabControl(Rva0047D090FactoryRecord *, Rva0047D090TabControlData *, GameFont *, bool);
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void assignDefaultGadgetLook(GameWindow *, GameFont *, bool);
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual GameWindow *create(Rva0047D090FactoryRecord *);
};

extern GameWindowManager *TheWindowManager;

GameWindow *GameWindowManager::gogoGadgetTabControl(
	Rva0047D090FactoryRecord *record,
	Rva0047D090TabControlData *source,
	GameFont *defaultFont,
	bool defaultVisual)
{
	if ((record->m_instanceData->m_style & 0x2000) == 0)
		return 0;
	GameWindow *tabControl = TheWindowManager->create(record);
	if (tabControl == 0)
		return 0;
	Rva0047D090TabControlData *tabData = new Rva0047D090TabControlData;
	*tabData = *source;
	typedef void (GameWindow::*SetUserData)(void *);
	union { void (*fn)(); SetUserData call; } setUserData = { j_00002e69 };
	(tabControl->*setUserData.call)(tabData);
	typedef void (__cdecl *ComputeTabRegion)(GameWindow *);
	union { void (*fn)(); ComputeTabRegion call; } computeTabRegion = { j_00048365 };
	(computeTabRegion.call)(tabControl);
	typedef void (__cdecl *CreateSubPanes)(GameWindow *);
	union { void (*fn)(); CreateSubPanes call; } createSubPanes = { j_0004b501 };
	(createSubPanes.call)(tabControl);
	typedef void (__cdecl *ShowSubPane)(GameWindow *, int);
	union { void (*fn)(); ShowSubPane call; } showSubPane = { j_00008936 };
	(showSubPane.call)(tabControl, 0);
	typedef int (RouteWinSetOwner::*SetOwner)(GameWindow *);
	union { void (*fn)(); SetOwner call; } setOwner = { j_00047230 };
	(((RouteWinSetOwner *)tabControl)->*setOwner.call)(record->m_owner);
	assignDefaultGadgetLook(tabControl, defaultFont, defaultVisual);
	return tabControl;
}