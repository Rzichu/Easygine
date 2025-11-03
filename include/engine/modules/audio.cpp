#include "audio.h"

#include "../engine.h"
#include "dev_console.h"
#include "../../misc/LogSys/log_sys.h"
#include "../../misc/EnumEra/enum_era.h"

#include <memory>

#ifndef _RELEASE
namespace easygine {
    extern aether::lgs::Timer EngineClock;
    extern aether::lgs::Logger EngineLogger;
}
#endif

namespace easygine {
    namespace audio {
        SoundObject::SoundObject(const sf::Sound &snd, EC_Volume type)
            : m_Sound(snd)
            , m_Type(type)
            {}
        
        S_SoundInfo::S_SoundInfo(float _pitch, float _attenuation, float _min_distance, sf::Vector3f _pos, bool _relative_to_lis, EC_Volume _type)
            : sound_buff{nullptr}
            , pitch {_pitch}
            , attenuation {_attenuation}
            , min_distance {_min_distance}
            , position {_pos}
            , relative_to_listener {_relative_to_lis}
            , type {_type}
            {}
        
        S_SoundInfo::S_SoundInfo(const std::shared_ptr<sf::SoundBuffer> &_sound_buff, float _pitch, float _attenuation, float _min_distance, sf::Vector3f _pos, bool _relative_to_lis, EC_Volume _type)
            : sound_buff{_sound_buff}
            , pitch {_pitch}
            , attenuation {_attenuation}
            , min_distance {_min_distance}
            , position {_pos}
            , relative_to_listener {_relative_to_lis}
            , type {_type}
            {}
        
        bool AudioMixer::init() {
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Audio initialization started.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

            this->changeAudioVolume(EC_Volume::Master, easygine::CORE::core().gameSettings()->getDoubleSetting(GAME_SETTING_AUDIO_VOLUME_MASTER, 100.0f, false), false);
            this->changeAudioVolume(EC_Volume::Music, easygine::CORE::core().gameSettings()->getDoubleSetting(GAME_SETTING_AUDIO_VOLUME_MUSIC, 100.0f, false), false);
            this->changeAudioVolume(EC_Volume::SFX, easygine::CORE::core().gameSettings()->getDoubleSetting(GAME_SETTING_AUDIO_VOLUME_SFX, 100.0f, false), false);
            this->changeAudioVolume(EC_Volume::Voice, easygine::CORE::core().gameSettings()->getDoubleSetting(GAME_SETTING_AUDIO_VOLUME_VOICE, 100.0f, false), false);
            this->changeAudioVolume(EC_Volume::Ambience, easygine::CORE::core().gameSettings()->getDoubleSetting(GAME_SETTING_AUDIO_VOLUME_AMBIENCE, 100.0f, false), false);

            this->muteAudio(EC_Volume::Master, easygine::CORE::core().gameSettings()->getBoolSetting(GAME_SETTING_AUDIO_MUTE_MASTER, false, false), false);
            this->muteAudio(EC_Volume::Music, easygine::CORE::core().gameSettings()->getBoolSetting(GAME_SETTING_AUDIO_MUTE_MUSIC, false, false), false);
            this->muteAudio(EC_Volume::SFX, easygine::CORE::core().gameSettings()->getBoolSetting(GAME_SETTING_AUDIO_MUTE_SFX, false, false), false);
            this->muteAudio(EC_Volume::Voice, easygine::CORE::core().gameSettings()->getBoolSetting(GAME_SETTING_AUDIO_MUTE_VOICE, false, false), false);
            this->muteAudio(EC_Volume::Ambience, easygine::CORE::core().gameSettings()->getBoolSetting(GAME_SETTING_AUDIO_MUTE_AMBIENCE, false, false), false);

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Audio initialization successful.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

            return true;
        }

        void AudioMixer::deinit() {
            
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Audio deinitialized.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
        }

