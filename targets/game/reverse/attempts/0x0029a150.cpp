// ?d_0029a150@@YAXXZ
// partial score=0.748394 date=2026-09-27
// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <math.h>
#define _OPERATOR_NEW_DEFINED_
#include "vector3.h"
// Retail owns four nontrivial Coord3D elements. coord.h is POD and coord3d.h
// adds out-of-line copy/assignment operations absent in this retail body.
struct Coord3D { Coord3D(); ~Coord3D(); float x,y,z; };
class BezierSegment { public: BezierSegment(Coord3D*); float getApproximateLength(float) const; void getSegmentPoints(int,_STL::vector<Coord3D>*) const; Coord3D points[4]; };
class Terrain0029A150 { public: virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c(); virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c(); virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c(); virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c(); virtual float height(const Coord3D*,const Coord3D*); };
extern Terrain0029A150* g_terrain0029A150;
struct Config0029A150 { char pad00[8]; float at08,at0c,at10,at14; char pad18[0x14]; float at2c,at30,at34,at38,at3c; bool at40,at41,at42; char pad43; float at44,at48; };
struct Difference0029A150 { float x,y,z; Difference0029A150(float a,float b,float c):x(a),y(b),z(c){} float length() const { return (float)sqrt(x*x+y*y+z*z); } };
inline const float& maximum0029A150(const float& a,const float& b) { return a>b?a:b; }
class FlightCurve0029A150 { public: bool build(bool recalculate,float height); char pad00[4]; Config0029A150* at04; char pad08[0x18]; _STL::vector<Coord3D> at20; Coord3D at2c,at38; float at44,at48; int at4c,at50,at54; };
bool FlightCurve0029A150::build(bool recalculate,float height) {
 Config0029A150* data=at04;
 if(height<0.5f) height=0.5f;
 float first=at54==0?data->at10:data->at34;
 float second=at54==0?data->at14:data->at38;
 Coord3D points[4];
 points[0]=at2c; points[3]=at38;
 float drop=at2c.z-at38.z;
 if(drop<0.0f) drop=0.0f;
 float factor=(height-drop)/height;
 if(factor<0.0f) factor=0.0f;
 at48=drop+height;
 points[1].x=first*(points[3].x-points[0].x)+points[0].x;
 points[1].y=first*(points[3].y-points[0].y)+points[0].y;
 points[2].x=second*(points[3].x-points[0].x)+points[0].x;
 points[2].y=second*(points[3].y-points[0].y)+points[0].y;
 if(data->at42) {
  points[1].z=(points[3].z-points[0].z)*data->at44+points[0].z;
  points[2].z=(points[3].z-points[0].z)*data->at48+points[0].z;
 } else {
  float ground=g_terrain0029A150->height(&points[0],&points[3]);
  float h1=at54==0?data->at08:data->at2c;
  float h2=at54==0?data->at0c:data->at30;
  h1*=height; h2=h2*factor*height;
  if(data->at3c>0.0f) {
   Vector3 difference(points[3].x-points[0].x,points[3].y-points[0].y,points[3].z-points[0].z);
   float scale=difference.Length()/data->at3c;
   if(scale>1.0f) scale=1.0f;
   points[1].z=first*(points[3].z-points[0].z)+points[0].z;
   points[2].z=second*(points[3].z-points[0].z)+points[0].z;
   if(points[1].z<ground) points[1].z=ground;
   points[1].z+=scale*h1;
   if(points[2].z<ground) points[2].z=ground;
   points[2].z+=scale*h2;
  } else {
   ground=maximum0029A150(ground,points[0].z);
   float base=maximum0029A150(ground,points[3].z);
   points[2].z=h2+base;
   points[1].z=h1+base;
  }
 }
 BezierSegment segment(points);
 if(recalculate) { float speed=at44; at4c=(int)(ceil(segment.getApproximateLength(1.0f)/speed)+1.0f); }
 if(at4c<3) at4c=3;
 segment.getSegmentPoints(at4c,&at20);
 return true;
}


