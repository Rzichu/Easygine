#include "object_components.h"

#include "../engine.h"

namespace easygine {
    namespace objects {
        SpriteComponent::SpriteComponent(const std::string &tex_name, const std::string &tex_file)
            : m_TextureResourceData{std::move(tex_name), std::move(tex_file)}
            {}
        
        SpriteComponent::~SpriteComponent() {
            this->unloadResources();
        }

        void SpriteComponent::loadResources(bool reset_rect) {
            this->m_Texture = internal_handle_core.gameResources()->loadSharedTexture(this->m_TextureResourceData.resource_name, this->m_TextureResourceData.resource_file);
            this->m_Sprite.setTexture(*this->m_Texture, reset_rect);
        }

        void SpriteComponent::loadResources(const sf::IntRect &tex_rect) {
            this->m_Texture = internal_handle_core.gameResources()->loadSharedTexture(this->m_TextureResourceData.resource_name, this->m_TextureResourceData.resource_file);
            this->m_Sprite.setTexture(*this->m_Texture);
            this->m_Sprite.setTextureRect(std::move(tex_rect));
        }

        void SpriteComponent::unloadResources() {
            internal_handle_core.gameResources()->unloadSharedTexture(this->m_TextureResourceData.resource_name);
        }

        void SpriteComponent::draw(sf::RenderTarget &target, sf::RenderStates states) const {
            target.draw(this->m_Sprite, states);
        }

        AnimationComponent::AnimationComponent()
            : m_Animations{thor::AnimationMap<sf::Sprite, std::string>()}
            , m_Animator{this->m_Animations}
            {}

        AnimationComponent::~AnimationComponent() {
            this->m_Animator.stop();
        }

        void AnimationComponent::update(sf::Sprite &animated, sf::Time delta_time) {
            this->m_Animator.update(delta_time);
            this->m_Animator.animate(animated);
        }

        AudioComponent::~AudioComponent() {
            this->unloadResources();
        }

        void AudioComponent::loadResources() {
            for (unsigned long long i {this->m_SoundResourceData.size()}; i--;) {
                this->m_Sounds.at(i).sound_buff = internal_handle_core.gameResources()->loadSharedSoundBuffer(this->m_SoundResourceData.at(i).resource_name, this->m_SoundResourceData.at(i).resource_file);
            }
        }

        void AudioComponent::unloadResources() {
            for (auto &snd : this->m_SoundResourceData) {
                internal_handle_core.gameResources()->unloadSharedSoundBuffer(snd.resource_name);
            }
        }

        void AudioComponent::playSound(const std::string &snd_name) {
            for (unsigned long long i {this->m_Sounds.size()}; i--;) {
                if (snd_name == this->m_SoundResourceData.at(i).resource_name) {
                    internal_handle_core.gameAudio()->playSound(this->m_Sounds.at(i));
                }
            }
        }
        
        ShaderComponent::~ShaderComponent() {
            this->unloadResources();
        }
        
        void ShaderComponent::loadResources(bool loadGeom) {
            if (internal_handle_core.shadersSupported()) {
                if (loadGeom && internal_handle_core.geometryShadersSupported()) {
                    this->m_Shader = internal_handle_core.gameResources()->loadSharedShader(m_ShaderResourceData.resource_name
                            , m_ShaderResourceData.resource_file[aether::enumera::enumToNum(sf::Shader::Vertex)]
                            , m_ShaderResourceData.resource_file[aether::enumera::enumToNum(sf::Shader::Geometry)]
                            , m_ShaderResourceData.resource_file[aether::enumera::enumToNum(sf::Shader::Fragment)]);
                }
                else {
                    this->m_Shader = internal_handle_core.gameResources()->loadSharedShader(m_ShaderResourceData.resource_name
                        , m_ShaderResourceData.resource_file[aether::enumera::enumToNum(sf::Shader::Vertex)]
                        , m_ShaderResourceData.resource_file[aether::enumera::enumToNum(sf::Shader::Fragment)]);
                }
            }
        }

        void ShaderComponent::loadResources(sf::Shader::Type shdr_type) {
            if (internal_handle_core.shadersSupported()) {
                if (shdr_type == sf::Shader::Type::Vertex) {
                    this->m_Shader = internal_handle_core.gameResources()->loadSharedShader(m_ShaderResourceData.resource_name
                            , m_ShaderResourceData.resource_file[aether::enumera::enumToNum(sf::Shader::Vertex)], sf::Shader::Vertex);
                }
                else if ((shdr_type == sf::Shader::Type::Geometry) && internal_handle_core.geometryShadersSupported()) {
                    this->m_Shader = internal_handle_core.gameResources()->loadSharedShader(m_ShaderResourceData.resource_name
                            , m_ShaderResourceData.resource_file[aether::enumera::enumToNum(sf::Shader::Geometry)], sf::Shader::Geometry);
                }
                else if (shdr_type == sf::Shader::Type::Fragment) {
                    this->m_Shader = internal_handle_core.gameResources()->loadSharedShader(m_ShaderResourceData.resource_name
                            , m_ShaderResourceData.resource_file[aether::enumera::enumToNum(sf::Shader::Fragment)], sf::Shader::Fragment);
                }
            }
        }

        void ShaderComponent::unloadResources() {
            internal_handle_core.gameResources()->unloadSharedShader(m_ShaderResourceData.resource_name);
        }
        
        sf::RenderStates ShaderComponent::getRenderStates() {
            sf::RenderStates states;
            if (internal_handle_core.shadersSupported()) {
                states.shader = &(*this->m_Shader);
            }
            states.blendMode = this->m_BlendMode;

            return states;
        }

        void ParticleComponent::update(sf::Time delta_time) {
            this->m_ParticleSystem.update(delta_time);
        }

        void ParticleComponent::draw(sf::RenderTarget &target) {
            target.draw(this->m_ParticleSystem);
        }

        void ParticleComponent::loadResources() {
            this->m_Texture = internal_handle_core.gameResources()->loadSharedTexture(this->m_TextureResourceData.resource_name, this->m_TextureResourceData.resource_file);
            this->m_ParticleSystem.setTexture(*this->m_Texture);
        }

        void ParticleComponent::loadResources(const sf::IntRect &tex_rect) {
            this->m_Texture = internal_handle_core.gameResources()->loadSharedTexture(this->m_TextureResourceData.resource_name, this->m_TextureResourceData.resource_file);
            this->m_ParticleSystem.setTexture(*this->m_Texture);
        }

        void ParticleComponent::unloadResources() {
            internal_handle_core.gameResources()->unloadSharedTexture(this->m_TextureResourceData.resource_name);
        }
    }
}