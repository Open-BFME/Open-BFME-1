// ?doForceObjectSelection@ScriptActions@@IAEXABVAsciiString@@0_N0@Z
// partial score=0.35 date=2026-09-09
// Full semantic reconstruction at the raw boundary 0x002FAF10..0x002FB0EE.
// Named identity: ScriptActions::executeAction OBJECT_FORCE_SELECT at
// ScriptActions.cpp:8793-8797.  The attempt uses the independently recovered
// BFME ScriptEngine slot +0x44, InGameUI select slot +0xe0, 0x70-byte
// AudioEventRTS/ObjectID constructor and audio slot +0x44.  Probe still drifts
// at the BFME Object/DLink layout and EH frame: retail sub esp 0x8c, while this
// source emitted sub esp 0x80; object-template/equality calls also remain
// unresolved.  No retail bytes are lifted here.

class BfmeInGameUISelectDrawable
{
public:
	virtual void _igui_select_00() = 0;
	virtual void _igui_select_01() = 0;
	virtual void _igui_select_02() = 0;
	virtual void _igui_select_03() = 0;
	virtual void _igui_select_04() = 0;
	virtual void _igui_select_05() = 0;
	virtual void _igui_select_06() = 0;
	virtual void _igui_select_07() = 0;
	virtual void _igui_select_08() = 0;
	virtual void _igui_select_09() = 0;
	virtual void _igui_select_0a() = 0;
	virtual void _igui_select_0b() = 0;
	virtual void _igui_select_0c() = 0;
	virtual void _igui_select_0d() = 0;
	virtual void _igui_select_0e() = 0;
	virtual void _igui_select_0f() = 0;
	virtual void _igui_select_10() = 0;
	virtual void _igui_select_11() = 0;
	virtual void _igui_select_12() = 0;
	virtual void _igui_select_13() = 0;
	virtual void _igui_select_14() = 0;
	virtual void _igui_select_15() = 0;
	virtual void _igui_select_16() = 0;
	virtual void _igui_select_17() = 0;
	virtual void _igui_select_18() = 0;
	virtual void _igui_select_19() = 0;
	virtual void _igui_select_1a() = 0;
	virtual void _igui_select_1b() = 0;
	virtual void _igui_select_1c() = 0;
	virtual void _igui_select_1d() = 0;
	virtual void _igui_select_1e() = 0;
	virtual void _igui_select_1f() = 0;
	virtual void _igui_select_20() = 0;
	virtual void _igui_select_21() = 0;
	virtual void _igui_select_22() = 0;
	virtual void _igui_select_23() = 0;
	virtual void _igui_select_24() = 0;
	virtual void _igui_select_25() = 0;
	virtual void _igui_select_26() = 0;
	virtual void _igui_select_27() = 0;
	virtual void _igui_select_28() = 0;
	virtual void _igui_select_29() = 0;
	virtual void _igui_select_2a() = 0;
	virtual void _igui_select_2b() = 0;
	virtual void _igui_select_2c() = 0;
	virtual void _igui_select_2d() = 0;
	virtual void _igui_select_2e() = 0;
	virtual void _igui_select_2f() = 0;
	virtual void _igui_select_30() = 0;
	virtual void _igui_select_31() = 0;
	virtual void _igui_select_32() = 0;
	virtual void _igui_select_33() = 0;
	virtual void _igui_select_34() = 0;
	virtual void _igui_select_35() = 0;
	virtual void _igui_select_36() = 0;
	virtual void _igui_select_37() = 0;
	virtual void selectDrawable(Drawable *drawable) = 0;
};

void ScriptActions::doForceObjectSelection(const AsciiString& teamName,
	const AsciiString& objectType, Bool centerInView,
	const AsciiString& audioToPlay)
{
	Team *team = ((BfmeScriptEngineVtbl_44 *)TheScriptEngine)->getTeamNamed(teamName, FALSE);
	if (!team)
		return;

	Object *bestGuess = NULL;
	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
		!iter.done(); iter.advance()) {
		Object *obj = iter.cur();
		if (!obj)
			continue;
		if (obj->getTemplate() && obj->getTemplate()->getName() == objectType) {
			if (bestGuess == NULL || obj->getID() < bestGuess->getID())
				bestGuess = obj;
		}
	}
	if (!(bestGuess && bestGuess->getDrawable()))
		return;

	((BfmeInGameUISelectDrawable *)TheInGameUI)->selectDrawable(bestGuess->getDrawable());
	BfmeAudioEventRTS audioEvent(audioToPlay, (ObjectID)0);
	audioEvent.setPlayerIndex(ThePlayerList->getLocalPlayer()->getPlayerIndex());
	((BfmeAudioVtbl_44 *)TheAudio)->addAudioEvent(&audioEvent);
	if (centerInView) {
		Coord3D pos = *bestGuess->getPosition();
		TheTacticalView->moveCameraTo(&pos, 0, 0, FALSE, 0.0f, 0.0f);
	}
}
