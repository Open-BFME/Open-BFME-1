// cl: /DNDEBUG /MD /EHsc
//
// ProductionUpdate::xfer, retail RVA 0x0029DB60.
//
// The neutral ProductionEntry layout view is not the Zero Hour header layout:
// retail stores both template pointers, serializes two real-valued fields, and
// keeps the list links at +0x3c/+0x40.  The separate constructor at 0x0029BCC0
// installs the one-slot table 0x010C0D90; slot 0 is ILT 0x00031651 to the
// scalar deleting destructor body at 0x0029C290.  The ProductionUpdate
// destructor at 0x0029D460 drains entries through that effective destructor.
// This TU uses an explicit layout view and emits no ProductionEntry table.

#include "../../../Common/System/xfer.h"

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

struct XferVersionView : Xfer::Version
{
	XferVersionView(UnsignedByte first, UnsignedByte current)
	{
		data[0] = first;
		data[1] = current;
	}
};

class __declspec(novtable) UpdateModule
{
protected:
	// ProductionUpdate::xfer is primary-table slot 3 (+0x0c); the first
	// three declarations are neutral anchors for the inherited slots.
	virtual void updateModuleSlot0();
	virtual void updateModuleSlot1();
	virtual void updateModuleSlot2();
	virtual void xfer(Xfer *xfer);

	UnsignedByte m_base[0x1C];
};

class __declspec(novtable) ProductionUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);
};

class AsciiString;

template <typename T>
class StringBase
{
private:
	friend class AsciiString;
	StringBase() : m_data(0) { }
	void set(const StringBase<T> &source);
	void releaseBuffer();
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() { }
	AsciiString &operator=(const AsciiString &that)
	{
		set(that);
		return *this;
	}
	~AsciiString()
	{
		releaseBuffer();
	}
};

class ThingTemplate
{
public:
	const AsciiString &getName() const
	{
		return *(const AsciiString *)((const UnsignedByte *)this + 0x20);
	}
};

class UpgradeTemplate
{
public:
	const AsciiString &getUpgradeName() const
	{
		return *(const AsciiString *)((const UnsignedByte *)this + 8);
	}
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

#define TheThingFactory (*(BfmeThingFactory **)0x012EF1D8)
#define TheUpgradeCenter (*(UpgradeCenter **)0x012EF188)

extern void j_00028560();
extern void j_00026dd7();

static __forceinline const ThingTemplate *bfmeFindTemplate(
	BfmeThingFactory *factory, const AsciiString &name)
{
	typedef const ThingTemplate *(BfmeThingFactory::*FindTemplateCall)(
		const AsciiString &);
	union { void (*raw)(void); FindTemplateCall member; } call;
	call.raw = j_00028560;
	return (factory->*call.member)(name);
}

static __forceinline const UpgradeTemplate *bfmeFindUpgrade(
	UpgradeCenter *center, const AsciiString &name)
{
	return center->findUpgrade(name);
}

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);
extern "C" int g_guardTargetTypeThrowInfo;
extern void *__cdecl operator new(unsigned int size);

class BfmeSeedTarget;
extern void __cdecl bfmeHandOver_0000C9B4(BfmeSeedTarget *target, void *item);

struct ProductionEntryLayout
{
	void *m_vptr;
	int m_type;
	const ThingTemplate *m_objectToProduce;
	const UpgradeTemplate *m_upgradeToResearch;
	unsigned int m_productionID;
	float m_percentComplete;
	float m_unknown18;
	int m_quantityTotal;
	int m_quantityProduced;
	int m_exitDoor;
	int m_unknown28;
	int m_unknown2c;
	int m_unknown30;
	bool m_unknown34;
	UnsignedByte m_padding35[3];
	int m_unknown38;
	ProductionEntryLayout *m_next;
	ProductionEntryLayout *m_prev;
	int m_unknown44;

	__forceinline ProductionEntryLayout()
	{
		initialize();
	}

	__forceinline void initialize()
	{
		m_vptr = (void *)0x010C0D90;
		m_type = 0;
		m_objectToProduce = 0;
		m_upgradeToResearch = 0;
		m_productionID = 1;
		m_percentComplete = 0;
		m_unknown18 = 0;
		m_quantityTotal = 0;
		m_quantityProduced = 0;
		m_exitDoor = 0;
		m_unknown28 = 0;
		m_unknown2c = 0;
		m_unknown30 = 0;
		m_unknown34 = false;
		m_unknown38 = 0;
		m_next = 0;
		m_prev = 0;
		m_unknown44 = 0;
	}
};

struct BfmeDoorInfo
{
	UnsignedInt m_openedFrame;
	UnsignedInt m_waitOpenFrame;
	UnsignedInt m_closedFrame;
	bool m_holdOpen;
	UnsignedByte m_padding[3];
};

struct BfmeModelConditionFlags
{
	UnsignedInt m_bits[10];
};

struct BfmeProductionUpdateLayout
{
	UnsignedByte m_prefix[0x28];
	ProductionEntryLayout *m_productionQueue;
	ProductionEntryLayout *m_productionQueueTail;
	UnsignedInt m_productionCount;
	UnsignedInt m_uniqueID;
	UnsignedInt m_constructionCompleteFrame;
	BfmeDoorInfo m_doors[4];
	BfmeModelConditionFlags m_clearFlags;
	BfmeModelConditionFlags m_setFlags;
	bool m_flagsDirty;
	UnsignedByte m_paddingCD[3];
	UnsignedInt m_unknownD0;
	bool m_unknownD4;
	UnsignedByte m_paddingD5[3];
	UnsignedInt m_objectID;
	UnsignedByte m_paddingDC[4];
	UnsignedInt m_unknownE0;
	UnsignedByte m_audioEvent[4];
};

