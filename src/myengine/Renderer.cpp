#include "Renderer.h"
#include "Core.h"
#include "Transform.h"
#include "AssetManager.h"
#include "Entity.h"
#include "Exception.h"
#include "Camera.h"
#include "Model.h"

#include <fstream>
#include <string>
#include <iostream>

namespace myengine
{

	void Renderer::onInitialize()
	{
		shader = getCore()->context->createShader();
		shader->parse("../shaders/VertShader.glshader", "../shaders/FragShader.glshader");

		lightPosition = rend::vec3(0, 3, -5);
		lightForward = true;

		ShaderMaterial defaultMat;
		material = defaultMat;
	}
	
	void Renderer::onInitialize(ShaderMaterial _material)
	{
		onInitialize();

		material = _material;
	}

void Renderer::onTick()
{
	if (lightForward)
	{
		if (lightPosition.z > -8)
		{
			lightPosition.z -= 0.01;
		}
		else
		{
			lightForward = false;
		}
	}
	else
	{
		if (lightPosition.z < -5)
		{
			lightPosition.z += 0.01;
		}
		else
		{
			lightForward = true;
		}
	}
}

void Renderer::onRender()
{
  shaderSetAll();
  shader->render();
}

void Renderer::shaderSetAll()
{
	shader->setMesh(model->mesh);

	shader->setUniform("u_Projection", getCore()->getCamera()->persp);
	shader->setUniform("u_View", getCore()->getCamera()->getViewMat());
	shader->setUniform("u_Model", getEntity()->getTransform()->getModel());
	shader->setUniform("viewPos", getEntity()->getCore()->getCamera()->getTransform()->position);

	//ShaderMaterial defaultMat;
	setShaderMaterial(material);
	ShaderPointLight defaultLight;
	defaultLight.SetPosition(lightPosition);
	setShaderPointLight(defaultLight);
}

void Renderer::setShaderMaterial(ShaderMaterial _material)
{
	shader->setUniform("material.albedo", _material.albedo);
	shader->setUniform("material.metallic", _material.metallic);
	shader->setUniform("material.roughness", _material.roughness);
	shader->setUniform("material.ao", _material.ao);
}

void Renderer::setShaderPointLight(ShaderPointLight _light)
{
	shader->setUniform("pointLight.constant", _light.constant);
	shader->setUniform("pointLight.linear", _light.linear);
	shader->setUniform("pointLight.quadratic", _light.quadratic);
	shader->setUniform("pointLight.position", _light.position);
	shader->setUniform("pointLight.color", _light.colour);
}

void Renderer::setModel(std::shared_ptr<Model> model)
{
  this->model = model;
}


}