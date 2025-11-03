#pragma once

#define GAME_TITLE                  "EasygineProject"

#ifdef _RELEASE
#define GAME_VERSION                "0.0.0.0 (Release Build)"
#else
#define GAME_VERSION                "0.0.0.0 (Debug Build)"
#endif

#define GAME_SETTINGS_PATH          "../"

#define GAME_ASSETS_DIR             "../assets/"

#define GAME_DEFAULT_ASSETS_DIR     "../assets/default/"

#define GAME_GUI_DIR                "../assets/gui/"

#define GAME_FONTS_DIR              "../assets/gui/fonts/"

#define GAME_THEME_DIR              "../assets/gui/theme/"

#define GAME_DATA_DIR               "../data/"

#define GAME_LOCALE_DIR             "../data/locale/"

#define GAME_SCREENSHOTS_DIR        "../screenshots/"

#define CMDLINE_BUFFER_SIZE         150

#define CMDLINE_HISTORY_SIZE        25

#define GAME_SETTING_WINDOW_MODE            "window_mode"
#define GAME_SETTING_WINDOW_RATIO_X         "resolution_x"
#define GAME_SETTING_WINDOW_RATIO_Y         "resolution_y"
#define GAME_SETTING_BITS_PER_PIXEL         "bits_per_pixel"
#define GAME_SETTING_FPS_LIMIT              "framerate_limit"
#define GAME_SETTING_VSYNC                  "vsync_enabled"
#define GAME_SETTING_LANGUAGE_TEXT          "language_text"
#define GAME_SETTING_LANGUAGE_DUBBING       "language_dubbing"
#define GAME_SETTING_CONSOLE_ENABLED        "developer_console_enabled"
#define GAME_SETTING_AUDIO_VOLUME_MASTER    "audio_master_volume"
#define GAME_SETTING_AUDIO_VOLUME_MUSIC     "audio_music_volume"
#define GAME_SETTING_AUDIO_VOLUME_SFX       "audio_sfx_volume"
#define GAME_SETTING_AUDIO_VOLUME_VOICE     "audio_voice_volume"
#define GAME_SETTING_AUDIO_VOLUME_AMBIENCE  "audio_ambience_volume"
#define GAME_SETTING_AUDIO_MUTE_MASTER      "audio_master_disabled"
#define GAME_SETTING_AUDIO_MUTE_MUSIC       "audio_music_disabled"
#define GAME_SETTING_AUDIO_MUTE_SFX         "audio_sfx_disabled"
#define GAME_SETTING_AUDIO_MUTE_VOICE       "audio_voice_disabled"
#define GAME_SETTING_AUDIO_MUTE_AMBIENCE    "audio_ambience_disabled"