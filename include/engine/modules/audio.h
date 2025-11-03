#pragma once

#include <SFML/Audio.hpp>

#include <array>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

namespace easygine {
    class CORE;

    namespace audio {
        enum class EC_Volume {
              Music
            , SFX
            , Voice
            , Ambience
            , Master
        };

        class SoundObject {
        public:
            inline sf::Sound & sound() {
                return this->m_Sound;
            };
            
            inline const sf::Sound & sound() const {
                return this->m_Sound;
            };
            
            inline EC_Volume type() {
                return this->m_Type;
            };
            
            inline const EC_Volume type() const {
                return this->m_Type;
            };

        public:
            SoundObject(const sf::Sound &snd, EC_Volume type);

            SoundObject()             = default;
            virtual ~SoundObject()    = default;

        private:
            sf::Sound m_Sound;
            EC_Volume m_Type {EC_Volume::SFX};
        };

        struct S_SoundInfo {
            S_SoundInfo(float _pitch, float _attenuation, float _min_distance, sf::Vector3f _pos, bool _relative_to_lis, EC_Volume _type);
            
            S_SoundInfo(const std::shared_ptr<sf::SoundBuffer> &_sound_buff, float _pitch, float _attenuation, float _min_distance, sf::Vector3f _pos, bool _relative_to_lis, EC_Volume _type);

            std::shared_ptr<sf::SoundBuffer> sound_buff;
            float pitch {1.0f};
            float attenuation {1.0f};
            float min_distance {1.0f};
            sf::Vector3f position {0, 0, 0};
            bool relative_to_listener {false};
            EC_Volume type {EC_Volume::SFX};
        };

        class AudioMixer {
            friend class easygine::CORE;
        public:
            bool openMusic(const std::string &filename, unsigned long long index);

            void soundInfoToMusic(unsigned long long index, const S_SoundInfo &sndinf);
            
            void pauseMusic();
            
            void resumeMusic();
            
            void stopMusic();
            
            inline sf::Music & getMusicPlayer(unsigned long long index) {
                return ((index > 2) ? this->m_MusicPlayer.at(2ull) : this->m_MusicPlayer.at(index));
            }
            
            inline const sf::Music & getMusicPlayer(unsigned long long index) const {
                return ((index > 2) ? this->m_MusicPlayer.at(2ull) : this->m_MusicPlayer.at(index));
            }

            void playSound(const S_SoundInfo &sndinf);

            void changeAudioVolume(EC_Volume type, float value, bool save = false);
            
            float getAudioVolume(EC_Volume type) const;
            
            void muteAudio(EC_Volume type, bool mute, bool save = false);
            
            bool getAudioMute(EC_Volume type) const;

        public:
            AudioMixer()    = default;
            ~AudioMixer()   = default;

        private:
            bool init();
            
            void deinit();
            
            void update();

            void pauseSounds();
            
            void  resumeSounds();
            
            void wipeSounds();
            
            void setAudioVolume(EC_Volume type);
        
        private:
            std::array<sf::Music, 3ull> m_MusicPlayer;
            std::vector<SoundObject> m_Sounds;
            std::array<float, 5ull> m_Volumes {100.0f, 100.0f, 100.0f, 100.0f, 100.0f};
            std::array<bool, 5ull> m_Muted {false, false, false, false, false};
        };

        class Listener {
        public:
            static inline void setDirection(const sf::Vector3f &direction = {0.0f, 0.0f, -1.0f}) {
                sf::Listener::setDirection(direction);
            }

            static inline void setGlobalVolume(float volume = 100.0f) {
                sf::Listener::setGlobalVolume(volume);
            }
            
            static inline void setPosition(const sf::Vector3f &position = {0.0f, 0.0f, 0.0f}) {
                sf::Listener::setPosition(position);
            }
            
            static inline void setUpVector(const sf::Vector3f &upVector = {0.0f, 1.0f, 0.0f}) {
                sf::Listener::setUpVector(upVector);
            }

            static inline sf::Vector3f getDirection() {
                return sf::Listener::getDirection();
            }
            
            static inline float getGlobalVolume() {
                return sf::Listener::getGlobalVolume();
            }
            
            static inline sf::Vector3f getPosition() {
                return sf::Listener::getPosition();
            }
            
            static inline sf::Vector3f getUpVector() {
                return sf::Listener::getUpVector();
            }

        public:
            Listener()  = delete;
            ~Listener() = delete;

            Listener(const Listener &copy)              = delete;
            Listener & operator=(const Listener &copy)  = delete;
        };
    }
}