# aiMoveToPosition selection in the November 6 census

The fetched census at 4a9fc0c92b (workflow 42215929602) lists seven emitters of the struct-keyed AICommandInterface::aiMoveToPosition. All have the COMDAT digest a49d2f1ceb11 and the census verdict unknown. The sole exclusive definition is in AICommandInterfaceMovementOrders.cpp. The earlier OneRing 180-byte copy is absent in this index. The five queue-4 consumers still report a selected-provider blocker, totalling 1,826 bytes.

The current MovementOrders object has the 219-byte body. Its three external calls resolve to the original targets and the four exception-list operands are the expected absolute zero. The remaining DIR32 operand is the object-local exception handler at offset 3, targeting RVA 0x00BF9BFB in retail. The native unwind reader finds FuncInfo at 0x00DE75B4 and one cleanup at 0x00BF9BF0, which reaches the AICommandParms destructor via its original incremental-link thunk. The verifier leaves the local handler reference unknown and the selection check falls back to the exclusive owner's identity. A common digest does not prove the handler or the kept definition.

A complete check of each candidate handler's associated unwind records is the next proof needed. No symbol pin, selection rule, source or link-credit total was changed.
