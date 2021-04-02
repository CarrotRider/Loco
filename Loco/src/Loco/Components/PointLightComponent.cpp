#include "stdafx.h"
#include "PointLightComponent.h"

#include "Loco/Renderer/Renderer.h"

namespace Loco {

	PointLightComponent::PointLightComponent(GameObject* owner, int updateOrder /*= 100*/)
		: LightComponent{ owner, updateOrder }
		, m_Radius{ 100 }
		, m_Attenuation{ 1.0f, 0.045, 0.0075 }
	{
		ResetAttenByRadius();
		GetRenderer()->AddLightComp(this);
	}


	PointLightComponent::~PointLightComponent()
	{
		GetRenderer()->RemoveLightComp(this);
	}

	 
	void PointLightComponent::ResetAttenByRadius()
	{
		if (m_Radius <= m_Distances[0])
			m_Attenuation = m_CalcFactors[0];
		else if (m_Radius >= m_Distances[11])
			m_Attenuation = m_CalcFactors[11];
		else
		{
			for (int i = 0; i < 12; i++)
			{
				if (m_Radius < m_Distances[i])
				{
					float percent = m_Radius / (m_Distances[i] - m_Distances[i - 1]);
					m_Attenuation.Constant = 1.0f;
					m_Attenuation.Linear = m_CalcFactors[i].Linear + percent * (m_CalcFactors[i - 1].Linear - m_CalcFactors[i].Linear);
					m_Attenuation.Quadratic = m_CalcFactors[i].Quadratic + percent * (m_CalcFactors[i - 1].Quadratic - m_CalcFactors[i].Quadratic);
				}
			}
		}
	}

	void PointLightComponent::SetAttenuation(float kc, float kl, float kq)
	{
		m_Attenuation.Constant = kc;
		m_Attenuation.Linear = kl;
		m_Attenuation.Quadratic = kq;
	}

	void PointLightComponent::SetAttenuation(PointLightComponent::Attenuation atten)
	{
		m_Attenuation = atten;
	}
}