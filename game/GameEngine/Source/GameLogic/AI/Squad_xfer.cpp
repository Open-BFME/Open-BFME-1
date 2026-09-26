// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/Common/System
// stlport
// Squad::xfer, retail 0x0018BF80 (274 bytes): slot 3 (BFME's Snapshot xfer
// slot) of Squad's vftable 0x01083E78, the only table holding it. Zero Hour
// Squad.cpp's xfer through BFME's Xfer interface: a light CRC skips it, the
// count goes through the unsigned-short overload, and saving is asked of the
// Xfer directly.
#include "xfer.h"
#include <vector>

struct BfmeFormattedText
{
	void *text;
	int tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(
	BfmeFormattedText *result, int tag, const char *format, ...);
__declspec(noreturn) void __stdcall _CxxThrowException(
	void *object, void *throwInfo);
extern int g_rva005c5100ThrowInfo;

struct XferVersion : public Xfer::Version
{
	XferVersion(unsigned char version, unsigned char currentVersion)
	{
		data[0] = version;
		data[1] = currentVersion;
	}
};

enum ObjectID
{
	INVALID_ID = 0
};

void friend_xferObjectID(Xfer *xfer, ObjectID *objectID);

class Object;

typedef _STL::vector<ObjectID> VecObjectID;
typedef VecObjectID::iterator VecObjectIDIt;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Squad.h
class Squad
{
protected:
	virtual void xfer( Xfer *xfer );

private:
	VecObjectID m_objectIDs;						// +0x04
	_STL::vector<Object *> m_objectsCached;			// +0x10
};

// ?xfer@Squad@@MAEXPAVXfer@@@Z
void Squad::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;

	// version
	{
		XferVersion version( 1, 1 );
		*xfer == version;
	}

	// length of object ID list
	unsigned short objectCount = m_objectIDs.size();
	*xfer == objectCount;

	// object id elements
	ObjectID objectID;
	if( xfer->IsStoring() )
	{

		// save each object id
		VecObjectIDIt it;
		for( it = m_objectIDs.begin(); it != m_objectIDs.end(); ++it )
		{

			// save object ID
			objectID = *it;
			friend_xferObjectID( xfer, &objectID );

		}  // end for, it

	}  // end if, save
	else
	{

		// the cached objects list should be empty
		if( m_objectsCached.size() != 0 )
		{
			BfmeFormattedText error;
			bfmeFormatText( &error, 5, 0 );
			_CxxThrowException( &error, &g_rva005c5100ThrowInfo );
		}  // end of

		// read all items
		for( unsigned short i = 0; i < objectCount; ++i )
		{

			// read id
			friend_xferObjectID( xfer, &objectID );

			// put on list
			m_objectIDs.push_back( objectID );

		}  // end for, i

	}  // end else, load

}  // end xfer
