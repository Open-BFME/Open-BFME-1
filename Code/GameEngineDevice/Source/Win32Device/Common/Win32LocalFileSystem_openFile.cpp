// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Win32LocalFileSystem::openFile retail 0x009CDD70, 22 bytes.
//
// BFME widened openFile to four parameters and left the two-parameter form as a
// forwarder, so the interesting body is NOT this one -- it is slot 3 at
// 0x009CDF50, 571 bytes. Zero Hour has only the wide form (it is what
// Win32LocalFileSystem.cpp in this tree still carries, allocating a
// Win32LocalFile and creating directories on the WRITE path), and that body
// belongs at slot 3, not here.
//
// The slot numbers are facts rather than inferences: three functions that
// byte-match retail reach this vtable and pin it. FileSystem::openFile calls
// TheLocalFileSystem through [edx+0x08], FileSystem::doesFileExist through
// [eax+0x10], and FileSystem::createDirectory through [eax+0x1c] -- slots 2, 4
// and 7 of 0x01143B98, whose slots 4 and 6 are already claimed as
// Win32LocalFileSystem methods.
//
// Retail pushes the two extra arguments as zero and tail-calls slot 3:
//
//   mov edx,[esp+8]      ; access
//   mov eax,[ecx]        ; vtable
//   push 0
//   push 0
//   push edx             ; access
//   mov edx,[esp+0x10]   ; filename (three pushes down from entry)
//   push edx
//   call [eax+0x0c]      ; slot 3
//
// The two zeros are the added parameters; nothing here says what they mean, so
// they stay unnamed.

class File;
typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/Common/Win32LocalFileSystem.h
class Win32LocalFileSystem
{
public:
	virtual ~Win32LocalFileSystem();										// slot 0
	virtual void init( void );											// slot 1
	// Declared widest-first on purpose. MSVC lays out a run of same-name virtual
	// overloads in reverse declaration order, so this ordering is what puts the
	// two-argument form at slot 2 and the four-argument one at slot 3; the
	// obvious ordering emits call [eax+0x08] here instead of [eax+0x0c].
	virtual File *openFile( const char *filename, Int access, Int a3, Int a4 );	// slot 3, +0x0c
	virtual File *openFile( const char *filename, Int access );					// slot 2, +0x08
};

// ?openFile@Win32LocalFileSystem@@UAEPAVFile@@PBDH@Z
File *Win32LocalFileSystem::openFile( const char *filename, Int access )
{
	return openFile( filename, access, 0, 0 );
}
