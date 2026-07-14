#pragma once
#ifndef _INC_VFW
#define _INC_VFW
// Minimal verbatim DX8-era Platform SDK vfw.h subset — the AVIFile interfaces
// used by WW3D2 FramGrab (vtable order = SDK; non-UNICODE A-variant mapping).
#include "objbase.h"

typedef DWORD FOURCC;
typedef UINT MMRESULT;
typedef struct IAVIStream *PAVISTREAM;
typedef struct IAVIFile *PAVIFILE;

#define OF_WRITE 0x00000001
#define OF_CREATE 0x00001000
#ifndef mmioFOURCC
#define mmioFOURCC(ch0, ch1, ch2, ch3) \
    ((DWORD)(BYTE)(ch0) | ((DWORD)(BYTE)(ch1) << 8) | \
    ((DWORD)(BYTE)(ch2) << 16) | ((DWORD)(BYTE)(ch3) << 24))
#endif
#define streamtypeVIDEO mmioFOURCC('v', 'i', 'd', 's')

#define AVIIF_KEYFRAME 0x00000010

typedef struct _AVISTREAMINFOA {
    DWORD fccType; DWORD fccHandler; DWORD dwFlags; DWORD dwCaps;
    WORD wPriority; WORD wLanguage;
    DWORD dwScale; DWORD dwRate; DWORD dwStart; DWORD dwLength;
    DWORD dwInitialFrames; DWORD dwSuggestedBufferSize; DWORD dwQuality; DWORD dwSampleSize;
    RECT rcFrame; DWORD dwEditCount; DWORD dwFormatChangeCount; char szName[64];
} AVISTREAMINFOA, *LPAVISTREAMINFOA, *PAVISTREAMINFOA;
typedef AVISTREAMINFOA AVISTREAMINFO, *LPAVISTREAMINFO, *PAVISTREAMINFO;

struct IAVIStream : public IUnknown {
    STDMETHOD(Create)(LPARAM lParam1, LPARAM lParam2) = 0;
    STDMETHOD(Info)(AVISTREAMINFOA *psi, LONG lSize) = 0;
    STDMETHOD_(LONG, FindSample)(LONG lPos, LONG lFlags) = 0;
    STDMETHOD(ReadFormat)(LONG lPos, LPVOID lpFormat, LONG *lpcbFormat) = 0;
    STDMETHOD(SetFormat)(LONG lPos, LPVOID lpFormat, LONG cbFormat) = 0;
    STDMETHOD(Read)(LONG lStart, LONG lSamples, LPVOID lpBuffer, LONG cbBuffer, LONG *plBytes, LONG *plSamples) = 0;
    STDMETHOD(Write)(LONG lStart, LONG lSamples, LPVOID lpBuffer, LONG cbBuffer, DWORD dwFlags, LONG *plSampWritten, LONG *plBytesWritten) = 0;
    STDMETHOD(Delete)(LONG lStart, LONG lSamples) = 0;
    STDMETHOD(ReadData)(DWORD fcc, LPVOID lpBuffer, LONG *lpcbBuffer) = 0;
    STDMETHOD(WriteData)(DWORD fcc, LPVOID lpBuffer, LONG cbBuffer) = 0;
    STDMETHOD(SetInfo)(AVISTREAMINFOA *plInfo, LONG cbInfo) = 0;
};

struct IAVIFile : public IUnknown {
    STDMETHOD(Info)(LPVOID pfi, LONG lSize) = 0;  // AVIFILEINFOW * in the SDK
    STDMETHOD(GetStream)(PAVISTREAM *ppStream, DWORD fccType, LONG lParam) = 0;
    STDMETHOD(CreateStream)(PAVISTREAM *ppStream, AVISTREAMINFOA *psi) = 0;
    STDMETHOD(WriteData)(DWORD fcc, LPVOID lpBuffer, LONG cbBuffer) = 0;
    STDMETHOD(ReadData)(DWORD fcc, LPVOID lpBuffer, LONG *lpcbBuffer) = 0;
    STDMETHOD(EndRecord)(void) = 0;
    STDMETHOD(DeleteStream)(DWORD fccType, LONG lParam) = 0;
};

void WINAPI AVIFileInit(void);
void WINAPI AVIFileExit(void);
HRESULT WINAPI AVIFileOpenA(PAVIFILE *ppfile, LPCSTR szFile, UINT uMode, CLSID *lpHandler);
#define AVIFileOpen AVIFileOpenA
ULONG WINAPI AVIFileAddRef(PAVIFILE pfile);
ULONG WINAPI AVIFileRelease(PAVIFILE pfile);
HRESULT WINAPI AVIFileCreateStreamA(PAVIFILE pfile, PAVISTREAM *ppavi, AVISTREAMINFOA *psi);
#define AVIFileCreateStream AVIFileCreateStreamA
ULONG WINAPI AVIStreamRelease(PAVISTREAM pstream);
HRESULT WINAPI AVIStreamSetFormat(PAVISTREAM pavi, LONG lPos, LPVOID lpFormat, LONG cbFormat);
HRESULT WINAPI AVIStreamWrite(PAVISTREAM pavi, LONG lStart, LONG lSamples, LPVOID lpBuffer, LONG cbBuffer, DWORD dwFlags, LONG *plSampWritten, LONG *plBytesWritten);

#endif  // _INC_VFW
