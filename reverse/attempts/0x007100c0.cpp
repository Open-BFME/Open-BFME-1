// ?addMapObjects@W3DRoadBuffer@@IAEXXZ
// partial score=0.35 date=2026-09-09
//
// Retail 0x007100C0, 1016 bytes. Route pin ?addMapObjects@W3DRoadBuffer@@IAEXXZ
// (and the earlier candidate name ?loadRoadsHelper1@W3DRoadBuffer@@QAEXXZ, same
// address) both resolve via reverse/symbols.csv route 0x0002001D -> 0x007100C0.
// Confirmed by disassembling ?loadRoads@W3DRoadBuffer@@QAEXXZ at 0x007105D0:
// its second call after the m_initialized guard and clearAllRoads() targets
// this exact route, matching ZH's W3DRoadBuffer::loadRoads() call sequence
// (clearAllRoads, addMapObjects, updateCountsAndFlags, insertTeeIntersections,
// insertCurveSegments, insertCrossTypeJoins, preloadRoadsInVertexAndIndexBuffers).
//
// The existing `present-unmatched` port of addMapObjects() in
// Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DRoadBuffer.cpp (ZH
// source: GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/GameClient/
// W3DRoadBuffer.cpp) needed two BFME-specific fixes that DID close part of
// the gap (compiled size went 1043 -> 970 against retail's 1016; started at
// 27 bytes over, now 46 bytes under):
//
// 1. Retail's body opens with the SAME "if (!m_initialized) return;" guard
//    (mov al,[this+0xc]; test al,al; je <near end>) that loadRoads() already
//    does before calling this function -- i.e. BFME added a redundant
//    defensive re-check inside addMapObjects() itself that ZH's source does
//    not have. Adding `if (!m_initialized) return;` as the first statement
//    reproduced retail's guard shape exactly (same je offset).
//
// 2. MapObject::getFirstMapObject() in the ZH header is a trivial
//    `return TheMapObjectListPtr;` (flat global load), but retail loads the
//    list head through BfmeTheMapObjectListHolder (pin
//    ?BfmeTheMapObjectListHolder@@3PAVBfmeMapObjectListHolder@@A @0x012ED5DC,
//    already used the same way by WorldHeightMap::freeListOfMapObjects and
//    W3DBridgeBuffer::loadBridges' BfmeThingBWF walk): `mov eax,[0x12ed5dc];
//    mov reg,[eax]` -- two loads, not one. Declaring a TU-local
//    `class BfmeMapObjectListHolder { public: MapObject *m_bfmeHead; };
//    extern BfmeMapObjectListHolder *BfmeTheMapObjectListHolder;` and seeding
//    the for-loop from `BfmeTheMapObjectListHolder->m_bfmeHead` instead of
//    `MapObject::getFirstMapObject()` reproduced that exact two-load shape
//    (mangled name matches the existing pin, no new symbol needed).
//
// UNRESOLVED: shortly after the loop's FLAG_ROAD_POINT1/FLAG_ROAD_POINT2
// checks, retail makes a real CALL (target resolved by decode_calls.py's
// heuristic to 0x0041325A, itself a gen-thunk of uncertain identity) where
// our port's pMapObj->getLocation()->x / ->y compile to direct inlined field
// loads off pMapObj (no call). Either BFME's MapObject::getLocation() is not
// the trivial one-liner from the ZH header (so it doesn't inline the same
// way here), or getFlag()/getName() take a different, non-inlined shape in
// this TU. decode_calls.py also reports 4 unresolved REL32 sites inside the
// #ifdef LOAD_TEST_ASSETS fallback block (getName/getPath lookups) with "not
// a decoded rel32 branch operand", i.e. real layout drift there too, though
// that block sits after the point where the diff has already gone off the
// rails. Register allocation cascades hard once the first content diff hits
// (262 diff lines total), so nothing past the call-vs-inline point is
// trustworthy evidence.
//
// Change to land: figure out why getLocation()/getFlag() are not inlining
// the way the plain ZH header would, in BFME's real MapObject layout -- try
// declaring a local non-inline forwarder, or check whether a modelled
// MapObject shim already exists elsewhere in Code/ with a non-trivial
// getLocation(). t=55min model=sonnet-5.1
//
// --- snippet actually tried (drop into W3DRoadBuffer.cpp in place of the
// present-unmatched addMapObjects, replacing MapObject::getFirstMapObject()) ---
//
// class BfmeMapObjectListHolder
// {
// public:
// 	MapObject *m_bfmeHead;
// };
// extern BfmeMapObjectListHolder *BfmeTheMapObjectListHolder;
//
// void W3DRoadBuffer::addMapObjects()
// {
// 	if (!m_initialized) {
// 		return;
// 	}
// 	MapObject *pMapObj;
// 	MapObject *pMapObj2;
// 	for (pMapObj = BfmeTheMapObjectListHolder->m_bfmeHead; pMapObj; pMapObj = pMapObj->getNext()) {
// 		if (m_numRoads >= m_maxRoadSegments) {
// 			break;
// 		}
// 		if (pMapObj->getFlag(FLAG_ROAD_POINT1)) {
// 			pMapObj2 = pMapObj->getNext();
// #ifdef _DEBUG
// 			DEBUG_ASSERTLOG(pMapObj2 && pMapObj2->getFlag(FLAG_ROAD_POINT2), ("Bad Flag\n"));
// #endif
// 			if (pMapObj2==NULL) break;
// 			if (!pMapObj2->getFlag(FLAG_ROAD_POINT2)) continue;
// 			Vector2 loc1, loc2;
// 			loc1.Set(pMapObj->getLocation()->x, pMapObj->getLocation()->y);
// 			loc2.Set(pMapObj2->getLocation()->x, pMapObj2->getLocation()->y);
// 			... (rest identical to the ZH source / existing present-unmatched body)
