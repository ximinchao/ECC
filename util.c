#include "util.h"

bool Util_IsLittleEndian()
{
	u32 i = 0x0123;
	
	if ((i & 0xFF) != 0x23)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Util_ModExponent(const u32 uiBase, const u32 uiExp, const u32 uiMod, u32* const puiRes)
{
	bool bRet =false;

	u32 i = 0;
	
	u32 x = 0, H = 0, n = 0, r = 0, t = 0;

	if (!puiRes)
	{
		bRet = false;
		goto END;
	}

	if (uiExp == 0)
	{
		*puiRes = 1;
		bRet = true;
		goto END;
	}

	x = uiBase;
	H = uiExp;
	n = uiMod;
	t = sizeof(H)*8;

	while (!(H & 0x8000))
	{
		t--;
		H = (H<<1);
	}
	H = (H<<1);
	
	r = x;
	for (i=0; i<t; i++)
	{
		r = (r*r) % n;
		
		if (H & 0x80)
		{
			r = (r*x) % n;
		}
		H = (H<<1);
	}
	*puiRes = r;
	
	bRet = true;
END:
	return bRet;
}
