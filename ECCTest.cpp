#include <stdio.h>
#include "util.h"
#include "BigNum.h"

bool BigNumTest()
{
	bool bRtn = false;
	u8 pbData[4] = {0xff, 0xff, 0xff, 0xf0};
	u32 i = 0;

	BigNum *bn1 = new BigNum();
	BigNum *bn2 = new BigNum(pbData, sizeof(pbData));
	BigNum *bn3 = new BigNum(pbData, sizeof(pbData), false);
	BigNum *bn4 = new BigNum(*bn3);
	BigNum bn5, bn6;

	bn1->printContent();
	bn2->printContent();
	bn3->printContent();
	bn4->printContent();

	(*bn1)[0] = 0x01;
	bn1->printContent();
	
	(*bn2)[1] = 0x02;
	bn2->printContent();
	
	(*bn1) = -0x05;
	bn1->printContent();

	for (i=0; i<10; i++)
	{
		++(*bn1);
		bn1->printContent();
	}

	for (i=0; i<10; i++)
	{
		--(*bn1);
		bn1->printContent();
	}

	bn5 = *bn1;
	bn5.printContent();

	bn6 = *bn2;
	bn6.printContent();

	bRtn = true;
END:
	return bRtn;
}

bool UtilTest()
{
	bool	bRtn = false;
	u32	uiBase = 15, uiExp = 103, uiMod = 143, uiRes = 0;

	if (!Util_ModExponent(uiBase, uiExp, uiMod, &uiRes))
	{
		bRtn = false;
		goto END;
	}

	printf("%d ^ %d mod %d = %d.\n", uiBase, uiExp, uiMod, uiRes);

	bRtn = true;
END:
	return bRtn;
}

int main()
{
	UtilTest();
	BigNumTest();

	return 0;
}
