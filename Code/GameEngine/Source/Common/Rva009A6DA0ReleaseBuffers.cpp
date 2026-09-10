// cl: /O2 /Ob0 /DNDEBUG /MD
// Codec subobject allocation family. Retail helpers use private ESI (cleanup)
// and EAX (initializer) arguments; static C++ preserves those conventions.
// Full bodies: 009A6DA0/67, 009A6DF0/206, 009A6F20/73.
// The factory is called by matched bfmeInitCodecJX; free routes through
// 009A5980 to matched 009A58E0. Integration entries below are not claimed.
void bfmeTwoBZB(void *what);
struct Rva009A6DA0Buffer {
 unsigned char pad[0x180];
 void *at180; void *at184; void *at188; void *at18C;
};
static void Rva009A6DA0ReleaseBuffers(Rva009A6DA0Buffer *self) {
 if(self->at188) bfmeTwoBZB(self->at188);
 self->at188=0; self->at180=0;
 if(self->at18C) bfmeTwoBZB(self->at18C);
 self->at18C=0; self->at184=0;
}
// Absent-from-retail integration entry; only the private helper is a candidate.
void ReleaseCodecBufferPair(Rva009A6DA0Buffer *self) { Rva009A6DA0ReleaseBuffers(self); }

class Bucket { public: enum BucketMagicEnum { Zero = 0 }; static void *operator new(unsigned int n, BucketMagicEnum m); };
static int Rva009A6DF0InitializeBuffers(Rva009A6DA0Buffer *self) {
 if(self->at188) bfmeTwoBZB(self->at188);
 self->at188=0; self->at180=0;
 if(self->at18C) bfmeTwoBZB(self->at18C);
 self->at18C=0; self->at184=0;
 self->at188=Bucket::operator new(160,Bucket::Zero);
 if(!self->at188) {
 if(self->at188) bfmeTwoBZB(self->at188);
 self->at188=0; self->at180=0;
 if(self->at18C) bfmeTwoBZB(self->at18C);
 self->at18C=0; self->at184=0;
 return 0;
 }
 self->at180=(void*)(((unsigned int)self->at188+31)&~31u);
 self->at18C=Bucket::operator new(160,Bucket::Zero);
 if(!self->at18C){Rva009A6DA0ReleaseBuffers(self);return 0;}
 self->at184=(void*)(((unsigned int)self->at18C+31)&~31u);
 return 1;
}
// Absent-from-retail C++ integration entry for the private initializer.
int InitializeCodecBufferPair(Rva009A6DA0Buffer *self) { return Rva009A6DF0InitializeBuffers(self); }

struct BfmeSubJX : Rva009A6DA0Buffer { unsigned char rest[0x990-sizeof(Rva009A6DA0Buffer)]; };
extern "C" void *__cdecl memset(void *p,int value,unsigned int n);
void Rva009A6EC0Release(void **what);
BfmeSubJX *bfmeMakeSubJX() {
 BfmeSubJX *result=(BfmeSubJX*)Bucket::operator new(0x990,Bucket::Zero);
 BfmeSubJX *self=result;
 if(!result) return 0;
 memset(result,0,0x990);
 if(!Rva009A6DF0InitializeBuffers(result)) { Rva009A6EC0Release((void**)&self); result=self; }
 return result;
}
