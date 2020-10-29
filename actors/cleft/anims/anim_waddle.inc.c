static const u16 cleft_anim_waddle_values[] = {
	0x0000, 0x0021, 0x0000, 0x0000, 0x0000, 0x0000, 0x7FFF, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x005F, 0x0140, 0x024E, 
	0x0330, 0x038E, 0x035B, 0x02D1, 0x0205, 0x010D, 0x0000, 0xFEF2, 0xFDFA, 
	0xFD2E, 0xFCA4, 0xFC71, 0xFCCF, 0xFDB1, 0xFEBF, 0xFFA0, 0xEAAA, 0xECDD, 
	0xF228, 0xF881, 0xFDCC, 0x0000, 0xFEC8, 0xFB80, 0xF6B3, 0xF0EA, 0xEAAA, 
	0xE469, 0xDEA0, 0xD9D4, 0xD68C, 0xD554, 0xD788, 0xDCD3, 0xE32C, 0xE876, 
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 
	0xFFFF, 0x0000, 0xEAAA, 0xE876, 0xE32C, 0xDCD3, 0xD788, 0xD554, 0xD68C, 
	0xD9D4, 0xDEA0, 0xE469, 0xEAAA, 0xF0EA, 0xF6B3, 0xFB80, 0xFEC8, 0x0000, 
	0xFDCC, 0xF881, 0xF228, 0xECDD, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
	0xFFFF, 0xFFFF, 0x0000, 0x0000, 
};

static const u16 cleft_anim_waddle_indices[] = {
	0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0002, 0x0001, 0x0003, 0x0001, 
	0x0004, 0x0001, 0x0005, 0x0001, 0x0006, 0x0010, 0x0007, 0x0014, 0x0017, 
	0x0014, 0x002B, 0x0009, 0x003F, 0x000B, 0x0048, 0x0014, 0x0053, 0x0011, 
	0x0067, 0x0001, 0x0078, 
};

static const struct Animation cleft_anim_waddle[] = {
	0,
	0,
	0,
	0,
	19,
	ANIMINDEX_NUMPARTS(cleft_anim_waddle_indices),
	cleft_anim_waddle_values,
	cleft_anim_waddle_indices,
	0,
};
