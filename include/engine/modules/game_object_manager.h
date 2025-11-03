#pragma once

#include "game_object.h"

#include <memory>
#include <vector>
#include <unordered_map>
#include <queue>

namespace easygine {
    class CORE;
    
    namespace objects {
        class GameObjectManager {
            friend class easygine::CORE;
        public:
            std::shared_ptr<BaseObject> registerObject(const std::shared_ptr<BaseObject> &obj);

            void unregisterObject(unsigned long long id);

            void unregisterObject(const std::shared_ptr<BaseObject> &obj);

            void markForDrawing(unsigned long long id);

            void unmarkForDrawing(unsigned long long id);

            void queueForDestruction(unsigned long long id);

        public:
            template<typename OBJ_TYPE>
            inline std::shared_ptr<OBJ_TYPE> getObject(unsigned long long id) {
                if (this->m_ObjRegistry.count(id)) {
                    return dynamic_cast<const std::shared_ptr<OBJ_TYPE> &>(*this->m_ObjRegistry.at(id));
                }
                return nullptr;
            }

        public:
            GameObjectManager()             = default;
            virtual ~GameObjectManager()    = default;

        protected:
            bool init();
            
            void deinit();

            void update();

            void render(sf::RenderTarget &target, const sf::RenderStates &states);

            void doFirstUpdates(sf::Time elapsed_time);
            
            void doUpdates(sf::Time elapsed_time);

        private:
            std::unordered_map<unsigned long long, std::shared_ptr<BaseObject>> m_ObjRegistry;
            std::vector<unsigned long long> m_ObjsToDraw;
            std::queue<unsigned long long> m_ObjsToDestroy;
        };
    }
}