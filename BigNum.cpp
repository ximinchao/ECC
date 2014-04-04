#include "BigNum.h"

/**************FRIEND FUNCTION********************/
bool BN_IsLittleEndian()
{
	u32 uiTmp = 0x0001;
	bool bRtn = false;

	if (*((u8*)&uiTmp) != 0)
	{
		bRtn = true;
	}

	return bRtn;
}

bool BN_ReverseBuffer(u8 *const pbData, const u32 uiDataSize)
{
	bool bRtn = false;
	u32 i = 0;

	if (!pbData || !uiDataSize)
	{
		bRtn = false;
		goto END;
	}

	for (i=0; i<uiDataSize/2; i++)
	{
		pbData[i] = pbData[i] ^ pbData[uiDataSize-i-1];
		pbData[uiDataSize-i-1] = pbData[i] ^ pbData[uiDataSize-i-1];
		pbData[i] = pbData[i] ^ pbData[uiDataSize-i-1];
	}

	bRtn = true;
END:
	return bRtn;
}

i8 BN_Compare_abs(const BigNum& bn1, const BigNum& bn2)
{
	i8 cRes = 0;
	u32 uiDataSize1 = 0, uiDataSize2 = 0;
	std::vector<u8>::const_reverse_iterator rit1, rit2;

	if (&bn1 == &bn2)
	{
		cRes = 0;
		goto END;
	}

	uiDataSize1 = bn1.m_vData.size();
	uiDataSize2 = bn2.m_vData.size();

	if (uiDataSize1 > uiDataSize2)
	{
		cRes = 1;
	}
	else if (uiDataSize1 < uiDataSize2)
	{
		cRes = -1;
	}
	else
	{
		rit1 = bn1.m_vData.rbegin();
		rit2 = bn2.m_vData.rbegin();

		while (rit1 != bn1.m_vData.rend())
		{
			if (*rit1 != *rit2)
			{
				if (*rit1 > *rit2)
				{
					cRes = 1;
				}
				else
				{
					cRes = -1;
				}
				break;
			}
			++rit1;
			++rit2;
		}
	}

END:
	return cRes;
}

i8 BN_Compare_abs(const BigNum& bn, const u32 uiData)
{
	u8 pbData[4] = {0};
	BigNum tmpBN;

	std::memcpy(pbData, &uiData, 4);
	if (BN_IsLittleEndian())
	{
		BN_ReverseBuffer(pbData, 4);
	}
	
	tmpBN.setData(pbData, sizeof(pbData));
	
	return BN_Compare_abs(bn, tmpBN);
}

i8 BN_Compare_abs(const u32 uiData, const BigNum& bn)
{
	return (-1)*BN_Compare_abs(bn, uiData);
}

bool BN_Add_abs(const BigNum& bn1, const BigNum& bn2, BigNum& bnRes)
{
	bool bRtn = false;
	std::vector<u8>::const_iterator itr1, itr1end, itr2, itr2end;
	std::vector<u8>::iterator itrRes;
	u32	uiRes = 0;
	u8	ucCarry = 0;
	
	itr1 = bn1.m_vData.begin();
	itr1end = bn1.m_vData.end();
	itr2 = bn2.m_vData.begin();
	itr2end = bn2.m_vData.end();
	itrRes = bnRes.m_vData.begin();

	while ((itr1 != itr1end) || (itr2 != itr2end) || (ucCarry != 0))
	{
		uiRes = 0;
		if (itr1 != itr1end)
		{
			uiRes += *itr1;
			++itr1;
		}
		if (itr2 != itr2end)
		{
			uiRes += *itr2;
			++itr2;
		}
		uiRes += ucCarry;
		
		if (uiRes > 0xff)
		{
			ucCarry = (u8)(uiRes >> 8);
			
			if (itrRes != bnRes.m_vData.end())
			{
				*itrRes = (u8)(uiRes & 0xff);
			}
			else
			{
				bnRes.m_vData.push_back((u8)(uiRes & 0xff));
			}
		}
		else
		{
			ucCarry = (u8)0;
			
			if (itrRes != bnRes.m_vData.end())
			{
				*itrRes = (u8)uiRes;
			}
			else
			{
				bnRes.m_vData.push_back((u8)(uiRes));
			}
		}

		++itrRes;
	}

	bRtn = true;

	bnRes.BN_Reorganize();
	return bRtn;
}

