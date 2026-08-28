// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: isolated thunk for GeometryInfo::parseGeometryIsSmall.
//
// The shared Code/GameEngine/Include/Common/INI/ini.h declares
// `static int scanBool(const char* token);`, but retail's scanBool is
// `?scanBool@INI@@SA_NPBD@Z` -- it returns bool, not int (already matched
// at 0x00852550 with that exact bool-returning mangled name). Compiling
// against the shared header's int-returning declaration forces MSVC to
// normalize the return value (test/setne) before storing it, which is not
// what retail does here (a bare `mov [ecx+4],al`). Rather than touch the
// shared header -- other TUs compile against it -- this file carries its
// own minimal local replica of the two INI members it needs, declared with
// retail's real signatures.
//
// Likewise, GeometryInfo here is a local replica: the shared geometry.h
// derives GeometryInfo from Snapshot (giving it a vtable pointer), but
// retail's GeometryInfo has no vptr -- Geometry.cpp's already-matched
// isIntersectedByLineSegment reads m_boundingSphereRadius at this+0x14,
// consistent with a plain (non-polymorphic) field layout starting at +0.
// m_isSmall is that layout's second field, at +0x4. We don't need the
// full field layout here, just that one offset and a private
// calcBoundingStuff() to tail-call into (already matched at 0x0087EE60).

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char* getNextToken(const char* seps = 0);
	static bool scanBool(const char* token);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Geometry.h
class GeometryInfo
{
public:
	static void parseGeometryIsSmall(INI* ini, void* instance, void* store, const void* userData);

private:
	void calcBoundingStuff();
};

/*static*/ void GeometryInfo::parseGeometryIsSmall(INI* ini, void* /*instance*/, void* store, const void* /*userData*/)
{
	*(bool*)((char*)store + 0x4) = INI::scanBool(ini->getNextToken());
	((GeometryInfo*)store)->calcBoundingStuff();
}
