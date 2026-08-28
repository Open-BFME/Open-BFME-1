// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?getVertexBuffer@StreakRendererClass@@AAEPAUVertexFormatXYZUV1@@I@Z: Code/Libraries/Source/WWVegas/WW3D2/streakRender.cpp
//
// StreakRendererClass::getVertexBuffer, isolated from the shared streakrender.h
// (that header is included by streakRender.cpp for other already-matched rows;
// this local replica avoids touching it).
//
// The ZH reference (streakRender.cpp) has this identical body, but ZH's header
// comments out TextureTileFactor / LastUsedSyncTime / CurrentUVOffset /
// UVOffsetDeltaPerMS for this class. Retail still writes m_vertexBufferSize and
// m_vertexBuffer at this+0x44 / this+0x48 -- the same slots SegLineRendererClass
// (the sibling class in this file, see seglinerenderer.h) uses for the same
// members -- so in BFME those four members are still live in StreakRendererClass
// too, just as they are in SegLineRendererClass. That places m_vertexBufferSize
// at this+0x44 without needing SegLineRendererClass's extra unknown-identity
// padding member (this class has no such drift).
//
// The multiply-by-element-size the growth path performs (0x14 = 20 bytes) is
// sizeof(VertexFormatXYZUV1) = x,y,z,u1,v1 (5 floats, no diffuse) -- confirming
// this is StreakRendererClass::getVertexBuffer and not the sibling
// SegLineRendererClass::getVertexBuffer (which uses VertexFormatXYZDUV1, 24
// bytes, and is already matched at a different retail address).
//
// For a POD element type with no explicit `operator new[]`/`operator delete[]`
// declaration visible, this MSVC 7.1 build folds `new T[n]` / `delete [] p`
// down to the scalar forms (??2/??3) as a size-cookie-avoidance optimization.
// The real project TUs pull in a header that declares the array forms first
// (as <new> does), so they keep ??_U/??_V; an isolated TU needs the same
// forward declarations to get the array forms retail actually calls.
void *operator new[](unsigned int);
void operator delete[](void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8fvf.h
struct VertexFormatXYZUV1
{
	float x;
	float y;
	float z;
	float u1;
	float v1;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/streakRender.h
class StreakRendererClass
{
private:
	unsigned char m_unreconstructed_00[0x44];		///< retail this+0x00 .. this+0x43
	unsigned int m_vertexBufferSize;					///< retail this+0x44
	VertexFormatXYZUV1 *m_vertexBuffer;				///< retail this+0x48

	VertexFormatXYZUV1 *getVertexBuffer(unsigned int number);
};

// ?getVertexBuffer@StreakRendererClass@@AAEPAUVertexFormatXYZUV1@@I@Z
VertexFormatXYZUV1 *StreakRendererClass::getVertexBuffer(unsigned int number)
{
	// TODO: use a stl vector instead of our own array.
	if (number > m_vertexBufferSize)
	{
		unsigned int numberToAlloc = number + (number >> 1);
		delete [] m_vertexBuffer;
		m_vertexBuffer = new VertexFormatXYZUV1[numberToAlloc];
		m_vertexBufferSize = numberToAlloc;
	}

	return m_vertexBuffer;
}
