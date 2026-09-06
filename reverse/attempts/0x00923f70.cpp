// ??0?$ShareBufferClass@VVector4@@@@QAE@HPBDH@Z
// partial score=0.35 date=2026-09-05
// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /Ireference/shims/sweep
#define Matrix4x4 Matrix4
//
// FUZZY-TWIN of ??0?$ShareBufferClass@E@@QAE@HPBDH@Z (0x005F3A70, 131B,
// Code/Libraries/Source/WWVegas/WW3D2/part_buf.cpp): same ShareBufferClass<T>
// three-arg constructor (count, name, alignment), but T is Vector4 (16
// bytes, `shl eax,4` instead of the twin's unsigned-char no-shift) --
// part_buf.cpp itself instantiates ShareBufferClass<Vector4> for
// ParticleBufferClass::Diffuse/TailDiffuse via NEW_REF. Same pattern as
// Code/Libraries/Source/WWVegas/WW3D2/MeshGeometryShareBufferInstantiations.cpp:
// force the COMDAT with a throwaway caller in an isolated TU using the same
// header set and flags part_buf.cpp uses.

#include "part_buf.h"

void rva00923f70ForceEmit(int count)
{
	ShareBufferClass<Vector4> *diffuse =
		new ShareBufferClass<Vector4>(count, "ParticleBufferClass::Diffuse", 0);
	diffuse->Clear();
}
