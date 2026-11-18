// cl: /Iinputs/reference/shims/zhcanonascii /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims /Iinputs/reference/shims/sweep
// stlport
#include "dx8wrapper.h"

//
// BFME's two-argument pixel-shader loader.  The retail body is the target of
// the 0x0001FC99 ILT used by the flat-terrain shader initializers.  The file-system types come from their existing headers. The BFME-specific
// D3D loader retains its two-argument declaration and shifted device slot.
#include "string_base.h"
#include "d3d8_shim_validated.h"

#ifndef NULL
#define NULL 0
#endif

#include "../../../../GameEngine/Include/Common/ScalarTypes.h"


#define HEAP_ZERO_MEMORY 8
extern "C" __declspec(dllimport) void * __stdcall GetProcessHeap(void);
extern "C" __declspec(dllimport) void * __stdcall HeapAlloc(void *, unsigned long, unsigned long);
extern "C" __declspec(dllimport) int __stdcall HeapFree(void *, unsigned long, void *);
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char *);
#define OutputDebugString OutputDebugStringA

#include "ascii_string.h"

#include "Common/file.h"
#include "Common/FileSystem.h"

// Address-scoped dispatch view: retail File's slots differ from Zero Hour's.
// Only +0x08 (close) and +0x0C (read) are used at this call site.
struct Rva00718A10Dispatch
{
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual Int slot0C(void *, Int);
};

extern FileSystem *TheFileSystem;

// The BFME device stores the shader methods at the shifted table offsets
// represented by the validated interface shim.  This global is the retail
// [0x01340534] device pointer.
typedef HRESULT (__stdcall *BfmeCreatePixelShader)(IDirect3DDevice8 *, const DWORD *, DWORD *);

// ?LoadAndCreateD3DShader@BfmeShaderLoader@@SAJPBDPAK@Z
class BfmeShaderLoader
{
public:
	static HRESULT LoadAndCreateD3DShader( const char *filename, DWORD *shader );
};

HRESULT BfmeShaderLoader::LoadAndCreateD3DShader( const char *filename, DWORD *shader )
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
			OutputDebugString( "Failed to allocate memory to load shader\n " );
			return (HRESULT)0x80004005L;
		}

		// BFME File slots are read +0x0C and close +0x08; Zero Hour adds a slot.
		((Rva00718A10Dispatch *)file)->slot0C((void *)shaderData, fileSize);
		((Rva00718A10Dispatch *)file)->slot08();

			IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
			HRESULT result = (*(BfmeCreatePixelShader **)device)[106]( device, shaderData, shader );
		HeapFree( GetProcessHeap(), 0, (void *)shaderData );

		if ( result < 0 )
		{
			OutputDebugString( "Failed to create shader\n " );
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

// Retail 0x00718B70 (ILT 0x00016CB6): the text-source sibling of the loader
// above. It reads the file into a zero-terminated heap buffer, assembles it
// with D3DXAssembleShader (retail 0x00A03887, the D3DX9 seven-argument form)
// and creates the pixel shader through the same device slot, retrying the
// assembly up to ten times while it fails with an error buffer. Its catch
// block is the separately rowed 0x00718D05. Address-derived names; identity
// unproven.
struct ID3DXBuffer
{
	virtual long __stdcall QueryInterface(const void *, void **) = 0;
	virtual unsigned long __stdcall AddRef(void) = 0;
	virtual unsigned long __stdcall Release(void) = 0;
	virtual void * __stdcall GetBufferPointer(void) = 0;
	virtual unsigned long __stdcall GetBufferSize(void) = 0;
};

extern "C" long __stdcall D3DXAssembleShader(const char *, unsigned int, const void *, void *, DWORD,
	ID3DXBuffer **, ID3DXBuffer **);

class Rva00718B70ShaderLoader
{
public:
	static HRESULT LoadAndCreateD3DShader( const char *filename, DWORD *shader );
};

HRESULT Rva00718B70ShaderLoader::LoadAndCreateD3DShader( const char *filename, DWORD *shader )
{
	try
	{
		for ( Int retry = 0; retry < 10; )
		{
			ID3DXBuffer *compiled = NULL;
			ID3DXBuffer *errors = NULL;

			File *file = TheFileSystem->openFile( filename, File::READ | File::BINARY );
			if ( file == NULL )
			{
				OutputDebugString( "Could not find file \n" );
				return (HRESULT)0x80004005L;
			}

			FileInfo fileInfo;
			TheFileSystem->getFileInfo( AsciiString( filename ), &fileInfo );
			DWORD fileSize = fileInfo.sizeLow;

			char *source = (char *)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, fileSize + 8 );
			if ( source == NULL )
			{
				OutputDebugString( "Failed to allocate memory to load shader\n " );
				return (HRESULT)0x80004005L;
			}

			((Rva00718A10Dispatch *)file)->slot0C( source, fileSize );
			source[fileSize] = 0;
			((Rva00718A10Dispatch *)file)->slot08();

			HRESULT hr = D3DXAssembleShader( source, fileSize, NULL, NULL, 0, &compiled, &errors );
			HeapFree( GetProcessHeap(), 0, source );

			if ( hr < 0 )
			{
				if ( compiled != NULL )
				{
					compiled->Release();
					compiled = NULL;
				}
				if ( errors == NULL )
					return (HRESULT)0x80004005L;
				errors->GetBufferPointer();
				errors->Release();
				if ( retry >= 9 )
					return (HRESULT)0x80004005L;
				++retry;
				continue;
			}

			IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
			HRESULT result = (*(BfmeCreatePixelShader **)device)[106]( device,
				(const DWORD *)compiled->GetBufferPointer(), shader );
			if ( compiled != NULL )
			{
				compiled->Release();
				compiled = NULL;
			}

			if ( result < 0 )
			{
				OutputDebugString( "Failed to create shader\n " );
				return (HRESULT)0x80004005L;
			}
			return 0;
		}
	}
	catch ( ... )
	{
		OutputDebugString( "Error opening file \n" );
		return (HRESULT)0x80004005L;
	}

	return 0;
}
