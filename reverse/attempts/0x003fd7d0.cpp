// ?computePointOnPath@Rva003FD7D0Path@@QAEXPAVObject@@PAVLocomotor@@PAURva003FD7D0Point@@_N@Z
// partial score=0.3180851063829787 date=2026-09-22
// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// Complete reconstruction of the 940-byte Path cursor body at RVA 003FD7D0.
// ABI: hub 002417E0 +015D and target ret16. Object argument is unused.
// Layout: target instructions and PathAdvanceCachedPoint.cpp; no guessed owner.
#include <math.h>
#include "../../Code/Libraries/Source/WWVegas/WWLib/basetype.h"
extern void j_0000650f();
class Object;
class Locomotor { public: float getPreferredHeight() const; };
class PathNode {
public:
 const PathNode *getNextOptimized(Coord2D *,float *) const;
 const Coord3D *getPosition() const {return &m_position;}
 int getLayer() const {return m_layer;}
 int getWaypointID() const {return m_waypointID;}
 const PathNode *getNextOptimized() const {return m_nextOptimized;}
 void *m_next, *m_previous;
 const PathNode *m_nextOptimized;
 Coord3D m_position;
 int m_layer;
 unsigned int m_flags1C;
 int m_waypointID;
};
struct Rva003FD7D0Point {
 float m_distance;
 Coord3D m_position;
 Coord3D m_nextPosition;
 int m_layer;
 int m_waypointID;
};
struct WaypointKind003FD7D0 { char m_pad00[0x60]; int m_kind60; };
class TerrainSlots003FD7D0 {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
 virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
 virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
 virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
 virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
 virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
 virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
 virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
 virtual WaypointKind003FD7D0 *slot80(int);
};
extern TerrainSlots003FD7D0 *TheTerrainLogic;
struct BlockRva003D5C60BlockAssign { unsigned int m_dword[3]; };
class Rva003D5C60BlockAssign { public: void set(const BlockRva003D5C60BlockAssign &); };
struct AIPathfinder003FD7D0 { char m_pad00[12]; Rva003D5C60BlockAssign *m_pathfinder; };
extern AIPathfinder003FD7D0 *TheAI;
class Rva003FD7D0Path {
public:
 void computePointOnPath(Object *,Locomotor *,Rva003FD7D0Point *,bool);
 unsigned int m_word00;
 const PathNode *m_path, *m_pathTail;
 unsigned int m_word0C;
 const PathNode *m_cachedNode;
 Coord3D m_cachedPosition;
 float m_cachedDistance;
};
void Rva003FD7D0Path::computePointOnPath(Object *,Locomotor *locomotor,Rva003FD7D0Point *point,bool useCache)
{
 float distance = 40.0f;
 if (locomotor) {
  distance = locomotor->getPreferredHeight();
  if (distance <= 0.1f) distance = useCache ? 0.1f : 1.0f;
 }
 point->m_layer = 1;
 Coord3D &out = point->m_position;
 out.zero();
 point->m_distance = 0.0f;
 point->m_waypointID = 0x7fffffff;
 point->m_nextPosition.zero();
 if (!m_path) return;
 if (!m_cachedNode) {
  m_cachedNode = m_path;
  m_cachedDistance = 0.0f;
  m_cachedPosition = *m_path->getPosition();
 }
 Coord3D *cached = &m_cachedPosition;
 float along = m_cachedDistance;
 const PathNode *current = m_cachedNode;
 Coord3D position = *cached;
 float segment = 0.00001f;
 Coord2D direction;
 while (current) {
  const PathNode *next = current->getNextOptimized(&direction,&segment);
  if (!next) break;
  float scale = 1.0f;
  if (next->getWaypointID() != 0x7fffffff) {
   WaypointKind003FD7D0 *waypoint = TheTerrainLogic->slot80(next->getWaypointID());
   if (waypoint) {
    if (waypoint->m_kind60 == 1 && segment - along > distance)
     distance = (segment - along) - 0.001;
    if (waypoint->m_kind60 == 3) {
     scale = segment / ((float)fabs(next->getPosition()->z - current->getPosition()->z) + 1.0f);
     if (scale > 1.0f) scale = 1.0f;
     else if (scale < 0.5f) scale *= 0.85f;
    }
   }
  }
  if (segment - along > distance * scale) {
   distance *= scale;
   out = position;
   { typedef void (Coord2D::*Normalize)(); union { void (*raw)(); Normalize member; } call; call.raw = j_0000650f; (direction.*call.member)(); }
   out.x += direction.x * distance;
   out.y += direction.y * distance;
   out.z += (next->getPosition()->z - current->getPosition()->z) * (distance / segment);
   point->m_distance = segment - along;
   along += distance;
   point->m_nextPosition = *next->getPosition();
   point->m_waypointID = next->getWaypointID();
   point->m_layer = next->getLayer();
   goto finished;
  }
  float consumed = (segment - along) / scale;
  current = next;
  position = *next->getPosition();
  along = 0.0f;
  distance -= consumed;
 }
 if (m_pathTail) {
  out = *m_pathTail->getPosition();
  point->m_nextPosition = *m_pathTail->getPosition();
  point->m_waypointID = m_pathTail->getWaypointID();
  point->m_layer = m_pathTail->getLayer();
  current = m_pathTail;
  point->m_distance = 0.0f;
  along = 0.0f;
  position = out;
  position.x -= cached->x;
  position.y -= cached->y;
  position.z -= cached->z;
  point->m_distance = position.length();
 }
finished:
 if (useCache) {
  m_cachedNode = current;
  m_cachedDistance = along;
  *cached = out;
  TheAI->m_pathfinder->set(*(const BlockRva003D5C60BlockAssign *)&out);
 }
 if (current) {
  const PathNode *next = current->getNextOptimized();
  float remaining = 0.0f;
  while (next) {
   point->m_distance = remaining + point->m_distance;
   next = next->getNextOptimized(&direction,&remaining);
  }
 }
}
