// ?xfer@GameClient@@MAEXPAVXfer@@@Z
// partial score=1.0 date=2026-10-09
// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// stlport
#include "xfer.h"
#include <list>
#include "ascii_string.h"
#include "unicode_string.h"
typedef int Int;
typedef bool Bool;
typedef float Real;
typedef int ObjectID;
typedef unsigned short UnsignedShort;
enum { INVALID_ID = 0, TRUE = 1, FALSE = 0 };
enum DrawableStatus { DRAWABLE_STATUS_NONE = 0 };
class Xfer;
// Snapshot has the BFME destructor, loadPostProcess, name and xfer slots.
class Snapshot
{
public:
    virtual ~Snapshot();
    virtual void loadPostProcess();
    virtual const char *name() const;
    virtual void xfer(Xfer *);
};
class Overridable
{
public:
    const Overridable *getFinalOverride() const
    {
        if (m_nextOverride)
            return m_nextOverride->getFinalOverride();
        return this;
    }

    void *m_vtable;
    Overridable *m_nextOverride;
};
class ThingTemplate : public Overridable {};
class Drawable;
class Object
{
public:
    virtual void objectSlot0();
    virtual void objectSlot1();
    virtual void objectSlot2();
    virtual void objectSlot3();
    virtual void objectSlot4();
    virtual void objectSlot5();
    virtual void objectSlot6();
    virtual void objectSlot7();
    virtual void objectSlot8();
    virtual void objectSlot9();
    virtual Drawable *getDrawable() const;
    int getID() const { return *(const int *)((const char *)this + 0x74); }
};
class Drawable {};
class GameLogic { public: Object *findObjectByID(ObjectID); void bindObjectAndDrawable(Object *, Drawable *); };
extern GameLogic *TheGameLogic;
class ThingFactory;
extern ThingFactory *TheThingFactory;
class Eva;
extern Eva *TheEva;
class SubsystemInterface { public: virtual ~SubsystemInterface(); char *m_name; };
class GameClient : public SubsystemInterface, public Snapshot
{
public:
    virtual void clientSlot1();
    virtual void clientSlot2();
    virtual void clientSlot3();
    virtual void clientSlot4();
    virtual void clientSlot5();
    virtual void clientSlot6();
    virtual void clientSlot7();
    virtual void clientSlot8();
    virtual void clientSlot9();
    virtual void clientSlot10();
    virtual void clientSlot11();
    virtual void clientSlot12();
    virtual void clientSlot13();
    virtual void clientSlot14();
    virtual void clientSlot15();
    virtual void clientSlot16();
    virtual void clientSlot17();
    virtual void clientSlot18();
    virtual void clientSlot19();
    virtual void clientSlot20();
    virtual void clientSlot21();
    virtual void clientSlot22();
    virtual void clientSlot23();
    virtual void destroyDrawable(Drawable *);
    virtual void clientSlot25();
    virtual void clientSlot26();
    virtual void clientSlot27();
    virtual void clientSlot28();
    virtual void clientSlot29();
    virtual void clientSlot30();
    virtual Drawable *getDrawableList();
    struct DrawableTOCEntry { AsciiString name; unsigned short id; };
    typedef std::list<DrawableTOCEntry> DrawableTOCList;
    typedef DrawableTOCList::iterator DrawableTOCListIterator;
    unsigned int m_frame;
    char m_pad10[0xA4];
    unsigned int m_rva00431380Field0B4;
    AsciiString m_rva00431380String0B8;
    bool m_rva00433340Flag0BC;
    bool m_rva00433340Flag0BD;
    char m_padBE[0x32];
    DrawableTOCList m_drawableTOC;
protected:
    virtual void xfer(Xfer *);

private:
    void xferDrawableTOC(Xfer *);
    DrawableTOCEntry *findTOCEntryByName(AsciiString);
    DrawableTOCEntry *findTOCEntryById(unsigned short);
};
extern GameClient *TheGameClient;
enum NameKeyType { NAMEKEY_INVALID = 0, FORCE_NAMEKEYTYPE_LONG = 0x7fffffff };
class StaticNameKey { public: NameKeyType key() const; };
class Dict { public: float getReal(NameKeyType, bool *) const; void setReal(NameKeyType, float); };
class MapObject { public: static Dict TheWorldDict; };
typedef std::list<UnicodeString> BriefingList;
BriefingList *GetBriefingTextList();
// ?findTOCEntryById@GameClient@@AAEPAUDrawableTOCEntry@1@G@Z absent-from-retail
inline GameClient::DrawableTOCEntry *GameClient::findTOCEntryById(unsigned short id)
{
    for (DrawableTOCListIterator it = m_drawableTOC.begin(); it != m_drawableTOC.end(); ++it)
        if ((*it).id == id)
            return &*it;
    return 0;
}
static Bool shouldSaveDrawable(const Drawable *draw)
{
    if ((*(const unsigned char *)((const char *)draw + 0x110) & 0x10) && !*(Object *const *)((const char *)draw + 0xfc))
        return false;
    return true;
}
class RetailXferView { public:
	virtual void slot0();
	virtual bool IsLoading();
	virtual bool IsStoring();
	virtual bool slot3();
	virtual bool IsLightCRC();
	virtual int beginBlock(const char *);
	virtual void endBlock();
	virtual void skipBlock(const char *);
	virtual void slot8();
	virtual void slot9();
	virtual Xfer &Version(unsigned char *);
	virtual void slot11();
	virtual Xfer &Snapshot(Snapshot *);
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
	virtual void slot24();
	virtual Xfer &UnicodeStringValue(UnicodeString *);
	virtual Xfer &AsciiStringValue(AsciiString *);
	virtual Xfer &Real(float *);
	virtual void slot28();
	virtual Xfer &UnsignedInt(unsigned int *);
	virtual Xfer &Int(int *);
	virtual Xfer &UnsignedShort(unsigned short *);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual Xfer &Bool(bool *);
};
void UpdateDiplomacyBriefingText(const UnicodeString &, bool);
void UpdateDiplomacyBriefingText(const AsciiString &, bool);
class RetailGameClientView { public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual bool slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
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
	virtual void slot24();
	virtual void slot25();
	virtual Xfer &AsciiStringValue(AsciiString *);
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual Drawable *getDrawableList();
};
static const ThingTemplate *retailTemplate(const Drawable *draw)
{
	const ThingTemplate *tmpl = *(ThingTemplate *const *)((const char *)draw + 4);
	if (tmpl == 0) return 0;
	return (const ThingTemplate *)tmpl->getFinalOverride();
}
static const AsciiString &retailThingName(const ThingTemplate *tmpl)
{
	return *(const AsciiString *)((const char *)tmpl + 0x20);
}
static const AsciiString &retailTemplateName(const Drawable *draw)
{
	return retailThingName(retailTemplate(draw));
}
class MidVirtualSlot90Receiver;
Xfer &Rva0010C3C0(MidVirtualSlot90Receiver *, void *);
class BfmeThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &); };
class BFMEThingFactory { public: Drawable *newDrawable(const ThingTemplate *, DrawableStatus, int); };
extern StaticNameKey CameraYawAngleKey;
inline UnicodeString::UnicodeString() : m_text(0) {}
inline UnicodeString::UnicodeString(const UnicodeString &o)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
		*(const StringBase<unsigned short> *)&o);
}
inline UnicodeString::~UnicodeString()
{
	((StringBase<unsigned short> *)this)->releaseBuffer();
}
struct BfmeXferException { char *text; int tag; };
extern "C" BfmeXferException *__cdecl bfmeFormatText(BfmeXferException *, int, const char *, ...);
extern "C" int g_xferExceptionThrowInfo;
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *, void *);
// ?xfer@GameClient@@MAEXPAVXfer@@@Z
void GameClient::xfer( Xfer *xfer )
{
	RetailXferView *view = reinterpret_cast<RetailXferView *>(xfer);
	if (xfer->IsLightCRC()) return;

	struct VersionPair00432010 : Xfer::Version
    {
        VersionPair00432010(unsigned char currentVersion)
        {
            data[0] = 1;
            data[1] = currentVersion;
        }
    };
	VersionPair00432010 version(2);
	*xfer == version;

	*xfer == m_frame;

	xferDrawableTOC( xfer );

	Drawable *draw;
	UnsignedShort drawableCount = 0;
	for( draw = reinterpret_cast<RetailGameClientView *>(this)->getDrawableList(); draw; draw = *(Drawable **)((char *)draw + 0x104) )
	{
		if (xfer->IsStoring() && !shouldSaveDrawable(draw))
			continue;
		drawableCount++;
	}
	*xfer == drawableCount;

	DrawableTOCEntry *tocEntry;
	ObjectID objectID;
	if( xfer->IsStoring() )
	{

		for( draw = reinterpret_cast<RetailGameClientView *>(this)->getDrawableList(); draw; draw = *(Drawable **)((char *)draw + 0x104) )
		{
			if (!shouldSaveDrawable(draw))
				continue;

			tocEntry = findTOCEntryByName( retailTemplateName(draw) );
			if( tocEntry == NULL )
			{
				BfmeXferException error;
				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, &g_xferExceptionThrowInfo);
			}

			*xfer == tocEntry->id;

			view->beginBlock("Drawable");

			objectID = *(Object **)((char *)draw + 0xfc) ? (*(Object **)((char *)draw + 0xfc))->getID() : INVALID_ID;
			Rva0010C3C0( (MidVirtualSlot90Receiver *)xfer, &objectID );

			view->Snapshot(draw ? (Snapshot *)((char *)draw + 0x60) : 0);

			view->endBlock();
		}

	}
	else
	{
		UnsignedShort tocID;
		const ThingTemplate *thingTemplate;
		Int dataSize;

		for( UnsignedShort i = 0; i < drawableCount; ++i )
		{

			*xfer == tocID;

			tocEntry = findTOCEntryById( tocID );
			if( tocEntry == NULL )
			{
				BfmeXferException error;
				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, &g_xferExceptionThrowInfo);
			}

			thingTemplate = ((BfmeThingFactory *)TheThingFactory)->findTemplate( tocEntry->name );
			if( thingTemplate == NULL )
			{
				view->skipBlock("Drawable");
				continue;
			}

			dataSize = view->beginBlock("Drawable");
			(void)dataSize;

			Rva0010C3C0( (MidVirtualSlot90Receiver *)xfer, &objectID );

			if( objectID != INVALID_ID )
			{
				Object *object = TheGameLogic->findObjectByID( objectID );

				if( object == NULL )
				{
					BfmeXferException error;
				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, &g_xferExceptionThrowInfo);
				}

				draw = object->getDrawable();
				if( draw == NULL )
				{
					BfmeXferException error;
				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, &g_xferExceptionThrowInfo);
				}

				const ThingTemplate* drawTemplate = retailTemplate(draw);
				if (drawTemplate->getFinalOverride() != thingTemplate->getFinalOverride())
				{
					TheGameClient->destroyDrawable( draw );
					draw = ((BFMEThingFactory *)TheThingFactory)->newDrawable( thingTemplate, DRAWABLE_STATUS_NONE, -1 );
					TheGameLogic->bindObjectAndDrawable(object, draw);
				}
			}
			else
			{

				draw = ((BFMEThingFactory *)TheThingFactory)->newDrawable( thingTemplate, DRAWABLE_STATUS_NONE, -1 );

				if( draw == NULL )
				{
					BfmeXferException error;
				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, &g_xferExceptionThrowInfo);
				}
			}

			view->Snapshot(draw ? (Snapshot *)((char *)draw + 0x60) : 0);

			view->endBlock();
		}

	}

	if (!xfer->IsCRC())
	{
		if( xfer->IsStoring() )
		{
			BriefingList *bList = GetBriefingTextList();
			Int numEntries = bList->size();
			*xfer == numEntries;
			for (BriefingList::const_iterator bIt = bList->begin(); bIt != bList->end(); ++bIt)
			{
				UnicodeString tempStr = *bIt;
				*xfer == tempStr;
			}
		}
		else
		{
			Int numEntries = 0;
			*xfer == numEntries;
			UpdateDiplomacyBriefingText(AsciiString::TheEmptyString, TRUE);
			while (numEntries-- > 0)
			{
				UnicodeString tempStr;
				*xfer == tempStr;
				UpdateDiplomacyBriefingText(tempStr, FALSE);
			}
		}
		if (version.data[1] > 1)
		{
			Bool hasYaw;
			Real yaw = MapObject::TheWorldDict.getReal(CameraYawAngleKey.key(), &hasYaw);
			*xfer == hasYaw;
			*xfer == yaw;
			if (hasYaw && xfer->IsLoading()) {
				NameKeyType yawKey = CameraYawAngleKey.key();
				MapObject::TheWorldDict.setReal(yawKey, yaw);
			}
		}
	}

	Rva0010C3C0((MidVirtualSlot90Receiver *)xfer, &m_rva00431380Field0B4);
	void *evaSnapshot = TheEva ? (char *)TheEva + 8 : 0;
	view->Snapshot((Snapshot *)evaSnapshot);
	*xfer == m_rva00431380String0B8;
	*xfer == m_rva00433340Flag0BC;
	*xfer == m_rva00433340Flag0BD;
}
