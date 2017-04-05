#include "SpriteComponent.h"
#include "BodyComponent.h"
#include "GameFunctions.h"
#include "GraphicsDevice.h"
#include "Texture.h"
#include "ArtAssetLibrary.h"

#include <memory>

SpriteComponent::SpriteComponent() : Component() {}

SpriteComponent::SpriteComponent(std::shared_ptr<Object> owner) : Component(owner)
{
	texture = NULL;
	gDevice = NULL;
}

SpriteComponent::~SpriteComponent() {}


bool SpriteComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	this->gDevice = initializers.gDevice;

	//Add Sprite to gDevice
	gDevice->AddSprite(this);

	// Get the Art Asset from the library
	texture = initializers.aLibrary->Search(initializers.textureId);
	if (texture == nullptr)
		return false;

	view = initializers.view;

	body = _owner->GetComponent<BodyComponent>();

	return true;
}

std::unique_ptr<Object> SpriteComponent::Update()
{
	return nullptr;
}

bool SpriteComponent::Finish()
{
	return false;
}

void SpriteComponent::Draw()
{
	//Extract position and angle
	GAME_VEC position = body->getPosition();
	GAME_FLT angle = body->getAngle();

	//Render to the Screen
	texture->Draw(gDevice->getRenderer(), view, position, angle, NULL);
}

Texture * SpriteComponent::getTexture()
{
	return texture.get();
}
