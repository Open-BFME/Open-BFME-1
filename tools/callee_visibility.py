#!/usr/bin/env python3
"""Reproduce MSVC 7.1's caller dependence on a non-inlined callee body.

Compiler experiment only: writes under build/, never changes a claim or pin.
Run: python3 tools/callee_visibility.py
"""
import hashlib
import json
import uuid

import build
from capstone import Cs, CS_ARCH_X86, CS_MODE_32


CALLER = """extern void tick();
__declspec(noinline) void write(int *p);
int consume() {
    int x;
    write(&x);
    int saved = x;
    tick();
    return saved;
}
"""
VARIANTS = {
    "declaration": CALLER,
    "visible": CALLER + "__declspec(noinline) void write(int *p) { *p = 3; }\n",
    "escaping": CALLER + "int *escaped;\n"
    "__declspec(noinline) void write(int *p) { *p = 3; escaped = p; }\n",
}


def run():
    directory = build.ROOT / "build" / "callee_visibility" / uuid.uuid4().hex
    directory.mkdir(parents=True)
    disassembler = Cs(CS_ARCH_X86, CS_MODE_32)
    records = {}
    for label, source in VARIANTS.items():
        path = directory / (label + ".cpp")
        path.write_text(source, encoding="utf-8")
        obj = path.with_suffix(".obj")
        build.compile_source(path, obj)  # Always a fresh compile.
        body, relocs = build.read_object_symbol_bytes(obj, "?consume@@YAHXZ")
        calls = [symbol for _, kind, symbol in relocs if kind == 0x14]
        records[label] = {
            "source": source,
            "size": len(body),
            "bytes": bytes(body).hex(),
            "relocations": relocs,
            "calls": calls,
            "instructions": [f"{ins.mnemonic} {ins.op_str}".rstrip()
                             for ins in disassembler.disasm(bytes(body), 0)],
        }
        print(f"{label:12} {len(body):2} bytes: "
              + "; ".join(records[label]["instructions"]))

    expected_calls = ["?write@@YAXPAH@Z", "?tick@@YAXXZ"]
    reproduced = (
        all(row["calls"] == expected_calls for row in records.values())
        and records["declaration"]["bytes"] == records["escaping"]["bytes"]
        and records["visible"]["bytes"] != records["declaration"]["bytes"]
    )
    compiler_root = build.vc71_root() / "Vc7" / "bin"
    compiler_hashes = {
        name: hashlib.sha256((compiler_root / name).read_bytes()).hexdigest()
        for name in ("cl.exe", "c1xx.dll", "c2.dll")
    }
    report = {"compiler_sha256": compiler_hashes,
              "command": build.compiler_command(path, obj)[0],
              "records": records, "reproduced": reproduced}
    receipt = directory / "result.json"
    receipt.write_text(json.dumps(report, indent=2), encoding="utf-8")
    print(f"receipt: {receipt.relative_to(build.ROOT)}")
    print("REPRODUCED" if reproduced else "NOT REPRODUCED with this toolchain")
    return 0 if reproduced else 1


if __name__ == "__main__":
    raise SystemExit(run())
