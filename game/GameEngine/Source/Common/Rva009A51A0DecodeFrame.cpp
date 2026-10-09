// cl: /O2 /G6 /MD
struct BfmeVp6Context;
extern "C" int __cdecl bfmeVp6ThresholdSelect(BfmeVp6Context *);
void __cdecl Rva009A8410(unsigned *);
struct Rva009A6130Context;
void __cdecl Rva009A6130PostFilterDispatch(Rva009A6130Context *, int, int, int, int, unsigned char *, unsigned char *, unsigned char *, int, int);
#define readTicks Rva009A8410
#define decodePlane Rva009A6130PostFilterDispatch
class Bucket {
public:
    enum BucketMagicEnum { Bucket_GLUE_NOT_IMPLEMENTED = 0 };
    static void *__cdecl operator new(unsigned, BucketMagicEnum);
};
struct Rva009A5C40Context;
int Rva009A5C40Initialize(Rva009A5C40Context *);
struct Rva009AAC80Context;
void Rva009AAC80CodecGrid(Rva009AAC80Context *);
struct Rva009AABB0Context;
void Rva009AABB0CodecDispatch(Rva009AABB0Context *);
struct Rva009AA8F0Context;
struct Rva009AA8F0Block;
void Rva009AA8F0Dispatch(Rva009AA8F0Context *, int, Rva009AA8F0Block *);
extern void (__cdecl *g_rva01356EAC)(void *, unsigned, unsigned, unsigned, unsigned);
extern void (__cdecl *g_bfmeToneReady)();
#define CLAMP_LEVELS(p, b, w, s, d) g_rva01356EAC(p, b, w, (unsigned)s, (unsigned)d)

struct Rva009A51A0Planes
{
	int yWidth;
	int yHeight;
	int yStride;
	int uvWidth;
	int uvHeight;
	int uvStride;
	unsigned char *y;
	unsigned char *u;
	unsigned char *v;
	unsigned char *yOrigin;
};

struct Rva009A51A0Instance
{
	unsigned char pad000[0x148];
	unsigned char *fragInfo;
	unsigned char pad14C[0x19C - 0x14C];
	unsigned char version;
	unsigned char pad19D[0x1A0 - 0x19D];
	unsigned int level;
	unsigned int processorFrequency;
	unsigned char pad1A8[0x1AC - 0x1A8];
	unsigned char frameType;
	unsigned char pad1AD[0x1B0 - 0x1AD];
	unsigned int width;
	unsigned int height;
	int yStride;
	int uvStride;
	unsigned char pad1C0[0x1DC - 0x1C0];
	int interlaced;
	unsigned char pad1E0[0x208 - 0x1E0];
	int reconYPlaneSize;
	int reconUVPlaneSize;
	unsigned char pad210[0x21C - 0x210];
	int reconYOffset;
	int reconUOffset;
	int reconVOffset;
	unsigned char pad228[0x23C - 0x228];
	unsigned int outputWidth;
	unsigned int outputHeight;
	unsigned char pad244[0x254 - 0x244];
	unsigned char *lastRecon;
	unsigned char pad258[0x25C - 0x258];
	unsigned char *postBuffer;
	unsigned char *postBufferRaw;
	unsigned char *scaleBuffer;
	unsigned char pad268[0x298 - 0x268];
	void *postProcessor;
	unsigned char pad29C[0x6A0 - 0x29C];
	int averageFrameQ;
	unsigned char pad6A4[0x918 - 0x6A4];
	unsigned int averagePostTime[10];
	unsigned char pad940[0x493C - 0x940];
	int blackClamp;
	int whiteClamp;
	int deinterlaceMode;
};

