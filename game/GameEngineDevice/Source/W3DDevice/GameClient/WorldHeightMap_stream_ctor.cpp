// cl: /DNDEBUG /MD /EHsc
// BFME WorldHeightMap::WorldHeightMap(ChunkInputStream*, bool) at retail
// 0x0074EB10.  The member layout is the witnessed BFME one taken from the
// landed destructor (game/GameEngineDevice/Source/W3DDevice/GameClient/
// WorldHeightMap_dtor.cpp) and the landed default constructor
// WorldHeightMap_ctor_Thunk.cpp: the two 0x200 texture slot arrays are
// in-object at +0x80C0/+0xD0C4 and the source/edge tile arrays begin at
// +0xA4/+0x40A4.  The vtable this ctor installs (0x01121B94) is the same one
// the destructor and the default constructor install, which is the class
// identity; both callers (??loadMapAbi@W3DTerrainLogic@@ and
// ?d_00731190@@) reach it through the retail body itself.
//
// tools/eh_info.py 0x0074EB10 reports 19 unwind states, and the build below
// emits the same 19 funclets with the same this-adjustments (+0x04, +0x14,
// +0x28 ... +0x80B0, +0x80C0, +0xD0C4, +0x120C4, +0x120CC, +0x120D4,
// +0x120DC, then the DataChunkInput local).  That is why the eleven vectors,
// the two texture slot arrays, the four texture refs, the refcount base and the
// DataChunkInput local all carry a declared destructor: the cleanup scopes ARE
// the state numbers 0x0B/0x0C/0x11/0x12 retail writes.

typedef int Int;
typedef bool Bool;

class ChunkInputStream;

// The layout is the one the matched DataChunkInput constructor at 0x001030D0
// writes (game/GameEngine/Source/Common/System/DataChunkInputCtorThunk.cpp):
// 0x28 bytes, which is also the local this constructor's unwind funclet at
// state 18 destroys.
class DataChunkTableOfContents
{
	void *m_list;
	int m_listLength;
	unsigned int m_nextID;
	bool m_headerOpened;
};

class DataChunkInput
{
public:
	DataChunkInput(ChunkInputStream *stream);
	~DataChunkInput(void);

private:
	ChunkInputStream *m_file;
	DataChunkTableOfContents m_contents;
	int m_fileposOfFirstChunk;
	void *m_parserList;
	void *m_chunkStack;
	void *m_currentObject;
	void *m_userData;
};

// The m_end_of_storage member is a nested one-pointer class object, not a raw
// pointer: the landed default constructor WorldHeightMap_ctor_Thunk.cpp spells
// it this way, and it is what places the initial EH state store after the two
// leading pointer stores instead of before them.
template <class T>
class Rva0074EB10AllocProxy
{
public:
	Rva0074EB10AllocProxy(T *p) : m_data(p) {}

	T *m_data;
};

template <class T>
class Rva0074EB10Vector
{
public:
	Rva0074EB10Vector(void) : m_start(0), m_finish(0), m_end_of_storage(0) {}
	~Rva0074EB10Vector(void);

	T *m_start;
	T *m_finish;
	Rva0074EB10AllocProxy<T> m_end_of_storage;
};

class Rva0074EB10TileData;

// The first thing retail calls after installing the vtable and clearing the
// member pointers is 0x0074E8C0 with ecx = this.  That address is the MATCHED
// ?bfmeClearJK@BfmeBigJK@@QAEXXZ (game/GameEngine/Source/Common/BfmeConv2077.cpp),
// so the call is a non-virtual member invoked on this.  The landed default
// constructor WorldHeightMap_ctor_Thunk.cpp reaches the same body through a
// TU-local BfmeBigJK shim and a reinterpret_cast; the shim is empty, so it
// changes no layout and this is not an invented class relationship.
class BfmeBigJK
{
public:
	void bfmeClearJK(void);
};

// Retail's 0x0074ACB0 loader is still a matched ?d_0074acb0@@YAXXZ gen-dump
// with no proven name, so the callee keeps its address token.  The pin
// ?b_0074acb0@@YAXXZ -> 0x0074ACB0 already exists in symbols.csv and
// tools/pin_consistency.py --symbol reports it consistent (extent 1511, owned by
// the matched ?d_0074acb0 row).  tools/eh_info.py plus the call site
// (ecx = this, then the DataChunkInput& and the bool, result unused) give the
// ABI: __thiscall, two stack slots, void.  The recorded verdict on 0x0074ACB0
// reads "caller proof identifies this as a parser-load helper split out of
// ??0WorldHeightMap@@QAE@PAVChunkInputStream@@_N@Z", which is the only support
// for the Load descriptor; no semantic name is claimed.
#pragma comment(linker, "/alternatename:?Rva0074ACB0Load@WorldHeightMap@@AAEXAAVDataChunkInput@@_N@Z=?b_0074acb0@@YAXXZ")

