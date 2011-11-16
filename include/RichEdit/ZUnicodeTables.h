#ifndef ZUNICODETABLES_H
#define ZUNICODETABLES_H

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZUnicodeTables;
#else
class ZUnicodeTables
{
public:
	// ??? int ???
	int case_info;
	int combining_info;
	int decimal_info;
	int decomposition_info;
	int decomposition_map;
	int direction_info;
	int indicScripts;
	int ligature_info;
	int ligature_map;
	int line_break_info;
	int otherScripts;
	int scriptTable;
	int symmetricPairsSize;
	int symmetricPairs;
	int unicode_info;
};
#endif

#endif
