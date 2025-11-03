#include "resource_manager.h"

#include "../defines.h"
#include "dev_console.h"
#include "../engine.h"
#include "../../misc/LogSys/log_sys.h"

#include <TGUI/Font.hpp>

#include <fstream>
#include <sstream>
#include <stdexcept>

#ifndef _RELEASE
namespace easygine {
    extern aether::lgs::Timer EngineClock;
    extern aether::lgs::Logger EngineLogger;
}
#endif

namespace easygine {
    namespace resources {
        bool ResourceManager::init() {
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Resource management initialization started.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

            

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Resource management initialization successful.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

            return true;
        }

        void ResourceManager::deinit() {
            
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Resource management deinitialized.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
        }

        const sf::Image & ResourceManager::loadUniqueImage(const std::string &resource_name, const std::string &resource_file) {
            try {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Retrieving unique image resource \'")lgs_MSG(resource_name)lgs_MSG("\'...");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                return this->m_UniqueImageResourceHandler[resource_name];
            }
            catch (thor::ResourceAccessException &e) {
                try {
                    const sf::Image &rsrc = this->m_UniqueImageResourceHandler.acquire(resource_name, thor::Resources::fromFile<sf::Image>(resource_file), thor::Resources::Reload);

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Loaded unique image resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    return rsrc;
                }
                catch (thor::ResourceLoadingException &e) {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed loading unique image resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    std::terminate();
                }
            }
        }

        const sf::Image & ResourceManager::loadUniqueImage(const std::string &resource_name, const thor::ResourceLoader<sf::Image> &resource_loader) {
            try {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Retrieving unique image resource \'")lgs_MSG(resource_name)lgs_MSG("\'...");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                return this->m_UniqueImageResourceHandler[resource_name];
            }
            catch (thor::ResourceAccessException &e) {
                try {
                    const sf::Image &rsrc = this->m_UniqueImageResourceHandler.acquire(resource_name, std::forward<const thor::ResourceLoader<sf::Image> &>(resource_loader), thor::Resources::Reload);

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Loaded unique image resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    return rsrc;
                }
                catch (thor::ResourceLoadingException &e) {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed loading unique image resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    std::terminate();
                }
            }
        }

        void ResourceManager::unloadUniqueImage(const std::string &resource_name) {
            try {
                this->m_UniqueImageResourceHandler.release(resource_name);

                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Unique image resource \'")lgs_MSG(resource_name)lgs_MSG("\' unloaded.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
            }
            catch (thor::ResourceAccessException &e) {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Unique image resource \'")lgs_MSG(resource_name)lgs_MSG("\' is not present.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
            }
        }

        const sf::Texture & ResourceManager::loadUniqueTexture(const std::string &resource_name, const std::string &resource_file, const sf::IntRect &tex_rect) {
            try {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Retrieving unique texture resource \'")lgs_MSG(resource_name)lgs_MSG("\'...");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                return this->m_UniqueTextureResourceHandler[resource_name];
            }
            catch (thor::ResourceAccessException &e) {
                try {
                    const sf::Texture &rsrc = this->m_UniqueTextureResourceHandler.acquire(resource_name, thor::Resources::fromFile<sf::Texture>(resource_file, tex_rect), thor::Resources::Reload);

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Loaded unique texture resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    return rsrc;
                }
                catch (thor::ResourceLoadingException &e) {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed loading unique texture resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    std::terminate();
                }
            }
        }

        const sf::Texture & ResourceManager::loadUniqueTexture(const std::string &resource_name, const thor::ResourceLoader<sf::Texture> &resource_loader) {
            try {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Retrieving unique texture resource \'")lgs_MSG(resource_name)lgs_MSG("\'...");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                return this->m_UniqueTextureResourceHandler[resource_name];
            }
            catch (thor::ResourceAccessException &e) {
                try {
                    const sf::Texture &rsrc = this->m_UniqueTextureResourceHandler.acquire(resource_name, std::forward<const thor::ResourceLoader<sf::Texture> &>(resource_loader), thor::Resources::Reload);

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Loaded unique texture resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    return rsrc;
                }
                catch (thor::ResourceLoadingException &e) {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed loading unique texture resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    std::terminate();
                }
            }
        }

