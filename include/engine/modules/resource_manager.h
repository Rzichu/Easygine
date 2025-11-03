#pragma once

#include <Thor/Resources.hpp>

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <TGUI/Backends/SFML/BackendFontSFML.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <future>
#include <memory>
#include <string>

namespace easygine {
    class CORE;
    
    namespace resources {
        class ResourceManager {
            friend class easygine::CORE;
        public:
            const sf::Image & loadUniqueImage(const std::string &resource_name, const std::string &resource_file);
            const sf::Image & loadUniqueImage(const std::string &resource_name, const thor::ResourceLoader<sf::Image> &resource_loader);
            void unloadUniqueImage(const std::string &resource_name);

            const sf::Texture & loadUniqueTexture(const std::string &resource_name, const std::string &resource_file, const sf::IntRect &tex_rect = sf::IntRect());
            const sf::Texture & loadUniqueTexture(const std::string &resource_name, const thor::ResourceLoader<sf::Texture> &resource_loader);
            void unloadUniqueTexture(const std::string &resource_name);

            const tgui::BackendFontSFML & loadUniqueFont(const std::string &resource_name, const std::string &resource_file);
            const tgui::BackendFontSFML & loadUniqueFont(const std::string &resource_name, const thor::ResourceLoader<tgui::BackendFontSFML> &resource_loader);
            void unloadUniqueFont(const std::string &resource_name);

            const sf::Shader & loadUniqueShader(const std::string &resource_name, const std::string &vert_file, const std::string &frag_file);
            const sf::Shader & loadUniqueShader(const std::string &resource_name, const std::string &vert_file, const std::string &geom_file, const std::string &frag_file);
            const sf::Shader & loadUniqueShader(const std::string &resource_name, const std::string &resource_file, sf::Shader::Type shader_type);
            const sf::Shader & loadUniqueShader(const std::string &resource_name, const thor::ResourceLoader<sf::Shader> &resource_loader);
            void unloadUniqueShader(const std::string &resource_name);

            const sf::SoundBuffer & loadUniqueSoundBuffer(const std::string &resource_name, const std::string &resource_file);
            const sf::SoundBuffer & loadUniqueSoundBuffer(const std::string &resource_name, const thor::ResourceLoader<sf::SoundBuffer> &resource_loader);
            void unloadUniqueSoundBuffer(const std::string &resource_name);

            std::shared_ptr<sf::Image> loadSharedImage(const std::string &resource_name, const std::string &resource_file);
            std::shared_ptr<sf::Image> loadSharedImage(const std::string &resource_name, const thor::ResourceLoader<sf::Image> &resource_loader);
            void unloadSharedImage(const std::string &resource_name);

            std::shared_ptr<sf::Texture> loadSharedTexture(const std::string &resource_name, const std::string &resource_file, const sf::IntRect &tex_rect = sf::IntRect());
            std::shared_ptr<sf::Texture> loadSharedTexture(const std::string &resource_name, const thor::ResourceLoader<sf::Texture> &resource_loader);
            void unloadSharedTexture(const std::string &resource_name);

            std::shared_ptr<tgui::BackendFontSFML> loadSharedFont(const std::string &resource_name, const std::string &resource_file);
            std::shared_ptr<tgui::BackendFontSFML> loadSharedFont(const std::string &resource_name, const thor::ResourceLoader<tgui::BackendFontSFML> &resource_loader);
            void unloadSharedFont(const std::string &resource_name);

            std::shared_ptr<sf::Shader> loadSharedShader(const std::string &resource_name, const std::string &vert_file, const std::string &frag_file);
            std::shared_ptr<sf::Shader> loadSharedShader(const std::string &resource_name, const std::string &vert_file, const std::string &geom_file, const std::string &frag_file);
            std::shared_ptr<sf::Shader> loadSharedShader(const std::string &resource_name, const std::string &resource_file, sf::Shader::Type shader_type);
            std::shared_ptr<sf::Shader> loadSharedShader(const std::string &resource_name, const thor::ResourceLoader<sf::Shader> &resource_loader);
            void unloadSharedShader(const std::string &resource_name);

            std::shared_ptr<sf::SoundBuffer> loadSharedSoundBuffer(const std::string &resource_name, const std::string &resource_file);
            std::shared_ptr<sf::SoundBuffer> loadSharedSoundBuffer(const std::string &resource_name, const thor::ResourceLoader<sf::SoundBuffer> &resource_loader);
            void unloadSharedSoundBuffer(const std::string &resource_name);

        public:
            auto & getUniqueImageResourceHandler() {
                return this->m_UniqueImageResourceHandler;
            }

            auto & getUniqueTextureResourceHandler() {
                return this->m_UniqueTextureResourceHandler;
            }

            auto & getUniqueFontResourceHandler() {
                return this->m_UniqueFontResourceHandler;
            }

            auto & getUniqueShaderResourceHandler() {
                return this->m_UniqueShaderResourceHandler;
            }

            auto & getUniqueSoundBufferResourceHandler() {
                return this->m_UniqueSoundBufferResourceHandler;
            }
            
            auto & getSharedImageResourceHandler() {
                return this->m_SharedImageResourceHandler;
            }

            auto & getSharedTextureResourceHandler() {
                return this->m_SharedTextureResourceHandler;
            }

            auto & getSharedFontResourceHandler() {
                return this->m_SharedFontResourceHandler;
            }

            auto & getSharedShaderResourceHandler() {
                return this->m_SharedShaderResourceHandler;
            }

            auto & getSharedSoundBufferResourceHandler() {
                return this->m_SharedSoundBufferResourceHandler;
            }
        
        protected:
            bool init();

            void deinit();

        protected:
            thor::ResourceHolder<sf::Image, std::string> m_UniqueImageResourceHandler;
            thor::ResourceHolder<sf::Texture, std::string> m_UniqueTextureResourceHandler;
            thor::ResourceHolder<tgui::BackendFontSFML, std::string> m_UniqueFontResourceHandler;
            thor::ResourceHolder<sf::Shader, std::string> m_UniqueShaderResourceHandler;
            thor::ResourceHolder<sf::SoundBuffer, std::string> m_UniqueSoundBufferResourceHandler;

            thor::ResourceHolder<sf::Image, std::string, thor::Resources::RefCounted> m_SharedImageResourceHandler;
            thor::ResourceHolder<sf::Texture, std::string, thor::Resources::RefCounted> m_SharedTextureResourceHandler;
            thor::ResourceHolder<tgui::BackendFontSFML, std::string, thor::Resources::RefCounted> m_SharedFontResourceHandler;
            thor::ResourceHolder<sf::Shader, std::string, thor::Resources::RefCounted> m_SharedShaderResourceHandler;
            thor::ResourceHolder<sf::SoundBuffer, std::string, thor::Resources::RefCounted> m_SharedSoundBufferResourceHandler;
        };
    }
}