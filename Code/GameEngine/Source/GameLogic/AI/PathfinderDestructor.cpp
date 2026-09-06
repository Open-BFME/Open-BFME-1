// BFME Pathfinder::~Pathfinder, retail RVA 0x003DC040, 229 bytes.
// The reference Pathfinder header has a different member layout. This file
// models the BFME destructor's member offsets without changing that shared
// header.

typedef unsigned int UnsignedInt;

extern void __cdecl f_00881eb0(void *block);
extern void __cdecl bfmeDeallocate(void *block, UnsignedInt bytes);
class AsciiString
{
public:
	~AsciiString();

private:
    char m_bfmeSize[4];
};

class PathfindLayer
{
public:
	~PathfindLayer();

private:
	char m_bfmeSize[0x44];
};

class BfmePathfindZoneManager
{
public:
    ~BfmePathfindZoneManager();

private:
	char m_bfmeSize[0x23860];
};

class BfmePathfinderDtorObject
{
public:
    ~BfmePathfinderDtorObject();

private:
	char m_bfmeSize[0x0C];
};

struct BfmeVectorElement
{
	char m_bfmeSize[0x0C];
};

class BfmeVector
{
public:
    ~BfmeVector()
    {
        BfmeVectorElement *start = m_start;
        if (start != 0)
        {
            UnsignedInt bytes = (UnsignedInt)((m_end - start) * sizeof(BfmeVectorElement));
            if (bytes > 0x80)
                f_00881eb0(start);
            else
                bfmeDeallocate(start, bytes);
        }
    }

    BfmeVectorElement *m_start;
	BfmeVectorElement *m_finish;
    BfmeVectorElement *m_end;
};

class PathfinderBaseFirst
{
public:
    virtual void pathfinderBaseSlot() {}
};

class PathfinderBaseSecond
{
public:
    virtual ~PathfinderBaseSecond() {}
};

class Pathfinder : public PathfinderBaseFirst, public PathfinderBaseSecond
{
public:
    ~Pathfinder();

    char m_bfmeGap[0x85C - 0x08];
	PathfindLayer m_layers[16];
    BfmePathfindZoneManager m_zoneManager;
    AsciiString m_strings[64];
	char m_bfmeGapAfterStrings[0x104];
    BfmePathfinderDtorObject m_dtorObject;
	BfmeVector m_vector;
};

Pathfinder::~Pathfinder()
{
}
