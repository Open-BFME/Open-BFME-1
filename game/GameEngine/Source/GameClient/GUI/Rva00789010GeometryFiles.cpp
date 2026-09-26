// cl: /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/scriptenginelayout /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define ASCIISTRING_H
#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "PreRTS.h"
#include "Common/FileSystem.h"
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

// 0x00789010: global filesystem enumerates the owner's geometry files.
// Owner identity is not established; retain its address-qualified name.
class Rva00789010Owner
{
public:
 void enumerateGeometry();
 void rva00788A30(const AsciiString &filename);
 AsciiString m_name;
};
extern FileSystem *Rva0134CB48FileSystem;

void Rva00789010Owner::enumerateGeometry()
{
 FilenameList files;
 AsciiString directory(m_name);
 ((StringBase<char> *)&directory)->concat("_geometry/", 10);
 Rva0134CB48FileSystem->getFileListInDirectory(directory, AsciiString("*.ru"), files, false);
 for (FilenameList::iterator it = files.begin(); it != files.end(); ++it)
  rva00788A30(*it);
}
