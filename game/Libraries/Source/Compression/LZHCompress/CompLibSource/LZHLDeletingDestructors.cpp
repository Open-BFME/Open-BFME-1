// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// Open-BFME5: LZHLCompressor scalar-deleting destructor at retail
// 0x00823150 (30 bytes).  The matched LZHLCompressor constructor at
// 0x008254C0 and complete destructor at 0x00825550 establish the identity.

class LZHLCompressor
{
public:
	~LZHLCompressor();
};

void forceLZHLCompressorDeletingDestructor(LZHLCompressor *value)
{
	delete value;
}

// Open-BFME5: LZHLDecompressor scalar-deleting destructor at retail
// 0x008231D0 (30 bytes).  The matched LZHLDecompressor constructor at
// 0x00826780 and complete destructor at 0x008267E0 establish the identity.

class LZHLDecompressor
{
public:
	~LZHLDecompressor();
};

void forceLZHLDecompressorDeletingDestructor(LZHLDecompressor *value)
{
	delete value;
}
