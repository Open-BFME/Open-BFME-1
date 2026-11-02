# 0x002475A0 HordeContain::DoXfer (1814 B): fresh rewrite, shape 0.914

Session a1/532, 2026-11-02. Bank: targets/game/reverse/attempts/0x002475a0.cpp
(1795/1814 B, shape 0.914; the previous bank was 0.43 with no visible flow).

## Identity
ilt_oracle CONFIRMS ?DoXfer@HordeContain@@MAEXAAVXfer@@@Z (BFME snapshot
spelling; ZH ?xfer@...PAVXfer is CONTRADICTED). The matched AODHordeContain
transfer calls it through ILT 0x00024BDB. [BFME 2 donor] Open-BFME-2 45afcff3
HordeContainXfer.cpp (version 13) matches the opening order only; BFME 1 is
version 3.

## Flow read from retail (all in the bank)
Base Gen_0022CD40::bfmeSeed, light-CRC gate, Version(1,3); Bools +E8/+E9/+1FE
and uint +140; list<int> +138 (int values, inline push_back); the
Rva00226FA0Less map<int,int> +120 (key via Rva0010C3C0); BitFlags +EC
(0x1CB270); set<Gen_t_000ef440_k4> +114 (insert_unique 0xEEC50 by ILT 0x499F9);
version < 3 block: vector<Gen_t_0023db70_m4pod> +1C0 of new'ed 8-byte records
(ctor {0,-1}, Version(1,1), bfmeHandOver_000353C8, int +4; push_back through
_M_insert_overflow 0x23B210); Bools +1FC/+1FD; vector<Rva00244A80Element 28 B>
+1D8 resized on load (resize(n) -> _M_fill_insert 0x2403E0) then per record
Coord3D +4 and Bool +10 through a default-constructed local copy; tail scalars
(+1E4 id, +1E8, +1B4 id, +1B8, +1BC id, +20C, +1CC, +1D0, +1D4, chained
Coord3D +214 == Bool +220, +1EC, +1F0, +1EC again, +1F8 id, +200, +204, +205,
+208 id) and Bool +221 when the version > 1.

## Remaining
Frame 0x60 vs retail 0x40 (/FAsc): retail shares recordVersion, the +1C0 count
(dead xfer home) and the loop locals more tightly, and has no separate copy of
resize's by-value `_Tp()` argument. A user-declared copy ctor on the 28-byte
element removes that copy (frame 0x44) but changes the vector code paths
(1757 B). Next: frame grouping per variable, then the erase loop shape.
