# Include the thing asset collector return in its extent

The old 336-byte claim at RVA 00143580 ends after ADD ESP,10h at 001436CD..001436CF. It omits RET 8 at 001436D0..001436D2; INT3 starts at 001436D3. This proves a complete 339-byte executable body. Both the final JE at 001436B3 and the final call at 001436B9 reach the common FS-chain and saved-register epilogue at 001436BE. All nine direct branches target instruction starts in the complete stream; no matched row overlaps it. Local retail PE/Capstone and Ghidra read_memory VA005436B0 independently agree.

The existing native ThingTemplateGetAssetList.cpp emits the full tail. Extend only the claim, verify its full body and all scoped siblings/references, and preserve source, pins and inherited identity.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.
