// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Rva000D74B0Map::xfer, retail 0x000D74B0 (269 bytes).  The target is the
// fourth virtual slot of the sibling map installed with vtable 0x01083E94;
// its constructor/destructor twins at 0x000DA590/0x000D3FA0 establish the
// embedded hash-map layout, but no semantic class name is proven.

#include <hash_map>

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

struct Rva000D74B0XferVersion
{
	Rva000D74B0XferVersion(UnsignedByte version) :
		m_version(version), m_currentVersion(version)
	{
	}

	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Snapshot;

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual Bool isSaving();
	virtual void slot03();
	virtual Bool isDoingCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(Rva000D74B0XferVersion *);
	virtual void slot11();
	virtual void xferSnapshot(Snapshot *);
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
	virtual void xferAsciiString(void *);
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void xferDword(int *);
	virtual void xferUnsignedShort(UnsignedShort *);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(Bool *);
};

class MidVirtualSlot90Receiver;
extern void Rva0010BE40(MidVirtualSlot90Receiver *, void *);

class Rva000D74B0PoolObject
{
public:
	virtual ~Rva000D74B0PoolObject() {}

protected:
	virtual void crc(Xfer *);
	virtual void xfer(Xfer *);
	virtual void loadPostProcess();
};

// Integer keys and one-dword values are witnessed. void* is the existing
// generic STL ABI representation, not a semantic claim about the stored value.
typedef int Rva000D74B0Key;
typedef _STL::pair<const Rva000D74B0Key, void *> Rva000D74B0MapPair;
typedef _STL::hash_map<Rva000D74B0Key, void *, _STL::hash<Rva000D74B0Key>,
	_STL::equal_to<Rva000D74B0Key>, _STL::allocator<Rva000D74B0MapPair> >
	Rva000D74B0MapType;

class Rva000D74B0Map : public Rva000D74B0PoolObject
{
public:
	virtual ~Rva000D74B0Map();

protected:
	virtual void crc(Xfer *);
	virtual void xfer(Xfer *);
	virtual void loadPostProcess();

private:
	Rva000D74B0MapType m_map;
};

// ?xfer@Rva000D74B0Map@@MAEXPAVXfer@@@Z
void Rva000D74B0Map::xfer(Xfer *xfer)
{
	if (xfer->isDoingCRC())
		return;

	Rva000D74B0XferVersion version(1);
	xfer->xferVersion(&version);

	Rva000D74B0MapType::iterator relationIt;
	UnsignedShort relationCount = m_map.size();
	xfer->xferUnsignedShort(&relationCount);

	Rva000D74B0Key key;
	void *relationship;
	if (xfer->isSaving())
	{
		for (relationIt = m_map.begin(); relationIt != m_map.end(); ++relationIt)
		{
			key = (*relationIt).first;
			xfer->xferDword(&key);
			relationship = (*relationIt).second;
			Rva0010BE40((MidVirtualSlot90Receiver *)xfer, &relationship);
		}
	}
	else
	{
		for (UnsignedShort i = 0; i < relationCount; ++i)
		{
			xfer->xferDword(&key);
			Rva0010BE40((MidVirtualSlot90Receiver *)xfer, &relationship);
			m_map[key] = relationship;
		}
	}
}
