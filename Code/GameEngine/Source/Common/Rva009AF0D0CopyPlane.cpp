// BFME VP6 row/plane helper called by the two matched copy-plane drivers.
// Retail uses a cdecl eight-argument ABI: the first four rows are copied
// directly, intermediate rows go through the codec's selected row callback,
// and the trailing four rows go through the adjacent edge helper.

extern "C" void * __cdecl memcpy(void *destination, const void *source,
	unsigned int bytes);
#pragma intrinsic(memcpy)

struct Rva009AF200Context;

typedef void (__cdecl *Rva009AF0D0Callback)(
    Rva009AF200Context *, unsigned char *, unsigned char *,
    unsigned int, unsigned int, int, const unsigned int *);

struct Rva009AF0D0Locals
{
    int distance;
    unsigned char *directDestination;
    unsigned int directRows;
    Rva009AF0D0Callback rowFunction;
};

extern Rva009AF0D0Callback g_rva01356EB4;
extern void __cdecl Rva009ADAA0(
	Rva009AF200Context *, unsigned char *, unsigned char *,
	unsigned int, unsigned int, int, const unsigned int *);

void copyPlane009AF0D0(
    Rva009AF200Context *context,
	unsigned int stride,
	int index,
	unsigned int width,
	unsigned int height,
	unsigned char *source,
    unsigned char *destination,
    const unsigned int *table)
{
    Rva009AF0D0Locals locals;
    locals.rowFunction = g_rva01356EB4;
    locals.directDestination = destination;
    locals.distance = (int)(source - destination);
    locals.directRows = 4;
    do
    {
        memcpy(locals.directDestination,
            locals.directDestination + locals.distance, stride);
        locals.directDestination += stride;
        --locals.directRows;
    }
    while (locals.directRows != 0);

    if (height > 1)
    {
        unsigned int eightRows = stride * 8;
        --height;
        do
        {
            source += eightRows;
            destination += eightRows;
            locals.rowFunction(
                context, source, destination,
                stride, width, index, table);
            index += width;
            --height;
		}
		while (height != 0);
	}

    unsigned char *tailDestination = destination + stride * 4;
    locals.distance = (int)(source - destination);
    locals.directRows = 4;
    do
    {
        memcpy(tailDestination, tailDestination + locals.distance, stride);
        tailDestination += stride;
        --locals.directRows;
    }
    while (locals.directRows != 0);

    Rva009ADAA0(
        context, source, destination, stride, width, index, table);
}