bool BN_Minus_abs(const BigNum& bn1, const BigNum& bn2, BigNum& bnRes)
{
	bool bRtn = false;
	std::vector<u8>::const_iterator itr1, itr1end, itr2, itr2end;
	std::vector<u8>::iterator itrRes;
	i32 iRes = 0;
	u8 ucCarry = 0;
	i8 iComRes = 0;

	iComRes = BN_Compare_abs(bn1, bn2);
	if (iComRes < 0)
	{
		bRtn = false;
		goto END;
	}
	else if (iComRes == 0)
	{
		bnRes = 0;
		bRtn = true;
		goto END;
	}
	
	itr1 = bn1.m_vData.begin();
	itr1end = bn1.m_vData.end();
	itr2 = bn2.m_vData.begin();
	itr2end = bn2.m_vData.end();
	itrRes = bnRes.m_vData.begin();

	//now, bn1.size >= bn2.size
	while ((itr1 != itr1end) || (ucCarry != 0))
	{
		iRes = (i32)(*itr1) - ucCarry;
		ucCarry = 0;
		
		if (itr2 != itr2end)
		{
			if (iRes < (i32)(*itr2))
			{
				ucCarry = 1;
				iRes += 0x100;
			}
			iRes -= (*itr2);

			++itr2;
		}

		if (itrRes != bnRes.m_vData.end())
		{
			*itrRes = (u8)iRes;
		}
		else
		{
			bnRes.m_vData.push_back((u8)(iRes));
		}

		++itr1;
		++itrRes;
	}

	bRtn = true;
END:
	bnRes.BN_Reorganize();
	return bRtn;
}

//not implement
bool BN_Multi_abs(const BigNum& bn1, const BigNum& bn2, BigNum& bnRes)
{
	bool bRtn = false;

	return bRtn;
}

//not implement
bool BN_Divide_abs(const BigNum& bn1, const BigNum& bn2, BigNum& bnRes)
{
	bool bRtn = false;

	return bRtn;
}

bool BN_Add(const BigNum& bn1, const BigNum& bn2, BigNum& bnRes)
{
	bool bRtn = false;
	i8 iComRes = 0;

	if (bn1.m_bPositive == bn2.m_bPositive)
	{
		BN_Add_abs(bn1, bn2, bnRes);
		bnRes.m_bPositive = bn1.m_bPositive;
	}
	else
	{
		iComRes = BN_Compare_abs(bn1, bn2);
		if (iComRes > 0)
		{
			//bn1>bn2
			BN_Minus_abs(bn1, bn2, bnRes);
			bnRes.m_bPositive = bn1.m_bPositive;
		}
		else if (iComRes < 0)
		{
			//bn1<bn2
			BN_Minus_abs(bn2, bn1, bnRes);
			bnRes.m_bPositive = bn2.m_bPositive;
		}
		else
		{
			bnRes = 0;
			bnRes.m_bPositive = true;
		}
	}
	bRtn = true;
END:
	return bRtn;
}

bool BN_Minus (const BigNum& bn1, const BigNum& bn2, BigNum& bnRes)
{
	bool bRtn = false;
	i8 iComRes = 0;

	if (bn1.m_bPositive != bn2.m_bPositive)
	{
		BN_Add_abs(bn1, bn2, bnRes);
		bnRes.m_bPositive = bn1.m_bPositive;
	}
	else
	{
		iComRes = BN_Compare_abs(bn1, bn2);
		if (iComRes > 0)
		{
			//bn1>bn2
			BN_Minus_abs(bn1, bn2, bnRes);
			bnRes.m_bPositive = bn1.m_bPositive;
		}
		else if (iComRes < 0)
		{
			//bn1<bn2
			BN_Minus_abs(bn2, bn1, bnRes);
			bnRes.m_bPositive = !(bn1.m_bPositive);
		}
		else
		{
			bnRes = 0;
			bnRes.m_bPositive = true;
		}
	}
	bRtn = true;
END:
	return bRtn;
}

//not implement
bool BN_Multi(const BigNum& bn1, const BigNum& bn2, BigNum& bnRes)
{
	bool bRtn = false;
	return bRtn;
}
//not implement
bool BN_Divide(const BigNum& bn1, const BigNum& bn2, BigNum& bnRes)
{
	bool bRtn = false;
	return bRtn;
}
//not implement
bool BN_Mode(const BigNum& bn1, const BigNum& bn2, BigNum& bnRes)
{
	bool bRtn = false;
	return bRtn;
}
//not implement
bool BN_Exp(const BigNum& bn1, const BigNum& bn2, BigNum& bnRes)
{
	bool bRtn = false;
	return bRtn;
}

