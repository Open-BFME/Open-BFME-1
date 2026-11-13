# Radius cursor Drawable helper emission

Queue21 d1c221c3d8: the radius-cursor TU emits a surplus getObject copy
whose COMDAT differs from the kept body. Its inline implementation remains
unchanged; imported forceinline suppresses only the unused standalone
copy. The531-byte caller at0043DBE0 passes the normal byte and relocation
gate, including6 switch entries,1 float and3 DIR32 references. Zero baseline
findings. The current COFF has no getObject symbol or import. No class,
layout, identity, flag, pin, alias, header or ledger edit.

Donor76f0baefa6f285d54bc1ca922397674312a5913f reviewed:
Code/GameEngine/Include/GameClient/Drawable.h exposes the same trivial
getter purpose; reverse/attempt_support/ingame-ui-helpers-link-20261015/
readme.md supports surplus-inline emission suppression. The existing
local+0xFC field and531-byte extent remain independent BFME1 evidence.

Paired frozen index90c15cdeca preview logs:
build/queue10-20261113/cursor-{before,after}.log. Before has two findings:
getObject COMDAT and handleRadiusCursor selected-provider conflict. The
latter is independent and remains; no linked-byte gain is claimed.
