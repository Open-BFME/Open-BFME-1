// cl: /DNDEBUG /MD /G6 /EHsc
// Address-derived BFME raw-array growth helper at retail 0x009338B0.

extern "C" __declspec(dllimport) void *__cdecl realloc(
	void *pointer, unsigned int bytes);

struct Render2DPackedVert
{
	unsigned char bytes[0x2C];
};

class Render2DRawArray
{
public:
	Render2DPackedVert *Add(int count);

	Render2DPackedVert *Data;
	int Size;
	int Count;
	int GrowthStep;
};

Render2DPackedVert *Render2DRawArray::Add(int count)
{
	if (count == 0 || (unsigned)count >= 0x80000000u)
		goto failure;

	Count += count;
	if ((unsigned)Count <= (unsigned)Size)
		return Data + (Count - count);

	Size = Count + GrowthStep;
	Data = (Render2DPackedVert *)realloc(
		Data, (unsigned)Size * sizeof(Render2DPackedVert));
	if (Data == 0)
		goto failure;
	return Data + (Count - count);

failure:
	return 0;
}
