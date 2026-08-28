#pragma once
#include <vector>
#include <utility>
#include "ascii_string.h"

class INI;
class Xfer;

// Retail's vtable (0x01141640) has nine slots. The ones we can name are
//   0 ~SubsystemInterface   1 init   2 loadIniFilesFromLegend   4 reset   5 update
// Slots 3, 6, 7 and 8 are base virtuals we have not identified (7 and 8 are empty
// bodies shared by ~130 classes), so the vtable we emit is shorter than retail's.
// Slots 1 and 2 are the load-bearing ones: SubsystemInterfaceList::initSubsystem
// dispatches through [vptr+4] and [vptr+8].
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface {
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	// BFME-only: look this subsystem up in TheSubsystemLegend by name and load the
	// INI files and directories its "LoadSubsystem" block lists. Returns TRUE if
	// the legend supplied anything, in which case initSubsystem skips the
	// hard-coded paths it was passed.
	virtual Bool loadIniFilesFromLegend();
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw( void ) {}
	inline void UPDATE(void) { update(); }
	inline void DRAW(void) { draw(); }
	void setName(AsciiString name) { m_name = name; }
	AsciiString getName(void);
protected:
	AsciiString m_name;
};

// The registry GameEngine::init drives; retail keeps it at 0x0134C6C8.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterfaceList
{
public:
	SubsystemInterfaceList();
	~SubsystemInterfaceList();

	void initSubsystem(SubsystemInterface *sys, void *slot, const char *path1,
					   const char *path2, const char *dirpath, Xfer *pXfer, AsciiString name);

	// Layout read off the two functions that touch it: the vector occupies +0x00
	// (start/finish/end at +0/+4/+8, eight-byte elements, so it holds pairs) and
	// the Xfer the legend loader passes to INI::load sits at +0x0c.
	std::vector<std::pair<SubsystemInterface *, void *> >	m_subsystems;	// +0x00
	Xfer													*m_xfer;		// +0x0c
};

extern SubsystemInterfaceList *TheSubsystemList;

// The eight-byte polymorphic holder the initSubsystem template news for every
// subsystem: a vptr (retail 0x01075D8C) plus the address of the global the
// subsystem was stored into. Handed to SubsystemInterfaceList::initSubsystem as
// its second argument and parked alongside the subsystem in m_subsystems, which
// is why that vector holds pairs.
// One instantiation per subsystem, not one shared class: each initSubsystem<T>
// stores a DIFFERENT vtable pointer here (0x1075D8C, 0x1075DA8, 0x1075DB4,
// 0x1075DCC, 0x1075DE8, 0x1075DEC for the six landed so far), which is only
// possible if the slot is parameterised on the same T. Modelling it as a plain
// class makes every instantiation claim one vtable symbol and trips the DIR32
// consistency check.
template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	SubsystemSlot(void *slot) : m_slot(slot) {}
	virtual ~SubsystemSlot();
	void *m_slot;
};

// GameEngine::init calls this once per subsystem; ZH has the same helper.
template<class SUBSYSTEM>
void initSubsystem(SUBSYSTEM *&sysref, AsciiString name, SUBSYSTEM *sys, Xfer *pXfer,
				   const char *path1 = 0, const char *path2 = 0, const char *dirpath = 0)
{
	sysref = sys;
	TheSubsystemList->initSubsystem(sys, new SubsystemSlot<SUBSYSTEM>(&sysref), path1, path2, dirpath, pXfer, name);
}
