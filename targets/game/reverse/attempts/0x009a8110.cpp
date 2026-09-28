// ?Rva009A8110Filter@@YAXPBE0PAEHHH@Z
// partial score=0.705 date=2026-09-28
// cl: /O2 /MD
// INT3-bounded 009A8110..009A840E. Selects horizontal, vertical, or
// two-pass interpolation from the signed distance between source pointers.
extern int Rva00ED7818Weights0[];
extern int Rva00ED781CWeights1[];
void Rva009A7FE0Vp6Filter(const unsigned char*, unsigned short*, int, const int*, const int*);
void Rva009A8110Filter(const unsigned char* first, const unsigned char* second,
                     unsigned char* destination, int pitch, int horizontal, int vertical)
{
    int distance=second-first;
    if(distance<0) { distance=first-second; first=second; }
    if(distance==1) {
        int delta=pitch-8;
        unsigned char* out=destination+2;
        int rows=8;
        do {
            for(int column=-2;column<=5;++column) {
                out[column]=(first[0]*Rva00ED7818Weights0[horizontal*2]+
                             first[1]*Rva00ED781CWeights1[horizontal*2]+64)>>7;
                ++first;
            }
            first+=delta;
            out+=8;
            --rows;
        } while(rows);
    } else if(distance==pitch) {
        unsigned char* out=destination+2;
        int rows=8;
        do {
            for(int column=-2;column<=5;++column) {
                out[column]=(first[0]*Rva00ED7818Weights0[vertical*2]+
                             first[pitch]*Rva00ED781CWeights1[vertical*2]+64)>>7;
                ++first;
            }
            first+=pitch-8;
            out+=8;
            --rows;
        } while(rows);
    } else {
        if(distance==pitch-1) --first;
        else if(distance!=pitch+1) return;
        Rva009A7FE0Vp6Filter(first,(unsigned short*)destination,pitch,
                            &Rva00ED7818Weights0[horizontal*2],&Rva00ED7818Weights0[vertical*2]);
    }
}
