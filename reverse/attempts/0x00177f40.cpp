// ?d_00177f40@@YAXXZ
// partial score=0.95 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class StateMachine;
class NotifyWeaponFiredInterface;

class AIAttackFireWeaponState
{
public:
	virtual void update();
	AIAttackFireWeaponState(StateMachine *machine, NotifyWeaponFiredInterface *notify);

private:
	char m_fields[0x28];
};

class Xfer
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual bool isLightCRC();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void xferUser(void *, int);
	virtual void xferVersion(XferVersion *);
	virtual void slot2C();
	virtual void xferSnapshot(void *);
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void xferAt4C(void *);
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void xferCoord3D(void *);
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void xferUnsignedInt(UnsignedInt *);
	virtual Xfer &operator==(int &);
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void xferBool(bool *);
};

class AIInternalMoveToState
{
protected:
	virtual void xfer(Xfer *xfer);

	char m_padding00[0x18];
	StateMachine *m_machine;
	char m_padding20[0x30];
};

class AIAttackMeleeEngageState : public AIInternalMoveToState
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	AIAttackFireWeaponState *m_fireWeaponState;
	int m_field54;
	UnsignedInt m_field58;
	char m_field5C[0x0C];
	char m_field68[0x08];
	UnsignedInt m_field70;
	bool m_field74;
	bool m_field75;
	char m_padding76[0x02];
	NotifyWeaponFiredInterface *m_notifyWeaponFired;
};

// ?xfer@AIAttackMeleeEngageState@@MAEXPAVXfer@@@Z
void AIAttackMeleeEngageState::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 3;
	xfer->xferVersion(&version);
	AIInternalMoveToState::xfer(xfer);

	if (!xfer->isLightCRC())
	{
		xfer->xferCoord3D(m_field5C);
		xfer->xferAt4C(m_field68);
		xfer->xferUnsignedInt(&m_field58);
		xfer->xferBool(&m_field75);

		if (version.m_currentVersion > 1)
		{
			if (m_fireWeaponState == 0)
				m_fireWeaponState = new AIAttackFireWeaponState(m_machine, m_notifyWeaponFired);

			int field54 = m_field54;
			xfer->operator==(field54);
			m_field54 = field54;
			xfer->xferSnapshot(m_fireWeaponState);
		}

		if (version.m_currentVersion > 2)
		{
			xfer->xferUnsignedInt(&m_field70);
			xfer->xferBool(&m_field74);
		}
	}
}
