#include "BigNum.h"

BigNum::BigNum()
{
	m_vData.reserve(BIGNUM_DEF_INITSIZE);
}

BigNum::BigNum(const BigNum& bn)
{
	m_vData.reserve(BIGNUM_DEF_INITSIZE);
	std::copy(bn.m_vData.begin(), bn.m_vData.end(), back_inserter(m_vData));
}

BigNum::BigNum(const u8* const pbContent, const u32 uiContentSize)
{
	u32	i = 0;
	
	m_vData.reserve(BIGNUM_DEF_INITSIZE);
	
	if (!pbContent || !uiContentSize)
	{
		return;
	}

	for (i=0; i<uiContentSize; i++)
	{
		m_vData.push_back(pbContent[i]);
	}
}

BigNum::~BigNum()
{
	m_vData.erase(m_vData.begin(), m_vData.end());
}

u32 BigNum::getSize()
{
	u32	uiDataSize = 0;

	uiDataSize = (u32)m_vData.size();

	return uiDataSize;
}

#ifdef BIGNUM_SUPPORT_PRINT
bool BigNum::printContent()
{
	bool	bRtn = false;
	u32	i = 0, uiDataSize = 0;
	//std::ostream::fmtflags osFlagOld = 0;

	//osFlagOld = std::cout.flag();//save old cout format flag, and set new format flag

	uiDataSize = (u32)m_vData.size();
	for (i=0; i<uiDataSize; i++)
	{
		std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << (u32)m_vData.at(i) << " ";
	}
	std::cout << std::endl;

	bRtn = true;
END:
	//std::cout.flag(osFlagOld);//restore cout format flag
	return bRtn;
}
#endif

u8 BigNum::operator [](u32 idx) const
{
	u8	ucData = 0;

	if (idx < m_vData.size())
	{
		ucData = m_vData.at(idx);
	}

	return ucData;
}

BigNum& BigNum::operator ++()
{
	std::vector<u8>::reverse_iterator	rit;
	
	rit = m_vData.rbegin();
	while (rit != m_vData.rend())
	{
		if (*rit == 0xff)
		{
			*rit = 0;
		}
		else
		{
			*rit += 1;
			break;
		}

		++rit;
	}

	return *this;
}

BigNum BigNum::operator ++(int)
{
	BigNum	tmpBN(*this);
	std::vector<u8>::reverse_iterator	rit;
	
	rit = m_vData.rbegin();
	while (rit != m_vData.rend())
	{
		if (*rit == 0xff)
		{
			*rit = 0;
		}
		else
		{
			*rit += 1;
			break;
		}

		++rit;
	}

	return tmpBN;
}

BigNum& BigNum::operator --()
{
	std::vector<u8>::reverse_iterator	rit;
	
	rit = m_vData.rbegin();
	while (rit != m_vData.rend())
	{
		if (*rit == 0)
		{
			*rit = 0xff;
		}
		else
		{
			*rit -= 1;
			break;
		}

		++rit;
	}

	return *this;
}

BigNum BigNum::operator --(int)
{
	BigNum tmpBN(*this);
	std::vector<u8>::reverse_iterator	rit;
	
	rit = m_vData.rbegin();
	while (rit != m_vData.rend())
	{
		if (*rit == 0)
		{
			*rit = 0xff;
		}
		else
		{
			*rit -= 1;
			break;
		}

		++rit;
	}

	return tmpBN;
}

BigNum& BigNum::operator + (BigNum& bn)
{
	return *this;
}

BigNum& BigNum::operator - (BigNum& bn)
{
	return *this;
}

BigNum& BigNum::operator * (BigNum& bn)
{
	return *this;
}

BigNum& BigNum::operator / (BigNum& bn)
{
	return *this;
}

BigNum& BigNum::operator % (BigNum& bn)
{
	return *this;
}

BigNum& BigNum::operator ^ (BigNum& bn)
{
	return *this;
}

BigNum& BigNum::operator = (BigNum& bn)
{
	m_vData.reserve(BIGNUM_DEF_INITSIZE);
	std::copy(bn.m_vData.begin(), bn.m_vData.end(), back_inserter(m_vData));
	
	return *this;
}
