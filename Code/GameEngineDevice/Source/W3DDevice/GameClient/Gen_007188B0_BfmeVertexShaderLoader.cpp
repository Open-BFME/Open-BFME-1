// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims /Ireference/shims/sweep
//
// BFME's two-argument vertex-shader loader.  The tree-buffer initializer calls
// this helper for Trees.vso through the 0x000078CE ILT.  Its file-system and
// exception shape is the same as the adjacent pixel loader; the BFME device
// exposes the vertex creation entry at the shifted slot 0x16C.
#include "string_base.h"
#include "d3d8_shim_validated.h"

#ifndef NULL
#define NULL 0
#endif

typedef int Int;
typedef bool Bool;

#define HEAP_ZERO_MEMORY 8
extern "C" __declspec(dllimport) void * __stdcall GetProcessHeap(void);
extern "C" __declspec(dllimport) void * __stdcall HeapAlloc(void *, unsigned long, unsigned long);
extern "C" __declspec(dllimport) int __stdcall HeapFree(void *, unsigned long, void *);
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char *);
#define OutputDebugString OutputDebugStringA

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const char *s )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase( s );
	}

	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

private:
	char *m_data;
};

struct FileInfo
{
	Int sizeHigh;
	Int sizeLow;
	Int timestampHigh;
	Int timestampLow;
};

class File
{
public:
	enum { READ = 0x01, BINARY = 0x40 };

	virtual ~File();
	virtual Bool open( const char *filename, Int access );
	virtual void close( void );
	virtual Int read( void *buffer, Int bytes );
};

class FileSystem
{
public:
	File *openFile( const char *filename, Int access );
	Bool getFileInfo( const AsciiString &filename, FileInfo *fileInfo ) const;
};

extern FileSystem *TheFileSystem;

// BFME's device table places the vertex creation entry at 0x16C.
extern IDirect3DDevice8 *g_retailShaderDevice;
typedef HRESULT (__stdcall *BfmeCreateVertexShader)(IDirect3DDevice8 *, const DWORD *, DWORD *);

// ?LoadAndCreateD3DShader@BfmeVertexShaderLoader@@SAJPBDPAK@Z
class BfmeVertexShaderLoader
{
public:
	static HRESULT LoadAndCreateD3DShader( const char *filename, DWORD *shader );
};

HRESULT BfmeVertexShaderLoader::LoadAndCreateD3DShader( const char *filename, DWORD *shader )
{
	try
	{
		File *file = TheFileSystem->openFile( filename, File::READ | File::BINARY );
		if ( file == NULL )
		{
			OutputDebugString( "Could not find file \n" );
			return (HRESULT)0x80004005L;
		}

		FileInfo fileInfo;
		TheFileSystem->getFileInfo( AsciiString( filename ), &fileInfo );
		DWORD fileSize = fileInfo.sizeLow;

		const DWORD *shaderData = (const DWORD *)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, fileSize );
		if ( shaderData == NULL )
		{
			OutputDebugString( "Failed to allocate memory to load shader\n" );
			return (HRESULT)0x80004005L;
		}

		file->read( (void *)shaderData, fileSize );
		file->close();

		IDirect3DDevice8 *device = g_retailShaderDevice;
		HRESULT result = (*(BfmeCreateVertexShader **)device)[91]( device, shaderData, shader );
		HeapFree( GetProcessHeap(), 0, (void *)shaderData );

		if ( result < 0 )
		{
			OutputDebugString( "Failed to create shader\n" );
			return (HRESULT)0x80004005L;
		}
	}
	catch ( ... )
	{
		OutputDebugString( "Error opening file \n" );
		return (HRESULT)0x80004005L;
	}

	return 0;
}
