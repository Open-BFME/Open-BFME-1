// cl: /DNDEBUG /MD /EHsc

// Retail 0x00730F30. If m_10, tail-call virtual slot 0x23C(arg); else return false.

class Gen_00730f30_Iface
{
public:
	virtual bool v0(int);
	virtual bool v1(int);
	virtual bool v2(int);
	virtual bool v3(int);
	virtual bool v4(int);
	virtual bool v5(int);
	virtual bool v6(int);
	virtual bool v7(int);
	virtual bool v8(int);
	virtual bool v9(int);
	virtual bool v10(int);
	virtual bool v11(int);
	virtual bool v12(int);
	virtual bool v13(int);
	virtual bool v14(int);
	virtual bool v15(int);
	virtual bool v16(int);
	virtual bool v17(int);
	virtual bool v18(int);
	virtual bool v19(int);
	virtual bool v20(int);
	virtual bool v21(int);
	virtual bool v22(int);
	virtual bool v23(int);
	virtual bool v24(int);
	virtual bool v25(int);
	virtual bool v26(int);
	virtual bool v27(int);
	virtual bool v28(int);
	virtual bool v29(int);
	virtual bool v30(int);
	virtual bool v31(int);
	virtual bool v32(int);
	virtual bool v33(int);
	virtual bool v34(int);
	virtual bool v35(int);
	virtual bool v36(int);
	virtual bool v37(int);
	virtual bool v38(int);
	virtual bool v39(int);
	virtual bool v40(int);
	virtual bool v41(int);
	virtual bool v42(int);
	virtual bool v43(int);
	virtual bool v44(int);
	virtual bool v45(int);
	virtual bool v46(int);
	virtual bool v47(int);
	virtual bool v48(int);
	virtual bool v49(int);
	virtual bool v50(int);
	virtual bool v51(int);
	virtual bool v52(int);
	virtual bool v53(int);
	virtual bool v54(int);
	virtual bool v55(int);
	virtual bool v56(int);
	virtual bool v57(int);
	virtual bool v58(int);
	virtual bool v59(int);
	virtual bool v60(int);
	virtual bool v61(int);
	virtual bool v62(int);
	virtual bool v63(int);
	virtual bool v64(int);
	virtual bool v65(int);
	virtual bool v66(int);
	virtual bool v67(int);
	virtual bool v68(int);
	virtual bool v69(int);
	virtual bool v70(int);
	virtual bool v71(int);
	virtual bool v72(int);
	virtual bool v73(int);
	virtual bool v74(int);
	virtual bool v75(int);
	virtual bool v76(int);
	virtual bool v77(int);
	virtual bool v78(int);
	virtual bool v79(int);
	virtual bool v80(int);
	virtual bool v81(int);
	virtual bool v82(int);
	virtual bool v83(int);
	virtual bool v84(int);
	virtual bool v85(int);
	virtual bool v86(int);
	virtual bool v87(int);
	virtual bool v88(int);
	virtual bool v89(int);
	virtual bool v90(int);
	virtual bool v91(int);
	virtual bool v92(int);
	virtual bool v93(int);
	virtual bool v94(int);
	virtual bool v95(int);
	virtual bool v96(int);
	virtual bool v97(int);
	virtual bool v98(int);
	virtual bool v99(int);
	virtual bool v100(int);
	virtual bool v101(int);
	virtual bool v102(int);
	virtual bool v103(int);
	virtual bool v104(int);
	virtual bool v105(int);
	virtual bool v106(int);
	virtual bool v107(int);
	virtual bool v108(int);
	virtual bool v109(int);
	virtual bool v110(int);
	virtual bool v111(int);
	virtual bool v112(int);
	virtual bool v113(int);
	virtual bool v114(int);
	virtual bool v115(int);
	virtual bool v116(int);
	virtual bool v117(int);
	virtual bool v118(int);
	virtual bool v119(int);
	virtual bool v120(int);
	virtual bool v121(int);
	virtual bool v122(int);
	virtual bool v123(int);
	virtual bool v124(int);
	virtual bool v125(int);
	virtual bool v126(int);
	virtual bool v127(int);
	virtual bool v128(int);
	virtual bool v129(int);
	virtual bool v130(int);
	virtual bool v131(int);
	virtual bool v132(int);
	virtual bool v133(int);
	virtual bool v134(int);
	virtual bool v135(int);
	virtual bool v136(int);
	virtual bool v137(int);
	virtual bool v138(int);
	virtual bool v139(int);
	virtual bool v140(int);
	virtual bool v141(int);
	virtual bool v142(int);
	virtual bool v143(int);
};

class Gen_00730f30
{
public:
	bool call(int a);

private:
	unsigned char m_pad[0x10];
	Gen_00730f30_Iface *m_10;
};

// ?call@Gen_00730f30@@QAE_NH@Z
bool Gen_00730f30::call(int a)
{
	if (m_10)
		return m_10->v143(a);
	return false;
}
