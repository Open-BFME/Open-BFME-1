// Retail 0x00205A20 (126 B). Receiver +4 supplies range (+8) and scale (+0xC).
// The source and destination positions are proven by the retail accesses;
// the original method spelling is unproved, so the identity retains its RVA.
// Scalar component copies preserve retail x87 evaluation and rounding order.
extern "C" double sqrt(double);
#pragma intrinsic(sqrt)
extern float g_bfmeDefaultBU;
extern const float BfmeZeroRange;
struct Rva00205A20Pos { float x,y,z; };
struct Rva00205A20Thing { char pad[0x38]; Rva00205A20Pos pos; };
struct Rva00205A20Info { char pad[8]; float range,scale; };
struct Rva00205A20Owner {
 void *vptr; Rva00205A20Info *info;
 float method(const Rva00205A20Pos *, const Rva00205A20Thing *) const;
};
float Rva00205A20Owner::method(const Rva00205A20Pos *from, const Rva00205A20Thing *to) const {
 if (info->scale == 1.0f) {
  Rva00205A20Pos delta;
  delta.x = to->pos.x;
  delta.y = to->pos.y;
  delta.z = to->pos.z;
  delta.x -= from->x;
  delta.y -= from->y;
  delta.z -= from->z;
  float value = g_bfmeDefaultBU - (float)sqrt(delta.z*delta.z + delta.y*delta.y + delta.x*delta.x)/info->range;
  if (!(value >= BfmeZeroRange)) return BfmeZeroRange;
  return value;
 }
 return g_bfmeDefaultBU;
}
