# 0x0078E570 drawBorder: the text call is not GameWindow::winGetText

The banked source for `?drawBorder@Rva0078E570@@UAEXPAVGameWindow@@@Z` called
`window->winGetText()`. Retail calls ILT `0x00007E82`, which jumps to
`0x00479B80`. That body and the matched `GameWindow::winGetText` at
`0x005CB9F0` are both 30-byte sret getters, but they read different members:

| body | receiver adjust | inner call |
|---|---|---|
| `0x005CB9F0` `GameWindow::winGetText` | `add ecx, 4` | ILT `0x0003E112` (`WinInstanceData::getText`) |
| `0x00479B80` (ledger `BfmeThingDPG::bfmeGoDPG`) | `add ecx, 0x30` | ILT `0x000424D3` |

So the retail call is not `winGetText`. The callee is modelled as the
address-derived `Rva00479B80Window::rva00479B80` (same thiscall sret ABI) and
pinned to ILT `0x00007E82`; its semantic name is not recovered.
