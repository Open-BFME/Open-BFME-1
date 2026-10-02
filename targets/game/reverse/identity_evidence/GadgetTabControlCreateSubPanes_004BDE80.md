# GadgetTabControlCreateSubPanes, RVA 0x004BDE80

The full name is independently supported by the Zero Hour twin in
`GeneralsMD/Code/GameEngine/Source/GameClient/GUI/Gadget/GadgetTabControl.cpp`,
lines 297-329. The BFME body retains the distinctive eight-pane loop, the
`Pane %d` name, the tab-pane style bit, parent enabled-state propagation,
existing-pane resizing/repositioning, and the final active-pane selection.

Retail evidence was read directly from the unpacked 1.03 image:

- Start RVA 0x004BDE80 follows four `CC` bytes; the last instruction is `ret`
  at 0x004BDFD6 and nine `CC` bytes follow, proving the 343-byte extent.
- ILT 0x00046538 reaches `GameWindow::winGetUserData` at 0x00478C70; the
  pane array is at user data +0x14, has eight entries, and activeTab is +0x40.
  These agree with the existing upstream `TabControlData` declaration.
- ILT 0x0000A65A reaches the matched `GadgetTabControlComputeSubPaneSize`
  at 0x004BDA60; ILT 0x00008936 reaches the matched
  `GadgetTabControlShowSubPane` at 0x004BDD10.
- ILT 0x00034991 reaches `GameWindow::winGetInstanceData` at 0x00478C60,
  whose body returns `this + 0x30`. This caller sets the instance style at
  +0x0C (independently witnessed by name_oracle) and names the pane through
  `m_decoratedNameString` at +0x18C, matching the upstream member and use.
- Format literal VA 0x010FD8FC is `Pane %d`. The function calls imported
  `sprintf`, inlines `strlen`, and calls the canonical
  `StringBase<char>::set(const char *, int)` at RVA 0x00887D20.
- The parent callback pointer is ILT 0x0000F0AB, which jumps to the matched
  `PassSelectedButtonsToParentSystem` at 0x0047C190; the latter's identity
  is also backed by the executable FunctionLexicon table.
- The remaining direct calls reach the matched `winGetStatus`, `winEnable`,
  `winSetSize`, and `winSetPosition` methods through their existing ILTs.
  `tools/callees.py 0x004BDE80 343` supplied the routes before reconstruction.

BFME's virtual factory at manager slot +0x74 takes one pointer to a 52-byte
record instead of Zero Hour's scalar argument list. This interface is also
used by the matched `GameWindowManagerScriptCreateWindow.cpp` body at
0x004874A0. This caller writes parent at record +0x00, zero status at +0x04,
x/y at +0x08/+0x0C, callback at +0x1C, and zeroes all remaining words.
In particular it does not copy the computed width/height into the record;
those locals are consumed only by the existing-pane branch. The reconstruction
preserves these exact stores rather than assuming the ZH scalar interface.
The record and virtual interface use address-derived names because their
original BFME type/member names are not established.

The first full reconstruction had the right 343-byte size and only twelve
non-relocation byte differences: constructor stores placed status too early.
Explicitly assigning the zero status after construction, as in the upstream
call's WIN_STATUS_NONE argument, restores the complete retail instruction
stream. No new pins, shared headers, or class redeclarations are required.
