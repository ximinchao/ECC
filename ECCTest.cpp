#include <stdio.h>
#include "util.h"
#include "BigNum.h"

bool BigNumTest()
{
	bool bRtn = false;

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
	
	return 0;
}
