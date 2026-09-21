"""The decompile wrapper's output handling (no Ghidra needed)."""
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import ghidra_decompile  # noqa: E402

STREAM = """INFO  SCRIPT: decompile_function.java (HeadlessAnalyzer)
INFO  decompile_function.java> RVA 0x003E8E10 FUN_007e8e10 @ 007e8e10 size 1852 (GhidraScript)
INFO  decompile_function.java> REFERENCES TO ENTRY: (GhidraScript)
INFO  decompile_function.java>   004296b8 UNCONDITIONAL_JUMP thunk_FUN_007e8e10@004296b8 (GhidraScript)
INFO  decompile_function.java> DECOMPILE: (GhidraScript)
INFO  decompile_function.java>
undefined4 __thiscall FUN_007e8e10(int param_1)
{
  return 0;
}
 (GhidraScript)
WARN  some analyzer noise (Whatever)
INFO  decompile_function.java> RVA 0x1000 falls inside FUN_00401000 @ 00401000 (GhidraScript)
INFO  decompile_function.java> RVA 0x1000 FUN_00401000 @ 00401000 size 12 (GhidraScript)
INFO  decompile_function.java> DECOMPILE: (GhidraScript)
void FUN_00401000(void) {}
"""


def test_stream_splits_into_one_clean_block_per_function():
    blocks = ghidra_decompile.split_output(STREAM)
    assert list(blocks) == ["0x003e8e10", "0x1000"]
    first = blocks["0x003e8e10"]
    assert first.startswith("RVA 0x003E8E10 FUN_007e8e10")
    assert "undefined4 __thiscall FUN_007e8e10(int param_1)" in first
    assert "GhidraScript" not in first and "analyzer noise" not in first
    assert "void FUN_00401000(void) {}" in blocks["0x1000"]


def test_nothing_decompiled_is_an_empty_result():
    assert ghidra_decompile.split_output("INFO  HEADLESS: nothing to do (HeadlessAnalyzer)\n") == {}
