# Team controlling-player inline provider

Queue16 d1c221c3d8 identifies duplicate getControllingPlayer. The inline
null-guarded call-site implementation in Team_killTeam.cpp stays visible
but imported forceinline suppresses its unused standalone definition.
The636-byte killTeam row passes the normal byte gate with both DIR32
references; its COFF has no getControllingPlayer definition or import.
No ABI, layout, behavior, flags, pin, alias or header edit.

Donor76f0baefa6f285d54bc1ca922397674312a5913f reviewed:
Code/GameEngine/Source/Common/RTS/Team.cpp and
reverse/attempt_support/ingame-ui-helpers-link-20261015/readme.md.
Only surplus-inline emission suppression is reused; donor Team layout
and semantics are not transferred. Canonical BFME1 getter remains in Team.cpp.

Paired frozen index90c15cdeca previews:
build/queue10-20261113/team-{before,after}.log. Multiple unrelated
list and killTeam provider conflicts remain; no linked-byte gain claimed.
