# 0x00161DC0 BuildListInfo::getTemplateName

Previously `dup_161dc0` (vendored byte-twin alias owned by ControlBarObserver.cpp,
object-symbol Rva000EE6D0StringAccessor::getString). Now
`?getTemplateName@BuildListInfo@@QBE?AVAsciiString@@XZ` in
game/GameEngine/Source/Common/System/BuildListInfo_getTemplateName.cpp.

BFME 1 target evidence:
- `tools/ilt_oracle.py check ?getTemplateName@BuildListInfo@@QBE?AVAsciiString@@XZ 0x49EFE`:
  CONFIRMED (exact, p_false 2.0e-4). ILT 0x00049EFE jumps to 0x00161DC0.
- symbols.csv already pinned the name at the ILT; its note says the matched
  caller at 0x0036E650 identifies BuildListInfo's template name at +8 through
  a hidden return buffer.
- Body (32 B): hidden-return thiscall, `ret 4`; copy-constructs the
  AsciiString at this+8 (StringBase<char> copy constructor 0x00887B60).

Zero Hour reference: GeneralsMD Common/SidesList.h, BuildListInfo
(`m_buildingName`, `m_templateName` after the vfptr) and its accessor
`AsciiString getTemplateName(void) const { return m_templateName; }`.

Link-queue row #33 (census 6c4dd9e650): AIPlayerComputeCenterAndRadiusOfBase.cpp
calls the out-of-line accessor, which no row owned under its real name.
