# 0x009E0360 is Targa::YFlip

The 144-byte body at RVA 0x009E0360 (previously the address-derived
`?m009E0360@Rva009E0360@@QAEXXZ`) is `Targa::YFlip()`.

- Caller: `tools/callees.py 0x9E0BF0 404` on the matched
  `Targa::Load(const char*, char*, char*, bool)` (TARGA.CPP, byte-verified)
  reports one direct call to 0x009E0360, between its calls to the matched
  `Targa::XFlip` (0x009E0290) and `Targa::InvertImage`. The source's only
  call at that point is `YFlip();` under `TGAIDF_YORIGIN`.
- Pin: symbols.csv already pins `?YFlip@Targa@@QAEXXZ` at 0x009E0360
  (pin_consistency --symbol: consistent).
- Layout: the body reads Header.Width (+0x0C), Header.Height (+0x0E),
  Header.PixelDepth (+0x10) and mImage (+0x20), Targa's canonical offsets.
- Shape: per-byte exchange of mirrored scan lines, the Zero Hour TARGA.CPP
  YFlip "old code left in for reference"; TARGA.CPP now carries that body
  and the stride/_swapBytes rewrite (never retail) is gone.
