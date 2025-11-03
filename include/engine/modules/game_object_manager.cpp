#include "game_object_manager.h"

#include "dev_console.h"
#include "../engine.h"
#include "../../misc/LogSys/log_sys.h"

#ifndef _RELEASE
namespace easygine {
    extern aether::lgs::Timer EngineClock;
    extern aether::lgs::Logger EngineLogger;
}
#endif

namespace easygine {
    namespace objects {
        bool GameObjectManager::init() {
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Game Objects initialization started.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);



            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Game Objects initialization successful.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

            return true;
        }

        void GameObjectManager::deinit() {
            this->m_ObjsToDraw.clear();
            this->m_ObjRegistry.clear();

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Game Objects deinitialized.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
        }

        std::shared_ptr<BaseObject> GameObjectManager::registerObject(const std::shared_ptr<BaseObject> &obj) {
            if (obj != nullptr) {
                unsigned long long obj_id = obj->getId();
                if (!this->m_ObjRegistry.count(obj_id)) {
                    if (!obj->m_Children.empty()) {
                        for (auto &child : obj->m_Children) {
                            this->registerObject(child);
                        }
                    }
                    if (this->m_ObjRegistry.emplace(obj_id, obj).second) {

                        lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Registered an object with id: ")lgs_MSG(obj_id)lgs_MSG(".");
                        CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                        lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
                    }
                }
            }

            return obj;
        }

        void GameObjectManager::unregisterObject(unsigned long long id) {
            if (this->m_ObjRegistry.count(id)) {
                if (this->m_ObjRegistry.at(id).unique()) {
                    if (!this->m_ObjRegistry.at(id)->m_Children.empty()) {
                        for (auto &child : this->m_ObjRegistry.at(id)->m_Children) {
                            this->unregisterObject(child->getId());
                        }
                    }
                        this->unmarkForDrawing(id);
                    this->m_ObjRegistry.erase(id);
                    
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Unregistered an object with id: ")lgs_MSG(id)lgs_MSG(".");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
                }
            }
        }

        void GameObjectManager::unregisterObject(const std::shared_ptr<BaseObject> &obj) {
            if (obj != nullptr) {
                unsigned long long obj_id = obj->getId();
                if (this->m_ObjRegistry.count(obj_id)) {
                    if (this->m_ObjRegistry.at(obj_id).unique()) {
                        if (!obj->m_Children.empty()) {
                            for (auto &child : obj->m_Children) {
                                this->unregisterObject(child->getId());
                            }
                        }
                        this->unmarkForDrawing(obj_id);
                        this->m_ObjRegistry.erase(obj_id);
                        
                        lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Unregistered an object with id: ")lgs_MSG(obj_id)lgs_MSG(".");
                        CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                        lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
                    }
                }
            }
        }

        void GameObjectManager::markForDrawing(unsigned long long id) {
            this->m_ObjsToDraw.emplace_back(id);
        }

        void GameObjectManager::unmarkForDrawing(unsigned long long id) {
            for (unsigned long long i {this->m_ObjsToDraw.size()}; i--;) {
                if (this->m_ObjsToDraw.at(i) == id) {
                    this->m_ObjsToDraw.erase(this->m_ObjsToDraw.begin() + id);
                }
            }
        }
        
        void GameObjectManager::queueForDestruction(unsigned long long id) {
            this->m_ObjsToDestroy.push(id);
        }

        void GameObjectManager::update() {
            while (!this->m_ObjsToDestroy.empty()) {
                this->unregisterObject(this->m_ObjsToDestroy.front());
                this->m_ObjsToDestroy.pop();
            }
        }

        void GameObjectManager::render(sf::RenderTarget &target, const sf::RenderStates &states) {
            for (auto &obj_id : this->m_ObjsToDraw) {
                target.draw(*this->m_ObjRegistry.at(obj_id), states);
            }
        }

        void GameObjectManager::doFirstUpdates(sf::Time elapsed_time) {
            for (auto &obj : this->m_ObjRegistry) {
                obj.second->firstUpdate(elapsed_time);
            }
        }

        void GameObjectManager::doUpdates(sf::Time elapsed_time) {
            for (auto &obj : this->m_ObjRegistry) {
                obj.second->update(elapsed_time);
            }
        }
    }
}