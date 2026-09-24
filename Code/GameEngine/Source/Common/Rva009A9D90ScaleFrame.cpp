// VPx three-plane frame scale, retail [0x009A9D90,0x009AA0F1).
// Calls the matched Scale2D body (0x009A9AD0) once per plane with the
// destination size rounded up from the scale ratios, then replicates the last
// written column into the unscaled right margin and the last written row
// into the unscaled bottom margin of each destination plane. The frame
// descriptor offsets are the retail loads: widths, heights and strides at
// +0x00..+0x14, plane pointers at +0x18..+0x20. The buffers are read with
// movsx, so the plane pointers are plain char. The owner is not proven, so
// the names keep the address token.

extern "C" void * __cdecl memcpy(void *, const void *, unsigned int);
extern "C" void * __cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memcpy, memset)

typedef unsigned char Byte;

void Rva009A9AD0Scale2D(
	Byte *source, int sourcePitch, unsigned int sourceWidth, unsigned int sourceHeight,
	Byte *dest, int destPitch, unsigned int destWidth, unsigned int destHeight,
	Byte *tempArea, Byte tempAreaHeight,
	unsigned int hscale, unsigned int hratio, unsigned int vscale, unsigned int vratio,
	unsigned int interlaced);

struct Rva009A9D90Frame
{
	int m_yWidth;       // 0x00
	int m_yHeight;      // 0x04
	int m_yStride;      // 0x08
	int m_uvWidth;      // 0x0c
	int m_uvHeight;     // 0x10
	int m_uvStride;     // 0x14
	char *m_yBuffer;    // 0x18
	char *m_uBuffer;    // 0x1c
	char *m_vBuffer;    // 0x20
};

void Rva009A9D90ScaleFrame(
	Rva009A9D90Frame *src,
	Rva009A9D90Frame *dst,
	Byte *tempArea,
	Byte tempHeight,
	unsigned int hscale,
	unsigned int hratio,
	unsigned int vscale,
	unsigned int vratio,
	unsigned int interlaced)
{
	int i;
	int dw = (hscale - 1 + src->m_yWidth * hratio) / hscale;
	int dh = (vscale - 1 + src->m_yHeight * vratio) / vscale;

	Rva009A9AD0Scale2D((Byte *)src->m_yBuffer, src->m_yStride, src->m_yWidth, src->m_yHeight,
		(Byte *)dst->m_yBuffer, dst->m_yStride, dw, dh,
		tempArea, tempHeight, hscale, hratio, vscale, vratio, interlaced);

	if (dw < dst->m_yWidth)
		for (i = 0; i < dh; ++i)
			memset(dst->m_yBuffer + i * dst->m_yStride + dw - 1,
				dst->m_yBuffer[i * dst->m_yStride + dw - 2],
				dst->m_yWidth - dw + 1);

	if (dh < dst->m_yHeight)
		for (i = dh - 1; i < dst->m_yHeight; ++i)
			memcpy(dst->m_yBuffer + i * dst->m_yStride,
				dst->m_yBuffer + (dh - 2) * dst->m_yStride,
				dst->m_yWidth + 1);

	Rva009A9AD0Scale2D((Byte *)src->m_uBuffer, src->m_uvStride, src->m_uvWidth, src->m_uvHeight,
		(Byte *)dst->m_uBuffer, dst->m_uvStride, dw / 2, dh / 2,
		tempArea, tempHeight, hscale, hratio, vscale, vratio, interlaced);

	if (dw / 2 < dst->m_uvWidth)
		for (i = 0; i < dst->m_uvHeight; ++i)
			memset(dst->m_uBuffer + i * dst->m_uvStride + dw / 2 - 1,
				dst->m_uBuffer[i * dst->m_uvStride + dw / 2 - 2],
				dst->m_uvWidth - dw / 2 + 1);

	if (dh / 2 < dst->m_uvHeight)
		for (i = dh / 2 - 1; i < dst->m_yHeight / 2; ++i)
			memcpy(dst->m_uBuffer + i * dst->m_uvStride,
				dst->m_uBuffer + (dh / 2 - 2) * dst->m_uvStride,
				dst->m_uvWidth);

	Rva009A9AD0Scale2D((Byte *)src->m_vBuffer, src->m_uvStride, src->m_uvWidth, src->m_uvHeight,
		(Byte *)dst->m_vBuffer, dst->m_uvStride, dw / 2, dh / 2,
		tempArea, tempHeight, hscale, hratio, vscale, vratio, interlaced);

	if (dw / 2 < dst->m_uvWidth)
		for (i = 0; i < dst->m_uvHeight; ++i)
			memset(dst->m_vBuffer + i * dst->m_uvStride + dw / 2 - 1,
				dst->m_vBuffer[i * dst->m_uvStride + dw / 2 - 2],
				dst->m_uvWidth - dw / 2 + 1);

	if (dh / 2 < dst->m_uvHeight)
		for (i = dh / 2 - 1; i < dst->m_yHeight / 2; ++i)
			memcpy(dst->m_vBuffer + i * dst->m_uvStride,
				dst->m_vBuffer + (dh / 2 - 2) * dst->m_uvStride,
				dst->m_uvWidth);
}
