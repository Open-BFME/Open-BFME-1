# 0x001D9540 bank naming

The older bank names its owner `BfmeVecCD` and its helper `BfmeAllocCD`, but it marks both identities unknown in `attempt_history/0x001d9540/a76ee8005a4f2705a98c992c97a453121cc8623e160348ae87031a2f15079624.json`.

ILT 0x0001D949 reaches 0x001D95B0, and ILT 0x00044166 reaches 0x001D95A0. Callers assign conflicting vector types to 0x001D95A0 and disagree about the base helper. No caller or table names the owner at 0x001D9540.

The current bank uses `Rva001D9540` and `Rva001D9540Alloc` to keep the retail address. It uses `m_pad` for one untyped byte. The probe matches all 67 bytes outside relocations, but conflicting helper identities still prevent a linked conversion.
