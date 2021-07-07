#pragma once
#include "ParticleEmitter.h"
#include "SceneMesh.h"
#include "Interface/IParticleRawGener.h"

#include <memory>

namespace wallpaper {

class ParticleSystem;

class ParticleSubSystem {
public:
	ParticleSubSystem(ParticleSystem& p, std::shared_ptr<SceneMesh> sm):parent(p),m_mesh(sm) {};
	ParticleSubSystem(ParticleSubSystem&) = delete;
	ParticleSubSystem(ParticleSubSystem&&) = delete;

	void Emitt();

	void AddEmitter(std::unique_ptr<ParticleEmitter>);
	void AddInitializer(ParticleInitOp&&);
	void AddOperator(ParticleOperatorOp&&);
private:
	ParticleSystem& parent;
	std::shared_ptr<SceneMesh> m_mesh;
	std::vector<std::unique_ptr<ParticleEmitter>> m_emiters;

	std::vector<Particle> m_particles;
	std::vector<ParticleInitOp> m_initializers;
	std::vector<ParticleOperatorOp> m_operators;
};

class Scene;
class ParticleSystem {
public:
	ParticleSystem(Scene& scene):scene(scene) {};
	~ParticleSystem() = default;
	ParticleSystem(ParticleSystem&) = delete;
	ParticleSystem(ParticleSystem&&) = delete;

	void Emitt();

	Scene& scene;

	std::vector<std::unique_ptr<ParticleSubSystem>> subsystems;
	std::unique_ptr<IParticleRawGener> gener;
};
}