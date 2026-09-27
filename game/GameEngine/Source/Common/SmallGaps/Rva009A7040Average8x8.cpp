// Retail 009A7040: average two byte planes into an 8x8 16-bit block.
// Four rows per group, with a shared input stride and tightly packed output.
void Rva009A7040Average8x8(const unsigned char *first,const unsigned char *second,unsigned short *dst,int stride) {
 int groups=2;
 do {
  dst[0]=(first[0]+second[0])>>1;
  dst[1]=(first[1]+second[1])>>1;
  dst[2]=(first[2]+second[2])>>1;
  dst[3]=(first[3]+second[3])>>1;
  dst[4]=(first[4]+second[4])>>1;
  dst[5]=(first[5]+second[5])>>1;
  dst[6]=(first[6]+second[6])>>1;
  dst[7]=(first[7]+second[7])>>1;
  first+=stride; second+=stride;
  dst[8]=(first[0]+second[0])>>1;
  dst[9]=(first[1]+second[1])>>1;
  dst[10]=(first[2]+second[2])>>1;
  dst[11]=(first[3]+second[3])>>1;
  dst[12]=(first[4]+second[4])>>1;
  dst[13]=(first[5]+second[5])>>1;
  dst[14]=(first[6]+second[6])>>1;
  dst[15]=(first[7]+second[7])>>1;
  first+=stride; second+=stride;
  dst[16]=(first[0]+second[0])>>1;
  dst[17]=(first[1]+second[1])>>1;
  dst[18]=(first[2]+second[2])>>1;
  dst[19]=(first[3]+second[3])>>1;
  dst[20]=(first[4]+second[4])>>1;
  dst[21]=(first[5]+second[5])>>1;
  dst[22]=(first[6]+second[6])>>1;
  dst[23]=(first[7]+second[7])>>1;
  first+=stride; second+=stride;
  dst[24]=(first[0]+second[0])>>1;
  dst[25]=(first[1]+second[1])>>1;
  dst[26]=(first[2]+second[2])>>1;
  dst[27]=(first[3]+second[3])>>1;
  dst[28]=(first[4]+second[4])>>1;
  dst[29]=(first[5]+second[5])>>1;
  dst[30]=(first[6]+second[6])>>1;
  dst[31]=(first[7]+second[7])>>1;
  first+=stride; second+=stride;
  dst+=32;
 } while (--groups);
}
