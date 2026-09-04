// cl: /DNDEBUG /MD
// Retail 0x007AB180: WaterTracksObj constructor.
//
// The retail WaterTracksObj has the standard RenderObj vtable at +0 and the
// BFME water-track payload through +0xb4.  Keep the object byte layout local
// so this isolated constructor does not pull in the still-unmatched siblings.

extern "C" void *bfmeWaterTracksObjVft[];

class WaterTracksObj
{
public:
    WaterTracksObj(void);

private:
    unsigned char m_storage[0xb8];
};

WaterTracksObj::WaterTracksObj(void)
{
    unsigned char *object = m_storage;

    *(void * volatile *)object = bfmeWaterTracksObjVft;
    *(volatile unsigned int *)(object + 0x04) = 0;

    *(volatile unsigned int *)(object + 0x34) = 2;
    *(volatile unsigned int *)(object + 0x38) = 2;
    *(float *)(object + 0x30) = 0.0f;
    *(unsigned char *)(object + 0x3c) = 0;
    *(unsigned int *)(object + 0x68) = 0;
    *(unsigned int *)(object + 0x6c) = 1;

    *(float *)(object + 0x70) = 0.0f;
    *(float *)(object + 0x74) = 0.0f;
    *(float *)(object + 0x78) = 0.0f;
    *(float *)(object + 0x7c) = 0.0f;
    *(float *)(object + 0x80) = 1.0f;
    *(float *)(object + 0x84) = 0.0f;
    *(float *)(object + 0x88) = 1.0f;
    *(float *)(object + 0x8c) = 1.0f;
    *(float *)(object + 0x90) = 0.0f;
    *(float *)(object + 0x94) = 1.0f;
    *(float *)(object + 0x98) = -1.0f;
    *(float *)(object + 0x9c) = 1.0f;
    *(float *)(object + 0xa0) = 1.0f;
    *(float *)(object + 0xa4) = 0.0f;
    *(float *)(object + 0xa8) = 0.0f;
    *(float *)(object + 0xac) = 0.0f;
    *(float *)(object + 0xb0) = 0.0f;
    *(float *)(object + 0xb4) = 0.0f;
}
