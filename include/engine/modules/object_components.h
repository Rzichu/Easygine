#pragma once

#include "audio.h"
#include "input.h"

#include "../../misc/EnumEra/enum_era.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>
#include <Thor/Particles.hpp>

#include <memory>
#include <vector>
#include <utility>

namespace easygine {
    namespace objects {
        struct S_ResourceData {
            S_ResourceData(const std::string &name, const std::string &file)
                : resource_name{std::forward<const std::string &>(name)}
                , resource_file{std::forward<const std::string &>(file)}
                {}
            
            S_ResourceData() = default;

            std::string resource_name {""};
            std::string resource_file {""};
        };

        struct S_ShaderResourceData {
            S_ShaderResourceData(const std::string &name, const std::string &file1, const std::string &file2, const std::string &file3)
                : resource_name{std::forward<const std::string &>(name)}
                , resource_file{std::forward<const std::string &>(file1), std::forward<const std::string &>(file2), std::forward<const std::string &>(file3)}
                {}
            
            S_ShaderResourceData() = default;

            std::string resource_name {""};
            std::string resource_file[3] {"", "", ""};
        };

        class BaseComponent {
        public:
            virtual ~BaseComponent() = default;

            BaseComponent(const BaseComponent &copy)                = default;
            BaseComponent & operator=(const BaseComponent &copy)    = default;
            
            BaseComponent(BaseComponent &&move)             = default;
            BaseComponent & operator=(BaseComponent &&move) = default;

        protected:
            BaseComponent() = default;
        };

        class SpriteComponent : public BaseComponent, public sf::Drawable, public sf::Transformable {
        public:
            void draw(sf::RenderTarget &target, sf::RenderStates states) const;

            inline void setTextureResource(const std::string &tex_name, const std::string &tex_file) {
                this->m_TextureResourceData.resource_name = std::forward<const std::string &>(tex_name);
                this->m_TextureResourceData.resource_file = std::forward<const std::string &>(tex_file);
            }

            void loadResources(bool reset_rect = false);
            void loadResources(const sf::IntRect &tex_rect);
            void unloadResources();

        public:
            inline sf::Sprite & sprite() {
                return this->m_Sprite;
            }

            inline const std::shared_ptr<sf::Texture> & texture() {
                return this->m_Texture;
            }
        
        public:
            SpriteComponent(const std::string &tex_name, const std::string &tex_file);
            SpriteComponent();
            virtual ~SpriteComponent();

            SpriteComponent(const SpriteComponent &copy)                = default;
            SpriteComponent & operator=(const SpriteComponent &copy)    = default;
            
            SpriteComponent(SpriteComponent &&move)             = default;
            SpriteComponent & operator=(SpriteComponent &&move) = default;
        
        protected:
            easygine::objects::S_ResourceData m_TextureResourceData;
            std::shared_ptr<sf::Texture> m_Texture {nullptr};
            sf::Sprite m_Sprite;
        };

        class AnimationComponent : public BaseComponent {
        public:
            void update(sf::Sprite &animated, sf::Time delta_time);
        
        public:
            inline auto & animator() {
                return this->m_Animator;
            }

            inline auto & animations() {
                return this->m_Animations;
            }
        
        public:
            AnimationComponent();
            virtual ~AnimationComponent();

            AnimationComponent(const AnimationComponent &copy)              = default;
            AnimationComponent & operator=(const AnimationComponent &copy)  = default;
            
            AnimationComponent(AnimationComponent &&move)               = default;
            AnimationComponent & operator=(AnimationComponent &&move)   = default;
        
        protected:
            thor::AnimationMap<sf::Sprite, std::string> m_Animations;
            thor::Animator<sf::Sprite, std::string> m_Animator;
        };

        class AudioComponent : public BaseComponent {
        public:
            inline void addSoundInfo(float _pitch, float _attenuation, float _min_distance, sf::Vector3f _pos, bool _relative_to_lis, easygine::audio::EC_Volume _type) {
                this->m_Sounds.emplace_back(easygine::audio::S_SoundInfo(_pitch, _attenuation, _min_distance, _pos, _relative_to_lis, _type));
            }

            inline void addSoundInfo(const easygine::audio::S_SoundInfo &snd_info) {
                this->m_Sounds.emplace_back(easygine::audio::S_SoundInfo(snd_info));
            }

