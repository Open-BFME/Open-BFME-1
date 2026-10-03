# C386D8: array cleanup and misidentified parent prerequisite

Parent RVA5A5AE0 begins `6AFF6826870301`, installing handler C38726.
FuncInfo E27BDC has six states in map E27BAC. Entry1 at E27BB4 is
`{0, 010386D8}` (action stored as VA). This independently owns the action.

Action C386D8 is22B through RET C386ED, immediately followed by the next
cleanup. It destroys50 elements of84 bytes at `[EBP-10]+8`, using callback
ILT41C7C -> 5A5460 (existing CursorInfo destructor) and CRT helper9F6D76.
Ghidra read_memory and retail capstone agree. No standalone emitter exists
in the currently ledgered parent source: it is a naked byte lift.

The old parent identity `W3DDisplayStringManager::newDisplayString` is
incompatible with the body, as the earlier identity-suspect record noted:

- Incoming ECX is retained in ESI and returned in EAX.
- It calls SubsystemInterface construction9A1A30, installs vtable VA0110D580,
  and constructs the50x54-hex CursorInfo array at+8 through9F6EE4.
- It initializes fields through+4E10, including the literal Times New Roman,
  tooltip colors/timings, cursor fields, and mouse-event buffers.
- Its full774B extent ends RET5A5DE5 with INT3 from5A5DE6.
- The same table is installed by the existing native Mouse destructor5A5500.
  Mouse_destructor.cpp declares the50 CursorInfo members and strings at
  +1070,+10FC,+1100,+1104, agreeing with every action in this parent map.
- The official GeneralsMD Mouse::Mouse twin (also present in Input/Mouse.cpp)
  initializes the matching mouse-event buffers, redraw mode, Times New Roman,
  tooltip50/50 timing, text220/220/220/255, and related fields.

These facts identify a Mouse constructor prerequisite, not an allocating
DisplayString factory. A source-backed cleanup promotion needs the correct
native parent frame and provider; retaining the mislabeled dump does not
supply one. This record changes neither the parent ledger nor source.

Native Input/Mouse.cpp probe of ??0Mouse@@QAE@XZ emits678B versus774B,
with561 nonrelocation differences, nine displaced relocation sites, shape0.842.
It constructs40 CursorInfo elements rather than retail50 and has a different
receiver-save frame. This existing source is not a matching parent or action
provider; no partial cleanup or production conversion is claimed.
