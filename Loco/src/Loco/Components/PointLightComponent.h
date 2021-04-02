#pragma once

#include "Loco/Core.h"

#include "LightComponent.h"

namespace Loco {

	class LOCO_API PointLightComponent :
		public LightComponent
	{
	public:
		struct Attenuation
		{
			float Constant;
			float Linear;
			float Quadratic;
		};
	public:
		PointLightComponent(GameObject* owner, int updateOrder = 100);
		virtual ~PointLightComponent();

		void OnUpdate(float deltaTime) override {}

		void ResetAttenByRadius();

		Attenuation GetAttenuation() const { return m_Attenuation; }
		void SetAttenuation(float kc, float kl, float kq);
		void SetAttenuation(Attenuation atten);

		float GetAttenConst() const { return m_Attenuation.Constant; }
		void SetAttenConst(float kc) { m_Attenuation.Constant = kc; }
		float GetAttenLinear() const { return m_Attenuation.Linear; }
		void SetAttenLinear(float kl) { m_Attenuation.Linear = kl; }
		float GetAttenQuad() const { return m_Attenuation.Quadratic; }
		void SetAttenQuad(float kq) { m_Attenuation.Quadratic = kq; }

		float GetRadius() const { return m_Radius; }
		void SetRadius(float radius) { m_Radius = radius; }

	private:
		float m_Radius;
		Attenuation m_Attenuation;

		// by Ogre3D
		float m_Distances[12]{
			7, 13, 20, 32, 50, 65,
			100, 160, 200, 325, 600, 3250 };
		Attenuation m_CalcFactors[12]{
			{ 1.0,	0.7,	1.8 },
			{ 1.0,	0.35,	0.44 },
			{ 1.0,	0.22,	0.20 },
			{ 1.0,	0.14,	0.07 },
			{ 1.0,	0.09,	0.032 },
			{ 1.0,	0.07,	0.017 },
			{ 1.0,	0.045,	0.0075 },
			{ 1.0,	0.027,	0.0028 },
			{ 1.0,	0.022,	0.0019 },
			{ 1.0,	0.014,	0.0007 },
			{ 1.0,	0.007,	0.0002 },
			{ 1.0,	0.0014,	0.000007 }
		};
	};
}