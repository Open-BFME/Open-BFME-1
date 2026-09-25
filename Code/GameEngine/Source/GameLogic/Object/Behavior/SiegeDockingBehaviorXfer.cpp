// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// SiegeDockingBehavior::xfer, retail 0x00206FF0.
//
// Identity: the vtable 0x010A6354 that SiegeDockingBehavior's constructor
// (0x002062C0) and destructor (0x002067C0) install holds ILT 0x00023330 ->
// 0x00206FF0 in slot 3, and the body is the xfer shape: a {1,1} version block,
// the UpdateModule::xfer base call (ILT 0x000044C1, the same one BridgeBehavior
// ::xfer calls), then the fields.
//
// The vector at +0x24 is the one stopDocking (0x00206710) deletes and clears.
// Its 36-byte records are only witnessed here, so their fields carry offsets.
//
// The load loop calls stopDocking at the top of EVERY iteration: retail's
// back edge (+0x16B) jumps to +0xE4, the mov ecx,ebp / call stopDocking pair,
// and only lea ebx,[ebp+0x24] is hoisted above it.  Calling it once before the
// loop is what left MSVC's eb 03 8d 49 00 alignment pad in every earlier bank.

#include <vector>

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

// Same operator== slot table the landed LivingWorldPlayerArmyXfer.cpp uses;
// MSVC lays the overloads out in reverse, so XferVersion is slot 10 (+0x28)
// and Bool slot 35 (+0x8C).
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
};

// ILT 0x0000C9B4 -> 0x0010C3C0, the ObjectID helper BridgeBehavior::xfer calls.
void friend_xferObjectID(Xfer *xfer, ObjectID *objectID);
// ILT 0x00012508 -> 0x0010C440, the enum forwarder onto Xfer slot 0x90.
void bfmeXferSiegeType(Xfer *xfer, void *value);

class UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_unmodelled04[0x20];
};

struct SiegeDockEntry00206FF0
{
	Int m_int00;
	Int m_enum04;
	Coord3D m_coord08;
	Coord3D m_coord14;
	ObjectID m_objectID20;
};

class SiegeDockingBehavior : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	void stopDocking();

	_STL::vector<SiegeDockEntry00206FF0 *> m_entries;	// +0x24
	Bool m_bool30;
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
			bfmeXferSiegeType(xfer, &m_entries[index]->m_enum04);
			*xfer == m_entries[index]->m_int00;
			*xfer == m_entries[index]->m_coord08;
			*xfer == m_entries[index]->m_coord14;
			friend_xferObjectID(xfer, &m_entries[index]->m_objectID20);
		}
	}
	else
	{
		UnsignedInt count = 0;
		*xfer == count;
		for (UnsignedInt index = 0; index < count; ++index)
		{
			stopDocking();
			SiegeDockEntry00206FF0 *entry = new SiegeDockEntry00206FF0;
			bfmeXferSiegeType(xfer, &entry->m_enum04);
			*xfer == entry->m_int00;
			*xfer == entry->m_coord08;
			*xfer == entry->m_coord14;
			friend_xferObjectID(xfer, &entry->m_objectID20);
			m_entries.push_back(entry);
		}
	}

	*xfer == m_bool30;
}
