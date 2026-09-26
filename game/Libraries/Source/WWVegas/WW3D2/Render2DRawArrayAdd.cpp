// cl: /DNDEBUG /MD /G6 /EHsc
// Address-derived BFME raw-array growth helper at retail 0x00933990.
//
// This is the 16-byte simple dynamic array used by the BFME renderer.  The
// element type is deliberately kept local: the surrounding Render2D classes
// have a different BFME layout from the vendored Zero Hour declaration.

extern "C" __declspec(dllimport) void *__cdecl realloc(
	void *pointer, unsigned int bytes);

struct Render2DCharElement
{
	unsigned char bytes[2];
};

class Render2DRawArray
{
public:
	Render2DCharElement *Add(int count);

	Render2DCharElement *Data;
	int Size;
	int Count;
	int GrowthStep;
};

Render2DCharElement *Render2DRawArray::Add(int count)
{
	if (count == 0 || (unsigned)count >= 0x80000000u)
		goto failure;

	Count += count;
	if ((unsigned)Count <= (unsigned)Size)
		return Data + (Count - count);

	Size = Count + GrowthStep;
	Data = (Render2DCharElement *)realloc(
		Data, (unsigned)Size * sizeof(Render2DCharElement));
	if (Data == 0)
		goto failure;
	return Data + (Count - count);

failure:
	return 0;
}
