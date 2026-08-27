// cl: /DNDEBUG /MD /EHs-c-
// Recovered from the EA Generals reference.  The three LZH-Light wrapper
// calls are pinned to the matching retail wrapper bodies in this executable.

class LZHLDecompressor
{
public:
	LZHLDecompressor();

private:
	unsigned char m_unreconstructed_00[ 0x98 ];
};

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;
typedef void *LZHL_DHANDLE;

LZHL_DHANDLE LZHLCreateDecompressor();
int LZHLDecompress(LZHL_DHANDLE, UnsignedByte *, UnsignedInt *, const UnsignedByte *, UnsignedInt *);
void LZHLDestroyDecompressor(LZHL_DHANDLE);

LZHL_DHANDLE LZHLCreateDecompressor()
{
	return new LZHLDecompressor;
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
