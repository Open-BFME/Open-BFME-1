// Apply a name-sync plan from `tools/ghidra_refdb.py sync-plan` to the open program:
//   -postScript apply_names.java <plan.tsv>
// Each plan line is rva<TAB>current<TAB>proposed<TAB>tier. Only evidence-tier names
// reach a plan (export / ilt / reloc); this script applies them and nothing else,
// tagging each with a plate comment so a later reader sees why the name is there.
// Run it only on the canonical reference project, never on an agent's working copy.
//@category Symbol
import java.io.BufferedReader;
import java.io.File;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.SourceType;

public class apply_names extends GhidraScript {
	@Override
	public void run() throws Exception {
		String[] args = getScriptArgs();
		if (args.length != 1) {
			throw new IllegalArgumentException("usage: <plan.tsv>");
		}
		long base = currentProgram.getImageBase().getOffset();
		int applied = 0, missing = 0;
		try (BufferedReader r = Files.newBufferedReader(new File(args[0]).toPath(), StandardCharsets.UTF_8)) {
			String line;
			while ((line = r.readLine()) != null) {
				String[] f = line.split("\t");
				if (f.length != 4) {
					continue;
				}
				Address entry = toAddr(base + Long.decode(f[0]));
				Function fn = getFunctionAt(entry);
				if (fn == null) {
					missing++;
					continue;
				}
				fn.setName(f[2], SourceType.IMPORTED);
				String note = "refdb-sync tier=" + f[3] + " was=" + f[1];
				String plate = fn.getComment();
				fn.setComment(plate == null ? note : plate + "\n" + note);
				applied++;
			}
		}
		println("apply_names: applied " + applied + ", no function at " + missing);
	}
}
