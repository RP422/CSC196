#include "particle_system.h"

ParticleSystem::ParticleSystem(size_t size)
{
	m_particle_pool = new PoolAllocator<Particle>(size);
}

ParticleSystem::~ParticleSystem()
{
	delete m_particle_pool;
}

void ParticleSystem::Update(float dt)
{
	for (Particle* particle : m_particles)
	{
		particle->lifespan -= dt;
		particle->active = (particle->lifespan > 0.0f);

		if (particle->active)
		{
			particle->prev_position = particle->position;
			particle->position = particle->position + particle->velocity * dt;
			particle->velocity = particle->velocity * particle->damping; // We're not accounting for dt here yet.
		}
	}

	auto iter = m_particles.begin();
	while (iter != m_particles.end())
	{
		if ((*iter)->active == false)
		{
			m_particle_pool->Free(*iter);
			iter = m_particles.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void ParticleSystem::Draw(Core::Graphics & graphics)
{
	for (Particle* particle : m_particles)
	{
		graphics.SetColor(particle->hue);
		graphics.DrawLine(particle->position.x, particle->position.y, particle->prev_position.x, particle->prev_position.y);
	}
}

void ParticleSystem::Create(const vector2 & position, const vector2 & velocity, const color & hue, float damping, float lifespan)
{
	Particle* particle = m_particle_pool->Get();
	
	if (particle)
	{
		particle->active = true;
		particle->position = position;
		particle->prev_position = position;
		particle->velocity = velocity;
		particle->hue = hue;
		particle->damping = damping;
		particle->lifespan = lifespan;

		m_particles.push_back(particle);
	}
}