        bool AudioMixer::openMusic(const std::string &filename, unsigned long long index) {
            if (this->m_MusicPlayer.at(index).openFromFile(filename)) {
                if (this->m_Muted.at(aether::enumera::enumToNum(EC_Volume::Music)) || this->m_Muted.at(aether::enumera::enumToNum(EC_Volume::Master))) {
                    this->m_MusicPlayer.at(index).setVolume(0.0f);
                }
                else {
                    this->m_MusicPlayer.at(index).setVolume(this->m_Volumes.at(aether::enumera::enumToNum(EC_Volume::Music)));
                }
                this->m_MusicPlayer.at(index).play();
                return true;
            }
            return false;
        }

        void AudioMixer::soundInfoToMusic(unsigned long long index, const S_SoundInfo &sndinf) {
            auto &music_player = this->m_MusicPlayer.at(index);
            music_player.setPitch(sndinf.pitch);
            music_player.setAttenuation(sndinf.attenuation);
            music_player.setMinDistance(sndinf.min_distance);
            music_player.setPosition(sndinf.position);
            music_player.setRelativeToListener(sndinf.relative_to_listener);
        }

        void AudioMixer::pauseMusic() {
            for (auto &music : this->m_MusicPlayer) {
                music.pause();
            }
        }

        void AudioMixer::resumeMusic() {
            for (auto &music : this->m_MusicPlayer) {
                music.play();
            }
        }

        void AudioMixer::stopMusic() {
            for (auto &music : this->m_MusicPlayer) {
                music.stop();
            }
        }

        void AudioMixer::playSound(const S_SoundInfo &sndinf) {
            if (this->m_Sounds.size() < 257ull) {
                auto &added_snd = this->m_Sounds.emplace_back(sf::Sound(*sndinf.sound_buff), sndinf.type);
                added_snd.sound().setPitch(sndinf.pitch);
                added_snd.sound().setAttenuation(sndinf.attenuation);
                added_snd.sound().setMinDistance(sndinf.min_distance);
                added_snd.sound().setPosition(sndinf.position);
                added_snd.sound().setRelativeToListener(sndinf.relative_to_listener);
                if (this->m_Muted.at(aether::enumera::enumToNum(sndinf.type)) || this->m_Muted.at(aether::enumera::enumToNum(EC_Volume::Master))) {
                    added_snd.sound().setVolume(0.0f);
                }
                else {
                    added_snd.sound().setVolume(this->m_Volumes.at(aether::enumera::enumToNum(sndinf.type)));
                }
                added_snd.sound().play();
            }
        }

        void AudioMixer::changeAudioVolume(EC_Volume type, float value, bool save) {
            switch (type) {
                case EC_Volume::Music: {
                    this->m_Volumes.at(aether::enumera::enumToNum(EC_Volume::Music)) = value;
                    if (save) {
                        easygine::CORE::core().gameSettings()->setSetting(GAME_SETTING_AUDIO_VOLUME_MUSIC, value);
                    }
                    break;
                }
                case EC_Volume::SFX: {
                    this->m_Volumes.at(aether::enumera::enumToNum(EC_Volume::SFX)) = value;
                    if (save) {
                        easygine::CORE::core().gameSettings()->setSetting(GAME_SETTING_AUDIO_VOLUME_SFX, value);
                    }
                    break;
                }
                case EC_Volume::Voice: {
                    this->m_Volumes.at(aether::enumera::enumToNum(EC_Volume::Voice)) = value;
                    if (save) {
                        easygine::CORE::core().gameSettings()->setSetting(GAME_SETTING_AUDIO_VOLUME_VOICE, value);
                    }
                    break;
                }
                case EC_Volume::Ambience: {
                    this->m_Volumes.at(aether::enumera::enumToNum(EC_Volume::Ambience)) = value;
                    if (save) {
                        easygine::CORE::core().gameSettings()->setSetting(GAME_SETTING_AUDIO_VOLUME_AMBIENCE, value);
                    }
                    break;
                }
                case EC_Volume::Master: {
                    this->m_Volumes.at(aether::enumera::enumToNum(EC_Volume::Master)) = value;
                    if (save) {
                        easygine::CORE::core().gameSettings()->setSetting(GAME_SETTING_AUDIO_VOLUME_MASTER, value);
                    }
                    break;
                }
                default: {}
            }
            this->setAudioVolume(type);
        }

