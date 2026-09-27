// cl: /DNDEBUG /MD /EHsc
// 0x00403EC0: sixteen 0x44-byte layers; full RET 4 ends at 0x00403FC4.
class BfmeTableAD { public: void bfmeFillAD(int); };
class PathfindLayer { public: bool isUsed(); };
struct Point403EC0 { int x,y; };
struct LayerRecord403EC0 {
 char head[0x18];
 Point403EC0 first,second;
 char gap28[0xc]; bool flag34;
 char tail35[0xf];
};
struct ZoneCell403EC0 { char head[0x224]; bool marked; char tail[3]; };
class ZoneLayers403EC0 {
 char head[0x23298]; int serial23298;
 char gap2329c[0x38c]; ZoneCell403EC0 **columns23628;
 int width2362c,height23630;
 void mark(int y,int x) {
  if (x<0 || y<0) return;
  int cx=x/16,cy=y/16;
  if (cx>=width2362c || cy>=height23630) return;
  columns23628[cx][cy].marked=true;
 }
public:
 void update(LayerRecord403EC0 *layer);
};
void ZoneLayers403EC0::update(LayerRecord403EC0 *layer)
{
 for (int i=0;i<16;++i) {
  LayerRecord403EC0 *record=&layer[i];
  ((BfmeTableAD *)record)->bfmeFillAD(serial23298++);
  if (((PathfindLayer *)record)->isUsed() && !record->flag34) {
   mark(record->first.y,record->first.x);
   mark(record->second.y,record->second.x);
  }
 }
}

