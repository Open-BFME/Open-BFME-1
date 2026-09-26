// cl: /DNDEBUG /MD /EHsc
// stlport

// DockUpdate::xfer at RVA 0x002CD700. RailedTransportDockUpdate::xfer
// calls this base implementation through ILT 0x0001D043.
// Xfer slot 4 is IsLightCRC (Common/System/xfer.h); slots 10, 24, 30
// and 35 are its version, Coord3D, int and bool transfer operators.
#include <limits.h>
struct Coord3D { float x,y,z; };
enum ObjectID { INVALID_ID=0 };
#include <vector>
// BFME supplies the single-argument resize overload through ILT 0x0002BB34.
namespace _STL {
template<> class vector<Coord3D, allocator<Coord3D> >
    : public _Vector_base<Coord3D, allocator<Coord3D> > {
public:
    unsigned size() const { return _M_finish - _M_start; }
    Coord3D &operator[](unsigned i) { return _M_start[i]; }
    void resize(unsigned);
};
}
struct XferVersionInfo {unsigned char currentVersion,version;};
// Local ABI declarations expose only the slots used by this body.
class Xfer {
public:
    virtual void reserved0();
    virtual void reserved1();
    virtual void reserved2();
    virtual void reserved3();
    virtual bool IsLightCRC()const;
    virtual void reserved5();
    virtual void reserved6();
    virtual void reserved7();
    virtual void reserved8();
    virtual void reserved9();
    virtual void xferVersion(XferVersionInfo*);
    virtual void reserved11();
    virtual void reserved12();
    virtual void reserved13();
    virtual void reserved14();
    virtual void reserved15();
    virtual void reserved16();
    virtual void reserved17();
    virtual void reserved18();
    virtual void reserved19();
    virtual void reserved20();
    virtual void reserved21();
    virtual void reserved22();
    virtual void reserved23();
    virtual void xferCoord3D(Coord3D*);
    virtual void reserved25();
    virtual void reserved26();
    virtual void reserved27();
    virtual void reserved28();
    virtual void reserved29();
    virtual void xferInt(int*);
    virtual void reserved31();
    virtual void reserved32();
    virtual void reserved33();
    virtual void reserved34();
    virtual void xferBool(bool*);
};
void friend_xferObjectID(Xfer*,ObjectID*);
class UpdateModule {
protected:
    virtual void xfer(Xfer*);
    char storage[0x20];
};
class DockUpdate : public UpdateModule {
protected:
    virtual void xfer(Xfer*);
    Coord3D m_enterPosition, m_dockPosition, m_exitPosition;
    int m_numberApproachPositions, m_numberApproachPositionBones;
    bool m_positionsLoaded;
    _STL::vector<Coord3D> m_approachPositions;
    _STL::vector<ObjectID> m_approachPositionOwners;
    _STL::vector<bool> m_approachPositionReached;
    ObjectID m_activeDocker;
    bool m_dockerInside, m_dockCrippled, m_dockOpen;
};
void DockUpdate::xfer(Xfer*xfer)
{

	UpdateModule::xfer(xfer);
	if(xfer->IsLightCRC()) return;
	// Keep the version temporary lifetime inside this transfer. Retail reuses
	// its slot for the vector loop counters and unpacked bit-vector value.
	{
		XferVersionInfo version = {1,1};
		xfer->xferVersion(&version);
	}

	// enter position
	xfer->xferCoord3D( &m_enterPosition );

	// dock position
	xfer->xferCoord3D( &m_dockPosition );

	// exit position
	xfer->xferCoord3D( &m_exitPosition );

	// # approach positions
	xfer->xferInt( &m_numberApproachPositions );

	// positions loaded
	xfer->xferBool( &m_positionsLoaded );

	// approach positions
	int vectorSize = m_approachPositions.size();
	xfer->xferInt( &vectorSize );
	m_approachPositions.resize(vectorSize);
	for( int vectorIndex = 0; vectorIndex < vectorSize; ++vectorIndex )
	{
		// Okay, this is cool.  On save, the size and a bunch of coords will be written.
		// on load, vectorSize will be at 0 from the .size, but will then get set
		// by the xfer, and properly control the number of Coords.
		xfer->xferCoord3D( &m_approachPositions[vectorIndex] );
	}

	// approach position owners
	vectorSize = m_approachPositionOwners.size();
	xfer->xferInt( &vectorSize );
	m_approachPositionOwners.resize(vectorSize);
	for( vectorIndex = 0; vectorIndex < vectorSize; ++vectorIndex )
	{
		friend_xferObjectID(xfer, &m_approachPositionOwners[vectorIndex] );
	}

	// approach positions reached
	vectorSize = m_approachPositionReached.size();
	xfer->xferInt( &vectorSize );
	m_approachPositionReached.resize(vectorSize);
	for( vectorIndex = 0; vectorIndex < vectorSize; ++vectorIndex )
	{
		// Vector of bool gets packed as bitfield internally
		bool unpack = m_approachPositionReached[vectorIndex];
		xfer->xferBool( &unpack );
	}

	// active docker
	friend_xferObjectID(xfer, &m_activeDocker );

	// docker inside
	xfer->xferBool( &m_dockerInside );

	// docker crippled
	xfer->xferBool( &m_dockCrippled );

	// dock open
	xfer->xferBool( &m_dockOpen );

}  
