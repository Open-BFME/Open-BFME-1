namespace D3DXShader
{
	class CShaderProgram
	{
	protected:
		long EmitDSX();
		long EmitDSY();
		long EmitFRC();
		long EmitMIN();
		long EmitMAX();
		long EmitLT();
		long EmitGE();
		long EmitADD();
		long EmitMUL();
		long EmitDST();
		long EmitLIT();
		long EmitCMP();
		long EmitCND();
		long EmitSINCOS();

		long EmitInstSimple(unsigned long opcode);
	};

	long CShaderProgram::EmitDSX() { return EmitInstSimple(0x5b); }
	long CShaderProgram::EmitDSY() { return EmitInstSimple(0x5c); }
	long CShaderProgram::EmitFRC() { return EmitInstSimple(0x13); }
	long CShaderProgram::EmitMIN() { return EmitInstSimple(0x0a); }
	long CShaderProgram::EmitMAX() { return EmitInstSimple(0x0b); }
	long CShaderProgram::EmitLT() { return EmitInstSimple(0x0c); }
	long CShaderProgram::EmitGE() { return EmitInstSimple(0x0d); }
	long CShaderProgram::EmitADD() { return EmitInstSimple(0x02); }
	long CShaderProgram::EmitMUL() { return EmitInstSimple(0x05); }
	long CShaderProgram::EmitDST() { return EmitInstSimple(0x11); }
	long CShaderProgram::EmitLIT() { return EmitInstSimple(0x10); }
	long CShaderProgram::EmitCMP() { return EmitInstSimple(0x58); }
	long CShaderProgram::EmitCND() { return EmitInstSimple(0x50); }
	long CShaderProgram::EmitSINCOS() { return EmitInstSimple(0x23); }
}
