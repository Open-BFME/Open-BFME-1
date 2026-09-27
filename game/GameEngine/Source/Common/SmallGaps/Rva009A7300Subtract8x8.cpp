// Retail 009A7300: byte pixels minus the existing 16-bit block.
// Four rows per iteration, two iterations for the complete 8x8 block.
void Rva009A7300Subtract8x8(const unsigned char *src, unsigned short *dst, int stride) {
 int groups=2;
 do {
  dst[0]=src[0]-dst[0];
  dst[1]=src[1]-dst[1];
  dst[2]=src[2]-dst[2];
  dst[3]=src[3]-dst[3];
  dst[4]=src[4]-dst[4];
  dst[5]=src[5]-dst[5];
  dst[6]=src[6]-dst[6];
  dst[7]=src[7]-dst[7];
  src+=stride;
  dst[8]=src[0]-dst[8];
  dst[9]=src[1]-dst[9];
  dst[10]=src[2]-dst[10];
  dst[11]=src[3]-dst[11];
  dst[12]=src[4]-dst[12];
  dst[13]=src[5]-dst[13];
  dst[14]=src[6]-dst[14];
  dst[15]=src[7]-dst[15];
  src+=stride;
  dst[16]=src[0]-dst[16];
  dst[17]=src[1]-dst[17];
  dst[18]=src[2]-dst[18];
  dst[19]=src[3]-dst[19];
  dst[20]=src[4]-dst[20];
  dst[21]=src[5]-dst[21];
  dst[22]=src[6]-dst[22];
  dst[23]=src[7]-dst[23];
  src+=stride;
  dst[24]=src[0]-dst[24];
  dst[25]=src[1]-dst[25];
  dst[26]=src[2]-dst[26];
  dst[27]=src[3]-dst[27];
  dst[28]=src[4]-dst[28];
  dst[29]=src[5]-dst[29];
  dst[30]=src[6]-dst[30];
  dst[31]=src[7]-dst[31];
  src+=stride;
  dst+=32;
 } while (--groups);
}