// ?Rva009A51A0DecodeFrame@@YAXPAXPAI@Z
// Ported from Open BFME 2 Code/Libraries/Source/VP6/GetYUVConfig.cpp.
void Rva009A51A0DecodeFrame(void *context, unsigned *out)
{
	Rva009A51A0Instance *instance = (Rva009A51A0Instance *)context;
	Rva009A51A0Planes *config = (Rva009A51A0Planes *)out;
	unsigned int endTicks;
	unsigned int startTicks;

	readTicks(&startTicks);
	instance->level = bfmeVp6ThresholdSelect((BfmeVp6Context *)instance);

	if (instance->level || (instance->interlaced && instance->deinterlaceMode))
	{
		if (!instance->postBuffer)
		{
			instance->postBufferRaw = (unsigned char *)Bucket::operator new(
				instance->reconYPlaneSize + 2 * instance->reconUVPlaneSize + 32 + instance->yStride,
				Bucket::Bucket_GLUE_NOT_IMPLEMENTED);
			instance->postBuffer = (unsigned char *)(((unsigned int)instance->postBufferRaw + 31) & ~31);
			Rva009A5C40Initialize((Rva009A5C40Context *)instance->postProcessor);
		}

		if (instance->level > 200)
		{
			decodePlane((Rva009A6130Context *)instance->postProcessor, instance->version, instance->frameType,
				instance->level - 200, instance->averageFrameQ, instance->lastRecon, instance->postBuffer,
				instance->fragInfo, 4, 1);
			readTicks(&endTicks);
			Rva009AAC80CodecGrid((Rva009AAC80Context *)instance);
		}
		else if (instance->level > 100)
		{
			decodePlane((Rva009A6130Context *)instance->postProcessor, instance->version, instance->frameType,
				instance->level - 100, instance->averageFrameQ, instance->lastRecon, instance->postBuffer,
				instance->fragInfo, 4, 1);
			readTicks(&endTicks);
			Rva009AABB0CodecDispatch((Rva009AABB0Context *)instance);
		}
		else
		{
			decodePlane((Rva009A6130Context *)instance->postProcessor, instance->version, instance->frameType,
				instance->level, instance->averageFrameQ, instance->lastRecon, instance->postBuffer,
				instance->fragInfo, 4, 1);
			readTicks(&endTicks);
		}

		if (instance->blackClamp)
			CLAMP_LEVELS(instance->postProcessor, instance->blackClamp, instance->whiteClamp, instance->postBuffer, instance->postBuffer);
	}

	if (instance->width >= instance->outputWidth && instance->height >= instance->outputHeight)
	{
		config->yWidth = instance->width;
		config->yHeight = instance->height;
		config->yStride = instance->yStride;
		config->uvWidth = instance->width >> 1;
		config->uvHeight = instance->height >> 1;
		config->uvStride = instance->uvStride;

		if (instance->level || (instance->interlaced && instance->deinterlaceMode))
		{
			config->y = instance->postBuffer + instance->reconYOffset + 48 * (instance->yStride + 1);
			config->u = instance->postBuffer + instance->reconUOffset + 24 * (instance->uvStride + 1);
			config->v = instance->postBuffer + instance->reconVOffset + 24 * (instance->uvStride + 1);
			config->yOrigin = instance->postBuffer + instance->reconYOffset;
		}
		else
		{
			config->y = instance->lastRecon + instance->reconYOffset + 48 * (instance->yStride + 1);
			config->u = instance->lastRecon + instance->reconUOffset + 24 * (instance->uvStride + 1);
			config->v = instance->lastRecon + instance->reconVOffset + 24 * (instance->uvStride + 1);
			config->yOrigin = instance->lastRecon + instance->reconYOffset;
		}
	}
	else
	{
		config->yWidth = instance->outputWidth + 32;
		config->yHeight = instance->outputHeight + 32;
		config->yStride = config->yWidth;
		config->uvWidth = config->yWidth / 2;
		config->uvHeight = config->yHeight / 2;
		config->uvStride = config->uvWidth;
		config->y = instance->scaleBuffer;
		config->u = instance->scaleBuffer + config->yWidth * config->yHeight;
		config->v = instance->scaleBuffer + config->yWidth * config->yHeight + config->uvWidth * config->uvHeight;
		config->yOrigin = instance->scaleBuffer;

		if (instance->level)
			Rva009AA8F0Dispatch((Rva009AA8F0Context *)instance->postProcessor, (int)instance->postBuffer, (Rva009AA8F0Block *)config);
		else
			Rva009AA8F0Dispatch((Rva009AA8F0Context *)instance->postProcessor, (int)instance->lastRecon, (Rva009AA8F0Block *)config);

		config->y += ((config->yHeight - instance->outputHeight) >> 1) * config->yStride
			+ ((config->yWidth - instance->outputWidth) >> 1);
		config->yWidth = instance->outputWidth;
		config->yHeight = instance->outputHeight;
		config->u += ((config->uvHeight - (instance->outputHeight >> 1)) >> 1) * config->uvStride
			+ ((config->uvWidth - (instance->outputWidth >> 1)) >> 1);
		config->v += ((config->uvHeight - (instance->outputHeight >> 1)) >> 1) * config->uvStride
			+ ((config->uvWidth - (instance->outputWidth >> 1)) >> 1);
		config->uvWidth = instance->outputWidth >> 1;
		config->uvHeight = instance->outputHeight >> 1;
	}

	g_bfmeToneReady();

	unsigned int duration = (endTicks - startTicks) / instance->processorFrequency;
	if (instance->averagePostTime[instance->level % 10] == 0)
		instance->averagePostTime[instance->level % 10] = duration;
	else
		instance->averagePostTime[instance->level % 10] = (7 * instance->averagePostTime[instance->level % 10] + duration) >> 3;
}
