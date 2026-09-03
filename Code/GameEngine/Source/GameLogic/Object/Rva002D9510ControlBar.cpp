// Address-derived control-bar dirtying helper at 0x002D9510.
// cl: /O2 /DNDEBUG /DWIN32 /MD

class Rva002D9510Value;

class Rva002D9510Target
{
public:
	void applyFirst(Rva002D9510Value *value);
	void applySecond(Rva002D9510Value *value);
};

class Rva002D9510Source
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual Rva002D9510Target *getTarget() = 0;
};

class Rva002D9510Data
{
public:
	unsigned char m_pad000[0x70];
	Rva002D9510Value *m_firstStorage;
	Rva002D9510Value *m_secondStorage;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	unsigned char m_pad000[0x24];
	bool m_dirty;
};

extern ControlBar *TheControlBar;

class Rva002D9510Owner
{
public:
	void applyAndDirty();
};

void Rva002D9510Owner::applyAndDirty()
{
	Rva002D9510Target *target = (*reinterpret_cast<Rva002D9510Source **>(reinterpret_cast<char *>(this) - 8))->getTarget();
	if (target) {
		target->applyFirst(reinterpret_cast<Rva002D9510Value *>(reinterpret_cast<char *>(*reinterpret_cast<Rva002D9510Data **>(reinterpret_cast<char *>(this) - 12)) + 0x70));
		target->applySecond(reinterpret_cast<Rva002D9510Value *>(reinterpret_cast<char *>(*reinterpret_cast<Rva002D9510Data **>(reinterpret_cast<char *>(this) - 12)) + 0x74));
	}
	TheControlBar->m_dirty = true;
}
