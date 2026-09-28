# ControlBar initialization, RVA 004A0F70

The full 3,660-byte body ends at exclusive RVA `004A1DBC`. Its existing
`ControlBar::init` identity agrees with the reference initialization sequence,
three CommandButton/CommandSet INI filenames, context-window names, scheme
manager construction, and final `switchToContext(CB_CONTEXT_NONE, NULL)`.
The new native body replaces `ControlBarInitThunk.cpp`'s emitted bytes.

## BFME layout and behavior

The reference ControlBar header is not a valid BFME layout: BFME has twenty
command slots, an additional context window, and arrays at +100, +150 and +1A0.
The TU keeps changed members offset-named. The retail body witnesses every
access. It creates a full-display overlay and twenty command overlays from the
52-byte record consumed by `GameWindowManager::winCreate` at RVA 0047EDE0,
virtual slot 29. The independently landed
`AptPalantirHeroSelectorRva00595D40.cpp` uses the same record. The record's
+08/+0C positions and +10/+14 dimensions are also witnessed by winCreate.
The helper at 00479440 publishes the parent window's creation state; its
existing native body and address-derived `Rva00479440::publish` name are reused.

Other observed differences include twelve rank-three science buttons, a lookup
of ButtonOptions without attaching a command, and hiding the popup layout's
windows by setting their size to 1x1 and position to -1,-1. No missing BFME
behavior is supplied from the reference by assumption.

The canonical INI view supplies retail's 0x848-byte object and the separate
three-argument `loadFile` entry at 00853A20. Canonical AsciiString supplies the
StringBase ownership ABI; its visible `str` specialization is the native
StringBase implementation. Two actual ICoord2D aggregates reproduce the aligned
frame naturally. Four independent integer locals do not. Explicit alignment
was unnecessary and retained EBP as a frame pointer instead of retail's saved
working register. The reference's inline `WindowLayout::setUpdate` and
`getFirstWindow` accessors reproduce the final temporary/register lifetimes.

The three static rank-icon members are identified by the same reference
assignments and the unique SSChevron1L/2L/3L literals. The retail stores are to
VA 012F33FC/012F3400/012F3404. Callback addresses in the creation/layout records
remain explicit: VA 0041E9BB routes to 004AF9F0, and VA 00411BF8 to 004C1990.
No stronger semantic names are claimed for those callbacks.

## Bounded dependency bindings

`ControlBar::init +DDD` passes `this` in ECX and calls ILT 0000B0D7, whose jump
independently resolves to RVA 004A9980. The complete 679-byte target looks up
observer windows, writes global window pointers, takes no stack arguments, and
ends in bare RET. It does not destroy a ControlBar or its members. The old
ledger calls it `ControlBar::~ControlBar`; another legacy observer identity is
at 004A9CD0. This conversion does not extend either unproved identity: it uses
`Rva004A9980::call` and one address-derived pin. No target bytes are credited.

The tooltip function pointer stored at eight sites is VA 0089CA90. Its complete
19-byte body loads its first stack argument, loads TheControlBar, pushes zero
and that argument, calls ILT 0003BCCD, and ends in bare RET. GameWindow's matched
`winSetTooltipFunc` declaration independently supplies the cdecl callback ABI
`(GameWindow*, WinInstanceData*, unsigned)`. The reference's callback body is
known to conflict with retail, so the TU uses `rva0049ca90` and a pin at the
proven address, without the misleading semantic name.

Before each binding, pin_consistency reported no pre-existing pin for the new
address-derived symbol. Its full check passes after both additions. The scoped
strict gate verifies 1/1 body, 42 string literals and five empty-string refs.
The conversion adds 3,660 native bytes; neither helper binding adds byte credit.
