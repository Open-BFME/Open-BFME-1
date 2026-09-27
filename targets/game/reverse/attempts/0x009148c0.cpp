// ?d_009148c0@@YAXXZ
// partial score=0.5866796200345423 date=2026-09-27
// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep

// Bank: BFME PointGroup position fill; 0x009148C0, 9232 bytes.
// Matched PointGroupClass::Render (0x00917B70+0x25A) proves the receiver and
// four-argument ABI. See identity_evidence/009148c0-geometry-recovery.md.
// Native reconstruction; remaining differences are cursor/register lifetimes,
// screen table setup ordering, and x87 evaluation. This is not a matched body.

#define Matrix4x4 Matrix4
#include "sharebuf.h"
#include "vector.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "matrix4.h"
#include "dx8wrapper.h"
#include "ww3d.h"
extern VectorClass<Vector3> VertexLoc;
extern Vector3 GroundMultiplierX, GroundMultiplierY;
class PointGroupClass {
public:
  enum PointModeEnum { TRIS, QUADS, SCREENSPACE };
  enum FlagsType { TRANSFORM, BILLBOARD };
  int Get_Flag(FlagsType f) { return (Flags >> f) & 1; }
  void rva009148C0(Vector3 *, float *, unsigned char *, int);

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
  static Vector3 _TriVertexLocationOrientationTable[256][3];
  static Vector3 _QuadVertexLocationOrientationTable[256][4];
  static Vector3 _ScreenspaceVertexLocationSizeTable[2][3];
};
void PointGroupClass::rva009148C0(Vector3 *point_loc, float *point_size,
                                  unsigned char *point_orientation,
                                  int active_points) {
  int i;

  /*
	** Generate the vertex locations from the point locations (note that both are in camera space).
	** Vertex locations depend on the point mode and the points' orientation and size
	*/

  // This defines the loop we run: the LSB indicates whether there is a size override array, the
  // next bit indicates whether there is an orientation override array, and the higher bits
  // indicate the point mode.
  enum LoopSelectionEnum {
    TRIS_NOSIZE_NOORIENT = ((int)TRIS << 2) + 0,
    TRIS_SIZE_NOORIENT = ((int)TRIS << 2) + 1,
    TRIS_NOSIZE_ORIENT = ((int)TRIS << 2) + 2,
    TRIS_SIZE_ORIENT = ((int)TRIS << 2) + 3,
    QUADS_NOSIZE_NOORIENT = ((int)QUADS << 2) + 0,
    QUADS_SIZE_NOORIENT = ((int)QUADS << 2) + 1,
    QUADS_NOSIZE_ORIENT = ((int)QUADS << 2) + 2,
    QUADS_SIZE_ORIENT = ((int)QUADS << 2) + 3,
    SCREEN_NOSIZE_NOORIENT = ((int)SCREENSPACE << 2) + 0,
    SCREEN_SIZE_NOORIENT = ((int)SCREENSPACE << 2) + 1,
    SCREEN_NOSIZE_ORIENT = ((int)SCREENSPACE << 2) + 2,
    SCREEN_SIZE_ORIENT = ((int)SCREENSPACE << 2) + 3,
  };
  LoopSelectionEnum loop_sel =
      (LoopSelectionEnum)(((int)PointMode << 2) + (point_orientation ? 2 : 0) +
                          (point_size ? 1 : 0));

  Vector3 *vertex_base = &VertexLoc[0];
  Vector3 *vertex_loc = vertex_base;

  switch (loop_sel) {

  case TRIS_NOSIZE_NOORIENT: {
    // Setup constant vertex offsets (since size and orientation are invariants)
    Vector3 scaled_offset[3];
    scaled_offset[0] =
        _TriVertexLocationOrientationTable[DefaultPointOrientation][0] *
        DefaultPointSize;
    scaled_offset[1] =
        _TriVertexLocationOrientationTable[DefaultPointOrientation][1] *
        DefaultPointSize;
    scaled_offset[2] =
        _TriVertexLocationOrientationTable[DefaultPointOrientation][2] *
        DefaultPointSize;

    // Add vertex offsets to point locations to get vertex locations
    for (i = 0; i < active_points; i++) {
      vertex_loc[0].X = point_loc[0].X + scaled_offset[0].X;
      vertex_loc[0].Y = point_loc[0].Y + scaled_offset[0].Y;
      vertex_loc[0].Z = point_loc[0].Z + scaled_offset[0].Z;
      vertex_loc[1].X = point_loc[0].X + scaled_offset[1].X;
      vertex_loc[1].Y = point_loc[0].Y + scaled_offset[1].Y;
      vertex_loc[1].Z = point_loc[0].Z + scaled_offset[1].Z;
      vertex_loc[2].X = point_loc[0].X + scaled_offset[2].X;
      vertex_loc[2].Y = point_loc[0].Y + scaled_offset[2].Y;
      vertex_loc[2].Z = point_loc[0].Z + scaled_offset[2].Z;
      point_loc++;
      vertex_loc += 3;
    }
  } break;

  case TRIS_SIZE_NOORIENT: {
    // Scale vertex offsets and add them to point locations to get vertex locations
    for (i = 0; i < active_points; i++) {
      vertex_loc[0].X =
          point_loc[0].X +
          _TriVertexLocationOrientationTable[DefaultPointOrientation][0].X *
              (*point_size);
      vertex_loc[0].Y =
          point_loc[0].Y +
          _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Y *
              (*point_size);
      vertex_loc[0].Z =
          point_loc[0].Z +
          _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Z *
              (*point_size);
      vertex_loc[1].X =
          point_loc[0].X +
          _TriVertexLocationOrientationTable[DefaultPointOrientation][1].X *
              (*point_size);
      vertex_loc[1].Y =
          point_loc[0].Y +
          _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Y *
              (*point_size);
      vertex_loc[1].Z =
          point_loc[0].Z +
          _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Z *
              (*point_size);
      vertex_loc[2].X =
          point_loc[0].X +
          _TriVertexLocationOrientationTable[DefaultPointOrientation][2].X *
              (*point_size);
      vertex_loc[2].Y =
          point_loc[0].Y +
          _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Y *
              (*point_size);
      vertex_loc[2].Z =
          point_loc[0].Z +
          _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Z *
              (*point_size);
      point_loc++;
      vertex_loc += 3;
      point_size++;
    }
  } break;

  case TRIS_NOSIZE_ORIENT: {
    // Scale vertex offsets and add them to point locations to get vertex locations
    for (i = 0; i < active_points; i++) {
      vertex_loc[0].X =
          point_loc[0].X +
          _TriVertexLocationOrientationTable[(*point_orientation)][0].X *
              DefaultPointSize;
      vertex_loc[0].Y =
          point_loc[0].Y +
          _TriVertexLocationOrientationTable[(*point_orientation)][0].Y *
              DefaultPointSize;
      vertex_loc[0].Z =
          point_loc[0].Z +
          _TriVertexLocationOrientationTable[(*point_orientation)][0].Z *
              DefaultPointSize;
      vertex_loc[1].X =
          point_loc[0].X +
          _TriVertexLocationOrientationTable[(*point_orientation)][1].X *
              DefaultPointSize;
      vertex_loc[1].Y =
          point_loc[0].Y +
          _TriVertexLocationOrientationTable[(*point_orientation)][1].Y *
              DefaultPointSize;
      vertex_loc[1].Z =
          point_loc[0].Z +
          _TriVertexLocationOrientationTable[(*point_orientation)][1].Z *
              DefaultPointSize;
      vertex_loc[2].X =
          point_loc[0].X +
          _TriVertexLocationOrientationTable[(*point_orientation)][2].X *
              DefaultPointSize;
      vertex_loc[2].Y =
          point_loc[0].Y +
          _TriVertexLocationOrientationTable[(*point_orientation)][2].Y *
              DefaultPointSize;
      vertex_loc[2].Z =
          point_loc[0].Z +
          _TriVertexLocationOrientationTable[(*point_orientation)][2].Z *
              DefaultPointSize;
      point_loc++;
      vertex_loc += 3;
      point_orientation++;
    }
  } break;

  case TRIS_SIZE_ORIENT: {
    // Scale vertex offsets and add them to point locations to get vertex locations
    for (i = 0; i < active_points; i++) {
      vertex_loc[0].X =
          point_loc[0].X +
          _TriVertexLocationOrientationTable[(*point_orientation)][0].X *
              (*point_size);
      vertex_loc[0].Y =
          point_loc[0].Y +
          _TriVertexLocationOrientationTable[(*point_orientation)][0].Y *
              (*point_size);
      vertex_loc[0].Z =
          point_loc[0].Z +
          _TriVertexLocationOrientationTable[(*point_orientation)][0].Z *
              (*point_size);
      vertex_loc[1].X =
          point_loc[0].X +
          _TriVertexLocationOrientationTable[(*point_orientation)][1].X *
              (*point_size);
      vertex_loc[1].Y =
          point_loc[0].Y +
          _TriVertexLocationOrientationTable[(*point_orientation)][1].Y *
              (*point_size);
      vertex_loc[1].Z =
          point_loc[0].Z +
          _TriVertexLocationOrientationTable[(*point_orientation)][1].Z *
              (*point_size);
      vertex_loc[2].X =
          point_loc[0].X +
          _TriVertexLocationOrientationTable[(*point_orientation)][2].X *
              (*point_size);
      vertex_loc[2].Y =
          point_loc[0].Y +
          _TriVertexLocationOrientationTable[(*point_orientation)][2].Y *
              (*point_size);
      vertex_loc[2].Z =
          point_loc[0].Z +
          _TriVertexLocationOrientationTable[(*point_orientation)][2].Z *
              (*point_size);
      point_loc++;
      vertex_loc += 3;
      point_size++;
      point_orientation++;
    }
  } break;

  case QUADS_NOSIZE_NOORIENT: {
    // Setup constant vertex offsets (since size and orientation are invariants)
    Vector3 scaled_offset[4];
    scaled_offset[0] =
        _QuadVertexLocationOrientationTable[DefaultPointOrientation][0] *
        DefaultPointSize;
    scaled_offset[1] =
        _QuadVertexLocationOrientationTable[DefaultPointOrientation][1] *
        DefaultPointSize;
    scaled_offset[2] =
        _QuadVertexLocationOrientationTable[DefaultPointOrientation][2] *
        DefaultPointSize;
    scaled_offset[3] =
        _QuadVertexLocationOrientationTable[DefaultPointOrientation][3] *
        DefaultPointSize;

    // Add vertex offsets to point locations to get vertex locations
    for (i = 0; i < active_points; i++) {
      vertex_loc[0].X = point_loc[0].X + scaled_offset[0].X;
      vertex_loc[0].Y = point_loc[0].Y + scaled_offset[0].Y;
      vertex_loc[0].Z = point_loc[0].Z + scaled_offset[0].Z;
      vertex_loc[1].X = point_loc[0].X + scaled_offset[1].X;
      vertex_loc[1].Y = point_loc[0].Y + scaled_offset[1].Y;
      vertex_loc[1].Z = point_loc[0].Z + scaled_offset[1].Z;
      vertex_loc[2].X = point_loc[0].X + scaled_offset[2].X;
      vertex_loc[2].Y = point_loc[0].Y + scaled_offset[2].Y;
      vertex_loc[2].Z = point_loc[0].Z + scaled_offset[2].Z;
      vertex_loc[3].X = point_loc[0].X + scaled_offset[3].X;
      vertex_loc[3].Y = point_loc[0].Y + scaled_offset[3].Y;
      vertex_loc[3].Z = point_loc[0].Z + scaled_offset[3].Z;
      point_loc++;
      vertex_loc += 4;
    }
  } break;

  case QUADS_SIZE_NOORIENT: {
    Vector3 *vertex_loc = vertex_base;
    // Scale vertex offsets and add them to point locations to get vertex locations
    for (i = 0; i < active_points; i++) {
      vertex_loc[0].X =
          point_loc[0].X +
          _QuadVertexLocationOrientationTable[DefaultPointOrientation][0].X *
              (*point_size);
      vertex_loc[0].Y =
          point_loc[0].Y +
          _QuadVertexLocationOrientationTable[DefaultPointOrientation][0].Y *
              (*point_size);
      vertex_loc[0].Z =
          point_loc[0].Z +
          _QuadVertexLocationOrientationTable[DefaultPointOrientation][0].Z *
              (*point_size);
      vertex_loc[1].X =
          point_loc[0].X +
          _QuadVertexLocationOrientationTable[DefaultPointOrientation][1].X *
              (*point_size);
      vertex_loc[1].Y =
          point_loc[0].Y +
          _QuadVertexLocationOrientationTable[DefaultPointOrientation][1].Y *
              (*point_size);
      vertex_loc[1].Z =
          point_loc[0].Z +
          _QuadVertexLocationOrientationTable[DefaultPointOrientation][1].Z *
              (*point_size);
      vertex_loc[2].X =
          point_loc[0].X +
          _QuadVertexLocationOrientationTable[DefaultPointOrientation][2].X *
              (*point_size);
      vertex_loc[2].Y =
          point_loc[0].Y +
          _QuadVertexLocationOrientationTable[DefaultPointOrientation][2].Y *
              (*point_size);
      vertex_loc[2].Z =
          point_loc[0].Z +
          _QuadVertexLocationOrientationTable[DefaultPointOrientation][2].Z *
              (*point_size);
      vertex_loc[3].X =
          point_loc[0].X +
          _QuadVertexLocationOrientationTable[DefaultPointOrientation][3].X *
              (*point_size);
      vertex_loc[3].Y =
          point_loc[0].Y +
          _QuadVertexLocationOrientationTable[DefaultPointOrientation][3].Y *
              (*point_size);
      vertex_loc[3].Z =
          point_loc[0].Z +
          _QuadVertexLocationOrientationTable[DefaultPointOrientation][3].Z *
              (*point_size);
      point_loc++;
      vertex_loc += 4;
      point_size++;
    }
  } break;

  case QUADS_NOSIZE_ORIENT: {
    Vector3 *vertex_loc = vertex_base;
    // Scale vertex offsets and add them to point locations to get vertex locations
    for (i = 0; i < active_points; i++) {
      vertex_loc[0].X =
          point_loc[0].X +
          _QuadVertexLocationOrientationTable[(*point_orientation)][0].X *
              DefaultPointSize;
      vertex_loc[0].Y =
          point_loc[0].Y +
          _QuadVertexLocationOrientationTable[(*point_orientation)][0].Y *
              DefaultPointSize;
      vertex_loc[0].Z =
          point_loc[0].Z +
          _QuadVertexLocationOrientationTable[(*point_orientation)][0].Z *
              DefaultPointSize;
      vertex_loc[1].X =
          point_loc[0].X +
          _QuadVertexLocationOrientationTable[(*point_orientation)][1].X *
              DefaultPointSize;
      vertex_loc[1].Y =
          point_loc[0].Y +
          _QuadVertexLocationOrientationTable[(*point_orientation)][1].Y *
              DefaultPointSize;
      vertex_loc[1].Z =
          point_loc[0].Z +
          _QuadVertexLocationOrientationTable[(*point_orientation)][1].Z *
              DefaultPointSize;
      vertex_loc[2].X =
          point_loc[0].X +
          _QuadVertexLocationOrientationTable[(*point_orientation)][2].X *
              DefaultPointSize;
      vertex_loc[2].Y =
          point_loc[0].Y +
          _QuadVertexLocationOrientationTable[(*point_orientation)][2].Y *
              DefaultPointSize;
      vertex_loc[2].Z =
          point_loc[0].Z +
          _QuadVertexLocationOrientationTable[(*point_orientation)][2].Z *
              DefaultPointSize;
      vertex_loc[3].X =
          point_loc[0].X +
          _QuadVertexLocationOrientationTable[(*point_orientation)][3].X *
              DefaultPointSize;
      vertex_loc[3].Y =
          point_loc[0].Y +
          _QuadVertexLocationOrientationTable[(*point_orientation)][3].Y *
              DefaultPointSize;
      vertex_loc[3].Z =
          point_loc[0].Z +
          _QuadVertexLocationOrientationTable[(*point_orientation)][3].Z *
              DefaultPointSize;
      point_loc++;
      vertex_loc += 4;
      point_orientation++;
    }
  } break;

  case QUADS_SIZE_ORIENT: {
    Vector3 *vertex_loc = vertex_base;
    if (!Get_Flag(BILLBOARD)) {
      Matrix4x4 view;
      Vector4 result;
      DX8Wrapper::Get_Transform(D3DTS_VIEW, view);
      for (i = 0; i < active_points; i++) {

        // If we're not billboarding, then the coordinate we have is in screen space.
        Matrix4x4 rotMat;
        D3DXMatrixRotationZ(
            &(D3DXMATRIX &)rotMat,
            ((float)(*point_orientation) / 255.0f * 2 * D3DX_PI));

        Vector4 orientedVecX = rotMat * GroundMultiplierX;
        Vector4 orientedVecY = rotMat * GroundMultiplierY;

        float sum_x = (orientedVecX.X + orientedVecY.X) * (*point_size);
        float sum_y = (orientedVecX.Y + orientedVecY.Y) * (*point_size);
        float difference_x = (orientedVecX.X - orientedVecY.X) * (*point_size);
        float difference_y = (orientedVecX.Y - orientedVecY.Y) * (*point_size);
        vertex_loc[0].X = point_loc[0].X + sum_x;
        vertex_loc[0].Y = point_loc[0].Y + sum_y;
        vertex_loc[0].Z = point_loc[0].Z;
        vertex_loc[1].X = point_loc[0].X + difference_x;
        vertex_loc[1].Y = point_loc[0].Y + difference_y;
        vertex_loc[1].Z = point_loc[0].Z;
        vertex_loc[2].X = point_loc[0].X - sum_x;
        vertex_loc[2].Y = point_loc[0].Y - sum_y;
        vertex_loc[2].Z = point_loc[0].Z;
        vertex_loc[3].X = point_loc[0].X - difference_x;
        vertex_loc[3].Y = point_loc[0].Y - difference_y;
        vertex_loc[3].Z = point_loc[0].Z;
        // now apply the view transform so that this data is in the format expected
        // upon the functions return.
        result = view * vertex_loc[0];
        vertex_loc[0].X = result.X;
        vertex_loc[0].Y = result.Y;
        vertex_loc[0].Z = result.Z;

        result = view * vertex_loc[1];
        vertex_loc[1].X = result.X;
        vertex_loc[1].Y = result.Y;
        vertex_loc[1].Z = result.Z;

        result = view * vertex_loc[2];
        vertex_loc[2].X = result.X;
        vertex_loc[2].Y = result.Y;
        vertex_loc[2].Z = result.Z;

        result = view * vertex_loc[3];
        vertex_loc[3].X = result.X;
        vertex_loc[3].Y = result.Y;
        vertex_loc[3].Z = result.Z;

        point_loc++;
        vertex_loc += 4;
        point_size++;
        point_orientation++;
      }
    } else {
      for (i = 0; i < active_points; i++) {

        vertex_loc[0].X =
            point_loc[0].X +
            _QuadVertexLocationOrientationTable[(*point_orientation)][0].X *
                (*point_size);
        vertex_loc[0].Y =
            point_loc[0].Y +
            _QuadVertexLocationOrientationTable[(*point_orientation)][0].Y *
                (*point_size);
        vertex_loc[0].Z =
            point_loc[0].Z +
            _QuadVertexLocationOrientationTable[(*point_orientation)][0].Z *
                (*point_size);
        vertex_loc[1].X =
            point_loc[0].X +
            _QuadVertexLocationOrientationTable[(*point_orientation)][1].X *
                (*point_size);
        vertex_loc[1].Y =
            point_loc[0].Y +
            _QuadVertexLocationOrientationTable[(*point_orientation)][1].Y *
                (*point_size);
        vertex_loc[1].Z =
            point_loc[0].Z +
            _QuadVertexLocationOrientationTable[(*point_orientation)][1].Z *
                (*point_size);
        vertex_loc[2].X =
            point_loc[0].X +
            _QuadVertexLocationOrientationTable[(*point_orientation)][2].X *
                (*point_size);
        vertex_loc[2].Y =
            point_loc[0].Y +
            _QuadVertexLocationOrientationTable[(*point_orientation)][2].Y *
                (*point_size);
        vertex_loc[2].Z =
            point_loc[0].Z +
            _QuadVertexLocationOrientationTable[(*point_orientation)][2].Z *
                (*point_size);
        vertex_loc[3].X =
            point_loc[0].X +
            _QuadVertexLocationOrientationTable[(*point_orientation)][3].X *
                (*point_size);
        vertex_loc[3].Y =
            point_loc[0].Y +
            _QuadVertexLocationOrientationTable[(*point_orientation)][3].Y *
                (*point_size);
        vertex_loc[3].Z =
            point_loc[0].Z +
            _QuadVertexLocationOrientationTable[(*point_orientation)][3].Z *
                (*point_size);

        point_loc++;
        vertex_loc += 4;
        point_size++;
        point_orientation++;
      }
    }
  } break;
    // Orientations are ignored for screensize pointgroups
  case SCREEN_NOSIZE_NOORIENT:
  case SCREEN_NOSIZE_ORIENT: {
    // Offsets need to be scaled to the current screen resolution

    // First find x and y scale factors (sizes in pixels need to be
    // normalized to 2D cam viewplane of -1,-1 to 1,1)
    int xres, yres, bitdepth;
    bool windowed;
    WW3D::Get_Render_Target_Resolution(xres, yres, bitdepth, windowed);

    float x_scale = (VPXMax - VPXMin) / xres;
    float y_scale = (VPYMax - VPYMin) / yres;

    int size_idx = (DefaultPointSize <= 1.0f) ? 0 : 1;
    Vector3 scaled_locs[3];
    scaled_locs[0].X =
        _ScreenspaceVertexLocationSizeTable[size_idx][0].X * x_scale;
    scaled_locs[0].Y =
        _ScreenspaceVertexLocationSizeTable[size_idx][0].Y * y_scale;
    scaled_locs[0].Z = _ScreenspaceVertexLocationSizeTable[size_idx][0].Z;
    scaled_locs[1].X =
        _ScreenspaceVertexLocationSizeTable[size_idx][1].X * x_scale;
    scaled_locs[1].Y =
        _ScreenspaceVertexLocationSizeTable[size_idx][1].Y * y_scale;
    scaled_locs[1].Z = _ScreenspaceVertexLocationSizeTable[size_idx][1].Z;
    scaled_locs[2].X =
        _ScreenspaceVertexLocationSizeTable[size_idx][2].X * x_scale;
    scaled_locs[2].Y =
        _ScreenspaceVertexLocationSizeTable[size_idx][2].Y * y_scale;
    scaled_locs[2].Z = _ScreenspaceVertexLocationSizeTable[size_idx][2].Z;
    // Add vertex offsets to point locations to get vertex locations

    for (i = 0; i < active_points; i++) {
      vertex_loc[0].X = point_loc[0].X + scaled_locs[0].X;
      vertex_loc[0].Y = point_loc[0].Y + scaled_locs[0].Y;
      vertex_loc[0].Z = point_loc[0].Z + scaled_locs[0].Z;
      vertex_loc[1].X = point_loc[0].X + scaled_locs[1].X;
      vertex_loc[1].Y = point_loc[0].Y + scaled_locs[1].Y;
      vertex_loc[1].Z = point_loc[0].Z + scaled_locs[1].Z;
      vertex_loc[2].X = point_loc[0].X + scaled_locs[2].X;
      vertex_loc[2].Y = point_loc[0].Y + scaled_locs[2].Y;
      vertex_loc[2].Z = point_loc[0].Z + scaled_locs[2].Z;
      point_loc++;
      vertex_loc += 3;
    }
  } break;

  case SCREEN_SIZE_NOORIENT:
  case SCREEN_SIZE_ORIENT: {
    // Offsets need to be scaled to the current screen resolution

    // First find x and y scale factors (sizes in pixels need to be
    // normalized to 2D cam viewplane of -1,-1 to 1,1)
    int xres, yres, bitdepth;
    bool windowed;
    WW3D::Get_Render_Target_Resolution(xres, yres, bitdepth, windowed);

    float x_scale = (VPXMax - VPXMin) / xres;
    float y_scale = (VPYMax - VPYMin) / yres;

    Vector3 scaled_locs[2][3];
    scaled_locs[0][0].X = _ScreenspaceVertexLocationSizeTable[0][0].X * x_scale;
    scaled_locs[0][0].Y = _ScreenspaceVertexLocationSizeTable[0][0].Y * y_scale;
    scaled_locs[0][0].Z = _ScreenspaceVertexLocationSizeTable[0][0].Z;
    scaled_locs[0][1].X = _ScreenspaceVertexLocationSizeTable[0][1].X * x_scale;
    scaled_locs[0][1].Y = _ScreenspaceVertexLocationSizeTable[0][1].Y * y_scale;
    scaled_locs[0][1].Z = _ScreenspaceVertexLocationSizeTable[0][1].Z;
    scaled_locs[0][2].X = _ScreenspaceVertexLocationSizeTable[0][2].X * x_scale;
    scaled_locs[0][2].Y = _ScreenspaceVertexLocationSizeTable[0][2].Y * y_scale;
    scaled_locs[0][2].Z = _ScreenspaceVertexLocationSizeTable[0][2].Z;
    scaled_locs[1][0].X = _ScreenspaceVertexLocationSizeTable[1][0].X * x_scale;
    scaled_locs[1][0].Y = _ScreenspaceVertexLocationSizeTable[1][0].Y * y_scale;
    scaled_locs[1][0].Z = _ScreenspaceVertexLocationSizeTable[1][0].Z;
    scaled_locs[1][1].X = _ScreenspaceVertexLocationSizeTable[1][1].X * x_scale;
    scaled_locs[1][1].Y = _ScreenspaceVertexLocationSizeTable[1][1].Y * y_scale;
    scaled_locs[1][1].Z = _ScreenspaceVertexLocationSizeTable[1][1].Z;
    scaled_locs[1][2].X = _ScreenspaceVertexLocationSizeTable[1][2].X * x_scale;
    scaled_locs[1][2].Y = _ScreenspaceVertexLocationSizeTable[1][2].Y * y_scale;
    scaled_locs[1][2].Z = _ScreenspaceVertexLocationSizeTable[1][2].Z;

    // Add vertex offsets to point locations to get vertex locations
    for (i = 0; i < active_points; i++) {
      int size_idx = ((*point_size) <= 1.0f) ? 0 : 1;
      vertex_loc[0].X = point_loc[0].X + scaled_locs[size_idx][0].X;
      vertex_loc[0].Y = point_loc[0].Y + scaled_locs[size_idx][0].Y;
      vertex_loc[0].Z = point_loc[0].Z + scaled_locs[size_idx][0].Z;
      vertex_loc[1].X = point_loc[0].X + scaled_locs[size_idx][1].X;
      vertex_loc[1].Y = point_loc[0].Y + scaled_locs[size_idx][1].Y;
      vertex_loc[1].Z = point_loc[0].Z + scaled_locs[size_idx][1].Z;
      vertex_loc[2].X = point_loc[0].X + scaled_locs[size_idx][2].X;
      vertex_loc[2].Y = point_loc[0].Y + scaled_locs[size_idx][2].Y;
      vertex_loc[2].Z = point_loc[0].Z + scaled_locs[size_idx][2].Z;
      point_loc++;
      vertex_loc += 3;
      point_size++;
    }
  } break;

  default:
    WWASSERT(0);
    break;
  }
}