// Declared so the retail element constructor/destructor operands have a name;
// both live behind the matched ILT thunks ?j_00027c55 / ?j_00041b32.
class Rva0074EB10TextureClass
{
public:
	void Release_Ref(void);
};

// The four out-of-line texture slots.  Retail clears each pointer after the two
// array constructions, so this default constructor exists but is not named in
// the member initialiser list.
class Rva0074EB10TextureRef
{
public:
	Rva0074EB10TextureRef(void) : m_ptr(0) {}
	~Rva0074EB10TextureRef(void);

	Rva0074EB10TextureClass *m_ptr;
};

// The two in-object texture slot arrays are constructed by the compiler's
// array-new helper: element size 0x28, count 0x200, element constructor
// ?j_00027c55 and element destructor ?j_00041b32.
class Rva0074EB10TextureSlot
{
public:
	Rva0074EB10TextureSlot(void);
	~Rva0074EB10TextureSlot(void);

private:
	char m_body[0x28];
};

// Non-polymorphic: the refcount is the first member of the base subobject,
// which the polymorphic derived class places at +0x04 behind its vtable.
class Rva0074EB10RefCount
{
public:
	Rva0074EB10RefCount(void) : NumRefs(1) {}
	~Rva0074EB10RefCount(void);

	Int NumRefs;
};

class WorldHeightMap : public Rva0074EB10RefCount
{
public:
	WorldHeightMap(ChunkInputStream *stream, Bool parseSizeOnly);

	virtual void Delete_This(void);

private:
	void Rva0074ACB0Load(DataChunkInput &input, Bool parseSizeOnly);

	Int m_width;
	Int m_height;
	Int m_borderSize;
	Rva0074EB10Vector<Int> m_boundaries;
	Int m_dataSize;
	Int *m_data;
	Rva0074EB10Vector<Int> m_vector28;
	char m_gap34[4];
	Rva0074EB10Vector<Int> m_vector38;
	Rva0074EB10Vector<Int> m_vector44;
	Rva0074EB10Vector<Int> m_vector50;
	Rva0074EB10Vector<Int> m_vector5c;
	Rva0074EB10Vector<Int> m_vector68;
	Rva0074EB10Vector<Int> m_vector74;
	Rva0074EB10Vector<Int> m_vector80;
	Int *m_tileNdxes;
	Int *m_blendTileNdxes;
	Int *m_cliffInfoNdxes;
	Int *m_extraBlendTileNdxes;
	char m_gap9c[8];
	Rva0074EB10TileData *m_sourceTiles[0x1000];
	Rva0074EB10TileData *m_edgeTiles[0x1000];
	Rva0074EB10Vector<int> m_vectorA4;
	Rva0074EB10Vector<int> m_vectorB0;
	char m_gap80bc[4];
	Rva0074EB10TextureSlot m_textureSlotsA[0x200];
	char m_gapD0c0[4];
	Rva0074EB10TextureSlot m_textureSlotsB[0x200];
	Rva0074EB10TextureRef m_texture0;
	Int m_terrainTexHeight;
	Rva0074EB10TextureRef m_texture1;
	Int m_alphaTexHeight;
	Rva0074EB10TextureRef m_texture2;
	Int m_alphaEdgeHeight;
	Rva0074EB10TextureRef m_texture3;
	Int m_drawOriginX;
	Int m_drawOriginY;
};

// ??0WorldHeightMap@@QAE@PAVChunkInputStream@@_N@Z
WorldHeightMap::WorldHeightMap(ChunkInputStream *stream, Bool parseSizeOnly)
	: m_boundaries(), m_vector28(), m_vector38(), m_vector44(), m_vector50(),
		m_vector5c(), m_vector68(), m_vector74(), m_vector80(), m_vectorA4(),
		m_vectorB0()
{
	reinterpret_cast<BfmeBigJK *>(this)->bfmeClearJK();

	DataChunkInput input(stream);
	Rva0074ACB0Load(input, parseSizeOnly);
}
