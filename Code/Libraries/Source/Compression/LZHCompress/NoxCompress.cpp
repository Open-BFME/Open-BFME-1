// cl: /DNDEBUG /MD /EHs-c-
// Recovered from the EA Generals reference.  The four LZH-Light wrapper
// calls are pinned to the matching retail wrapper bodies in this executable.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;
typedef void *LZHL_DHANDLE;

class LZHLDecompressor
{
public:
	LZHLDecompressor();
	int decompress( UnsignedByte *, UnsignedInt *, const UnsignedByte *, UnsignedInt * );

private:
	unsigned char m_unreconstructed_00[ 0x98 ];
};

LZHL_DHANDLE LZHLCreateDecompressor();
__declspec(noinline) int LZHLDecompress(LZHL_DHANDLE, UnsignedByte *, UnsignedInt *, const UnsignedByte *, UnsignedInt *);
void LZHLDestroyDecompressor(LZHL_DHANDLE);

struct FILE;

extern "C" __declspec(dllimport) FILE * __cdecl fopen(const char *, const char *);
extern "C" __declspec(dllimport) int __cdecl fseek(FILE *, long, int);
extern "C" __declspec(dllimport) long __cdecl ftell(FILE *);
extern "C" __declspec(dllimport) unsigned int __cdecl fread(void *, unsigned int, unsigned int, FILE *);
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(const void *, unsigned int, unsigned int, FILE *);
extern "C" __declspec(dllimport) int __cdecl fclose(FILE *);
extern "C" __declspec(dllimport) void * __cdecl malloc(unsigned int);
extern "C" __declspec(dllimport) void __cdecl free(void *);

typedef void *LZHL_CHANDLE;

template <class T> const T &min(const T &a, const T &b)
{
	if (a < b) {
		return a;
	} else {
		return b;
	}
}

LZHL_CHANDLE LZHLCreateCompressor();
unsigned int LZHLCompress(LZHL_CHANDLE, void *, void *, unsigned int);
void LZHLDestroyCompressor(LZHL_CHANDLE);
unsigned int LZHLCompressorCalcMaxBuf(unsigned);

#define BLOCKSIZE 500000

Bool DecompressFile(char *infile, char *outfile)
{
	UnsignedInt rawSize = 0, compressedSize = 0;
	FILE *inFilePtr = 0;
	FILE *outFilePtr = 0;
	char *inBlock = 0;
	char *outBlock = 0;
	LZHL_DHANDLE decompress;
	Int ok = 0;
	UnsignedInt srcSz, dstSz;

	if ((infile == 0) || (outfile == 0))
		return false;

	inFilePtr = fopen(infile, (const char *)0x0107FF20);
	if (inFilePtr)
	{
		fseek(inFilePtr, 0, 2);
		compressedSize = ftell(inFilePtr);
		fseek(inFilePtr, 0, 0);

		compressedSize -= sizeof(UnsignedInt);
		fread(&rawSize, 1, sizeof(UnsignedInt), inFilePtr);

		inBlock = (char *)malloc(compressedSize);
		outBlock = (char *)malloc(rawSize);

		if ((inBlock == 0) || (outBlock == 0))
			return false;

		fread(inBlock, 1, compressedSize, inFilePtr);
		fclose(inFilePtr);

		srcSz = compressedSize;
		dstSz = rawSize;
		decompress = LZHLCreateDecompressor();

		for (;;)
		{
			ok = LZHLDecompress(decompress, (UnsignedByte *)outBlock + rawSize - dstSz, &dstSz,
				(const UnsignedByte *)inBlock + compressedSize - srcSz, &srcSz);

			if (!ok)
				break;
			if (srcSz <= 0)
				break;
		}

		LZHLDestroyDecompressor(decompress);
		outFilePtr = fopen(outfile, (const char *)0x0107FF60);
		if (outFilePtr)
		{
			fwrite(outBlock, rawSize, 1, outFilePtr);
			fclose(outFilePtr);
		}
		else
			return false;

		free(inBlock);
		free(outBlock);
		return true;
	}

	return false;
}

Bool CompressFile(char *infile, char *outfile)
{
	unsigned int rawSize = 0;
	unsigned int compressedSize = 0, compressed = 0, i = 0;
	FILE *inFilePtr = 0;
	FILE *outFilePtr = 0;
	char *inBlock = 0;
	char *outBlock = 0;
	LZHL_CHANDLE compressor;
	unsigned int blocklen;

	if ((infile == 0) || (outfile == 0))
		return false;

	inFilePtr = fopen(infile, (const char *)0x0107FF20);
	if (inFilePtr)
	{
		fseek(inFilePtr, 0, 2);
		rawSize = ftell(inFilePtr);
		fseek(inFilePtr, 0, 0);

		inBlock = (char *)malloc(rawSize);
		outBlock = (char *)malloc(LZHLCompressorCalcMaxBuf(rawSize));

		if ((inBlock == 0) || (outBlock == 0))
			return false;

		fread(inBlock, 1, rawSize, inFilePtr);
		fclose(inFilePtr);

		compressor = LZHLCreateCompressor();
		for (i = 0; i < rawSize; i += BLOCKSIZE)
		{
			blocklen = min((unsigned int)BLOCKSIZE, rawSize - i);
			compressed = LZHLCompress(compressor, outBlock + compressedSize, inBlock + i, blocklen);
			compressedSize += compressed;
		}

		LZHLDestroyCompressor(compressor);

		outFilePtr = fopen(outfile, (const char *)0x0107FF60);
		if (outFilePtr)
		{
			fwrite(&rawSize, sizeof(unsigned int), 1, outFilePtr);
			fwrite(outBlock, compressedSize, 1, outFilePtr);
			fclose(outFilePtr);
		}
		else
			return false;

		free(inBlock);
		free(outBlock);
		return true;
	}

	return false;
}

LZHL_DHANDLE LZHLCreateDecompressor()
{
	return new LZHLDecompressor;
}

__declspec(noinline) int LZHLDecompress( LZHL_DHANDLE handle, UnsignedByte *dst, UnsignedInt *dstSz,
	const UnsignedByte *src, UnsignedInt *srcSz )
{
	return ( (LZHLDecompressor *)handle )->decompress( dst, dstSz, src, srcSz );
}

Bool DecompressMemory(void *inBufferVoid, Int inSize, void *outBufferVoid, Int& outSize)
{
	UnsignedByte *inBuffer = (UnsignedByte *)inBufferVoid;
	UnsignedByte *outBuffer = (UnsignedByte *)outBufferVoid;
	UnsignedInt rawSize = 0, compressedSize = 0;
	LZHL_DHANDLE decompress;
	Int ok = 0;
	UnsignedInt srcSz, dstSz;

	if ((inBuffer == 0) || (outBuffer == 0) || (inSize < 4) || (outSize == 0))
		return false;

	compressedSize = inSize;
	rawSize = outSize;
	srcSz = compressedSize;
	dstSz = rawSize;
	decompress = LZHLCreateDecompressor();

	for (;;)
	{
		ok = LZHLDecompress(decompress, outBuffer + rawSize - dstSz, &dstSz,
			inBuffer + compressedSize - srcSz, &srcSz);

		if (!ok)
			break;
		if (srcSz <= 0)
			break;
	}

	LZHLDestroyDecompressor(decompress);
	outSize = rawSize;
	return true;
}
