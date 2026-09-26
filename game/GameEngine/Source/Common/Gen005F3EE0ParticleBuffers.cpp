// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep

// Gen005F3EE0::Gen005F3EE0, retail 0x005F3EE0, 383 bytes. The one-byte static
// that s4Second (0x005F40C0) constructs once. Its constructor allocates the
// four particle scratch buffers kept in the adjacent globals 0x012F6DC8..D4;
// the first two carry the names the retail literals give them
// ("FXParticleSystem::CategoryModule<CAT_DRAW>::m_posBuffer" / "m_RGBABuffer").
//
// The globals are real externs, not casts of their addresses: a store through
// a constant address lets VC7.1 schedule the null-allocation tail's final
// store ahead of `pop esi`, where retail has it after.

#include "vector3.h"
#include "vector4.h"
#include "sharebuf.h"

// Out of line in retail: 0x005F3BE0 (via ILT 0x00049832) and 0x005F3D60 (via
// ILT 0x000281EB). The float and byte instantiations are inlined here.
template <>
ShareBufferClass<Vector3>::ShareBufferClass(int, const char *, int);

template <>
ShareBufferClass<Vector4>::ShareBufferClass(int, const char *, int);

// Only the byte this body reads; GlobalData's own +0x4f is m_useHalfHeightMap
// (targets/game/reverse/field_names.csv), so +0xDCD keeps its offset name.
class GlobalData
{
public:
	unsigned char m_before0DCD[0xDCD];
	unsigned char m_field0DCD;
};

extern GlobalData *TheWritableGlobalData;

extern ShareBufferClass<Vector3> *g_vector3Buffer;			// 0x012F6DC8
extern ShareBufferClass<Vector4> *g_vector4Buffer;			// 0x012F6DCC
extern ShareBufferClass<float> *g_floatBuffer;				// 0x012F6DD0
extern ShareBufferClass<unsigned char> *g_byteBuffer;		// 0x012F6DD4

class Gen005F3EE0
{
public:
	Gen005F3EE0();
	~Gen005F3EE0();
};

// ??0Gen005F3EE0@@QAE@XZ
Gen005F3EE0::Gen005F3EE0()
{
	int count = 0x200;
	if (TheWritableGlobalData->m_field0DCD != 0)
		count = 0x400;

	g_vector3Buffer = new ShareBufferClass<Vector3>(count,
		"FXParticleSystem::CategoryModule<CAT_DRAW>::m_posBuffer", 0);

	g_vector4Buffer = new ShareBufferClass<Vector4>(count,
		"FXParticleSystem::CategoryModule<CAT_DRAW>::m_RGBABuffer", 0);

	g_floatBuffer = new ShareBufferClass<float>(count, 0);

	g_byteBuffer = new ShareBufferClass<unsigned char>(count, 0);
}
