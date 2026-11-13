# Cast_Ray clamped-height helper emission

Queue7 d1c221c3d8 identifies duplicate getClipHeight. Keep the retail84-byte
provider in BaseHeightMapGetClipHeight.cpp; suppress the unused inline
copy in BaseHeightMap_Cast_Ray.cpp with imported forceinline. All five
retail call-site expansions stay byte-exact. The normal paired gate verifies
2/2 rows,39 floats and43 DIR32 references. The caller COFF has no
getClipHeight symbol, defined, undefined or imported. Declared-definitions
check passes. No flags, headers, types, layouts, pins or ledger edits.

BFME2 donor76f0baefa6f285d54bc1ca922397674312a5913f reviewed:
Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapCastRay.cpp
and reverse/attempt_support/ingame-ui-helpers-link-20261015/readme.md.
The native caller already cites the first as its semantic guide; the
second supports imported forceinline surplus-emission suppression. BFME1
inline expansion and BFME2 outlined sampling differ; no donor layout copied.

Paired frozen index90c15cdeca previews in
build/queue10-20261113/castray-{before,after}.log: caller duplicate disappears.
These are frozen-census diagnostics, not current closed-strict placement.
