#include <stdio.h>
#include "util.h"
#include "BigNum.h"

bool BigNumTest()
{
	bool	bRtn = false;
	u32	i = 0;	
	u8	pbData[2] = {0xff, 0xf0};

	BigNum	*bn =new BigNum(pbData, sizeof(pbData));
	BigNum	*bn2 = new BigNum(*bn);
	
	bn->printContent();
	bn2->printContent();

	for (i=0; i<0x10; i++)
	{
		++(*bn);
		bn->printContent();
	}
	
	for (i=0; i<0x10; i++)
	{
		--(*bn);
		bn->printContent();
	}

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
