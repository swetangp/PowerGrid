#pragma once
#include "soln.h"

soln::soln()
{

}
SummaryCard2::SummaryCard2()
{

}
void SummaryCard2::displaySummary()
{
	cout << "1. Determine Turn Order\n" << endl;
	cout << "2. Buy Power Plant\nThe first player begins.\nPer round, each may buy only one power plant\n" << endl;
	cout << "3. Buy Raw Materials\nThe last player begins.\nMaximum double input per power plant.\n" << endl;
	cout << "4. Building\nThe last player begins.\n" << endl;
	cout << "5. Bureaucracy\n-Get money.\n-In phase 1 and 2: Place highest power plant under the stack.\nIn phase 3: Remove lowest power plant from the game.\nRestock raw materials\n" << endl;
}
void SummaryCard2::displayScoring()
{
	int houseScore[20];
	for (int i = 0; i <= 21; i++)
	{
		houseScore[i] = i;
	}
	int electroScore[21] = { 10, 22, 33, 44, 54, 64, 73, 82, 90, 98, 105, 112, 118, 124, 129, 134, 138, 142, 145, 148, 150 };
}
PowerPlantCard2::PowerPlantCard2()
{
	set[0] = PowerPlantCard2(3, "oil", 2, NULL, NULL, "black", 1);
	set[1] = PowerPlantCard2(4, "coal", 2, NULL, NULL, "brown", 1);
	set[2] = PowerPlantCard2(5, "oil", 2, "coal", 2, "black/brown", 1);
	set[3] = PowerPlantCard2(6, "garbage", 1, NULL, NULL, "yellow", 1);
	set[4] = PowerPlantCard2(7, "oil", 3, NULL, NULL, "black", 2);
	set[5] = PowerPlantCard2(8, "coal", 3, NULL, NULL, "brown", 21);
	set[6] = PowerPlantCard2(9, "oil", 1, NULL, NULL, "black", 1);
	set[7] = PowerPlantCard2(10, "coal", 2, NULL, NULL, "brown", 2);
	set[8] = PowerPlantCard2(11, "uranium", 2, NULL, NULL, "red", 2);
	set[9] = PowerPlantCard2(12, "coal", 2, "oil", 2, "black/brown", 2);
	set[10] = PowerPlantCard2(13, "none", 0, NULL, NULL, "green", 1);
	set[11] = PowerPlantCard2(14, "garbage", 2, NULL, NULL, "yellow", 2);
	set[12] = PowerPlantCard2(15, "coal", 2, NULL, NULL, "brown", 3);
	set[13] = PowerPlantCard2(16, "oil", 2, NULL, NULL, "black", 3);
	set[14] = PowerPlantCard2(17, "uranium", 1, NULL, NULL, "red", 2);
	set[15] = PowerPlantCard2(18, "none", 0, NULL, NULL, "green", 2);
	set[16] = PowerPlantCard2(19, "garbage", 2, NULL, NULL, "yellow", 3);
	set[17] = PowerPlantCard2(20, "coal", 3, NULL, NULL, "black", 5);
	set[18] = PowerPlantCard2(21, "oil", 2, "coal", 2, "black/brown", 4);
	set[19] = PowerPlantCard2(22, "none", 0, NULL, NULL, "green", 2);
	set[20] = PowerPlantCard2(23, "uranium", 1, NULL, NULL, "red", 3);
	set[21] = PowerPlantCard2(24, "garbage", 2, NULL, NULL, "yellow", 4);
	set[22] = PowerPlantCard2(25, "coal", 2, NULL, NULL, "brown", 5);
	set[23] = PowerPlantCard2(26, "oil", 2, NULL, NULL, "black", 5);
	set[24] = PowerPlantCard2(27, "none", 0, NULL, NULL, "green", 3);
	set[25] = PowerPlantCard2(28, "uranium", 1, NULL, NULL, "red", 4);
	set[26] = PowerPlantCard2(29, "coal", 1, "oil", 1, "black/brown", 4);
	set[27] = PowerPlantCard2(30, "garbage", 3, NULL, NULL, "yellow", 6);
	set[28] = PowerPlantCard2(31, "coal", 3, NULL, NULL, "brown", 6);
	set[29] = PowerPlantCard2(32, "oil", 3, NULL, NULL, "black", 6);
	set[30] = PowerPlantCard2(33, "none", 0, NULL, NULL, "green", 4);
	set[31] = PowerPlantCard2(34, "uranium", 1, NULL, NULL, "red", 5);
	set[32] = PowerPlantCard2(35, "oil", 1, NULL, NULL, "black", 5);
	set[33] = PowerPlantCard2(36, "coal", 3, NULL, NULL, "brown", 7);
	set[34] = PowerPlantCard2(37, "none", 0, NULL, NULL, "green", 4);
	set[35] = PowerPlantCard2(38, "garbage", 3, NULL, NULL, "yellow", 7);
	set[35] = PowerPlantCard2(39, "uranium", 1, NULL, NULL, "red", 6);
	set[36] = PowerPlantCard2(40, "oil", 2, NULL, NULL, "black", 6);
	set[37] = PowerPlantCard2(42, "coal", 2, NULL, NULL, "brown", 6);
	set[38] = PowerPlantCard2(44, "none", 0, NULL, NULL, "green", 5);
	set[39] = PowerPlantCard2(46, "coal", 3, "oil", 3, "brown", 7);
	set[40] = PowerPlantCard2(50, "none", 0, NULL, NULL, "blue", 6);

}
PowerPlantCard2::PowerPlantCard2(int n, string rT, int rC, string rT2, int rC2, string c, int hC)
{
	number = n;
	resourceType = rT;
	resourceCost = rC;
	resourceType2 = rT2;
	resourceCost = rC2;
	colour = c;
	houseCost = hC;
}