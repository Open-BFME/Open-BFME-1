// ?update@BannerCarrierUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.92 date=2026-09-12
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB

typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class BFMESelectionStatusBits
{
public:
	Bool test(UnsignedInt bit) const;
};

class BfmeHordeMember
{
public:
	Bool bfmeBlocksFormationRefresh();

	unsigned char m_pad_000[0x31e];
	unsigned char m_flag31E;
};

class BfmeHordeOwnerInterface
{
public:
	Bool bfmeBlocksFormationRefresh();
};

class Object;

class BannerCarrierUpdateCallbackTail
{
public:
	void **m_vtable;
};

class BannerCarrierUpdateCallback
{
public:
	void **m_vtable;
};

typedef BannerCarrierUpdateCallbackTail *(__fastcall *BannerCarrierGetTail)(
	BannerCarrierUpdateCallback *self);
typedef Bool (__fastcall *BannerCarrierNotify)(
	BannerCarrierUpdateCallbackTail *self, void *vtable, void *outParam,
	Int radius);

inline BannerCarrierUpdateCallbackTail *getBannerCarrierTail(
	BannerCarrierUpdateCallback *self)
{
	return ((BannerCarrierGetTail)self->m_vtable[0x68 / 4])(self);
}

inline Bool notifyBannerCarrier(BannerCarrierUpdateCallbackTail *self,
	void *outParam, Int radius)
{
	return ((BannerCarrierNotify)self->m_vtable[0x8c / 4])(
		self, self->m_vtable, outParam, radius);
}

class BfmeHordeOwner;

class Object : public BFMESelectionStatusBits
{
public:
	Object *bfmeResolveMeleeTarget(Int flags);

	unsigned char m_pad_000[0x94];
	UnsignedInt m_status94;
	unsigned char m_pad_098[0x118 - 0x98];
	UnsignedInt m_status118;
	unsigned char m_pad_11C[0x1f8 - 0x11c];
	BfmeHordeOwnerInterface *m_field1F8;
	BannerCarrierUpdateCallback *m_field1FC;
	unsigned char m_pad_200[0x204 - 0x200];
	BfmeHordeMember *m_field204;
	unsigned char m_pad_208[0x214 - 0x208];
	BfmeHordeOwner *m_field214;
};

class GameLogic
{
public:
	unsigned char m_pad_000[0x3c];
	UnsignedInt m_frame;
};

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)

class BfmeHordeOwner : public Object
{
public:
	UnsignedInt bfmeGetFormationRefreshValue();
};

class BannerCarrierUpdateModuleData
{
	void *m_vtable;
	UnsignedInt m_field4;

public:
	UpdateSleepTime m_field8;
	UnsignedInt m_field0C;
	unsigned char m_pad_010[0x38 - 0x10];
	unsigned char m_field38;
};

class Rva00285300Base
{
public:
	void j0003767d();
	void j000454d0(Object *object);
};

class BannerCarrierUpdate
{
public:
	virtual UpdateSleepTime update();
};

// ?update@BannerCarrierUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime BannerCarrierUpdate::update()
{
	register const BannerCarrierUpdateModuleData *const moduleData =
		*(BannerCarrierUpdateModuleData **)((char *)this - 0xc);
	register Object *const object = *(Object **)((char *)this - 8);
	BfmeHordeMember *hordeMember;

	if (!object)
		return moduleData->m_field8;

	if (object->m_status118 & 0x10)
		return moduleData->m_field8;

	if (object->m_status94 & 0x20000000)
		return moduleData->m_field8;

	hordeMember = object->m_field204;
	if (hordeMember)
	{
		if (hordeMember->bfmeBlocksFormationRefresh())
			return moduleData->m_field8;
		if (hordeMember->m_flag31E)
			return moduleData->m_field8;
	}

	Object *meleeTarget = object->bfmeResolveMeleeTarget(0);
	BfmeHordeOwnerInterface *owner = meleeTarget ? meleeTarget->m_field1F8 : object->m_field1F8;
	if (owner)
	{
		if (owner->bfmeBlocksFormationRefresh())
			return moduleData->m_field8;
	}

	if (moduleData->m_field38)
	{
		((Rva00285300Base *)((char *)this - 0x10))->j0003767d();
		return moduleData->m_field8;
	}

	if (object->test(0x25))
		return moduleData->m_field8;
	if (object->test(0x3c))
		return moduleData->m_field8;

	if (object->m_field214)
	{
		UnsignedInt frame = TheBfmeGameLogic->m_frame;
		UnsignedInt refreshValue = object->m_field214->bfmeGetFormationRefreshValue();
		if (refreshValue > frame - moduleData->m_field0C)
			return moduleData->m_field8;
	}

	int localOut = object->m_field214 == 0 ? 0 : 0;
	if (object->m_field214)
	{
		Object *melee1 = object->m_field214->bfmeResolveMeleeTarget(0);
		if (melee1)
		{
			Object *melee2 = object->m_field214->bfmeResolveMeleeTarget(0);
			BannerCarrierUpdateCallbackTail *tail = getBannerCarrierTail(
				melee2->m_field1FC);
			if (notifyBannerCarrier(tail, &localOut, moduleData->m_field0C))
				return moduleData->m_field8;
		}
	}

	((Rva00285300Base *)((char *)this - 0x10))->j000454d0(object);
	return moduleData->m_field8;
}
