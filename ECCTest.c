#include <stdio.h>
#include "util.h"

int main()
{
	unsigned int uiBase = 23, uiExp = 22, uiMod = 97, uiRes = 0;

	if (Util_ModExponent(uiBase, uiExp, uiMod, &uiRes))
	{
		printf("%d ^ %d mod %d = %d.\n", uiBase, uiExp, uiMod, uiRes);
	}
	
	return 0;
}
