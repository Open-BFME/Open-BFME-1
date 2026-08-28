// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?evaluateAudioHasCompleted@ScriptConditions@@IAE_NPAVParameter@@@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// Clean C++ reconstruction of the ScriptConditions "HasCompleted" predicate.
//
// Retail folded three identical bodies onto this address:
//   ScriptConditions::evaluateVideoHasCompleted
//   ScriptConditions::evaluateSpeechHasCompleted
//   ScriptConditions::evaluateAudioHasCompleted
// (Bool ScriptConditions::evaluateXHasCompleted(Parameter *pParm) { return
// TheScriptEngine->isXComplete(pParm->getString(), true); }). Each is a
// one-line __thiscall member that forwards a single Parameter through to a
// TheScriptEngine virtual and returns its Bool result -- identical machine
// code, so only one of the three names can occupy this RVA and the other two
// must be identical-code-folded onto it elsewhere.
//
// Parameter carries its AsciiString at offset +0x10 here (confirmed by the
// already-matched WriteParameter row: "type at this+0x00 int at +0x08 real
// at +0x0C string at +0x10 coord at +0x14"), matching retail's
// `add edx,0x10` exactly -- getString() is a raw field read, no call. The
// vendored ZH Parameter layout (vtable + type + initialized + int + real
// + string) would put the string at +0x14, so it is not used here; a local
// replica keeps the drift out of the shared header.
//
// TheScriptEngine's virtual is reached at vtable slot 0xa8 (index 42). The
// dispatch class below models only that ABI slice: 42 anonymous pad slots
// so the compiler places the real target at the correct vtable offset, then
// the (const AsciiString&, Bool) -> Bool slot that retail actually calls.
// Which named ScriptEngine method that slot really is does not change the
// bytes emitted for the caller, so it is left unidentified rather than
// guessed.

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
	unsigned char m_unreconstructed_00[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }

private:
	// verified via the matched WriteParameter row: string field at +0x10
	unsigned char m_pad_00[0x10];
	AsciiString m_string;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();

	/// unidentified -- retail folded evaluateVideoHasCompleted,
	/// evaluateSpeechHasCompleted and evaluateAudioHasCompleted onto one
	/// body, so which of isVideoComplete/isSpeechComplete/isAudioComplete
	/// sits at vtable +0xa8 cannot be told apart from this call site alone.
	virtual Bool unidentified_isComplete(const AsciiString &, Bool);	///< vtable +0xa8
};

extern ScriptEngine *TheScriptEngine;					///< retail [0x012F076C]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	Bool evaluateAudioHasCompleted(Parameter *);
};

// ?evaluateAudioHasCompleted@ScriptConditions@@IAE_NPAVParameter@@@Z
Bool ScriptConditions::evaluateAudioHasCompleted(Parameter *pAudioParm)
{
	return TheScriptEngine->unidentified_isComplete(pAudioParm->getString(), true);
}
