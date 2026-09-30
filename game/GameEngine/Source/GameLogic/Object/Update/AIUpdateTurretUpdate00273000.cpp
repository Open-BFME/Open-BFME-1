// Retail 0x00273000, reached only through ILT 0x00010456. Runs both turret AIs of an
// AIUpdateInterface and keeps the smallest sleep time. name_oracle witnesses
// AIUpdateInterface+0x1E8 m_turretAI, Object+0x344 m_privateStatus and Object+0x1A4
// m_disabledMask; the sole callee is TurretAI::updateTurretAI (ILT 0x00002342 ->
// 0x0018D710). No named caller or vtable slot names the method, so it stays opaque.
// The disabled test is two separate bits (0x04, 0x10) that MSVC folds into one
// `test byte ptr ..., 0x14`; spelling it as one 0x14 mask flips the ESI/EDI
// assignment of the object and receiver.

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class TurretAI
{
public:
	UpdateSleepTime updateTurretAI();
};

class BfmeObjectSub204
{
public:
	virtual void bfmeSlot00();
	virtual void bfmeSlot01();
	virtual void bfmeSlot02();
	virtual void bfmeSlot03();
	virtual void bfmeSlot04();
	virtual void bfmeSlot05();
	virtual void bfmeSlot06();
	virtual void bfmeSlot07();
	virtual void bfmeSlot08();
	virtual void bfmeSlot09();
	virtual void bfmeSlot10();
	virtual void bfmeSlot11();
	virtual void bfmeSlot12();
	virtual void bfmeSlot13();
	virtual void bfmeSlot14();
	virtual void bfmeSlot15();
	virtual void bfmeSlot16();
	virtual void bfmeSlot17();
	virtual void bfmeSlot18();
	virtual void bfmeSlot19();
	virtual void bfmeSlot20();
	virtual void bfmeSlot21();
	virtual void bfmeSlot22();
	virtual void bfmeSlot23();
	virtual void bfmeSlot24();
	virtual void bfmeSlot25();
	virtual void bfmeSlot26();
	virtual void bfmeSlot27();
	virtual void bfmeSlot28();
	virtual void bfmeSlot29();
	virtual void bfmeSlot30();
	virtual void bfmeSlot31();
	virtual void bfmeSlot32();
	virtual void bfmeSlot33();
	virtual void bfmeSlot34();
	virtual void bfmeSlot35();
	virtual void bfmeSlot36();
	virtual void bfmeSlot37();
	virtual void bfmeSlot38();
	virtual void bfmeSlot39();
	virtual void bfmeSlot40();
	virtual void bfmeSlot41();
	virtual void bfmeSlot42();
	virtual void bfmeSlot43();
	virtual void bfmeSlot44();
	virtual void bfmeSlot45();
	virtual void bfmeSlot46();
	virtual void bfmeSlot47();
	virtual void bfmeSlot48();
	virtual void bfmeSlot49();
	virtual void bfmeSlot50();
	virtual void bfmeSlot51();
	virtual void bfmeSlot52();
	virtual void bfmeSlot53();
	virtual void bfmeSlot54();
	virtual void bfmeSlot55();
	virtual void bfmeSlot56();
	virtual void bfmeSlot57();
	virtual void bfmeSlot58();
	virtual void bfmeSlot59();
	virtual void bfmeSlot60();
	virtual void bfmeSlot61();
	virtual void bfmeSlot62();
	virtual void bfmeSlot63();
	virtual void bfmeSlot64();
	virtual void bfmeSlot65();
	virtual void bfmeSlot66();
	virtual void bfmeSlot67();
	virtual void bfmeSlot68();
	virtual void bfmeSlot69();
	virtual void bfmeSlot70();
	virtual void bfmeSlot71();
	virtual void bfmeSlot72();
	virtual void bfmeSlot73();
	virtual void bfmeSlot74();
	virtual void bfmeSlot75();
	virtual void bfmeSlot76();
	virtual void bfmeSlot77();
	virtual void bfmeSlot78();
	virtual void bfmeSlot79();
	virtual void bfmeSlot80();
	virtual void bfmeSlot81();
	virtual void bfmeSlot82();
	virtual void bfmeSlot83();
	virtual void bfmeSlot84();
	virtual void bfmeSlot85();
	virtual void bfmeSlot86();
	virtual void bfmeSlot87();
	virtual void bfmeSlot88();
	virtual void bfmeSlot89();
	virtual void bfmeSlot90();
	virtual void bfmeSlot91();
	virtual void bfmeSlot92();
	virtual void bfmeSlot93();
	virtual void bfmeSlot94();
	virtual void bfmeSlot95();
	virtual void bfmeSlot96();
	virtual void bfmeSlot97();
	virtual void bfmeSlot98();
	virtual bool bfmeSlot99();					///< vtable +0x18C
};

class Object
{
public:
	unsigned char m_bfmeUnreconstructed_000[0x1a4];
	int m_disabledMask;						///< retail this+0x1A4
	unsigned char m_bfmeUnreconstructed_1A8[0x204 - 0x1a8];
	BfmeObjectSub204 *m_bfmeSub204;				///< retail this+0x204, owner unwitnessed
	unsigned char m_bfmeUnreconstructed_208[0x344 - 0x208];
	int m_privateStatus;						///< retail this+0x344
};

class AIUpdateInterface
{
public:
	void rva00273000(Object *obj, UpdateSleepTime *sleep);

	unsigned char m_bfmeUnreconstructed_000[0x1e8];
	TurretAI *m_turretAI[2];					///< retail this+0x1E8
};

void AIUpdateInterface::rva00273000(Object *obj, UpdateSleepTime *sleep)
{
	BfmeObjectSub204 *sub = obj->m_bfmeSub204;
	if (sub != 0 && sub->bfmeSlot99())
		return;
	if (obj->m_privateStatus & 1)
		return;
	if ((obj->m_disabledMask & 0x04) || (obj->m_disabledMask & 0x10))
		return;

	for (int i = 0; i < 2; i++)
	{
		TurretAI *turret = m_turretAI[i];
		if (turret != 0)
		{
			UpdateSleepTime tmp = turret->updateTurretAI();
			if (tmp < *sleep)
				*sleep = tmp;
		}
	}
}
