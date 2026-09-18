// cl: /DNDEBUG /MD /EHsc
// The map and script writers call this incremental-link thunk, which routes
// to DataChunkOutput::openDataChunk at retail 0x001041F0.

class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short version);
};

class BfmeChunkZO
{
public:
	void bfmeOpenZO(char *name, unsigned short version);
};

void BfmeChunkZO::bfmeOpenZO(char *name, unsigned short version)
{
	((DataChunkOutput *)this)->openDataChunk(name, version);
}
