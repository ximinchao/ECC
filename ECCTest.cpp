#include <stdio.h>
#include "util.h"
#include "BigNum.h"

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
	(*bn1) = -0x1f;
	bn1->printContent();

	bRtn = true;
END:
	return bRtn;
}

bool BigNumIncTest()
{
	bool bRtn = false;
	u8 pbData[4] = {0xff, 0xff, 0xff, 0xf0};
	u32 i = 0;

	BigNum *bn = new BigNum();

	printf("=======BigNumIncTest========\n");

	(*bn) = -0x1f;
	bn->printContent();

	printf("Test ++: ");
	for (i=0; i<0x20; i++)
	{
		++(*bn);
	}
	bn->printContent();

	printf("Test --: ");
	for (i=0; i<0x20; i++)
	{
		--(*bn);
	}
	bn->printContent();

	bRtn = true;
END:
	return bRtn;
}

bool BigNumAddTest()
{
	bool bRtn = false;
	u8 pbData[4] = {0xff, 0xff, 0xff, 0xf0};
	u32 i = 0;

	BigNum *bn = new BigNum();
	BigNum *bn1 = new BigNum();
	BigNum *bn2 = new BigNum(pbData, sizeof(pbData));
	
	printf("=======BigNumAddTest========\n");
	
	for (i=0; i<5; i++)
	{
		switch(i)
		{
			case 0:
				*bn1 = -0x1f;
				break;
			case 1:
				bn1->setData(pbData, sizeof(pbData), true);
				bn2->setData(pbData, sizeof(pbData), false);
				break;
			case 2:
				*bn1 = 0xf111;
				*bn2 = 0xfff;
				break;
			case 3:
				*bn1 = -0x0100;
				*bn2 = 0xff;
				break;
			case 4:
				*bn1 = 0x1f;
				*bn2 = 0xffe1;
				break;
		}

		printf("***case %d***\n", i);
		printf("bn1: ");
		bn1->printContent();
		printf("bn2: ");
		bn2->printContent();
		printf("BN_Add: \n");
		BN_Add(*bn1, *bn2, *bn2);
		bn1->printContent();
		bn2->printContent();
	}

	bRtn = true;
END:
	return bRtn;
}

bool BigNumMinusTest()
{
	bool bRtn = false;
	u8 pbData[4] = {0xff, 0xff, 0xff, 0xf0};
	u32 i = 0;

	BigNum *bn = new BigNum();
	BigNum *bn1 = new BigNum();
	BigNum *bn2 = new BigNum(pbData, sizeof(pbData));
	
	printf("=======BigNumMinusTest========\n");
	
	for (i=0; i<5; i++)
	{
		switch(i)
		{
			case 0:
				*bn1 = -0x1f;
				break;
			case 1:
				bn1->setData(pbData, sizeof(pbData), true);
				bn2->setData(pbData, sizeof(pbData), false);
				break;
			case 2:
				*bn1 = 0xf111;
				*bn2 = 0xfff;
				break;
			case 3:
				*bn1 = -0x0100;
				*bn2 = 0xff;
				break;
			case 4:
				*bn1 = 0x1f;
				*bn2 = 0xffe1;
				break;
		}

		printf("***case %d***\n", i);
		printf("bn1: ");
		bn1->printContent();
		printf("bn2: ");
		bn2->printContent();
		printf("BN_Minus: \n");
		BN_Minus(*bn1, *bn2, *bn2);
		bn1->printContent();
		bn2->printContent();
	}

	bRtn = true;
END:
	return bRtn;
}

int main()
{
	UtilTest();
	BigNumIncTest();
	BigNumAddTest();
	BigNumMinusTest();

	return 0;
}