static __forceinline void bfmeXferFlags(BfmeModelConditionFlags *flags,
	Xfer *xfer)
{
	typedef void (BfmeModelConditionFlags::*FlagsXferCall)(Xfer *);
	union { void (*raw)(void); FlagsXferCall member; } call;
	call.raw = j_00026dd7;
	(flags->*call.member)(xfer);
}

class __single_inheritance AudioManager;
#define TheAudio (*(AudioManager **)0x012ED668)

#define PRODUCTION_UPDATE_XFER_ERROR() \
	do { \
		XferException error; \
		bfmeFormatText(&error, 5, 0); \
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo); \
	} while (0)

// ?xfer@ProductionUpdate@@MAEXPAVXfer@@@Z
void ProductionUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;

	XferVersionView version(1, 3);
	*xfer == version;

	BfmeProductionUpdateLayout *update =
		reinterpret_cast<BfmeProductionUpdateLayout *>(this);
	ProductionEntryLayout *production;
	UnsignedShort productionCount = 0;
	for (production = update->m_productionQueue; production;
		production = production->m_next)
		++productionCount;
	*xfer == productionCount;

	if (xfer->IsStoring())
		{
			AsciiString name;
			for (production = update->m_productionQueue; production;
				production = production->m_next)
			{
				xfer->XferRawBytes(&production->m_type, 4);
				switch (production->m_type)
				{
				case 1:
				case 3:
					name = *(const AsciiString *)((const UnsignedByte *)
						production->m_objectToProduce + 0x20);
					break;
				case 2:
					name = *(const AsciiString *)((const UnsignedByte *)
						production->m_upgradeToResearch + 8);
					break;
				default:
					PRODUCTION_UPDATE_XFER_ERROR();
				}
			*xfer == name;
			xfer->XferRawBytes(&production->m_productionID, 4);
			*xfer == production->m_percentComplete;
			*xfer == production->m_unknown18;
			*xfer == production->m_quantityTotal;
			*xfer == production->m_quantityProduced;
			*xfer == production->m_exitDoor;
			*xfer == production->m_unknown28;
			*xfer == production->m_unknown34;
			xfer->XferRawBytes(&production->m_unknown2c, 4);
			int value = production->m_unknown30;
			*xfer == value;
		}
	}
	else
	{
		AsciiString name;
		if (update->m_productionQueue != 0)
			PRODUCTION_UPDATE_XFER_ERROR();

		for (UnsignedShort i = 0; i < productionCount; ++i)
		{
			production = new ProductionEntryLayout;

			if (update->m_productionQueue == 0)
				update->m_productionQueue = production;
			if (update->m_productionQueueTail != 0)
			{
				update->m_productionQueueTail->m_next = production;
				production->m_prev = update->m_productionQueueTail;
			}
			UnsignedInt *type = (UnsignedInt *)&production->m_type;
			update->m_productionQueueTail = production;

			xfer->XferRawBytes(type, 4);
			*xfer == name;
			switch (*type)
			{
			case 1:
			case 3:
				production->m_objectToProduce = bfmeFindTemplate(
					TheThingFactory, name);
				break;
			case 2:
				production->m_upgradeToResearch = bfmeFindUpgrade(
					TheUpgradeCenter, name);
				break;
			default:
				break;
			}

			xfer->XferRawBytes(&production->m_productionID, 4);
			*xfer == production->m_percentComplete;
			*xfer == production->m_unknown18;
			*xfer == production->m_quantityTotal;
			*xfer == production->m_quantityProduced;
			*xfer == production->m_exitDoor;
			*xfer == production->m_unknown28;
			*xfer == production->m_unknown34;
			xfer->XferRawBytes(&production->m_unknown2c, 4);
			int value;
			*xfer == value;
			production->m_unknown30 = value;
		}
	}

	xfer->XferRawBytes(&update->m_productionCount, 4);
	*xfer == update->m_uniqueID;
	*xfer == update->m_constructionCompleteFrame;
	UnsignedInt reserved = 0;
	*xfer == reserved;
	bfmeHandOver_0000C9B4((BfmeSeedTarget *)xfer, &update->m_objectID);
	*xfer == update->m_unknownD0;
	*xfer == update->m_unknownD4;

	for (UnsignedInt i = 0; i < 4; ++i)
	{
		*xfer == update->m_doors[i].m_openedFrame;
		*xfer == update->m_doors[i].m_waitOpenFrame;
		*xfer == update->m_doors[i].m_closedFrame;
		*xfer == update->m_doors[i].m_holdOpen;
	}

	bfmeXferFlags(&update->m_clearFlags, xfer);
	bfmeXferFlags(&update->m_setFlags, xfer);
	*xfer == update->m_flagsDirty;
	if (version.data[1] >= 2)
		*xfer == update->m_unknownE0;
	if (version.data[1] >= 3)
	{
		AudioManager *audio = TheAudio;
		if (audio == 0)
			return;
		typedef void (AudioManager::*AudioXferCall)(Xfer *, void *);
		(audio->**(AudioXferCall *)(*(char **)audio + 0x148))(
			xfer, (void *)((UnsignedByte *)this + 0xE4));
	}
}