            inline void addSoundResource(const std::string &snd_name, const std::string &snd_file) {
                this->m_SoundResourceData.emplace_back(easygine::objects::S_ResourceData(std::forward<const std::string &>(snd_name), std::forward<const std::string &>(snd_file)));
            }

            void loadResources();
            void unloadResources();
            void playSound(const std::string &snd_name);
        
        public:
            inline auto & sounds() {
                return this->m_Sounds;
            }
        
        public:
            AudioComponent() = default;
            virtual ~AudioComponent();

            AudioComponent(const AudioComponent &copy)              = default;
            AudioComponent & operator=(const AudioComponent &copy)  = default;
            
            AudioComponent(AudioComponent &&move)               = default;
            AudioComponent & operator=(AudioComponent &&move)   = default;
        
        protected:
            std::vector<easygine::audio::S_SoundInfo> m_Sounds;
            std::vector<easygine::objects::S_ResourceData> m_SoundResourceData;
        };

        class ShaderComponent : public BaseComponent {
        public:
            sf::RenderStates getRenderStates();

            inline void setShaderName(const std::string &shdr_name) {
                this->m_ShaderResourceData.resource_name = std::forward<const std::string&>(shdr_name);
            }

            inline void setVertexShader(const std::string &shdr_file) {
                this->m_ShaderResourceData.resource_file[aether::enumera::enumToNum(sf::Shader::Vertex)] = std::forward<const std::string &>(shdr_file);
            }

            inline void setGeometryShader(const std::string &shdr_file) {
                this->m_ShaderResourceData.resource_file[aether::enumera::enumToNum(sf::Shader::Geometry)] = std::forward<const std::string &>(shdr_file);
            }

            inline void setFragmentShader(const std::string &shdr_file) {
                this->m_ShaderResourceData.resource_file[aether::enumera::enumToNum(sf::Shader::Fragment)] = std::forward<const std::string &>(shdr_file);
            }

            void loadResources(bool loadGeom);
            void loadResources(sf::Shader::Type shdr_type);
            void unloadResources();

        public:
            inline auto & shader() {
                return this->m_Shader;
            }

            inline auto & blendMode() {
                return this->m_BlendMode;
            }
        
        public:
            ShaderComponent(const std::string &shdr_name) {
                this->m_ShaderResourceData.resource_name = std::forward<const std::string &>(shdr_name);
            }

            ShaderComponent() = default;
            virtual ~ShaderComponent();

            ShaderComponent(const ShaderComponent &copy)                = default;
            ShaderComponent & operator=(const ShaderComponent &copy)    = default;
            
            ShaderComponent(ShaderComponent &&move)             = default;
            ShaderComponent & operator=(ShaderComponent &&move) = default;
        
        protected:
            easygine::objects::S_ShaderResourceData m_ShaderResourceData;
            std::shared_ptr<sf::Shader> m_Shader {nullptr};
            sf::BlendMode m_BlendMode {sf::BlendMode()};
        };

        class ParticleComponent : public BaseComponent {
        public:
            void update(sf::Time delta_time);

            void draw(sf::RenderTarget &target);

            inline void setTextureResource(const std::string &tex_name, const std::string &tex_file) {
                this->m_TextureResourceData.resource_name = std::forward<const std::string &>(tex_name);
                this->m_TextureResourceData.resource_file = std::forward<const std::string &>(tex_file);
            }

            void loadResources();
            void loadResources(const sf::IntRect &tex_rect);
            void unloadResources();

        public:
            inline auto & particleSystem() {
                return this->m_ParticleSystem;
            }

            inline const std::shared_ptr<sf::Texture> & texture() {
                return this->m_Texture;
            }
        
        public:
            ParticleComponent()             = default;
            virtual ~ParticleComponent()    = default;

            ParticleComponent(const ParticleComponent &copy)                = default;
            ParticleComponent & operator=(const ParticleComponent &copy)    = default;
            
            ParticleComponent(ParticleComponent &&move)             = default;
            ParticleComponent & operator=(ParticleComponent &&move) = default;
        
        protected:
            easygine::objects::S_ResourceData m_TextureResourceData;
            std::shared_ptr<sf::Texture> m_Texture {nullptr};
            thor::ParticleSystem m_ParticleSystem;
        };
    }
}