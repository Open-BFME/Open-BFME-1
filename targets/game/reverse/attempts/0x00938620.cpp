// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep
// partial score=0.896 date=2026-09-27
// Address-derived body: retail RVA 0x00938620, 1057 bytes.
//
// W3DDisplay::init (0x006ED5B0) is the only caller, and it copy-constructs TWO
// by-value AsciiStrings (GlobalData+0xDC4 and +0xDC0) into the outgoing
// argument slots with the StringBase<char> copy constructor at 0x00887B60
// before the call, and the callee's unwind map (handler 0x00C5D4A0, FuncInfo
// 0x00E4C634) destroys the two incoming slots at establisher-frame +4 and +8.
// The body reads and releases both before a plain `ret`, so the ABI is two
// by-value AsciiStrings and the 0-argument name the lift carried
// (?Load_Asset_Dat@@YA_NXZ) cannot be retail's identity. docs/analysis/
// 0x006ed5b0-relocations.md records the same conclusion from the caller side.
//
// What the body does: runs the two asset builder executables, then walks a
// .big-style directory whose first four bytes are "BIGF" or "BIG4", loading
// every entry whose leading directory component is not "asset.dat", and
// finally loads <arg1>\asset.dat and ./asset.dat through Load_Asset_Catalog.

#include <windows.h>
#include <stdio.h>
#include <string.h>

extern "C" void *__cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)
extern "C" int __cdecl strcmp(const char *, const char *);
#pragma intrinsic(strcmp)
extern "C" int __cdecl _strcmpi(const char *, const char *);
extern "C" __declspec(dllimport) unsigned long __stdcall htonl(unsigned long);
__declspec(dllimport) BOOL WINAPI GetExitCodeProcess(HANDLE, DWORD *);

typedef int Int;
typedef bool Bool;

struct StringHeader
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	char data[1];

	__forceinline const char *peek(void) const
	{
		return &data[0];
	}
};

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	StringBase() : m_data(0) {}
	~StringBase()
	{
		releaseBuffer();
	}

	StringHeader *m_data;

private:
	StringBase(const StringBase<T> &other);
	void releaseBuffer();
};

extern const char g_bfmeEmptyAscii[];

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	char *concat(const char *text, Int length);

	__forceinline const char *str(void) const
	{
		return m_data ? m_data->peek() : g_bfmeEmptyAscii;
	}

	__forceinline bool isNotEmpty(void) const
	{
		return m_data != 0 && m_data->length != 0;
	}
};

// 0x012D719C and 0x012D71A0 hold the two magic pointers retail compares the
// four-byte file signature against.
extern const char *Rva012D719CMagic;
extern const char *Rva012D71A0Magic;
const char *Rva012D719CMagic = "BIGF";
const char *Rva012D71A0Magic = "BIG4";

void Create_Rva00972880_Prototype(void);
bool Load_Asset_Catalog(void *stream);
void Rva009EBC50(Int code);

// ?Rva00938620@@YA_NVAsciiString@@0@Z
bool Rva00938620(AsciiString assetPath, AsciiString assetName)
{
	DWORD exitCode;
	PROCESS_INFORMATION processInfo;
	STARTUPINFOA startupInfo;
	MEMORYSTATUS memoryStatus;
	char entryName[260];

	Create_Rva00972880_Prototype();

	memset(&startupInfo, 0, sizeof(startupInfo));
	startupInfo.cb = sizeof(startupInfo);
	if (CreateProcessA(0, (char *)"TextureAssetBuilder.exe", 0, 0, FALSE, 0x8000000, 0, 0,
	                   &startupInfo, &processInfo))
	{
		WaitForSingleObject(processInfo.hProcess, 0xffffffff);
		GetExitCodeProcess(processInfo.hProcess, &exitCode);
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
	}

	memset(&startupInfo, 0, sizeof(startupInfo));
	startupInfo.cb = sizeof(startupInfo);
	if (CreateProcessA(0, (char *)"assetCacheBuilder.exe", 0, 0, FALSE, 0x8000000, 0, 0,
	                   &startupInfo, &processInfo))
	{
		WaitForSingleObject(processInfo.hProcess, 0xffffffff);
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
	}

	if (assetName.isNotEmpty()) {
		FILE *file = fopen(assetName.str(), "rb");
		if (file) {
			fread(entryName, 4, 1, file);
			entryName[4] = 0;
			if (strcmp(entryName, Rva012D719CMagic) == 0 || strcmp(entryName, Rva012D71A0Magic) == 0) {
				DWORD entryCount = 0;
				DWORD signature = 0;
				Int entry = 0;
				// Retail reads the same header field twice; the first value is dead.
				fread(&signature, 4, 1, file);
				fread(&signature, 4, 1, file);
				entryCount = htonl(signature);
				fseek(file, 16, SEEK_SET);
				while (++entry < entryCount) {
					DWORD entryOffset = 0;
					DWORD entrySize = 0;
					Int pos;
					fread(&entryOffset, 4, 1, file);
					fread(&entrySize, 4, 1, file);
					entrySize = htonl(entrySize);
					entryOffset = htonl(entryOffset);
					pos = -1;
					do {
						++pos;
						fread(&entryName[pos], 1, 1, file);
					} while (entryName[pos]);
					while (pos >= 0 && entryName[pos] != '\\' && entryName[pos] != '/') {
						--pos;
					}
					if (_strcmpi(&entryName[pos + 1], "asset.dat") == 0) {
						fseek(file, entryOffset, SEEK_SET);
						if (entry < entryCount) {
							Load_Asset_Catalog(file);
						}
						break;
					}
				}
			}
			fclose(file);
		}
	}

	if (assetPath.isNotEmpty()) {
		assetPath.concat("\\asset.dat", 10);
		FILE *file = fopen(assetPath.str(), "rb");
		if (file) {
			Load_Asset_Catalog(file);
			fclose(file);
		}
	}

	FILE *file = fopen("asset.dat", "rb");
	if (file) {
		Bool loaded = Load_Asset_Catalog(file);
		fclose(file);
		if (loaded) {
			GlobalMemoryStatus(&memoryStatus);
			if (memoryStatus.dwMemoryLoad > 0x20000000) {
				Rva009EBC50(memoryStatus.dwMemoryLoad + 0xe0000000);
			} else {
				Rva009EBC50(0);
			}
			return true;
		}
	}
	return false;
}