/*************PRIVATE***************/
bool BigNum::BN_Inc_abs()
{
	bool bRtn = false;
	std::vector<u8>::iterator itr;
	bool bOperate = false;

	itr = m_vData.begin();
	while (itr != m_vData.end())
	{
		if (*itr == 0xff)
		{
			*itr = 0;
		}
		else
		{
			*itr += 1;
			bOperate = true;
			break;
		}

		++itr;
	}

	if (!bOperate)
	{
		m_vData.push_back((u8)0x01);
		bOperate = true;
	}

	bRtn = true;
	BN_Reorganize();
	return bRtn;
}

bool BigNum::BN_Dec_abs()
{
	bool bRtn = false;
	std::vector<u8>::iterator itr;
	std::vector<u8>::reverse_iterator rit;

	if (BN_IsZero())
	{
		bRtn = false;
		goto END;
	}

	itr = m_vData.begin();
	while (itr != m_vData.end())
	{
		if (*itr == 0)
		{
			*itr = 0xff;
		}
		else
		{
			*itr -= 1;
			break;
		}

		++itr;
	}

	bRtn = true;
END:
	BN_Reorganize();
	return bRtn;
}

bool BigNum::BN_IsZero() const
{
	bool bRtn = false;
	
	if ((m_vData.size() == 1) && (m_vData[0] == 0))
	{
		bRtn = true;
	}

	return bRtn;
}

bool BigNum::BN_Reorganize()
{
	bool bRtn = false;
	std::vector<u8>::reverse_iterator rit;
	u32 uiDataSize = 0;

	uiDataSize = m_vData.size();
	rit = m_vData.rbegin();
	while ((uiDataSize > 1) && (*rit == 0))
	{
		m_vData.pop_back();
		++rit;
		--uiDataSize;
	}

	if ((uiDataSize == 1) && (m_vData[0] == 0))
	{
		//Zero
		m_bPositive = true;
	}
	
	bRtn = true;
END:
	return bRtn;
}

/*********************PUBLIC*********************/
//CONSTRUCTOR
BigNum::BigNum()
{
	m_bPositive = true;
	m_vData.reserve(BIGNUM_DEF_INITSIZE);
	m_vData.push_back((u8)0);
}

BigNum::BigNum(const BigNum& bn)
{
	m_bPositive = bn.m_bPositive;

	m_vData.reserve(BIGNUM_DEF_INITSIZE);
	std::copy(bn.m_vData.begin(), bn.m_vData.end(), back_inserter(m_vData));
	
	BN_Reorganize();
}

BigNum::BigNum(const u8* const pbContent, const u32 uiContentSize, const bool bPositive)
{
	setData(pbContent, uiContentSize, bPositive);
}

BigNum::~BigNum()
{
	m_vData.erase(m_vData.begin(), m_vData.end());
}

u32 BigNum::getSize() const
{
	u32	uiDataSize = 0;

	uiDataSize = (u32)m_vData.size();

	return uiDataSize;
}

#ifdef BIGNUM_SUPPORT_PRINT
bool BigNum::printContent() const
{
	bool	bRtn = false;
	u32	i = 0, uiDataSize = 0;
	//std::ostream::fmtflags osFlagOld = 0;

	//osFlagOld = std::cout.flag();//save old cout format flag, and set new format flag

	if (m_bPositive)
	{
		std::cout << "+";
	}
	else
	{
		std::cout << "-";
	}

	uiDataSize = (u32)m_vData.size();
	for (i=0; i<uiDataSize; i++)
	{
		std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << (u32)m_vData.at(uiDataSize-i-1) << " ";
	}
	std::cout << std::endl;

	bRtn = true;
END:
	//std::cout.flag(osFlagOld);//restore cout format flag
	return bRtn;
}
#endif

u8& BigNum::operator [](u32 idx)
{
	u32 uiSize = m_vData.size();

	if (idx < uiSize)
	{
		return m_vData.at(uiSize-idx-1);
	}

	return m_vData.at(uiSize-1);
}

bool BigNum::setData(const u8* const pbContent, const u32 uiContentSize, const bool bPositive)
{
	bool bRtn = false;
	u32	i = 0;

	if (!pbContent || !uiContentSize)
	{
		bRtn = false;
		goto END;
	}
	
	m_bPositive = bPositive;
	m_vData.resize(0);
	m_vData.reserve(BIGNUM_DEF_INITSIZE);
	
	for (i=0; i<uiContentSize; i++)
	{
		m_vData.push_back(pbContent[uiContentSize-i-1]);
	}

	bRtn = true;
	BN_Reorganize();
END:
	return bRtn;
}

BigNum& BigNum::operator ++()
{
	if (m_bPositive)
	{
		BN_Inc_abs();
	}
	else
	{
		BN_Dec_abs();
		BN_Reorganize();
	}

	return *this;
}

