// cl: /DNDEBUG /MD /EHsc
//
// stlport
// Open-BFME5: GameLogic::~GameLogic, retail RVA 0x0038F080, 821 bytes.
// This is the BFME layout, not the shorter ZH GameLogic twin.  The retail
// constructor at 0x003928E0 is the raw 839-byte function (still a dump).  0x003929D0
// is its +0xF0 interior, and the earlier 0x00392B27 reference is also an
// interior instruction (+0x247), not a function entry.  The constructor's
// raw stores at that instruction establish the +0x170, +0x1A0, +0x1AC and
// +0x1B0 tail; the destructor's unwind states and member calls establish the
// earlier fields below.  The second base is the trivial BfmeBaseVUQ family:
// the matched constructor installs secondary vtable 0x010EB560, this body
// restores 0x01073744 at +0x08, and no EH action or call names a
// BfmeBaseVUQ destructor.  This is the same proven inline/no-op base ABI
// documented by Rva000E9A40Destructor.cpp, so the empty virtual declaration
// below models retail behavior and is not a dummy callback/body.  The primary
// SubsystemInterface destructor is the existing retail body at 0x009A1A40.
// Parent verification: Snapshot::~Snapshot at 0x0005C520 is exactly the
// 7-byte store of vtable 0x01073744 followed by ret. The empty C++ base
// destructor emits this real vtable restoration implicitly. The same base
// vtable is restored by the +0x170 member destructor at 0x00364437.
// Matched scalar-deleting GameLogic destructor 0x00390A20 calls this body
// through ILT 0x0001356B; the full target ends with ret at 0x0038F3B4.
//
// Direct callee proof from complete retail boundaries:
//   0x0038E950/126B and 0x0038EA00/126B: STLport int-key hash-map teardown;
//     [this+0x04] and [this+0x0C] are bucket pointers, with 0x80-byte
//     scalar/deallocate dispatch.  Their ILTs are 0x00039590/0x00044102.
//   0x00387480/66B and 0x000CEBD0/66B: STLport int-list-base clear/destroy;
//     sentinel next links are walked and 0x0C-byte nodes are deallocated.
//     Their ILTs are 0x0000CD1F/0x0000E68D.
//   0x000658A0/149B: matched STLport vector<BFMERetailAsciiString> teardown;
//     three pointer fields and each four-byte string releases its buffer.
//     Its ILT is 0x00026AB2.
//   0x003894E0/126B: the third STLport int-key hash-map teardown; ILT
//     0x0003711E.  0x00389AB0/58B is the object-list clear body; its node
//     callback receives node+0x08 and its node size is 0x10.
//   0x00387FB0/45B: three-pointer int-vector base destructor, ILT 0x000392AC.
//     0x00386080/8B adds 0x18 to ecx and tail-jumps to the matched
//     BFMERetailAsciiString::releaseBuffer body at 0x00887940, ILT 0x0002A8E2.
//   0x003643C0/137B is the existing matched Gen_003643C0 destructor, ILT
//     0x0000B5CD.  0x0038D000/112B is the existing matched
//     Gen_0038D000::bfmeClear body, ILT 0x00041641.  The existing matched
//     GameLogic::closeWindows body is 0x00396950/294B, ILT 0x00003486.

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>

// The +0x4C member is the concrete STLport list<int> whose out-of-line base
// destructor is the retail 0x00387480 body.  Keep the vendor instantiation in
// this production TU so its object symbol is available to the address-qualified
// ledger row below without retaining the old generated tgrid owner.
template class _STL::_List_base<int, _STL::allocator<int> >;

extern void __cdecl setFPMode(void);                    // retail 0x008FC4C0

// The 0x0000324C incremental-link thunk resolves to the already matched
// BfmeHostXY::bfmeClearXY body at 0x003871C0.  Keep that real receiver and
// signature here instead of hiding the call behind the generated thunk name.
class BfmeHostXY
{
public:
	void bfmeClearXY(void);
};

extern void __cdecl bfmeFreeScalar(void *block);                     // 0x00881EB0
extern void __cdecl bfmeDeallocate(void *block, unsigned int bytes); // 0x0082E5F0

// Existing matched receiver declarations.  These names are real source-level
// symbols, not alternates for incremental-link thunks.
class BfmeNodeR
{
public:
	int m_head[34];
	BfmeNodeR *m_next;
};

