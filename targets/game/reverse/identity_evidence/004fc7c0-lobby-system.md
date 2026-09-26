# WOLLobbyMenuSystem, 004FC7C0

The retail FunctionLexicon record at VA012A9578 is `{0,010875D8,00402DF1}`.
The literal is `WOLLobbyMenuSystem`; ILT00002DF1 jumps to004FC7C0.
The shipped FunctionLexicon.cpp pairs this callback with the same literal.
The complete3452-byte extent comprises executable bytes through+0D4A,
one alignment NOP, a five-address jump table at+0D4C and28 index bytes at+0D60.
The following bytes are INT3 padding; the final index byte is data, not an instruction.

The native callback uses canonical WWLib strings and the independently landed
GameWindow view. Its BFME compatibility checks use room words+430/+434/+438
and GlobalData words+BD0/+BC8/+BD4. The first GlobalData word passes twice to
the independently recovered100-byte opaque hook wrapper Rva0009B4B0.
The words retain offset names: no unsupported semantic field names are asserted.
Each room value is captured before comparison; this preserves its read before
the opaque hook and reproduces retail's boolean lifetimes and common error tail.
The PeerRequest constructor/destructor and independent deque strides prove0x194
bytes; text/password are+10/+1C and its payload union starts+E4. This callback
stores join request11, list request7 and extended-info request20.

## Direct dependencies

* The PlayerInfoMap lookup uses the existing AsciiComparator declaration/pin.
  The independently emitted237-byte `_M_find` exactly reproduces004F18C0,
  including the comparator's by-value AsciiString calls. No new tree pin.
* Retail calls00017F76 ->004FB290 to clear TheLobbyQueuedUTMs atVA012F463C.
  The source declares list<PeerResponse>; retail's56-byte loop calls the payload
  destructor via00044733 ->004DAC70 and then operator delete. The independently
  matched PeerResponse copy426B/assignment537B prove the0x330-byte payload.
  Native list<PeerResponse>::clear reproduces all56bytes with resolved calls.
  This corrects the old QueuedDownload label and moves ownership only; no new
  headline bytes are credited for this helper.
* Retail0004059D ->0062C650 is the one-byte RET RefreshGameInfoListBox.
  The shipped LobbyUtils.cpp body is empty and has the exact two-window cdecl
  signature. The aligned caller passes GetGameListBox/GetGameInfoListBox and
  cleans8bytes. The pin supplies that independently supported callee identity.
* Retail00044A3A ->0062C5D0 is a3-byte `xor eax,eax;ret` clone of
  GetGameInfoListBox. LobbyUtils.cpp explicitly returns NULL. The existing
  ledger name resolves only to a different ICF zero-return body; the new real-body
  pin names this caller's witnessed clone without changing any generated row.

The old reference WOLLobbyMenu.cpp remains unchanged: four existing generated
EH funclet rows still use that emitter. Only the former naked callback file is
removed; the new ledger owner is the exact native TU. Helper ownership changes
and pins are dependency repairs, excluded from the3452-byte headline increment.
