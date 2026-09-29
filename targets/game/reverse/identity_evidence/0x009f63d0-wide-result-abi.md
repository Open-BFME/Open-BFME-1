# 0x009F63D0 PartitionManagerImpl::GetObjectsInRange

The EA evidence table, `targets/game/reverse/ea_evidence.csv`, maps retail RVA `0x009F63D0` to the `PartitionManagerImpl::GetObjectsInRange` method in `Libraries/Source/partitionmanager/partitionmanager_impl.cpp`. The row marks `chain+direct` evidence as `strong`. This EA identity supersedes the earlier guessed name `BfmeWideResultSource::bfmeMakeWideResult`. The new `Rva009F2AB0Mask` type serves as a separate mask filter helper, not as the method's owner.

Four byte-matched forwarding functions call the body with a hidden result pointer and six stack arguments. They confirm the call ABI, but they do not prove its original name. The body spans 555 bytes and ends with `ret 0x1C` at offset `+0x228`. It loops through 17 twelve-byte records at `this+0x18` and calls the matched query at RVA `0x009F4130`. The address-derived extern `g_012DBD60` names its distance callback table because no source or pin proves a semantic name. The body may sort the result through the method at RVA `0x009F4020`.

`BfmeWideResultForward.cpp` contains the matched body beside its callers. `tools/probe.py` reports `EXACT` modulo 18 relocation slots, and the scoped `./build.sh` links all five matched rows.
