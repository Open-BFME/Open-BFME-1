// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep

// BFME PointGroup UV helper, retail RVA 0x00916CD0 (1453 bytes).
// The matched renderer at 0x00917B70+0x26C proves this split helper and its ABI.
// pointgr.h does not declare the BFME helper; the view follows the already
// matched PointGroupClassRender.cpp and native field accessors.
// The final opaque integer ABI word carries an optional address of four floats.
// No semantic rectangle class is asserted. Evidence:
// targets/game/reverse/identity_evidence/00916cd0-pointgroup-uv.md

#include "sharebuf.h"
#include "vector.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
extern VectorClass<Vector2> VertexUV;

class PointGroupClass {
public:
  enum PointModeEnum { TRIS, QUADS, SCREENSPACE };
  void rva00916CD0(unsigned char *, int, int);

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
  unsigned int Flags;
  float DefaultPointSize;
  Vector3 DefaultPointColor;
  float DefaultPointAlpha;
  unsigned char DefaultPointOrientation, DefaultPointFrame;
  float VPXMin, VPYMin, VPXMax, VPYMax;
  static Vector2 *_TriVertexUVFrameTable[5];
  static Vector2 *_QuadVertexUVFrameTable[5];
};
void PointGroupClass::rva00916CD0(unsigned char *point_frame, int active_points,
                                  int bounds_address) {
  Vector2 *vertex_uv = &VertexUV[0];
  unsigned frame_mask =
      ~(0xFFFFFFFFu << (FrameRowColumnCountLog2 + FrameRowColumnCountLog2));
  if (point_frame) {
    if (PointMode != QUADS) {
      Vector2 *uv_ptr = _TriVertexUVFrameTable[FrameRowColumnCountLog2];
      for (int i = 0; i < active_points; i++) {
        vertex_uv[0] = uv_ptr[0];
        vertex_uv[1] = uv_ptr[1];
        vertex_uv[2] = uv_ptr[2];
        vertex_uv += 3;
      }
    } else {
      Vector2 *uv_ptr = _QuadVertexUVFrameTable[FrameRowColumnCountLog2];
      for (int i = 0; i < active_points; i++) {
        vertex_uv[0] = uv_ptr[0];
        vertex_uv[1] = uv_ptr[1];
        vertex_uv[2] = uv_ptr[2];
        vertex_uv[3] = uv_ptr[3];
        vertex_uv += 4;
      }
    }
  } else {
    if (PointMode != QUADS) {
      Vector2 *uv_ptr = _TriVertexUVFrameTable[FrameRowColumnCountLog2] +
                        ((DefaultPointFrame & frame_mask) * 3);
      if (bounds_address) {
        const float *bounds = (const float *)bounds_address;
        float u0 = bounds[0], v0 = bounds[1], du = bounds[2] - u0,
              dv = bounds[3] - v0;
        for (int j = 0; j < 3; j++) {
          uv_ptr[j].X = u0 + uv_ptr[j].X * du;
          uv_ptr[j].Y = v0 + uv_ptr[j].Y * dv;
        }
      }
      for (int i = 0; i < active_points; i++) {
        vertex_uv[0] = uv_ptr[0];
        vertex_uv[1] = uv_ptr[1];
        vertex_uv[2] = uv_ptr[2];
        vertex_uv += 3;
      }
    } else {
      Vector2 *uv_ptr = _QuadVertexUVFrameTable[FrameRowColumnCountLog2] +
                        ((DefaultPointFrame & frame_mask) * 4);
      if (bounds_address) {
        const float *bounds = (const float *)bounds_address;
        float u0 = bounds[0], v0 = bounds[1], du = bounds[2] - u0,
              dv = bounds[3] - v0;
        for (int j = 0; j < 4; j++) {
          uv_ptr[j].X = u0 + uv_ptr[j].X * du;
          uv_ptr[j].Y = v0 + uv_ptr[j].Y * dv;
        }
      }
      for (int i = 0; i < active_points; i++) {
        vertex_uv[0] = uv_ptr[0];
        vertex_uv[1] = uv_ptr[1];
        vertex_uv[2] = uv_ptr[2];
        vertex_uv[3] = uv_ptr[3];
        vertex_uv += 4;
      }
    }
  }
}
