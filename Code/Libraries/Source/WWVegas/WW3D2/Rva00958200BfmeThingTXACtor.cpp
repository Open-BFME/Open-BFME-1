// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00958200: BFME's TXA AVI-stream constructor.

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef int LONG;
typedef unsigned int UINT;

struct IAVIFile;
struct IAVIStream;
typedef IAVIFile *PAVIFILE;
typedef IAVIStream *PAVISTREAM;

struct RvaRect00958200
{
	LONG left;
	LONG top;
	LONG right;
	LONG bottom;
};

struct RvaAviStreamInfo00958200
{
	DWORD fccType;
	DWORD fccHandler;
	DWORD dwFlags;
	DWORD dwCaps;
	WORD wPriority;
	WORD wLanguage;
	DWORD dwScale;
	DWORD dwRate;
	DWORD dwStart;
	DWORD dwLength;
	DWORD dwInitialFrames;
	DWORD dwSuggestedBufferSize;
	DWORD dwQuality;
	DWORD dwSampleSize;
	RvaRect00958200 rcFrame;
	DWORD dwEditCount;
	DWORD dwFormatChangeCount;
	char szName[64];
};

struct RvaBitmapInfoHeader00958200
{
	DWORD biSize;
	LONG biWidth;
	LONG biHeight;
	WORD biPlanes;
	WORD biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG biXPelsPerMeter;
	LONG biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
};

struct RvaAviCompressOptions00958200
{
	DWORD fccType;
	DWORD fccHandler;
	DWORD dwKeyFrameEvery;
	DWORD dwQuality;
	DWORD dwBytesPerSecond;
	DWORD dwFlags;
	void *lpFormat;
	DWORD cbFormat;
	void *lpParms;
	DWORD cbParms;
	DWORD dwInterleaveEvery;
};

struct RvaOpenError00958200
{
	char unused[0x38];
	char text[0x200];
	DWORD reserved;
};

extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);
extern "C" __declspec(dllimport) int __cdecl _access(const char *path, int mode);
extern "C" __declspec(dllimport) int __stdcall SetRect(RvaRect00958200 *rect, int left, int top, int right, int bottom);
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char *text);

extern "C" void __stdcall AVIFileInit(void);
extern "C" int __stdcall AVIFileOpen(PAVIFILE *file, const char *name, unsigned mode, void *handler);
extern "C" int __stdcall AVIFileCreateStreamA(PAVIFILE file, PAVISTREAM *stream, void *info);
extern "C" int __stdcall AVIMakeCompressedStream(PAVISTREAM *compressed, PAVISTREAM stream, void *options, void *handler);
extern "C" int __stdcall AVIFileReadData(PAVISTREAM stream, unsigned long position, void *format, long size);
void __stdcall bfmeReleaseATXA(void *stream);
void __stdcall bfmeReleaseBTXA(void *file);
void *operator new[](unsigned int size);
extern "C" long __ftol2(double value);

class BfmeThingTXA
{
public:
	virtual ~BfmeThingTXA();
	BfmeThingTXA(const char *filename, int width, int height, int bitcount,
		float framerate, int count, bool compressed);

	int m_bfmeImageSize;
	int m_bfmeCount;
	void *m_bfmeBuf;
	int m_bfmeReserved0;
	int m_bfmeReserved1;
	PAVIFILE m_bfmeB;
	PAVISTREAM m_bfmeA;
};

__forceinline void rva00958200Cleanup(BfmeThingTXA *self, PAVISTREAM stream)
{
	bfmeReleaseATXA(stream);
	bfmeReleaseBTXA(self->m_bfmeB);
	self->m_bfmeB = 0;
	self->m_bfmeA = 0;
}

