#include <stdio.h>
#include "util.h"

int main()
{
	u32 uiBase = 15, uiExp = 103, uiMod = 143, uiRes = 0;

	if (Util_ModExponent(uiBase, uiExp, uiMod, &uiRes))
	{
		printf("%d ^ %d mod %d = %d.\n", uiBase, uiExp, uiMod, uiRes);
	}
	
	return 0;
}
