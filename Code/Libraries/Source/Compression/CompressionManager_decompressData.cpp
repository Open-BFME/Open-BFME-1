// cl: /DNDEBUG /MD /EHs-c-

// CompressionManager::decompressData, 0x0081E890, 240 bytes.
//
// The name is not inferred: a byte-true call in
// CachedFileInputStream_open_Thunk.cpp already encodes this address, and
// getCompressionType (0x0081E560), getUncompressedSize and isDataCompressed
// are ledgered on the same class beside it.
//
// The reference's body unchanged, and the compression-type constants confirm
// it arm for arm: BTREE is 12, HUFF 13, REFPACK 1, NOXLZH 2 and the ZLIB
// levels are the closed range 3..11 -- exactly the reference's enum, tested in
// the reference's order. The three EAC decoders are __stdcall so the arms end
// without a stack adjustment, and MSVC folds the reference's
// `if (ret) return ret; else return 0;` down to a plain return in each.
//
// One callee is pinned rather than owned: ?DecompressMemory@@YA_NPAXH0AAH@Z at
// 0x0081EB80, the NOXLZH arm's decoder. Its four arguments are the reference's
// in order, outSize by reference, and the return is folded into the
// `neg al / sbb / and` that yields destLen or zero.
//
// Only what this body needs is declared; the compression headers would drag in
// the whole EAC and ZLib surface for four prototypes.

typedef int Int;
typedef unsigned char UnsignedByte;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);

enum CompressionType
{
	COMPRESSION_MIN = 0,
	COMPRESSION_NONE = COMPRESSION_MIN,
	COMPRESSION_REFPACK,
	COMPRESSION_NOXLZH,
	COMPRESSION_ZLIB1,
	COMPRESSION_ZLIB2,
	COMPRESSION_ZLIB3,
	COMPRESSION_ZLIB4,
	COMPRESSION_ZLIB5,
	COMPRESSION_ZLIB6,
	COMPRESSION_ZLIB7,
	COMPRESSION_ZLIB8,
	COMPRESSION_ZLIB9,
	COMPRESSION_BTREE,
	COMPRESSION_HUFF
};

enum { Z_OK = 0, Z_STREAM_END = 1 };

extern "C" {
	int __stdcall BTREE_decode(void *dest, const void *compresseddata, int *compressedsize);
	int __stdcall HUFF_decode(void *dest, const void *compresseddata, int *compressedsize);
	int __stdcall REF_decode(void *dest, const void *compresseddata, int *compressedsize);
	int uncompress(UnsignedByte *dest, unsigned long *destLen, const UnsignedByte *source, unsigned long sourceLen);
}

Bool DecompressMemory(void *inBufferVoid, Int inSize, void *outBufferVoid, Int &outSize);	// retail 0x0081EB80

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression/Compression.h
class CompressionManager
{
public:
	static CompressionType getCompressionType(const void *mem, Int len);	// retail 0x0081E560
	static Bool isDataCompressed(const void *mem, Int len);
	static Int getUncompressedSize(const void *mem, Int len);
	static Int decompressData(const void *src, Int srcLen, void *dest, Int destLen);
};

// ?getCompressionType@CompressionManager@@SA?AW4CompressionType@@PBXH@Z
CompressionType CompressionManager::getCompressionType( const void *mem, Int len )
{
	if (len < 8)
		return COMPRESSION_NONE;

	if (memcmp(mem, "NOX", 4) == 0)
		return COMPRESSION_NOXLZH;
	if (memcmp(mem, "ZL1", 4) == 0)
		return COMPRESSION_ZLIB1;
	if (memcmp(mem, "ZL2", 4) == 0)
		return COMPRESSION_ZLIB2;
	if (memcmp(mem, "ZL3", 4) == 0)
		return COMPRESSION_ZLIB3;
	if (memcmp(mem, "ZL4", 4) == 0)
		return COMPRESSION_ZLIB4;
	if (memcmp(mem, "ZL5", 4) == 0)
		return COMPRESSION_ZLIB5;
	if (memcmp(mem, "ZL6", 4) == 0)
		return COMPRESSION_ZLIB6;
	if (memcmp(mem, "ZL7", 4) == 0)
		return COMPRESSION_ZLIB7;
	if (memcmp(mem, "ZL8", 4) == 0)
		return COMPRESSION_ZLIB8;
	if (memcmp(mem, "ZL9", 4) == 0)
		return COMPRESSION_ZLIB9;
	if (memcmp(mem, "EAB", 4) == 0)
		return COMPRESSION_BTREE;
	if (memcmp(mem, "EAH", 4) == 0)
		return COMPRESSION_HUFF;

	return (CompressionType)(memcmp(mem, "EAR", 4) == 0);
}

Bool CompressionManager::isDataCompressed( const void *mem, Int len )
{
	CompressionType t = getCompressionType(mem, len);
	return t != COMPRESSION_NONE;
}

Int CompressionManager::getUncompressedSize( const void *mem, Int len )
{
	if (len < 8)
		return len;

	CompressionType compType = getCompressionType( mem, len );
	switch (compType)
	{
		case COMPRESSION_NOXLZH:
		case COMPRESSION_ZLIB1:
		case COMPRESSION_ZLIB2:
		case COMPRESSION_ZLIB3:
		case COMPRESSION_ZLIB4:
		case COMPRESSION_ZLIB5:
		case COMPRESSION_ZLIB6:
		case COMPRESSION_ZLIB7:
		case COMPRESSION_ZLIB8:
		case COMPRESSION_ZLIB9:
		case COMPRESSION_BTREE:
		case COMPRESSION_HUFF:
		case COMPRESSION_REFPACK:
			return *(Int *)(((UnsignedByte *)mem)+4);
	}

	return len;
}

// ?decompressData@CompressionManager@@SAHPBXHPAXH@Z
Int CompressionManager::decompressData( const void *srcVoid, Int srcLen, void *destVoid, Int destLen )
{
	if (srcLen < 8)
		return 0;

	UnsignedByte *src = (UnsignedByte *)srcVoid;
	UnsignedByte *dest = (UnsignedByte *)destVoid;

	CompressionType compType = getCompressionType(src, srcLen);

	if (compType == COMPRESSION_BTREE)
	{
		Int slen = srcLen - 8;
		Int ret = BTREE_decode(dest, src+8, &slen);
		if (ret)
			return ret;
		else
			return 0;
	}
	if (compType == COMPRESSION_HUFF)
	{
		Int slen = srcLen - 8;
		Int ret = HUFF_decode(dest, src+8, &slen);
		if (ret)
			return ret;
		else
			return 0;
	}
	if (compType == COMPRESSION_REFPACK)
	{
		Int slen = srcLen - 8;
		Int ret = REF_decode(dest, src+8, &slen);
		if (ret)
			return ret;
		else
			return 0;
	}

	if (compType == COMPRESSION_NOXLZH)
	{
		Bool ret = DecompressMemory(src+8, srcLen-8, dest, destLen);
		if (ret)
			return destLen;
		else
			return 0;
	}

	if (compType >= COMPRESSION_ZLIB1 && compType <= COMPRESSION_ZLIB9)
	{
		unsigned long outLen = destLen;
		Int err = uncompress(dest, &outLen, src+8, srcLen-8);
		if (err == Z_OK || err == Z_STREAM_END)
		{
			return outLen;
		}
		else
		{
			return 0;
		}
	}

	return 0;
}