class BfmeVecR
{
public:
	void **m_start;
	void **m_finish;
	void **m_end;
};

class BfmeSingletonR
{
public:
	virtual ~BfmeSingletonR(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0C(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1C(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2C(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3C(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual void slot4C(void);
	virtual void slot50(void);
	virtual void slot54(void);
	virtual void slot58(void);
	virtual void slot5C(void);
	virtual void slot60(void);
	virtual void slot64(void);
	virtual void slot68(void);
	virtual void slot6C(void);
	virtual void bfmeRefresh(void);                 // vtable slot +0x80
};

class Gen_0038D000
{
public:
	void bfmeClear(void);

private:
	int m_head[42];                                  // +0x000
	BfmeNodeR *m_list;                               // +0x0A8
	int m_gap[44];                                   // +0x0AC
	BfmeVecR m_vector;                               // +0x15C
};

// The target's +0x170 member is the same typed class as the already matched
// 0x003643C0 body.  Its raw body calls releaseBuffer on +0x04, a 0x00035D8C
// mid-member on +0x18, and tears down the three-pointer vector at +0x24.
class BfmeTailV
{
public:
	~BfmeTailV(void);

private:
	int m_value;
};

class BfmeMidA
{
public:
	~BfmeMidA(void);

private:
	int *m_start;
	int *m_finish;
	int *m_end;
};

class BfmeVecMemberV
{
public:
	int *m_start;
	int *m_finish;
	int *m_end;
};


class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ(void) { }
};

class Gen_003643C0 : public BfmeBaseVUQ
{
public:
	virtual ~Gen_003643C0(void);

private:
	BfmeTailV m_string;                             // +0x04
	int m_pad[4];                                   // +0x08
	BfmeMidA m_mid;                                 // +0x18
	BfmeVecMemberV m_vector;                        // +0x24
};

// These classes are declaration-only ABI views of the proven vtable calls.
// No callback or deleting-destructor body is invented here.
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface(void);

private:
	int m_name;
};


class BfmeBackground
{
public:
	virtual void slot00(void) = 0;
	virtual void deleteInstance(unsigned int) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0C(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1C(void) = 0;
	virtual void destroyWindows(void) = 0;
};

class TerrainLogic
{
public:
	virtual ~TerrainLogic(void);
};

class GhostObjectManager
{
public:
	virtual ~GhostObjectManager(void);
};

class PartitionManager
{
public:
	virtual ~PartitionManager(void);
};

class BfmeWindowManager
{
public:
	virtual ~BfmeWindowManager(void);
};

class ScriptActionsInterface
{
public:
	virtual ~ScriptActionsInterface(void);
};

class ScriptConditionsInterface
{
public:
	virtual ~ScriptConditionsInterface(void);
};

class BfmeJ1023
{
public:
	virtual ~BfmeJ1023(void);
};

// The manager at this address is independently observed by the 0x006DABB0
// destructor.  Its slot-zero release is the last singleton call in this body.
class Manager012EF4F0
{
public:
	virtual ~Manager012EF4F0(void);
};

extern TerrainLogic *TheTerrainLogic;                         // 0x012EF4CC
extern GhostObjectManager *TheGhostObjectManager;             // 0x012EF4FC
extern PartitionManager *ThePartitionManager;                  // 0x012ED5B8
extern PartitionManager *TheShroudManager;                     // 0x012ED5BC
extern BfmeWindowManager *g_bfmeWindowManager;                 // 0x012ED5C4
extern ScriptActionsInterface *TheScriptActions;               // 0x012F0620
extern ScriptConditionsInterface *TheScriptConditions;         // 0x012F06B0
extern BfmeJ1023 *g_bfmeJ1023;                                 // 0x012F1044
extern Manager012EF4F0 *g_012EF4F0;                            // 0x012EF4F0
extern void *TheBfmeGameLogic;                                 // 0x012F0898

struct RvaHashIntFunctor
{
};

struct RvaHashEqualIntFunctor
{
};

struct RvaHashSelectFirstFunctor
{
};

struct RvaHashBuckets
{
	void **m_start;
	void **m_finish;
	void **m_endOfStorage;
};

class Rva0038E950HashMap
{
public:
	~Rva0038E950HashMap(void);

private:
	RvaHashIntFunctor m_hash;
	RvaHashEqualIntFunctor m_equal;
	RvaHashSelectFirstFunctor m_select;
	RvaHashBuckets m_buckets;                       // +0x04
	unsigned int m_numElements;                    // +0x10
};

class Rva0038EA00HashMap
{
public:
	~Rva0038EA00HashMap(void);

private:
	RvaHashIntFunctor m_hash;
	RvaHashEqualIntFunctor m_equal;
	RvaHashSelectFirstFunctor m_select;
	RvaHashBuckets m_buckets;                       // +0x04
	unsigned int m_numElements;                    // +0x10
	unsigned int m_state34;                         // +0x14
	unsigned int m_state38;                         // +0x18
	unsigned int m_state3C;                         // +0x1C
	unsigned char m_flag40;                         // +0x20
	unsigned char m_pad41[3];                       // +0x21
	unsigned int m_state44;                         // +0x24
	unsigned int m_state48;                         // +0x28
};

struct RvaIntListNode
{
	RvaIntListNode *m_next;
	RvaIntListNode *m_prev;
	int m_value;
};

// Address-qualified ledger identity for the concrete STLport list<int> member
// at GameLogic +0x4C.  Its exact body is the vendor _List_base<int> dtor; the
// alternatename preserves the authentic member-dtor call in GameLogic while
// the vendor instantiation supplies the sole emitted implementation.
class Rva00387480IntList
{
public:
	~Rva00387480IntList(void);

private:
	RvaIntListNode *m_node;
};

#pragma comment(linker, "/alternatename:??1Rva00387480IntList@@QAE@XZ=??1?$_List_base@HV?$allocator@H@_STL@@@_STL@@QAE@XZ")

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString(void)
	{
		releaseBuffer();
	}

private:
	void releaseBuffer(void);                                // 0x00887940
	void *m_data;
};

class Rva000658A0AsciiVector
{
public:
	~Rva000658A0AsciiVector(void);

private:
	BFMERetailAsciiString *m_start;
	BFMERetailAsciiString *m_finish;
	BFMERetailAsciiString *m_endOfStorage;
};

class Rva003894E0HashMap
{
public:
	~Rva003894E0HashMap(void);

private:
	RvaHashIntFunctor m_hash;
	RvaHashEqualIntFunctor m_equal;
	RvaHashSelectFirstFunctor m_select;
	RvaHashBuckets m_buckets;                       // +0x04
	unsigned int m_numElements;                    // +0x10
};

class Rva00387FB0IntVector
{
public:
	~Rva00387FB0IntVector(void);

private:
	int *m_start;
	int *m_finish;
	int *m_end;
};

class Rva00386080AsciiStringElement
{
public:
	~Rva00386080AsciiStringElement(void);

private:
	unsigned int m_prefix[6];                    // +0x00 .. +0x14
	BFMERetailAsciiString m_string;              // +0x18; tail dtor adds 0x18
};

class Rva000CEBD0IntListState
{
public:
	~Rva000CEBD0IntListState(void);

private:
	RvaIntListNode *m_node;                       // +0x00
	unsigned int m_valueCount;                    // +0x04
	unsigned int m_capacity;                     // +0x08
	unsigned int m_limit;                         // +0x0C
	unsigned char m_enabled;                      // +0x10
	unsigned char m_pad11[3];                     // +0x11
	unsigned int m_state14;                       // +0x14
	unsigned char m_flag18;                       // +0x18
	unsigned char m_flag19;                       // +0x19
	unsigned char m_flag1A;                       // +0x1A
	unsigned char m_flag1B;                       // +0x1B
	unsigned int m_reserved[15];                  // +0x1C .. +0x57
};

class Rva00389AB0ObjectList
{
public:
	void clear(void);

	~Rva00389AB0ObjectList(void)
	{
		clear();

		void *node = m_node;
		if (node)
			bfmeDeallocate(node, 0x10);
	}

private:
	void *m_node;
};

class BfmeVectorMember
{
public:
	~BfmeVectorMember(void)
	{
		int *start = m_start;

		if (start)
		{
			unsigned int bytes = sizeof(int) * (m_end - start);

			if (bytes > 0x80)
				bfmeFreeScalar(start);
			else
				bfmeDeallocate(start, bytes);
		}
	}

private:
	int *m_start;
	int *m_finish;
	int *m_end;
};

class GameLogic : public SubsystemInterface, public BfmeBaseVUQ
{
public:
	virtual ~GameLogic(void);
	void closeWindows(void);

private:
	Rva0038E950HashMap m_hash0C;                      // +0x0C
	Rva0038EA00HashMap m_controlBarOverrides;                      // +0x20
	Rva00387480IntList m_list4C;                     // +0x4C
	BFMERetailAsciiString m_string50;                 // +0x50
	Rva000658A0AsciiVector m_vector54;                // +0x54
	BFMERetailAsciiString m_scriptHulkMaxLifetimeOverride;                 // +0x60
	BFMERetailAsciiString m_string64;                 // +0x64
	unsigned char m_pad68[8];                         // +0x68
	BFMERetailAsciiString m_string70;                 // +0x70
	unsigned char m_pad74[4];                         // +0x74
	BFMERetailAsciiString m_string78;                 // +0x78
	BFMERetailAsciiString m_string7C;                 // +0x7C
	BFMERetailAsciiString m_string80;                 // +0x80
	BFMERetailAsciiString m_string84;                 // +0x84
	BFMERetailAsciiString m_string88;                 // +0x88
	unsigned char m_pad8C[0x18];                      // +0x8C
	BfmeBackground *m_background;                     // +0xA4
	unsigned char m_padA8[8];                         // +0xA8
	Rva003894E0HashMap m_listB0;                      // +0xB0
	Rva00387FB0IntVector m_arrayC4[4];               // +0xC4
	BfmeVectorMember m_vectorF4;                      // +0xF4
	unsigned char m_pad100[4];                        // +0x100
	Rva000CEBD0IntListState m_member104;              // +0x104
	BfmeVectorMember m_vector15C;                     // +0x15C
	unsigned char m_pad168[8];                        // +0x168
	Gen_003643C0 m_member170;                          // +0x170
	int m_fpuState;                                   // +0x1A0
	void *m_extra1A4;                                 // +0x1A4
	unsigned char m_flag1A8;                          // +0x1A8
	unsigned char m_pad1A9[3];                        // +0x1A9
	Rva00389AB0ObjectList m_objectTOC;                // +0x1AC
	Rva00386080AsciiStringElement m_playerLeaveStatus[8]; // +0x1B0
};

// Retail layout checks: 4-byte string handles, 12-byte vector triples,
// and the full 0x290-byte GameLogic object including eight 0x1C-byte records.
typedef char GameLogicSize290[(sizeof(GameLogic) == 0x290) ? 1 : -1];
typedef char TailMemberSize30[(sizeof(Gen_003643C0) == 0x30) ? 1 : -1];
typedef char StringElementSize1C[(sizeof(Rva00386080AsciiStringElement) == 0x1C) ? 1 : -1];
typedef char IntVectorSize0C[(sizeof(Rva00387FB0IntVector) == 0x0C) ? 1 : -1];

// ??1GameLogic@@UAE@XZ
GameLogic::~GameLogic(void)
{
	if (m_fpuState == 0)
		setFPMode();
	++m_fpuState;

	m_objectTOC.clear();

	if (m_background)
	{
		m_background->destroyWindows();

		if (m_background)
		{
			m_background->deleteInstance(1);
		}
		m_background = 0;
	}

	reinterpret_cast<Gen_0038D000 *>(this)->bfmeClear();

	if (TheTerrainLogic)
		delete TheTerrainLogic;
	TheTerrainLogic = 0;
	if (TheGhostObjectManager)
		delete TheGhostObjectManager;
	TheGhostObjectManager = 0;
	if (ThePartitionManager)
		delete ThePartitionManager;
	ThePartitionManager = 0;
	if (TheShroudManager)
		delete TheShroudManager;
	TheShroudManager = 0;
	if (g_bfmeWindowManager)
		delete g_bfmeWindowManager;
	g_bfmeWindowManager = 0;
	if (TheScriptActions)
		delete TheScriptActions;
	TheScriptActions = 0;
	if (TheScriptConditions)
		delete TheScriptConditions;
	TheScriptConditions = 0;
	if (g_bfmeJ1023)
		delete g_bfmeJ1023;
	g_bfmeJ1023 = 0;
	if (g_012EF4F0)
		delete g_012EF4F0;
	g_012EF4F0 = 0;

	reinterpret_cast<BfmeHostXY *>(this)->bfmeClearXY();
	closeWindows();
	TheBfmeGameLogic = 0;
}
