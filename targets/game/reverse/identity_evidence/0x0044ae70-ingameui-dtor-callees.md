# Callee names for InGameUI::~InGameUI (0x0044AE70)

The destructor (936 bytes, `??1InGameUI@@UAE@XZ`, ilt_oracle CONFIRMED) calls each member's out-of-line destructor through an ILT thunk. The member offsets come from the `lea ecx, [esi+off]` before each call. The element types are the ones Zero Hour's `InGameUI.h` gives these members, and BFME 2's `InGameUI.h` repeats them for +0x10, +0x18 and +0x1C.

`tools/ilt_oracle.py check` confirms every instantiation name below at its body address. For each container base destructor, about 230 element types were tried per address: pointers to and values of every Zero Hour InGameUI-related class, plus int, unsigned int and void*. Exactly one confirmed at each address. Expected false fits are about 0.15 per address, so the oracle result is supporting evidence and the member types are the primary evidence.

| Call (retail offset, ILT) | Member | Body | Name |
|---|---|---|---|
| +0x202, 0x00024BD6 | +0x1298 `list<FloatingTextData*>` (ZH m_floatingTextList) | 0x004400F0 | `_List_base<FloatingTextData*>::~_List_base` |
| +0x1AF, 0x000445B2 | +0x1304 list of 8-byte POD elements (oracle fits `ICoord2D`, but that name is pinned to other bodies already) | 0x00440510 | `_List_base<Rva00440510Element>::~_List_base` (address-named) |
| +0x1F2, 0x0001C8B9 | +0x12C0 `list<WorldAnimationData*>` (ZH m_worldAnimationList) | 0x004401E0 | `_List_base<WorldAnimationData*>::~_List_base` |
| +0x1E2, 0x00002270 | +0x12C4 list, element type not found | 0x004402D0 | `_List_base<Rva004402D0Element*>::~_List_base` (address-named) |
| +0x37A, 0x000292D5 | +0x10 `list<WindowLayout*>` (ZH m_windowLayouts) | 0x00440400 | `_List_base<WindowLayout*>::~_List_base` |
| +0x2DC, 0x00031C7D | +0x77C `map<AsciiString, NamedTimerInfo*>` (ZH NamedTimerMap) | 0x004491D0 | `_Rb_tree<AsciiString, pair<const AsciiString, NamedTimerInfo*>, ...>::~_Rb_tree` |
| +0x170, 0x0004B380 | member call | 0x0043F400 | `InGameUI::clearFloatingText` (protected) |
| +0x177, 0x0002DD53 | member call | 0x0043F5D0 | `InGameUI::clearWorldAnimations` (protected) |

Zero Hour's destructor ends with `delete[] m_placeIcon; clearFloatingText(); clearWorldAnimations(); resetIdleWorker();`. Retail calls 0x0043F400, 0x0043F5D0, then 0x0043FBB0, then 0x0043FAF0 (`InGameUI::resetIdleWorker`, already matched under that name).

0x0043FBB0 is a BFME addition with no confirmed name, so the source calls it by its ledger name, `Gen_0043FBB0::bfmeClear`. The BFME 2 donor's destructor (`Code/GameEngine/Source/GameClient/InGameUIDtor.cpp` at 2bac16a6) also has an unnamed call at this point, after clearWorldAnimations.

The existing ledger rows at 0x004400F0, 0x004401E0, 0x004402D0, 0x00440400 and 0x000FD1D0 are `tg_` instances in HordeContainDestructors.cpp. They share one guessed `list<int>` object symbol, and the oracle contradicts that name at each of them. The pins above give the InGameUI destructor resolvable names without changing those rows.