        float AudioMixer::getAudioVolume(EC_Volume type) const {
            switch (type) {
                case EC_Volume::Music: {
                    return this->m_Volumes.at(aether::enumera::enumToNum(EC_Volume::Music));
                }
                case EC_Volume::SFX: {
                    return this->m_Volumes.at(aether::enumera::enumToNum(EC_Volume::SFX));
                }
                case EC_Volume::Voice: {
                    return this->m_Volumes.at(aether::enumera::enumToNum(EC_Volume::Voice));
                }
                case EC_Volume::Ambience: {
                    return this->m_Volumes.at(aether::enumera::enumToNum(EC_Volume::Ambience));
                }
                case EC_Volume::Master:
                default: {
                    return this->m_Volumes.at(aether::enumera::enumToNum(EC_Volume::Master));
                }
            }
        }

        void AudioMixer::muteAudio(EC_Volume type, bool mute, bool save) {
            switch (type) {
                case EC_Volume::Music: {
                    this->m_Muted.at(aether::enumera::enumToNum(EC_Volume::Music)) = mute;
                    if (mute) {
                        for (auto &music : this->m_MusicPlayer) {
                            music.setVolume(0.0f);
                        }
                    }
                    else {
                        for (auto &music : this->m_MusicPlayer) {
                            music.setVolume(this->m_Volumes.at(aether::enumera::enumToNum(EC_Volume::Music)));
                        }
                    }
                    if (save) {
                        easygine::CORE::core().gameSettings()->setSetting(GAME_SETTING_AUDIO_MUTE_MUSIC, mute);
                    }
                    break;
                }
                case EC_Volume::SFX: {
                    this->m_Muted.at(aether::enumera::enumToNum(EC_Volume::SFX)) = mute;
                    for (auto snd: this->m_Sounds) {
                        if (snd.type() == EC_Volume::SFX) {
                            if (mute) {
                                snd.sound().setVolume(0.0f);
                            }
                            else {
                                snd.sound().setVolume(this->m_Volumes.at(aether::enumera::enumToNum(EC_Volume::SFX)));
                            }
                        }
                    }
                    if (save) {
                        easygine::CORE::core().gameSettings()->setSetting(GAME_SETTING_AUDIO_MUTE_SFX, mute);
                    }
                    break;
                }
                case EC_Volume::Voice: {
                    this->m_Muted.at(aether::enumera::enumToNum(EC_Volume::Voice)) = mute;
                    for (auto snd: this->m_Sounds) {
                        if (snd.type() == EC_Volume::Voice) {
                            if (mute) {
                                snd.sound().setVolume(0.0f);
                            }
                            else {
                                snd.sound().setVolume(this->m_Volumes.at(aether::enumera::enumToNum(EC_Volume::Voice)));
                            }
                        }
                    }
                    if (save) {
                        easygine::CORE::core().gameSettings()->setSetting(GAME_SETTING_AUDIO_MUTE_VOICE, mute);
                    }
                    break;
                }
                case EC_Volume::Ambience: {
                    this->m_Muted.at(aether::enumera::enumToNum(EC_Volume::Ambience)) = mute;
                    for (auto snd: this->m_Sounds) {
                        if (snd.type() == EC_Volume::Ambience) {
                            if (mute) {
                                snd.sound().setVolume(0.0f);
                            }
                            else {
                                snd.sound().setVolume(this->m_Volumes.at(aether::enumera::enumToNum(EC_Volume::Ambience)));
                            }
                        }
                    }
                    if (save) {
                        easygine::CORE::core().gameSettings()->setSetting(GAME_SETTING_AUDIO_MUTE_AMBIENCE, mute);
                    }
                    break;
                }
                case EC_Volume::Master:
                default: {
                    this->m_Muted.at(aether::enumera::enumToNum(EC_Volume::Master)) = mute;
                    if (mute) {
                        Listener::setGlobalVolume(0.0f);
                    }
                    else {
                        Listener::setGlobalVolume(this->m_Volumes.at(4ull));
                    }
                    if (save) {
                        easygine::CORE::core().gameSettings()->setSetting(GAME_SETTING_AUDIO_MUTE_MASTER, mute);
                    }
                }
            }
        }

