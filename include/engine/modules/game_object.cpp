#include "game_object.h"

#include "../engine.h"
#include "game_object_manager.h"

#include "../../misc/RNG/rng.h"

namespace easygine {
    namespace internal_uid_gen {
        static aether::rng::SimpleRandom s_uidGenerator;
    }

    namespace objects {
        BaseObject::BaseObject()
            : m_Id(internal_uid_gen::s_uidGenerator.getUlong(0ull, ULONG_LONG_MAX))
            {}

        unsigned long long BaseObject::linkChildObject(const std::shared_ptr<BaseObject> &obj) {
            if (this->m_Children.emplace_back(obj) != nullptr) {
                return this->m_Children.size() - 1ull;
            }
            return this->m_Children.max_size();
        }
            
        void BaseObject::unlinkChildObjectById(unsigned long long id) {
            for (unsigned long long i {this->m_Children.size()}; i--;) {
                if (this->m_Children.at(i)->getId() == id) {
                    this->m_Children.at(i) = nullptr;
                    break;
                }
            }
        }

        void BaseObject::unlinkChildObjectByIndex(unsigned long long index) {
            if (index < this->m_Children.size()) {
                this->m_Children.at(index) = nullptr;
            }
        }

        void BaseObject::destroy() const {
            internal_handle_core.gameObjects()->queueForDestruction(this->m_Id);
        }

        void BaseObject::drawChildren(sf::RenderTarget& target, const sf::RenderStates &states) const {
            if (!this->m_Children.empty()) {
                for (auto &child : this->m_Children) {
                    if (child != nullptr) {
                        target.draw(*child, states);
                    }
                }
            }
        }
    }
}