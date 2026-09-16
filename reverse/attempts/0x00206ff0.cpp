// ?xfer@SiegeDockingBehavior@@MAEXPAVXfer@@@Z
// partial score=0.95 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Retail's vtable slot at 0x00CA6360 is SiegeDockingBehavior::xfer.  The
// vector at +0x24 owns 36-byte docking records, and the enabled flag is at
// +0x30.

#define _STLP_USE_STATIC_LIB 1
#define _M_insert_overflow j_0003a292
#include <vector>
#undef _M_insert_overflow

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

struct XferAsciiString {};
struct XferUnicodeString {};
struct XferCoord3DBase {};
struct XferICoord3D {};
struct XferRegion3D {};
struct XferIRegion3D {};
struct XferCoord2D {};
struct XferICoord2D {};
struct XferRegion2D {};
struct XferIRegion2D {};
struct XferRealRange {};
struct XferRGBColor {};
struct XferRGBAColorReal {};
struct XferRGBAColorInt {};
struct XferSnapshot {};
struct XferReservedTag {};

class Xfer
{
public:
	virtual ~Xfer();
	virtual Bool IsLoading();
	virtual Bool IsStoring();
	virtual Bool IsCRC();
	virtual Bool IsLightCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Xfer &operator ==(Bool &value);
	virtual Xfer &operator ==(char &value);
	virtual Xfer &operator ==(UnsignedByte &value);
	virtual Xfer &operator ==(short &value);
	virtual Xfer &operator ==(unsigned short &value);
	virtual Xfer &operator ==(Int &value);
	virtual Xfer &operator ==(UnsignedInt &value);
	virtual Xfer &operator ==(__int64 &value);
	virtual Xfer &operator ==(float &value);
	virtual Xfer &operator ==(XferAsciiString &value);
	virtual Xfer &operator ==(XferUnicodeString &value);
	virtual Xfer &operator ==(Coord3D &value);
	virtual Xfer &operator ==(XferICoord3D &value);
	virtual Xfer &operator ==(XferRegion3D &value);
	virtual Xfer &operator ==(XferIRegion3D &value);
	virtual Xfer &operator ==(XferCoord2D &value);
	virtual Xfer &operator ==(XferICoord2D &value);
	virtual Xfer &operator ==(XferRegion2D &value);
	virtual Xfer &operator ==(XferIRegion2D &value);
	virtual Xfer &operator ==(XferRealRange &value);
	virtual Xfer &operator ==(XferRGBColor &value);
	virtual Xfer &operator ==(XferRGBAColorReal &value);
	virtual Xfer &operator ==(XferRGBAColorInt &value);
	virtual Xfer &operator ==(XferSnapshot &value);
	virtual Xfer &operator ==(XferReservedTag &value);
	virtual Xfer &operator ==(XferVersion &version);
	virtual void slot36();
	virtual Xfer &xferEnum(const char *name, void *value, UnsignedInt size);
};

void friend_xferObjectID(Xfer *xfer, ObjectID *objectID);
void *operator new(unsigned int size);

void bfmeXferSiegeType(Xfer *xfer, void *value);

class UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_base[0x20];
};

struct SiegeDockingEntry
{
	Int m_kind;
	Int m_siegeType;
	Coord3D m_position;
	Coord3D m_direction;
	ObjectID m_objectID;
};

class SiegeDockingBehavior : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	void stopDocking();
	_STL::vector<SiegeDockingEntry *> m_entries;
	Bool m_enabled;
};

// ?xfer@SiegeDockingBehavior@@MAEXPAVXfer@@@Z
void SiegeDockingBehavior::xfer(Xfer *xfer)
{
	{
		XferVersion version;
		version.m_version = 1;
		version.m_currentVersion = 1;
		*xfer == version;
	}
	UpdateModule::xfer(xfer);

	if (xfer->IsStoring())
	{
		UnsignedInt count = m_entries.size();
		*xfer == count;
		for (UnsignedInt index = 0; index < count; ++index)
		{
			bfmeXferSiegeType(xfer, &m_entries[index]->m_siegeType);
			*xfer == m_entries[index]->m_kind;
			*xfer == m_entries[index]->m_position;
			*xfer == m_entries[index]->m_direction;
			friend_xferObjectID(xfer, &m_entries[index]->m_objectID);
		}
	}
	else
	{
		UnsignedInt count = 0;
		*xfer == count;
		register UnsignedInt index = 0;
		register _STL::vector<SiegeDockingEntry *> *entries;
		if (index < count)
		{
			entries = &m_entries;
			this->stopDocking();
			do
			{
				SiegeDockingEntry *entry = (SiegeDockingEntry *)operator new(sizeof(SiegeDockingEntry));
				bfmeXferSiegeType(xfer, &entry->m_siegeType);
				*xfer == entry->m_kind;
				*xfer == entry->m_position;
				*xfer == entry->m_direction;
				friend_xferObjectID(xfer, &entry->m_objectID);
				entries->push_back(entry);
				++index;
			} while (index < count);
		}
	}

	*xfer == m_enabled;
}