BfmeThingTXA::BfmeThingTXA(const char *filename, int width, int height, int bitcount,
	float framerate, int count, bool compressed)
{
	m_bfmeCount = count;
	m_bfmeReserved0 = 0;
	m_bfmeReserved1 = 0;
	m_bfmeB = 0;
	m_bfmeA = 0;
	m_bfmeBuf = 0;
	m_bfmeImageSize = ((((unsigned int)width * (unsigned int)bitcount + 31) >> 3) & 0x1ffffffc) * height;

	register int counter = 0;
	int result;
	RvaOpenError00958200 open_error;
	char file[256];

	do
	{
		sprintf(file, "%s%d.AVI", filename, counter++);
		result = _access(file, 0);
	}
	while (result != -1);

	AVIFileInit();
	int hr = AVIFileOpen(&m_bfmeB, file, 0x1001, 0);
	if (hr != 0)
	{
		sprintf(open_error.text, "Unable to open %s\n", file);
		OutputDebugStringA(open_error.text);
		m_bfmeB = 0;
		return;
	}

	RvaAviStreamInfo00958200 stream_info;
	stream_info.fccType = 0x73646976;
	stream_info.fccHandler = 0x4356534d;
	stream_info.dwFlags = 0;
	stream_info.dwCaps = 0;
	stream_info.wPriority = 0;
	stream_info.wLanguage = 0;
	stream_info.dwScale = 1;
	stream_info.dwRate = (int)framerate;
	stream_info.dwStart = 0;
	stream_info.dwLength = 0;
	stream_info.dwInitialFrames = 0;
	stream_info.dwSuggestedBufferSize = 0;
	stream_info.dwQuality = 0;
	stream_info.dwSampleSize = 0;
	SetRect(&stream_info.rcFrame, 0, 0, width, height);
	stream_info.dwEditCount = 0;
	stream_info.dwFormatChangeCount = 0;
	sprintf(stream_info.szName, "G");

	PAVISTREAM stream;
	hr = AVIFileCreateStreamA(m_bfmeB, &stream, &stream_info);
	if (hr != 0)
	{
		char error[256];
		sprintf(error, "Unable to create AVI stream\n");
		OutputDebugStringA(error);
		bfmeReleaseBTXA(m_bfmeB);
		m_bfmeB = 0;
		return;
	}

	if (compressed)
	{
		RvaAviCompressOptions00958200 options;
		options.fccType = 0x73646976;
		options.fccHandler = 0x75796668;
		options.dwKeyFrameEvery = 0x12c;
		options.dwQuality = 0x2710;
		options.dwFlags = 4;
		options.lpFormat = 0;
		options.cbFormat = 0;
		options.lpParms = 0;
		options.cbParms = 0;
		hr = AVIMakeCompressedStream(&m_bfmeA, stream, &options, 0);
		if (hr != 0)
		{
			char error[256];
			sprintf(error, "Unable to compress AVI stream\n");
			OutputDebugStringA(error);
			rva00958200Cleanup(this, stream);
			return;
		}
		bfmeReleaseATXA(stream);
	}
	else
	{
		m_bfmeA = stream;
	}

	int bitmap_width = width;
	int bitmap_height = height;
	unsigned short bitmap_bitcount = (unsigned short)bitcount;
	RvaBitmapInfoHeader00958200 bitmap_info;
	bitmap_info.biWidth = bitmap_width;
	bitmap_info.biHeight = bitmap_height;
	bitmap_info.biBitCount = bitmap_bitcount;
	bitmap_info.biSizeImage = m_bfmeImageSize;
	bitmap_info.biSize = sizeof(bitmap_info);
	bitmap_info.biPlanes = 1;
	bitmap_info.biCompression = 0;
	bitmap_info.biXPelsPerMeter = 1;
	bitmap_info.biYPelsPerMeter = 1;
	bitmap_info.biClrUsed = 0;
	bitmap_info.biClrImportant = 0;

	hr = AVIFileReadData(m_bfmeA, 0, &bitmap_info, sizeof(bitmap_info));
	if (hr != 0)
	{
		char error[256];
		sprintf(error, "Unable to set AVI format\n");
		OutputDebugStringA(error);
		rva00958200Cleanup(this, m_bfmeA);
		return;
	}

	m_bfmeBuf = new unsigned char[m_bfmeImageSize * count];
	if (m_bfmeBuf == 0)
	{
		char error[256];
		sprintf(error, "Unable to allocate AVI buffer\n");
		OutputDebugStringA(error);
	}
}
