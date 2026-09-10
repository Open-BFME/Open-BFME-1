// cl: /O2 /Ob0 /DNDEBUG /MD
// Full retail [009A6DA0,009A6DE3); caller009A6DF0 carries self in ESI.
// The two frees route through009A5980 to matched009A58E0.
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
