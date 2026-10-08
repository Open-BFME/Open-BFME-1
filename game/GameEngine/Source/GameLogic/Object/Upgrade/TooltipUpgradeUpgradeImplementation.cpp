// TooltipUpgrade::upgradeImplementation at retail 0x002D9510: slot 9 of the UpgradeMux table
// 0x010CE1A0, reached only through ILT 0x0002DBF0. TooltipUpgrade's registered
// constructor 0x002D93E0 stores that table. Evidence:
// targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md
// Address-derived control-bar dirtying helper at 0x002D9510.
// cl: /O2 /DNDEBUG /DWIN32 /MD

class Rva002D9510Value;

class Rva002D9510Target
{
public:
	void applyFirst(Rva002D9510Value *value);
	void applySecond(Rva002D9510Value *value);
};

// Retail calls reach ILT 0x00031F75 -> 0x00418B50 and ILT 0x00025162 ->
// 0x00415AA0; called by those ledger row names.
class AsciiString;
template <class T> class StringBase;

class Rva00418B50Owner
{
public:
	void setName(const AsciiString &name);
};

class Rva00415AA0
{
public:
	void assign(const StringBase<char> &value);
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	unsigned char m_pad000[0x24];
	bool m_UIDirty;
};

extern ControlBar *TheControlBar;

class TooltipUpgrade
{
protected:
	virtual void upgradeImplementation();
};

void TooltipUpgrade::upgradeImplementation()
{
	Rva002D9510Target *target = (*reinterpret_cast<Rva002D9510Source **>(reinterpret_cast<char *>(this) - 8))->getTarget();
	if (target) {
		reinterpret_cast<Rva00418B50Owner *>(target)->setName(*reinterpret_cast<const AsciiString *>(reinterpret_cast<Rva002D9510Value *>(reinterpret_cast<char *>(*reinterpret_cast<Rva002D9510Data **>(reinterpret_cast<char *>(this) - 12)) + 0x70)));
		reinterpret_cast<Rva00415AA0 *>(target)->assign(*reinterpret_cast<const StringBase<char> *>(reinterpret_cast<Rva002D9510Value *>(reinterpret_cast<char *>(*reinterpret_cast<Rva002D9510Data **>(reinterpret_cast<char *>(this) - 12)) + 0x74)));
	}
	TheControlBar->m_UIDirty = true;
}
