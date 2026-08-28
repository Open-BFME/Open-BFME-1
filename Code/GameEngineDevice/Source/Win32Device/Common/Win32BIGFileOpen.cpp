// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep
// readable body of ?openFile@Win32BIGFile@@UAEPAVFile@@PBDH@Z: Code/GameEngineDevice/Source/Win32Device/Common/Win32BIGFile.cpp
//
// Win32BIGFile::openFile(const Char *, Int) -- the two-argument form.
//
// BFME split Zero Hour's single openFile into two virtuals: this one takes the
// filename and access flags and forwards to a four-argument form with two zeros
// appended. That extra virtual is the whole reason ArchiveFile has nine vtable
// slots where Zero Hour's has eight, and it is why every slot from
// closeAllFiles onward sits one lower than Zero Hour's declaration order.
//
// It cannot live in Win32BIGFile.cpp because the four-argument overload does not
// exist in Zero Hour's Win32BIGFile.h, and the forward has to go through the
// vtable -- retail is call [eax+0xc], slot 3 -- so the class needs the real slot
// numbering to reproduce that displacement. The class below is therefore a
// layout skeleton whose only job is to put the two overloads at slots 2 and 3,
// the same dummy-virtual technique already used for the InGameUI and Radar slot
// pins; the two virtuals ahead of them are the destructor and getFileInfo.
//
// The extra two are an offset bias and a length override -- see the landed body
// in Win32BIGFileOpenArchived.cpp. Passing zeros asks for the whole entry from
// its recorded offset, which is exactly what Zero Hour's single openFile does.
class File;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/Common/Win32BIGFile.h
class Win32BIGFile
{
public:
	virtual ~Win32BIGFile();									// slot 0
	virtual bool getFileInfo( const void *filename, void *fileInfo ) const;	// slot 1
	// Declared four-argument first so that the two land at slots 2 and 3 in that
	// order: MSVC lays overloads of one name into the vtable back to front, and
	// declaring them the readable way round put the four-argument form at slot 2,
	// which showed up as the one wrong byte in an otherwise exact forward
	// (call [eax+8] where retail has call [eax+0xc]).
	virtual File *openFile( const char *filename, int access, int offset, int size );	// slot 3
	virtual File *openFile( const char *filename, int access );		// slot 2
};

// ?openFile@Win32BIGFile@@UAEPAVFile@@PBDH@Z
File *Win32BIGFile::openFile( const char *filename, int access )
{
	return openFile( filename, access, 0, 0 );
}
