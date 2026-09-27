// Retail 009A74D0 copies eight rows of two dwords with one shared byte stride.
void Rva009A74D0Copy8x8(const unsigned char *src, unsigned char *dst, int stride) {
 for (int row=0; row<8; ++row) {
  ((unsigned int*)dst)[0] = ((const unsigned int*)src)[0];
  ((unsigned int*)dst)[1] = ((const unsigned int*)src)[1];
  src += stride;
  dst += stride;
 }
}
// Independent function following two INT3 bytes at 009A755E.
void Rva009A7560Copy12x12(const unsigned char *src, unsigned char *dst, int srcStride, int dstStride) {
 dst += 2; src += 2;
 int rows = 12;
 do {
  dst[-2]=src[-2];
  dst[-1]=src[-1];
  dst[0]=src[0];
  dst[1]=src[1];
  dst[2]=src[2];
  dst[3]=src[3];
  dst[4]=src[4];
  dst[5]=src[5];
  dst[6]=src[6];
  dst[7]=src[7];
  dst[8]=src[8];
  dst[9]=src[9];
  src += srcStride; dst += dstStride;
 } while (--rows);
}