BigNum& BigNum::operator --()
{
	if (!m_bPositive)
	{
		BN_Inc_abs();
	}
	else if (BN_IsZero())
	{
		//Zero
		BN_Inc_abs();
		m_bPositive = false;
	}
	else
	{
		BN_Dec_abs();
		BN_Reorganize();
	}

	return *this;
}

BigNum& BigNum::operator = (const BigNum& bn)
{
	if (&bn == this)
	{
		goto END;
	}

	m_bPositive = bn.m_bPositive;
	m_vData.resize(0);
	m_vData.reserve(BIGNUM_DEF_INITSIZE);
	std::copy(bn.m_vData.begin(), bn.m_vData.end(), back_inserter(m_vData));
END:
	BN_Reorganize();
	return *this;
}

BigNum& BigNum::operator += (const BigNum& bn)
{
	BN_Add(*this, bn, *this);
	return *this;
}

BigNum& BigNum::operator -= (const BigNum& bn)
{
	BN_Minus(*this, bn, *this);
	return *this;
}

//not implement
BigNum& BigNum::operator *= (const BigNum& bn)
{
	return *this;
}

//not implement
BigNum& BigNum::operator /= (const BigNum& bn)
{
	return *this;
}

//not implement
BigNum& BigNum::operator %= (const BigNum& bn)
{
	return *this;
}

//not implement
BigNum& BigNum::operator ^= (const BigNum& bn)
{
	return *this;
}

BigNum& BigNum::operator = (const i32 iData)
{
	bool bRtn = false;
	bool bPositive = true;
	u8 pbData[4] = {0};
	i32 iIntData = 0;
	
	if (iData < 0)
	{
		iIntData = (-1)*iData;
		bPositive = false;
	}
	else
	{
		iIntData = iData;
	}

	std::memcpy(pbData, &iIntData, 4);
	if (BN_IsLittleEndian())
	{
		if (!BN_ReverseBuffer(pbData, 4))
		{
			bRtn = false;
			goto END;
		}
	}

	if (!setData(pbData, 4, bPositive))
	{
		bRtn = false;
		goto END;
	}

	bRtn = true;
END:
	return *this;
}

BigNum& BigNum::operator += (const i32 iData)
{
	BigNum tmpBN;

	tmpBN = iData;
	BN_Add(*this, tmpBN, *this);

	return *this;
}

BigNum& BigNum::operator -= (const i32 iData)
{
	BigNum tmpBN;

	tmpBN = iData;
	BN_Minus(*this, tmpBN, *this);

	return *this;
}

//not implement
BigNum& BigNum::operator *= (const i32 iData)
{
	return *this;
}

//not implement
BigNum& BigNum::operator /= (const i32 iData)
{
	return *this;
}

//not implement
BigNum& BigNum::operator %= (const i32 iData)
{
	return *this;
}

//not implement
BigNum& BigNum::operator ^= (const i32 iData)
{
	return *this;
}

bool BigNum::operator > (const BigNum& bn) const
{
	bool bRtn = false;

	if (m_bPositive != bn.m_bPositive)
	{
		bRtn = (m_bPositive);
	}
	else if (m_bPositive)
	{
		//positive
		if (BN_Compare_abs(*this, bn) > 0)
		{
			bRtn = true;
		}
		else
		{
			bRtn = false;
		}
	}
	else
	{
		//negative
		if (BN_Compare_abs(*this, bn) < 0)
		{
			bRtn = true;
		}
		else
		{
			bRtn = false;
		}
	}

	return bRtn;
}

bool BigNum::operator >= (const BigNum& bn) const
{
	bool bRtn = false;

	if (m_bPositive != bn.m_bPositive)
	{
		bRtn = (m_bPositive);
	}
	else if (m_bPositive)
	{
		//positive
		if (BN_Compare_abs(*this, bn) >= 0)
		{
			bRtn = true;
		}
		else
		{
			bRtn = false;
		}
	}
	else
	{
		//negative
		if (BN_Compare_abs(*this, bn) <= 0)
		{
			bRtn = true;
		}
		else
		{
			bRtn = false;
		}
	}

	return bRtn;
}

bool BigNum::operator < (const BigNum& bn) const
{
	return ! ((*this) >= (bn));
}

bool BigNum::operator <= (const BigNum& bn) const
{
	return !((*this) > (bn));
}

bool BigNum::operator == (const BigNum& bn) const
{
	bool bRtn = false;

	if (m_bPositive != bn.m_bPositive)
	{
		bRtn = false;
	}
	else
	{
		bRtn = (BN_Compare_abs(*this, bn) == 0);
	}

	return bRtn;
}

bool BigNum::operator != (const BigNum& bn) const
{
	return !((*this) == (bn));
}
