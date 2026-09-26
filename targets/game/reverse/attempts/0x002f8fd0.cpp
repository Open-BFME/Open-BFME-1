// ?doMoveCameraAlongWaypointPath@ScriptActions@@IAEXABVAsciiString@@MMMM@Z
// partial score=0.15 date=2026-09-10
// Exact canonical candidate body retained from Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp.
// ?doMoveCameraAlongWaypointPath@ScriptActions@@IAEXABVAsciiString@@MMMM@Z
void ScriptActions::doMoveCameraAlongWaypointPath(const AsciiString& waypoint, Real sec, Real cameraStutterSec, Real easeIn, Real easeOut)
{
	for (Waypoint *way = TheTerrainLogic->getFirstWaypoint(); way; way = way->getNext()) {
		if (way->getName() == waypoint) {
			TheTacticalView->moveCameraAlongWaypointPath(way, sec*1000, cameraStutterSec*1000, true, easeIn*1000.0f, easeOut*1000.0f);			
			break;
		}
	}
}