        void ResourceManager::unloadUniqueTexture(const std::string &resource_name) {
            try {
                this->m_UniqueTextureResourceHandler.release(resource_name);

                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Unique texture resource \'")lgs_MSG(resource_name)lgs_MSG("\' unloaded.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
            }
            catch (thor::ResourceAccessException &e) {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Unique texture resource \'")lgs_MSG(resource_name)lgs_MSG("\' is not present.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
            }
        }

        const tgui::BackendFontSFML & ResourceManager::loadUniqueFont(const std::string &resource_name, const std::string &resource_file) {
            try {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Retrieving unique font resource \'")lgs_MSG(resource_name)lgs_MSG("\'...");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                return this->m_UniqueFontResourceHandler[resource_name];
            }
            catch (thor::ResourceAccessException &e) {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("FONT LOADERS NOT SUPPORTED YET.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
                    std::terminate();
            }
        }

        const tgui::BackendFontSFML & ResourceManager::loadUniqueFont(const std::string &resource_name, const thor::ResourceLoader<tgui::BackendFontSFML> &resource_loader) {
            try {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Retrieving unique font resource \'")lgs_MSG(resource_name)lgs_MSG("\'...");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                return this->m_UniqueFontResourceHandler[resource_name];
            }
            catch (thor::ResourceAccessException &e) {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("FONT LOADERS NOT SUPPORTED YET.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
                    std::terminate();
            }
        }

        void ResourceManager::unloadUniqueFont(const std::string &resource_name) {
            try {
                this->m_UniqueFontResourceHandler.release(resource_name);

                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Unique font resource \'")lgs_MSG(resource_name)lgs_MSG("\' unloaded.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
            }
            catch (thor::ResourceAccessException &e) {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Unique font resource \'")lgs_MSG(resource_name)lgs_MSG("\' is not present.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
            }
        }

        const sf::Shader & ResourceManager::loadUniqueShader(const std::string &resource_name, const std::string &vert_file, const std::string &frag_file) {
            try {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Retrieving unique shader resource \'")lgs_MSG(resource_name)lgs_MSG("\'...");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                return this->m_UniqueShaderResourceHandler[resource_name];
            }
            catch (thor::ResourceAccessException &e) {
                try {
                    const sf::Shader &rsrc = this->m_UniqueShaderResourceHandler.acquire(resource_name, thor::Resources::fromFile<sf::Shader>(vert_file, frag_file), thor::Resources::Reload);

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Loaded unique shader resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    return rsrc;
                }
                catch (thor::ResourceLoadingException &e) {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed loading unique shader resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    std::terminate();
                }
            }
        }
        
        const sf::Shader & ResourceManager::loadUniqueShader(const std::string &resource_name, const std::string &vert_file, const std::string &geom_file, const std::string &frag_file) {
            try {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Retrieving unique shader resource \'")lgs_MSG(resource_name)lgs_MSG("\'...");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                return this->m_UniqueShaderResourceHandler[resource_name];
            }
            catch (thor::ResourceAccessException &e) {
                try {
                    std::stringstream shdr_vert_stream;
                    std::ifstream shdr_vert(vert_file, std::ios::in);
                    if (shdr_vert.is_open()) {
                        shdr_vert_stream << shdr_vert.rdbuf();
                    }
                    else {
                        thor::ResourceLoadingException exc("Failed to open shader file.");
                        throw exc;
                    }
                    
                    std::stringstream shdr_geom_stream;
                    std::ifstream shdr_geom(geom_file, std::ios::in);
                    if (shdr_geom.is_open()) {
                        shdr_geom_stream << shdr_geom.rdbuf();
                    }
                    else {
                        thor::ResourceLoadingException exc("Failed to open shader file.");
                        throw exc;
                    }

                    std::stringstream shdr_frag_stream;
                    std::ifstream shdr_frag(frag_file, std::ios::in);
                    if (shdr_frag.is_open()) {
                        shdr_frag_stream << shdr_frag.rdbuf();
                    }
                    else {
                        thor::ResourceLoadingException exc("Failed to open shader file.");
                        throw exc;
                    }

                    const sf::Shader &rsrc = this->m_UniqueShaderResourceHandler.acquire(resource_name, thor::Resources::fromMemory<sf::Shader>(shdr_vert_stream.str(), shdr_geom_stream.str(), shdr_frag_stream.str()), thor::Resources::Reload);

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Loaded unique shader resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    return rsrc;
                }
                catch (thor::ResourceLoadingException &e) {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed loading unique shader resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    std::terminate();
                }
            }
        }

        const sf::Shader & ResourceManager::loadUniqueShader(const std::string &resource_name, const std::string &resource_file, sf::Shader::Type shader_type) {
            try {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Retrieving unique shader resource \'")lgs_MSG(resource_name)lgs_MSG("\'...");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                return this->m_UniqueShaderResourceHandler[resource_name];
            }
            catch (thor::ResourceAccessException &e) {
                try {
                    const sf::Shader &rsrc = this->m_UniqueShaderResourceHandler.acquire(resource_name, thor::Resources::fromFile<sf::Shader>(resource_file, shader_type), thor::Resources::Reload);

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Loaded unique shader resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    return rsrc;
                }
                catch (thor::ResourceLoadingException &e) {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed loading unique shader resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    std::terminate();
                }
            }
        }

        const sf::Shader & ResourceManager::loadUniqueShader(const std::string &resource_name, const thor::ResourceLoader<sf::Shader> &resource_loader) {
            try {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Retrieving unique shader resource \'")lgs_MSG(resource_name)lgs_MSG("\'...");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                return this->m_UniqueShaderResourceHandler[resource_name];
            }
            catch (thor::ResourceAccessException &e) {
                try {
                    const sf::Shader &rsrc = this->m_UniqueShaderResourceHandler.acquire(resource_name, std::forward<const thor::ResourceLoader<sf::Shader> &>(resource_loader), thor::Resources::Reload);

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Loaded unique shader resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    return rsrc;
                }
                catch (thor::ResourceLoadingException &e) {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed loading unique shader resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    std::terminate();
                }
            }
        }

        void ResourceManager::unloadUniqueShader(const std::string &resource_name) {
            try {
                this->m_UniqueShaderResourceHandler.release(resource_name);

                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Unique shader resource \'")lgs_MSG(resource_name)lgs_MSG("\' unloaded.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
            }
            catch (thor::ResourceAccessException &e) {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Unique shader resource \'")lgs_MSG(resource_name)lgs_MSG("\' is not present.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
            }
        }

        const sf::SoundBuffer & ResourceManager::loadUniqueSoundBuffer(const std::string &resource_name, const std::string &resource_file) {
            try {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Retrieving unique sound buffer resource \'")lgs_MSG(resource_name)lgs_MSG("\'...");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                return this->m_UniqueSoundBufferResourceHandler[resource_name];
            }
            catch (thor::ResourceAccessException &e) {
                try {
                    const sf::SoundBuffer &rsrc = this->m_UniqueSoundBufferResourceHandler.acquire(resource_name, thor::Resources::fromFile<sf::SoundBuffer>(resource_file), thor::Resources::Reload);

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Loaded unique sound buffer resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    return rsrc;
                }
                catch (thor::ResourceLoadingException &e) {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed loading unique sound buffer resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    std::terminate();
                }
            }
        }

        const sf::SoundBuffer & ResourceManager::loadUniqueSoundBuffer(const std::string &resource_name, const thor::ResourceLoader<sf::SoundBuffer> &resource_loader) {
            try {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Retrieving unique sound buffer resource \'")lgs_MSG(resource_name)lgs_MSG("\'...");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                return this->m_UniqueSoundBufferResourceHandler[resource_name];
            }
            catch (thor::ResourceAccessException &e) {
                try {
                    const sf::SoundBuffer &rsrc = this->m_UniqueSoundBufferResourceHandler.acquire(resource_name, std::forward<const thor::ResourceLoader<sf::SoundBuffer> &>(resource_loader), thor::Resources::Reload);

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Loaded unique sound buffer resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    return rsrc;
                }
                catch (thor::ResourceLoadingException &e) {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed loading unique sound buffer resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    std::terminate();
                }
            }
        }

        void ResourceManager::unloadUniqueSoundBuffer(const std::string &resource_name) {
            try {
                this->m_UniqueSoundBufferResourceHandler.release(resource_name);

                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Unique sound buffer resource \'")lgs_MSG(resource_name)lgs_MSG("\' unloaded.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
            }
            catch (thor::ResourceAccessException &e) {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Unique sound buffer resource \'")lgs_MSG(resource_name)lgs_MSG("\' is not present.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
            }
        }

        std::shared_ptr<sf::Image> ResourceManager::loadSharedImage(const std::string &resource_name, const std::string &resource_file) {
            try {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Retrieving shared image resource \'")lgs_MSG(resource_name)lgs_MSG("\'...");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                return this->m_SharedImageResourceHandler[resource_name];
            }
            catch (thor::ResourceAccessException &e) {
                try {
                    const std::shared_ptr<sf::Image> &rsrc = this->m_SharedImageResourceHandler.acquire(resource_name, thor::Resources::fromFile<sf::Image>(resource_file), thor::Resources::Reuse);

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Loaded shared image resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    return rsrc;
                }
                catch (thor::ResourceLoadingException &e) {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed loading shared image resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    std::terminate();
                }
            }
        }

        std::shared_ptr<sf::Image> ResourceManager::loadSharedImage(const std::string &resource_name, const thor::ResourceLoader<sf::Image> &resource_loader) {
            try {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Retrieving shared image resource \'")lgs_MSG(resource_name)lgs_MSG("\'...");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                return this->m_SharedImageResourceHandler[resource_name];
            }
            catch (thor::ResourceAccessException &e) {
                try {
                    const std::shared_ptr<sf::Image> &rsrc = this->m_SharedImageResourceHandler.acquire(resource_name, std::forward<const thor::ResourceLoader<sf::Image> &>(resource_loader), thor::Resources::Reuse);

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Loaded shared image resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    return rsrc;
                }
                catch (thor::ResourceLoadingException &e) {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed loading shared image resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    std::terminate();
                }
            }
        }

        void ResourceManager::unloadSharedImage(const std::string &resource_name) {
            try {
                this->m_SharedImageResourceHandler.release(resource_name);

                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Shared image resource \'")lgs_MSG(resource_name)lgs_MSG("\' unloaded.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
            }
            catch (thor::ResourceAccessException &e) {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Shared image resource \'")lgs_MSG(resource_name)lgs_MSG("\' is not present.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
            }
        }

        std::shared_ptr<sf::Texture> ResourceManager::loadSharedTexture(const std::string &resource_name, const std::string &resource_file, const sf::IntRect &tex_rect) {
            try {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Retrieving shared texture resource \'")lgs_MSG(resource_name)lgs_MSG("\'...");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                return this->m_SharedTextureResourceHandler[resource_name];
            }
            catch (thor::ResourceAccessException &e) {
                try {
                    const std::shared_ptr<sf::Texture> &rsrc = this->m_SharedTextureResourceHandler.acquire(resource_name, thor::Resources::fromFile<sf::Texture>(resource_file, tex_rect), thor::Resources::Reuse);

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Loaded shared texture resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    return rsrc;
                }
                catch (thor::ResourceLoadingException &e) {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed loading shared texture resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    std::terminate();
                }
            }
        }

        std::shared_ptr<sf::Texture> ResourceManager::loadSharedTexture(const std::string &resource_name, const thor::ResourceLoader<sf::Texture> &resource_loader) {
            try {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Retrieving shared texture resource \'")lgs_MSG(resource_name)lgs_MSG("\'...");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                return this->m_SharedTextureResourceHandler[resource_name];
            }
            catch (thor::ResourceAccessException &e) {
                try {
                    const std::shared_ptr<sf::Texture> &rsrc = this->m_SharedTextureResourceHandler.acquire(resource_name, std::forward<const thor::ResourceLoader<sf::Texture> &>(resource_loader), thor::Resources::Reuse);

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Loaded shared texture resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    return rsrc;
                }
                catch (thor::ResourceLoadingException &e) {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed loading shared texture resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    std::terminate();
                }
            }
        }

        void ResourceManager::unloadSharedTexture(const std::string &resource_name) {
            try {
                this->m_SharedTextureResourceHandler.release(resource_name);

                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Shared texture resource \'")lgs_MSG(resource_name)lgs_MSG("\' unloaded.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
            }
            catch (thor::ResourceAccessException &e) {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Shared texture resource \'")lgs_MSG(resource_name)lgs_MSG("\' is not present.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
            }
        }

        std::shared_ptr<tgui::BackendFontSFML> ResourceManager::loadSharedFont(const std::string &resource_name, const std::string &resource_file) {
            try {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Retrieving shared font resource \'")lgs_MSG(resource_name)lgs_MSG("\'...");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                return this->m_SharedFontResourceHandler[resource_name];
            }
            catch (thor::ResourceAccessException &e) {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("FONT LOADERS NOT SUPPORTED YET.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
                    std::terminate();
            }
        }

        std::shared_ptr<tgui::BackendFontSFML> ResourceManager::loadSharedFont(const std::string &resource_name, const thor::ResourceLoader<tgui::BackendFontSFML> &resource_loader) {
            try {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Retrieving shared font resource \'")lgs_MSG(resource_name)lgs_MSG("\'...");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                return this->m_SharedFontResourceHandler[resource_name];
            }
            catch (thor::ResourceAccessException &e) {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("FONT LOADERS NOT SUPPORTED YET.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
                    std::terminate();
            }
        }

        void ResourceManager::unloadSharedFont(const std::string &resource_name) {
            try {
                this->m_SharedFontResourceHandler.release(resource_name);

                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Shared font resource \'")lgs_MSG(resource_name)lgs_MSG("\' unloaded.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
            }
            catch (thor::ResourceAccessException &e) {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Shared font resource \'")lgs_MSG(resource_name)lgs_MSG("\' is not present.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
            }
        }

        std::shared_ptr<sf::Shader> ResourceManager::loadSharedShader(const std::string &resource_name, const std::string &vert_file, const std::string &frag_file) {
            try {
                const std::shared_ptr<sf::Shader> &rsrc = this->m_SharedShaderResourceHandler.acquire(resource_name, thor::Resources::fromFile<sf::Shader>(vert_file, frag_file), thor::Resources::Reuse);

                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Loaded shared shader resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                return rsrc;
            }
            catch (thor::ResourceLoadingException &e) {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed loading shared shader resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                std::terminate();
            }
        }
        
        std::shared_ptr<sf::Shader> ResourceManager::loadSharedShader(const std::string &resource_name, const std::string &vert_file, const std::string &geom_file, const std::string &frag_file) {
            try {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Retrieving shared shader resource \'")lgs_MSG(resource_name)lgs_MSG("\'...");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                return this->m_SharedShaderResourceHandler[resource_name];
            }
            catch (thor::ResourceAccessException &e) {
                try {
                    std::stringstream shdr_vert_stream;
                    std::ifstream shdr_vert(vert_file, std::ios::in);
                    if (shdr_vert.is_open()) {
                        shdr_vert_stream << shdr_vert.rdbuf();
                    }
                    else {
                        thor::ResourceLoadingException exc("Failed to open shader file.");
                        throw exc;
                    }
                    
                    std::stringstream shdr_geom_stream;
                    std::ifstream shdr_geom(geom_file, std::ios::in);
                    if (shdr_geom.is_open()) {
                        shdr_geom_stream << shdr_geom.rdbuf();
                    }
                    else {
                        thor::ResourceLoadingException exc("Failed to open shader file.");
                        throw exc;
                    }

                    std::stringstream shdr_frag_stream;
                    std::ifstream shdr_frag(frag_file, std::ios::in);
                    if (shdr_frag.is_open()) {
                        shdr_frag_stream << shdr_frag.rdbuf();
                    }
                    else {
                        thor::ResourceLoadingException exc("Failed to open shader file.");
                        throw exc;
                    }

                    const std::shared_ptr<sf::Shader> &rsrc = this->m_SharedShaderResourceHandler.acquire(resource_name, thor::Resources::fromMemory<sf::Shader>(shdr_vert_stream.str(), shdr_geom_stream.str(), shdr_frag_stream.str()), thor::Resources::Reuse);

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Loaded shared shader resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    return rsrc;
                }
                catch (thor::ResourceLoadingException &e) {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed loading shared shader resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
                    
                    std::terminate();
                }
            }
        }

        std::shared_ptr<sf::Shader> ResourceManager::loadSharedShader(const std::string &resource_name, const std::string &resource_file, sf::Shader::Type shader_type) {
            try {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Retrieving shared shader resource \'")lgs_MSG(resource_name)lgs_MSG("\'...");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                return this->m_SharedShaderResourceHandler[resource_name];
            }
            catch (thor::ResourceAccessException &e) {
                try {
                    const std::shared_ptr<sf::Shader> &rsrc = this->m_SharedShaderResourceHandler.acquire(resource_name, thor::Resources::fromFile<sf::Shader>(resource_file, shader_type), thor::Resources::Reuse);

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Loaded shared shader resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    return rsrc;
                }
                catch (thor::ResourceLoadingException &e) {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed loading shared shader resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    std::terminate();
                }
            }
        }

        std::shared_ptr<sf::Shader> ResourceManager::loadSharedShader(const std::string &resource_name, const thor::ResourceLoader<sf::Shader> &resource_loader) {
            try {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Retrieving shared shader resource \'")lgs_MSG(resource_name)lgs_MSG("\'...");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                return this->m_SharedShaderResourceHandler[resource_name];
            }
            catch (thor::ResourceAccessException &e) {
                try {
                    const std::shared_ptr<sf::Shader> &rsrc = this->m_SharedShaderResourceHandler.acquire(resource_name, std::forward<const thor::ResourceLoader<sf::Shader> &>(resource_loader), thor::Resources::Reuse);

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Loaded shared shader resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    return rsrc;
                }
                catch (thor::ResourceLoadingException &e) {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed loading shared shader resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    std::terminate();
                }
            }
        }

        void ResourceManager::unloadSharedShader(const std::string &resource_name) {
            try {
                this->m_SharedShaderResourceHandler.release(resource_name);

                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Shared shader resource \'")lgs_MSG(resource_name)lgs_MSG("\' unloaded.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
            }
            catch (thor::ResourceAccessException &e) {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Shared shader resource \'")lgs_MSG(resource_name)lgs_MSG("\' is not present.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
            }
        }

        std::shared_ptr<sf::SoundBuffer> ResourceManager::loadSharedSoundBuffer(const std::string &resource_name, const std::string &resource_file) {
            try {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Retrieving shared sound buffer resource \'")lgs_MSG(resource_name)lgs_MSG("\'...");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                return this->m_SharedSoundBufferResourceHandler[resource_name];
            }
            catch (thor::ResourceAccessException &e) {
                try {
                    const std::shared_ptr<sf::SoundBuffer> &rsrc = this->m_SharedSoundBufferResourceHandler.acquire(resource_name, thor::Resources::fromFile<sf::SoundBuffer>(resource_file), thor::Resources::Reuse);

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Loaded shared sound buffer resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    return rsrc;
                }
                catch (thor::ResourceLoadingException &e) {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed loading shared sound buffer resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    std::terminate();
                }
            }
        }

        std::shared_ptr<sf::SoundBuffer> ResourceManager::loadSharedSoundBuffer(const std::string &resource_name, const thor::ResourceLoader<sf::SoundBuffer> &resource_loader) {
            try {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Retrieving shared sound buffer resource \'")lgs_MSG(resource_name)lgs_MSG("\'...");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                return this->m_SharedSoundBufferResourceHandler[resource_name];
            }
            catch (thor::ResourceAccessException &e) {
                try {
                    const std::shared_ptr<sf::SoundBuffer> &rsrc = this->m_SharedSoundBufferResourceHandler.acquire(resource_name, std::forward<const thor::ResourceLoader<sf::SoundBuffer> &>(resource_loader), thor::Resources::Reuse);

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Loaded shared sound buffer resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    return rsrc;
                }
                catch (thor::ResourceLoadingException &e) {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed loading shared sound buffer resource \'")lgs_MSG(resource_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    std::terminate();
                }
            }
        }

        void ResourceManager::unloadSharedSoundBuffer(const std::string &resource_name) {
            try {
                this->m_SharedSoundBufferResourceHandler.release(resource_name);

                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Shared sound buffer resource \'")lgs_MSG(resource_name)lgs_MSG("\' unloaded.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
            }
            catch (thor::ResourceAccessException &e) {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Shared sound buffer resource \'")lgs_MSG(resource_name)lgs_MSG("\' is not present.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
            }
        }
    }
}