#pragma once

#include <Survive/forward.h>

namespace Survive
{

class Range
{
public:

	Range()
		:
	m_Min(0.0f),
	m_Max(0.0f)
	{

	}

	Range(float A, float B)
	{
		m_Min = std::min(A, B);
		m_Max = std::max(A, B);
	}

	bool Overlap(const Range& R)const
	{
		return R.GetMin() <= m_Max && m_Min <= R.GetMax();
	}

	void Join(const Range& R)
	{
		m_Min = m_Min < R.GetMin() ? m_Min : R.GetMin();
		m_Max = m_Max > R.GetMax() ? m_Max : R.GetMax();
	}

	float GetMin()const
	{
		return m_Min;
	}

	float GetMax()const
	{
		return m_Max;
	}

private:

	float m_Min;
	float m_Max;
};

}