# 0x0052AF40 AptPlayerStatus message handler

Retail vtable 0x01106DEC slot 2 points through ILT 0x0003558A to this
123-byte body. The matched `AptPlayerStatus` destructor at 0x0052BEC0
installs that vtable; the matched `AptPlayerStatus::input` occupies slot 1.
The separate DisconnectScreen vtable also places its matched
`_bfme_checkMsg` in slot 2. These independent routes establish the class
and message-handler role.

The matched `AptPlayerStatus::InitGadgets` in the same source file stores mute
check boxes at this+0x268 and signed slot numbers at this+0x288. The retail
body compares the selected window against those eight entries, calls
`GameInfo::getSlot` with the corresponding signed index, calls
`GadgetCheckBoxIsChecked` on the selected window, then stores the result at
`GameSlot+0xA`, which the layout witness names `m_isMuted`. All three direct
callees resolve through their retail ILT routes. The body returns the base
`BfmeMsgHandler::defaultHandler` result for other messages and 1 for
`GBM_SELECTED` (0x4008); preserving that return path is necessary for both
behavior and bytes.

The scratch probe emitted 123/123 bytes with four relocation slots. Declaring
the loop index before the window cursor reproduced the retail initialization
order. The strict scoped build verifies this body and the existing 196-byte
`InitGadgets` sibling together.
