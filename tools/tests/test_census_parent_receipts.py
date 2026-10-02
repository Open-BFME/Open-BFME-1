"""Fresh preprocessor receipts remain available for STLport parent roots."""
import json
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build
import census_receipts as proofs


class CensusParentIncludeReceiptTests(unittest.TestCase):
    def test_cacheable_parent_root_also_keeps_the_fresh_pp_proof(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary) / "project"
            source = root / "game" / "unit.cpp"
            source.parent.mkdir(parents=True)
            source.write_text('#include "header.h"\n')
            header = source.parent / "header.h"
            header.write_text("// included\n")
            output = root / "unit.obj"
            output.parent.mkdir(parents=True, exist_ok=True)
            output.write_bytes(b"compiled object")
            sidecar = build._deps_sidecar(output)
            sidecar.write_text(json.dumps({"search_roots": ["@ROOT_PARENT@/include"]}))

            files = {str(path.resolve()): proofs.digest(path) for path in (source, header)}
            before = {"files": files, "preprocessed": "stable-pp", "signature": {},
                      "generations": {}}
            command, env = ["cl", "-c", str(source)], {"INCLUDE": ""}
            receipt = proofs.Receipts(root / "compile_inputs.json")
            with patch.object(build, "ROOT", root), \
                    patch.object(proofs, "snapshot", return_value=before), \
                    patch.object(proofs, "_normal_cache_current", return_value=True):
                receipt.after(source, output, command, env, before,
                              "Note: including file: " + str(header))
                self.assertIn(str(output.resolve()), receipt.entries)
                self.assertTrue(proofs._has_external_search_root(output))


if __name__ == "__main__":
    unittest.main()
