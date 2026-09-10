// ?createUnitOnTeamAt@ScriptActions@@IAEXABVAsciiString@@000@Z
// partial score=0.38 date=2026-09-09
// Retail boundary: RVA 0x002F92A5, 604 bytes, ending at 0x002F9500.
// Direct dispatcher: ScriptActions.cpp:8131-8135.
void ScriptActions::createUnitOnTeamAt(const AsciiString& unitName, const AsciiString& objType,
	const AsciiString& teamName, const AsciiString& waypoint)
{
	Object *pOldObj = ((BfmeScriptEngineVtbl_6c *)TheScriptEngine)->getUnitNamedByValue(unitName);
	if (pOldObj && !pOldObj->isEffectivelyDead()) {
		AsciiString str = "WARNING - Object with name ";
		str.concat(unitName);
		str.concat(" already exists. Failed Create.");
		TheScriptEngine->AppendDebugMessage(str, FALSE);
		return;
	}
	Team *theTeam = ((BfmeScriptEngineVtbl_44 *)TheScriptEngine)->getTeamNamed(teamName, FALSE);
	if (!theTeam) {
		theTeam = TheTeamFactory->createTeam(teamName);
	}
	if (!theTeam) {
		TheScriptEngine->AppendDebugMessage("***WARNING - Team not found:***", FALSE);
		TheScriptEngine->AppendDebugMessage(teamName, TRUE);
		DEBUG_LOG(("WARNING - Team %s not found.\n", teamName.str()));
		return;
	}
	const ThingTemplate *thingTemplate = ((BfmeThingFactory *)TheThingFactory)->findTemplate(objType);
	if (!thingTemplate) {
		DEBUG_LOG(("WARNING - ThingTemplate '%s' not found.\n", objType.str()));
		return;
	}
	Object *obj = TheThingFactory->newObject(thingTemplate, theTeam);
	if (!obj) {
		return;
	}
	if (unitName != m_unnamedUnit) {
		obj->setName(unitName);
		if (pOldObj || TheScriptEngine->didUnitExist(unitName)) {
			TheScriptEngine->transferObjectName(unitName, obj);
		} else {
			TheScriptEngine->addObjectToCache(obj);
		}
	}
	Waypoint *way = ((BfmeTerrainLogicVtbl_7c *)TheTerrainLogic)->getWaypointByName(waypoint);
	if (way) {
		Coord3D destination = *way->getLocation();
		obj->setPosition(&destination);
	}
}
