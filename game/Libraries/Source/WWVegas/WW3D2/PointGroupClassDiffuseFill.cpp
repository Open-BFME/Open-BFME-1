// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep

// BFME PointGroup diffuse fill, retail RVA 0x00912880 (1124 bytes).
// The matched renderer 0x00917B70+0x279 proves this helper and its ABI.
// pointgr.h omits the split BFME methods; this view uses the existing renderer
// layout through PointMode. See identity_evidence/00912880-pointgroup-color.md.

#include "sharebuf.h"
#include "vector.h"
#include "vector3.h"
#include "vector4.h"
extern VectorClass<Vector4> VertexDiffuse;

class PointGroupClass {
public:
  enum PointModeEnum { TRIS, QUADS, SCREENSPACE };
  void rva00912880(Vector4 *, int);

private:
  virtual void abstract_dtor();
  ShareBufferClass<Vector3> *PointLoc;
  ShareBufferClass<Vector4> *PointDiffuse;
  ShareBufferClass<unsigned int> *APT;
  ShareBufferClass<float> *PointSize;
  ShareBufferClass<unsigned char> *PointOrientation, *PointFrame;
  int PointCount;
  unsigned char FrameRowColumnCountLog2;
  void *dword_24;
  unsigned int dword_28;
  PointModeEnum PointMode;
};
void PointGroupClass::rva00912880(Vector4 *point_diffuse, int active_points) {
  if (point_diffuse) {
    Vector4 *vertex_color = &VertexDiffuse[0];
    if (PointMode != QUADS) {
      for (int i = 0; i < active_points; i++) {
        vertex_color[0] = point_diffuse[0];
        vertex_color[1] = point_diffuse[0];
        vertex_color[2] = point_diffuse[0];
        point_diffuse++;
        vertex_color += 3;
      }
    } else {
      for (int i = 0; i < active_points; i++) {
        vertex_color[0] = point_diffuse[0];
        vertex_color[1] = point_diffuse[0];
        vertex_color[2] = point_diffuse[0];
        vertex_color[3] = point_diffuse[0];
        point_diffuse++;
        vertex_color += 4;
      }
    }
  }
}
