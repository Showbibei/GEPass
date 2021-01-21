#include <rend/rend.h>


namespace myengine 
{
	struct ShaderMaterial
	{

		rend::vec3 albedo;
		float metallic;
		float roughness;
		float ao;

		ShaderMaterial()
		{
			albedo = rend::vec3(1, 0, 1);
			metallic = 0;
			roughness = 0.3;
			ao = 0;
		}

		void SetMaterial(rend::vec3 _albedo)
		{
			albedo = _albedo;
		}

		void SetMaterial(rend::vec3 _albedo, float _metallic, float _roughness, float _ao)
		{
			albedo = _albedo;
			metallic = _metallic;
			roughness = _roughness;
			ao = _ao;
		}
	};


}