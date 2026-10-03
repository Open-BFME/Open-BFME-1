// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib /I.
// stlport
// BFME GlobalLanguage::init, 978 bytes at RVA 00439560.
// Identity, paired-string list and File ABI: identity_evidence/00439560-font-init.md.
// The address-qualified view preserves BFME layout without changing ZH headers.
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <windows.h>
#include <string.h>
#include "game/Libraries/Source/WWVegas/WWLib/ascii_string.h"
#define ASCIISTRING_H
#define __INI_H_
#include "game/GameEngine/Include/Common/INI/INI.h"
#include "Common/file.h"
#include "Common/FileSystem.h"
#include <list>
extern "C" __declspec(dllimport) unsigned long __stdcall GetTempPathA(unsigned long,char*);
AsciiString GetRegistryLanguage();
extern const char *g_012B53A8;
// BFME File omits the reference MemoryPoolObject pool-query virtual slot.
// Native File still supplies the independently valid deleteOnClose inline.
class Rva00439560FileView {public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual int sizeAt11();virtual void slot12();virtual char *readEntireAndCloseAt13();};
struct Rva00439560FontEntry {AsciiString sourcePath;AsciiString extractedPath;};
class Rva00439560GlobalLanguage {public: void init();char opaque00[0x134];std::list<Rva00439560FontEntry> localFonts;};
typedef char Rva00439560IniSize[sizeof(INI)==0x848 ? 1 : -1];
typedef char Rva00439560FontEntrySize[sizeof(Rva00439560FontEntry)==8 ? 1 : -1];

// ?init@Rva00439560GlobalLanguage@@QAEXXZ
void Rva00439560GlobalLanguage::init()
{
	INI ini;
	AsciiString fname;
	fname.format("Lang\\%s\\Language.ini",GetRegistryLanguage().str());
	OSVERSIONINFOA osvi;
	osvi.dwOSVersionInfoSize=sizeof(osvi);
	AsciiString tempName;
	tempName.format("Lang\\%s\\Language9x.ini",GetRegistryLanguage().str());
	bool isExist=TheFileSystem->doesFileExist(tempName.str());
	if(GetVersionExA(&osvi)&&osvi.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS&&isExist)fname=tempName;
	ini.loadFile(fname,INI_LOAD_OVERWRITE,0);
	if(localFonts.size())
	{
		HMODULE library=LoadLibraryA("GDI32.DLL");
		if(library)
		{
			typedef int (__stdcall *AddFontProc)(const char*,unsigned long,void*);
			AddFontProc addFont=(AddFontProc)GetProcAddress(library,"AddFontResourceExA");
			char tempPath[MAX_PATH];
			if(GetTempPathA(MAX_PATH,tempPath))
			{
				strcat(tempPath,"\\");
				strcat(tempPath,g_012B53A8);
				CreateDirectoryA(tempPath,0);
				if(addFont)
				{
					for(std::list<Rva00439560FontEntry>::iterator it=localFonts.begin();it!=localFonts.end();++it)
					{
						AsciiString &font=it->sourcePath;
						File *file=TheFileSystem->openFile(font.str(),File::READ);
						if(file)
						{
							file->deleteOnClose();
							int size=((Rva00439560FileView*)file)->sizeAt11();
							char *data=((Rva00439560FileView*)file)->readEntireAndCloseAt13();
							if(data)
							{
								char tempFile[MAX_PATH];
								bool written=false;
								if(GetTempFileNameA(tempPath,"lrf",0,tempFile))
								{
									HANDLE handle=CreateFileA(tempFile,GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
									if(handle!=INVALID_HANDLE_VALUE)
									{
										DWORD bytesWritten;
										if(WriteFile(handle,data,size,&bytesWritten,0))
										{
											written=true;
											CloseHandle(handle);
										}
										else
										{
											CloseHandle(handle);
											DeleteFileA(tempFile);
										}
									}
								}
								delete[] data;
								if(written)
								{
									if(addFont(tempFile,0x30,0))it->extractedPath=tempFile;
									else DeleteFileA(tempFile);
								}
							}
						}
					}
				}
			}
			FreeLibrary(library);
		}
	}
}
