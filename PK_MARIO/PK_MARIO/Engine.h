#ifndef ENGINE_H_
#define ENGINE_H_

#include "StdAfx.h"
#include "SpriteConfig.h"
#include "Renderer.h"

class Engine {
public:
	static Engine& Get() {
		static Engine engine;
		return engine;
	}

	void Load() {
		m_sprite_config.reset(new SpriteConfig());
		m_renderer.reset(new Renderer());
	}

	SpriteConfigPtr GetSpriteConfig() {
		return m_sprite_config;
	}

	RendererPtr GetRenderer() {
		return m_renderer;
	}

private:
	SpriteConfigPtr m_sprite_config;
	RendererPtr m_renderer;

};

#endif /* ENGINE_H_ */
