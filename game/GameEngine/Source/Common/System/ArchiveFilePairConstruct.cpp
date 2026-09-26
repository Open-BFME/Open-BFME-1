// cl: /DNDEBUG /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/archivefilesystem_nosubsystem /Iinputs/reference/shims/asciistring_thin /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// RVA 0x00062900, 79 bytes. The ArchiveFile tree passes its eight-byte pair
// as (destination, source) to STLport's cdecl placement construction helper.
#include "PreRTS.h"
#include "Common/AsciiString.h"
#include <map>

class ArchiveFile;

// The thin string view follows ArchiveFileSystem.cpp. A potentially throwing
// StringBase copy preserves the compiler's placement-delete cleanup envelope.
template <class T> class StringBase
{
    friend class AsciiString;
private:
    StringBase(const StringBase<T> &src);
    void *m_data;
};

inline AsciiString::AsciiString(const AsciiString &src)
{
    ((StringBase<char> *)this)->StringBase<char>::StringBase(
        *(const StringBase<char> *)&src);
}

typedef _STL::pair<const AsciiString, ArchiveFile *> ArchiveFilePair;

template void _STL::_Construct<ArchiveFilePair, ArchiveFilePair>(
    ArchiveFilePair *, const ArchiveFilePair &);
