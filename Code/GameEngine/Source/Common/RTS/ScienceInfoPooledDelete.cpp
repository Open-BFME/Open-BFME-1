// cl: /DNDEBUG /MD /EHsc
//
// ScienceInfo's placement operator delete, retail 0x007EFFF0 -- the one shared
// 12-byte body every MEMORY_POOL_GLUE class folds onto.  BFME releases through
// the CRT free import at 0x009F6C3A where ZH's macro routes the call to
// ::operator delete.
//
// This cannot be fixed inside Common/RTS/Science.cpp the way FXList.cpp and
// InGameUI.cpp fix theirs: Science.cpp reaches Common/Science.h through
// PreRTS.h -> Common/INI.h, so the class is already defined before any
// TU-scoped macro override in the .cpp could be seen.

extern "C" void free( void *p );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Science.h
class ScienceInfo
{
public:
	enum ScienceInfoMagicEnum { ScienceInfo_GLUE_NOT_IMPLEMENTED = 0 };

	void operator delete( void *p, ScienceInfoMagicEnum e );
};

// ??3ScienceInfo@@SAXPAXW4ScienceInfoMagicEnum@0@@Z
void ScienceInfo::operator delete( void *p, ScienceInfoMagicEnum e )
{
	free( p );
}
