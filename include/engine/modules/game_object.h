#pragma once

#include "object_components.h"

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

namespace easygine {
    class CORE;

    namespace objects {
        class GameObjectManager;
        
        class BaseObject : public sf::Drawable, public sf::Transformable {
            friend class easygine::CORE;
            friend class GameObjectManager;
        public:
            virtual void firstUpdate(sf::Time delta_time) {}

            virtual void update(sf::Time delta_time) {}

            virtual unsigned long long linkChildObject(const std::shared_ptr<BaseObject> &obj);
            
            virtual void unlinkChildObjectById(unsigned long long id);
            
            virtual void unlinkChildObjectByIndex(unsigned long long index);

            template<typename OBJ_TYPE>
            inline std::shared_ptr<OBJ_TYPE> getChildObjectById(unsigned long long id) const {
                for (unsigned long long i {this->m_Children.size()}; i--;) {
                    if (this->m_Children.at(i)->getId() == id) {
                        return dynamic_cast<const std::shared_ptr<OBJ_TYPE> &>(this->m_Children.at(i));
                        break;
                    }
                }
                return nullptr;
            }

            template<typename OBJ_TYPE>
            inline std::shared_ptr<OBJ_TYPE> getChildObjectByIndex(unsigned long long index) const {
                if (index < this->m_Children.size()) {
                    return dynamic_cast<const std::shared_ptr<OBJ_TYPE> &>(this->m_Children.at(index));
                }
                return nullptr;
            }
            
            inline unsigned long long getId() const {
                return this->m_Id;
            }

            void destroy() const;

        public:
            virtual ~BaseObject() = default;

            BaseObject(const BaseObject &copy)              = delete;
            BaseObject & operator=(const BaseObject &copy)  = delete;

        protected:
            BaseObject();

        protected:
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {}

            virtual void drawChildren(sf::RenderTarget& target, const sf::RenderStates &states) const;
        
        protected:
            unsigned long long m_Id;
            std::vector<std::shared_ptr<BaseObject>> m_Children;
        };
    }
}