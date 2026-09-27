// ?updateShorelineTiles@BaseHeightMapRenderObjClass@@QAEXHHHHPAVWorldHeightMap@@@Z
// partial score=1.0 date=2026-09-27
// stlport
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/bfmeheightmap /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
#include <string.h>
class WorldHeightMap;
#include "W3DDevice/GameClient/W3DWater.h"
#include "Common/GlobalData.h"

// Native BFME updateShorelineTiles, RVA 006C76B0, 1249 bytes.
// Identity: matched setShoreLineDetail and initHeightData callers; ZH twin.
// BFME owner layout differs from the shared ZH-derived BaseHeightMap header:
// tile pointer/count/capacity are +30C0/+30C4/+30C8; depth/opacity +3018/+301C.
// The typed owner is necessary for the retail ECX-base SIB encoding in removal.
// WorldHeightMap +8/+C extents, +10 border, +20 data size, +24 ushort samples.
// BFME shoreline records are five words, unlike the ZH cached-vertex form.
struct ShorelineTile006C76B0 { int m_xy; float t0,t1,t2,t3; };
class BaseHeightMapRenderObjClass {
 char pad[0x3018]; float depthAt3018,opacityAt301C; char pad3020[0xa0];
 ShorelineTile006C76B0* m_shoreLineTilePositions; int m_numShoreLineTiles,m_shoreLineTilePositionsSize;
public:
 void updateShorelineTiles(int,int,int,int,WorldHeightMap*);
};
static unsigned short height006C76B0(WorldHeightMap* map,int x,int y)
{
 int width=*(int*)((char*)map+8);
 int ndx=x+width*y;
 int m_dataSize=*(int*)((char*)map+0x20);
 if (ndx>=0 && ndx<m_dataSize && *(unsigned short**)((char*)map+0x24)) return (*(unsigned short**)((char*)map+0x24))[ndx];
 return 0;
}
void BaseHeightMapRenderObjClass::updateShorelineTiles(int minX,int minY,int maxX,int maxY,WorldHeightMap* pMap)
{
 int border=*(int*)((char*)pMap+0x10);
 if(minX<0) minX=0;
 if(minY<0) minY=0;
 if(maxX>*(int*)((char*)pMap+8)-1) maxX=*(int*)((char*)pMap+8)-1;
 if(maxY>*(int*)((char*)pMap+12)-1) maxY=*(int*)((char*)pMap+12)-1;
 if(!this->m_shoreLineTilePositions){ this->m_shoreLineTilePositions=new ShorelineTile006C76B0[4096]; this->m_shoreLineTilePositionsSize=4096; }
 for(int j=0;j<this->m_numShoreLineTiles;j++) {
  int x=this->m_shoreLineTilePositions[j].m_xy&0xffff;
  int y=this->m_shoreLineTilePositions[j].m_xy>>16;
  if(x>=minX && x<maxX && y>=minY && y<maxY) {
   memcpy(this->m_shoreLineTilePositions+j,this->m_shoreLineTilePositions+j+1,(this->m_numShoreLineTiles-1-j)*sizeof(ShorelineTile006C76B0));
   this->m_numShoreLineTiles--; j--;
  }
 }
 if(*(float*)((char*)this+0x3018)==0 || !*((char*)TheWritableGlobalData+0x8c)) return;
 float transparentDepth=*(float*)((char*)this+0x3018)**(float*)((char*)this+0x301c);
 float depthScaleFactor=1.0f/transparentDepth;
 for(j=minY;j<maxY;j++) for(int i=minX;i<maxX;i++) {
  float X0=(i-border)*10.0f;
  float Y0=(j-border)*10.0f;
  float waterZ0=TheWaterRenderObj->getWaterHeight(X0,Y0);
  float X1=(i-border+1)*10.0f;
  float Y1=(j-border+1)*10.0f;
  float waterZ1=TheWaterRenderObj->getWaterHeight(X1,Y0);
  float waterZ2=TheWaterRenderObj->getWaterHeight(X1,Y1);
  float waterZ3=TheWaterRenderObj->getWaterHeight(X0,Y1);
  float terrainZ0=0.0390625f*height006C76B0(pMap,i,j);
  float terrainZ1=0.0390625f*height006C76B0(pMap,i+1,j);
  float terrainZ2=0.0390625f*height006C76B0(pMap,i+1,j+1);
  float terrainZ3=0.0390625f*height006C76B0(pMap,i,j+1);
  int waterSide=(waterZ0>terrainZ0);
  waterSide |= (waterZ1>terrainZ1)<<1;
  waterSide |= (waterZ2>terrainZ2)<<2;
  waterSide |= (waterZ3>terrainZ3)<<3;
  if(!waterSide || waterZ0*waterZ1*waterZ2*waterZ3<=0) continue;
  if(waterSide<15 || waterZ0-terrainZ0<transparentDepth || waterZ1-terrainZ1<transparentDepth || waterZ2-terrainZ2<transparentDepth || waterZ3-terrainZ3<transparentDepth) {
   if(this->m_numShoreLineTiles>=this->m_shoreLineTilePositionsSize) {
    ShorelineTile006C76B0* tempPositions=new ShorelineTile006C76B0[this->m_shoreLineTilePositionsSize+512];
    memcpy(tempPositions,this->m_shoreLineTilePositions,this->m_shoreLineTilePositionsSize*sizeof(ShorelineTile006C76B0));
    delete[] this->m_shoreLineTilePositions;
    this->m_shoreLineTilePositions=tempPositions; this->m_shoreLineTilePositionsSize+=512;
   }
   ShorelineTile006C76B0* shoreInfo=&this->m_shoreLineTilePositions[this->m_numShoreLineTiles];
   shoreInfo->m_xy=i|(j<<16);
   shoreInfo->t0=(waterZ0-terrainZ0)*depthScaleFactor;
   shoreInfo->t1=(waterZ1-terrainZ1)*depthScaleFactor;
   shoreInfo->t2=(waterZ2-terrainZ2)*depthScaleFactor;
   shoreInfo->t3=(waterZ3-terrainZ3)*depthScaleFactor;
   this->m_numShoreLineTiles++;
  }
 }
}