        bool AudioMixer::getAudioMute(EC_Volume type) const {
            switch (type) {
                case EC_Volume::Music: {
                    return this->m_Muted.at(aether::enumera::enumToNum(EC_Volume::Music));
                }
                case EC_Volume::SFX: {
                    return this->m_Muted.at(aether::enumera::enumToNum(EC_Volume::SFX));
                }
                case EC_Volume::Voice: {
                    return this->m_Muted.at(aether::enumera::enumToNum(EC_Volume::Voice));
                }
                case EC_Volume::Ambience: {
                    return this->m_Muted.at(aether::enumera::enumToNum(EC_Volume::Ambience));
                }
                case EC_Volume::Master:
                default: {
                    return this->m_Muted.at(aether::enumera::enumToNum(EC_Volume::Master));
                }
            }
        }

        void AudioMixer::update() {
            if (!this->m_Sounds.empty()) {
                if (this->m_Sounds.back().sound().getStatus() == sf::SoundSource::Status::Stopped) {
                    this->m_Sounds.pop_back();
                }
            }
        }

        void AudioMixer::pauseSounds() {
            for (auto &snd: this->m_Sounds) {
                snd.sound().pause();
            }
        }

        void AudioMixer::resumeSounds() {
            for (auto &snd: this->m_Sounds) {
                snd.sound().play();
            }
        }

        void AudioMixer::wipeSounds() {
            for (auto &snd: this->m_Sounds) {
                snd.sound().stop();
            }
            this->m_Sounds.clear();
        }

        void AudioMixer::setAudioVolume(EC_Volume type) {
            switch (type) {
                case EC_Volume::Music: {
                    if (this->m_Muted.at(aether::enumera::enumToNum(EC_Volume::Music)) || this->m_Muted.at(aether::enumera::enumToNum(EC_Volume::Master))) {
                        for (auto &music : this->m_MusicPlayer) {
                            music.setVolume(0.0f);
                        }
                    }
                    else {
                        for (auto &music : this->m_MusicPlayer) {
                            music.setVolume(this->m_Volumes.at(aether::enumera::enumToNum(EC_Volume::Music)));
                        }
                    }
                    break;
                }
                case EC_Volume::SFX: {
                    for (auto &snd: this->m_Sounds) {
                        if (snd.type() == EC_Volume::SFX) {
                            if (this->m_Muted.at(aether::enumera::enumToNum(EC_Volume::SFX)) || this->m_Muted.at(aether::enumera::enumToNum(EC_Volume::Master))) {
                                snd.sound().setVolume(0.0f);
                            }
                            else {
                                snd.sound().setVolume(this->m_Volumes.at(aether::enumera::enumToNum(EC_Volume::SFX)));
                            }
                        }
                    }
                    break;
                }
                case EC_Volume::Voice: {
                    for (auto &snd: this->m_Sounds) {
                        if (this->m_Muted.at(aether::enumera::enumToNum(EC_Volume::Voice)) || this->m_Muted.at(aether::enumera::enumToNum(EC_Volume::Master))) {
                            snd.sound().setVolume(0.0f);
                        }
                        else {
                            snd.sound().setVolume(this->m_Volumes.at(aether::enumera::enumToNum(EC_Volume::Voice)));
                        }
                    }
                    break;
                }
                case EC_Volume::Ambience: {
                    for (auto &snd: this->m_Sounds) {
                        if (this->m_Muted.at(aether::enumera::enumToNum(EC_Volume::Ambience)) || this->m_Muted.at(aether::enumera::enumToNum(EC_Volume::Master))) {
                            snd.sound().setVolume(0.0f);
                        }
                        else {
                            snd.sound().setVolume(this->m_Volumes.at(aether::enumera::enumToNum(EC_Volume::Ambience)));
                        }
                    }
                    break;
                }
                case EC_Volume::Master:
                default: {
                    if (this->m_Muted.at(aether::enumera::enumToNum(EC_Volume::Master))) {
                        Listener::setGlobalVolume(0.0f);
                    }
                    else {
                        Listener::setGlobalVolume(this->m_Volumes.at(aether::enumera::enumToNum(EC_Volume::Master)));
                    }
                }
            }
        }
    }
}