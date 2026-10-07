# ScriptEngine::setSequentialTimer(Object *, Int) at 0x00339980

The 55-byte body at 0x00339980 was ledgered as the placeholder
`?bfmeMarkYZ@BfmeTableYZ@@QAEXPAUBfmeThingYZ@@H@Z`.

- Its ILT 0x00044A1C is pinned in symbols.csv as
  `?setSequentialTimer@ScriptEngine@@QAEXPAVObject@@H@Z`, and the matched
  `ScriptActions::doUnitGuardForFramecount` (0x00302B40) calls it twice through
  that ILT with (object, framecount[*5]) on TheScriptEngine, as Zero Hour's
  doUnitGuardForFramecount calls setSequentialTimer.
- `ilt_oracle.py check ?setSequentialTimer@ScriptEngine@@QAEXPAVObject@@H@Z
  0x00339980` reports CONFIRMED (exact); the placeholder name is CONTRADICTED.
- The body matches Zero Hour ScriptEngine::setSequentialTimer(Object*, Int):
  return on a null object, walk m_sequentialScripts, and set m_framesToWait on
  the first script whose m_objectID equals the object's ID.
