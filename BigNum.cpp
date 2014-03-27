#include "BigNum.h"

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
		rit = m_vData.pop_back();
		--uiDataSize;
	}
	
	bRtn = true;
END:
	return bRtn;
}

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

bool BigNum::setData(const u8* const pbContent, const u32 uiContentSize, const bool bPositive)
{
	u32	i = 0;
	
	m_bPositive = bPositive;
	m_vData.resize(0);
	m_vData.reserve(BIGNUM_DEF_INITSIZE);

	if (!pbContent || !uiContentSize)
	{
		m_vData.push_back((u8)0);
		return;
	}

	for (i=0; i<uiContentSize; i++)
	{
		m_vData.push_back(pbContent[uiContentSize-i-1]);
	}

	BN_Reorganize();
}

u8& BigNum::operator [](u32 idx)
{
	u32 uiSize = m_vData.size();

	if (idx < uiSize)
	{
		return m_vData.at(uiSize-idx-1);
	}

	return m_vData.at(uiSize-1);
}

bool BigNum::BN_IsLittleEndian() const
{
	u32 uiTmp = 0x0001;
	bool bRtn = false;

	if (*((u8*)&uiTmp) != 0)
	{
		bRtn = true;
	}

	return bRtn;
}

bool BigNum::BN_ReverseBuffer(u8 *const pbData, const u32 uiDataSize)
{
	bool bRtn = false;
	u32 i = 0;

	if (!pbData || !uiDataSize)
	{
		bRtn = false;
		goto END:
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

//not implement
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

//not implement
BigNum& BigNum::operator --()
{
	if (m_bPositive)
	{
		BN_Inc_Dec();
	}
	return *this;
}

BigNum& BigNum::operator = (BigNum& bn)
{
	if (&bn == this)
	{
		goto END;
	}

	m_vData.resize(0);
	m_vData.reserve(BIGNUM_DEF_INITSIZE);
	std::copy(bn.m_vData.begin(), bn.m_vData.end(), back_inserter(m_vData));	
END:
	BN_Reorganize();
	return *this;
}

//not implement
BigNum& BigNum::operator +=(BigNum& bn)
{
	std::vector<u8>::iterator itr1, itr2;
	u32	uiRes = 0;
	u8	ucCarry = 0;
	
	itr1 = m_vData.begin();
	itr2 = bn.m_vData.begin();

	while ((itr1 != m_vData.end()) && (itr2 != bn.m_vData.end()))
	{
		if ((itr1 != m_vData.end()) && (itr2 != bn.m_vData.end()))
		{
			uiRes = *itr1 + *itr2 + ucCarry;
		}
		else if (itr2 != bn.m_vData.end())
		{
			uiRes = *itr2 + ucCarry;
		}
		else if (itr1 != m_vData.end())
		{
			uiRes = *itr1 + ucCarry;
		}
		else
		{
			uiRes = ucCarry;
		}
		
		if (uiRes > 0xff)
		{
			ucCarry = (u8)(uiRes >> 8);
			
			if (itr1 != m_vData.end())
			{
				*itr1 = (u8)(uiRes & 0xff);
			}
			else
			{
				m_vData.push_back((u8)(uiRes & 0xff));
			}
		}
		else
		{
			ucCarry = (u8)0;
			
			if (itr1 != m_vData.end())
			{
				*itr1 = (u8)uiRes;
			}
			else
			{
				m_vData.push_back((u8)(uiRes));
			}
		}

		++itr1;
		++itr2;
	}

	if (ucCarry)
	{
		m_vData.push_back((u8)ucCarry);
	}

	BN_Reorganize();
	return *this;
}

i8 BN_Compare_abs(const BigNum& bn1, const BigNum& bn2) const
{
	i8 cRes = 0;
	u32 uiDataSize1 = 0, uiDataSize2 = 0;
	std::vector<u8>::reverse_iterator rit1, rit2;

	if (&bn1 == &bn2)
	{
		cRes = 0;
		goto END;
	}

	uiDataSize1 = bn1.size();
	uiDataSize2 = bn2.size();

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
				cRes = (*rit1 - *rit2);
				break;
			}
			++rit1;
			++rit2;
		}
	}

END:
	return cRes;
}

i8 BN_Compare_abs(const BigNum& bn, const u32 uiData) const
{
	u8 pbData[4] = {0};
	BigNum tmpBN;

	memcpy(pbData, &uiData, 4);
	if (BN_IsLittleEndian())
	{
		BN_ReverseBuffer(pbData, 4);
	}
	
	tmpBN.setData(pbData, sizeof(pbData));
	
	return BN_Compare_abs(bn, tmpBN);
}

i8 BN_Compare_abs(const u32 uiData, const BigNum& bn) const
{
	return (-1)*BN_Compare_abs(bn, uiData);
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

bool operator >= (const BigNum& bn) const
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

bool operator < (const BigNum& bn) const
{
	return ! ((*this) >= (bn));
}

bool operator <= (const BigNum& bn) const
{
	return !((*this) > (bn));
}

bool operator == (const BigNum& bn) const
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

bool operator != (const BigNum& bn) const
{
	return !((*this) == (bn));
}

//not implement
bool operator > (const u32 uiData) const
{
	bool bRtn = false;

	return bRtn;
}

//not implement
bool operator >= (const u32 uiData) const
{
	bool bRtn = false;

	return bRtn;
}

//not implement
bool operator < (const u32 uiData) const
{
	bool bRtn = false;

	return bRtn;
}

//not implement
bool operator <= (const u32 uiData) const
{
	bool bRtn = false;

	return bRtn;
}

//not implement
bool operator == (const u32 uiData) const
{
	bool bRtn = false;

	return bRtn;
}

//not implement
bool operator != (const u32 uiData) const
{
	bool bRtn = false;

	return bRtn;
}

