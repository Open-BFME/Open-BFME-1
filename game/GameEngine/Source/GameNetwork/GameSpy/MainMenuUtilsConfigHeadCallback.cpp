// cl: /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWDownload /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDownload /Iinputs/reference/shims/gamespy
// stlport
// Config HEAD callback: Zero Hour MainMenuUtils.cpp with BFME's online file
// and the byte-count ABI of its bundled GameSpy SDK.
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "ascii_string.h"
#include "urlBuilder.h"

class GlobalData {
public:
    AsciiString getPath_UserData() const;
};
extern GlobalData *TheWritableGlobalData;
#define TheGlobalData ((const GlobalData *)TheWritableGlobalData)

static int timeThroughOnline;
static int checksLeftBeforeOnline;
extern volatile unsigned char g_rva012F7178PatchCheckLayoutActive;
static char *configBuffer;
void Rva004C5490();
void d_0062ea60();

enum GHTTPBool { GHTTPFalse, GHTTPTrue };
enum GHTTPResult { GHTTPSuccess };
extern "C" char * __cdecl ghttpGetHeaders(int request);
typedef GHTTPBool (__cdecl *GHTTPCompletedCallback)(int, GHTTPResult, char *, __int64, void *);
extern "C" int __cdecl ghttpGetA(const char *, int, GHTTPCompletedCallback, void *);
GHTTPBool __cdecl configCallback(int request, GHTTPResult result, char *buffer, __int64 bufferLen, void *param);
struct Rva0062F130Header {
    int refs;
    unsigned short length, capacity;
    char text[1];
};
static __forceinline int compareContentLength(const AsciiString &key)
{
    Rva0062F130Header *keyData = *(Rva0062F130Header * const *)&key;
    int keyLen = keyData ? keyData->length : 0;
    const char *keyText = keyData ? keyData->text : "";
    int count = keyLen < 14 ? keyLen : 14;
    int comparison = memcmp(keyText, "Content-Length", count);
    if (comparison != 0)
        return comparison;
    return keyLen - 14;
}

GHTTPBool __cdecl configHeadCallback(int request, GHTTPResult result, char *buffer, __int64 bufferLen, void *param)
{
    if ((int)param != timeThroughOnline)
        return GHTTPTrue;

    if (result == 0)
    {
        AsciiString headers(ghttpGetHeaders(request));
        AsciiString line;
        while (headers.nextToken(&line, "\n\r"))
        {
            AsciiString key;
            AsciiString val;
            line.nextToken(&key, ": ");
            line.nextToken(&val, ": \r\n");
            Rva0062F130Header *valueData = *(Rva0062F130Header **)&val;
            if (compareContentLength(key) == 0 &&
                valueData && valueData->length != 0)
            {
                int serverLen = atoi(val.str());
                int fileLen = 0;
                AsciiString fname;
                fname.format("%sLoTRB4MEOnline\\Config.txt", TheGlobalData->getPath_UserData().str());
                FILE *fp = fopen(fname.str(), "rb");
                if (fp)
                {
                    fseek(fp, 0, SEEK_END);
                    fileLen = ftell(fp);
                    fclose(fp);
                }
                if (serverLen == fileLen)
                {
                    --checksLeftBeforeOnline;
                    if (g_rva012F7178PatchCheckLayoutActive && !checksLeftBeforeOnline)
                    {
                        Rva004C5490();
                        g_rva012F7178PatchCheckLayoutActive = false;
                    }
                    if (configBuffer)
                    {
                        delete[] configBuffer;
                        configBuffer = 0;
                    }
                    AsciiString fname;
                    fname.format("%sLoTRB4MEOnline\\Config.txt", TheGlobalData->getPath_UserData().str());
                    FILE *fp = fopen(fname.str(), "rb");
                    if (fp)
                    {
                        configBuffer = new char[fileLen];
                        fread(configBuffer, fileLen, 1, fp);
                        configBuffer[fileLen - 1] = 0;
                        fclose(fp);
                        if (!checksLeftBeforeOnline)
                            d_0062ea60();
                        return GHTTPTrue;
                    }
                }
            }
        }
    }

    std::string gameURL, mapURL, configURL, motdURL;
    FormatURLFromRegistry(gameURL, mapURL, configURL, motdURL);
    ghttpGetA(configURL.c_str(), 1, configCallback, param);
    return GHTTPTrue;
}
