/*
    fmod_studio_common.h
    Copyright (c), Firelight Technologies Pty, Ltd. 2014.

    This header defines common enumerations, structs and callbacks that are shared between the C and C++ interfaces.
*/

#ifndef FMOD_STUDIO_COMMON_H
#define FMOD_STUDIO_COMMON_H

#include "fmod.h"

typedef unsigned int FMOD_STUDIO_INITFLAGS;

/*
[DEFINE]
[
    [NAME]
    FMOD_STUDIO_INITFLAGS

    [DESCRIPTION]
    Studio System initialization flags.
    Use them with Studio::System::initialize in the *studioflags* parameter to change various behavior.

    [REMARKS]

    [SEE_ALSO]
    Studio::System::initialize
]
*/
#define FMOD_STUDIO_INIT_NORMAL                     0x00000000  /* Initialize normally. */
#define FMOD_STUDIO_INIT_LIVEUPDATE                 0x00000001  /* Enable live update. */
#define FMOD_STUDIO_INIT_ALLOW_MISSING_PLUGINS      0x00000002  /* Load banks even if they reference plugins that have not been loaded. */
#define FMOD_STUDIO_INIT_SYNCHRONOUS_UPDATE         0x00000004  /* Disable asynchronous processing and perform all processing on the calling thread instead. */
/* [DEFINE_END] */

typedef struct FMOD_STUDIO_SYSTEM FMOD_STUDIO_SYSTEM;
typedef struct FMOD_STUDIO_EVENTDESCRIPTION FMOD_STUDIO_EVENTDESCRIPTION;
typedef struct FMOD_STUDIO_EVENTINSTANCE FMOD_STUDIO_EVENTINSTANCE;
typedef struct FMOD_STUDIO_CUEINSTANCE FMOD_STUDIO_CUEINSTANCE;
typedef struct FMOD_STUDIO_PARAMETERINSTANCE FMOD_STUDIO_PARAMETERINSTANCE;
typedef struct FMOD_STUDIO_MIXERSTRIP FMOD_STUDIO_MIXERSTRIP;
typedef struct FMOD_STUDIO_BANK FMOD_STUDIO_BANK;

/*
[ENUM]
[
    [DESCRIPTION]
    Intended to control on-demand bank loading.

    [REMARKS]
    Currently unsupported. Reserved for future functionality.

    [SEE_ALSO]
    Studio::System::getEvent
    Studio::System::getMixerStrip
]
*/
typedef enum
{
    FMOD_STUDIO_LOAD_BEGIN_NOW,                 /* Reserved. */
    FMOD_STUDIO_LOAD_PROHIBITED,                /* Reserved. */

    FMOD_STUDIO_LOAD_FORCEINT = 65536           /* Makes sure this enum is signed 32bit. */
} FMOD_STUDIO_LOADING_MODE;

/*
[ENUM]
[
    [DESCRIPTION]
    These values describe the loading status of the sample data required for an event or bank.

    [REMARKS]
    Calling Studio::EventDescription::createInstance or Studio::Bank::loadSampleData may
    trigger asynchronous loading of sample data.

    [SEE_ALSO]
    Studio::EventInstance::getLoadingState
    Studio::MixerStrip::getLoadingState
    Studio::Bank::getLoadingState
    Studio::Bank::getSampleLoadingState
]
*/
typedef enum
{
    FMOD_STUDIO_LOADING_STATE_UNLOADING,        /* Currently unloading. */
    FMOD_STUDIO_LOADING_STATE_UNLOADED,         /* Sample data not loaded. */
    FMOD_STUDIO_LOADING_STATE_LOADING,          /* Loading in progress. */
    FMOD_STUDIO_LOADING_STATE_LOADED,           /* Loaded and ready to play. */

    FMOD_STUDIO_LOADING_STATE_FORCEINT = 65536  /* Makes sure this enum is signed 32bit. */
} FMOD_STUDIO_LOADING_STATE;

/*
[ENUM]
[
    [DESCRIPTION]
    Specifies how to use the memory buffer passed to Studio::System::loadBankMemory.

    [REMARKS]

    [SEE_ALSO]
    Studio::System::loadBankMemory
    Studio::Bank::unload
]
*/
typedef enum
{
    FMOD_STUDIO_LOAD_MEMORY,                    /* When passed to Studio::System::loadBankMemory, FMOD duplicates the memory into its own buffers. Your buffer can be freed after Studio::System::loadBankMemory returns. */
    FMOD_STUDIO_LOAD_MEMORY_POINT,              /* This differs from FMOD_STUDIO_LOAD_MEMORY in that FMOD uses the memory as is, without duplicating the memory into its own buffers. Cannot not be freed after load, only after calling Studio::Bank::unload. */

    FMOD_STUDIO_LOAD_MEMORY_FORCEINT = 65536    /* Makes sure this enum is signed 32bit. */
} FMOD_STUDIO_LOAD_MEMORY_MODE;

/*
[ENUM]
[
    [DESCRIPTION]
    Describes the type of a parameter.

    [REMARKS]
    There are two primary types of parameters: game controlled and automatic.
    Game controlled parameters receive their value from the API using
    Studio::ParameterInstance::setValue. Automatic parameters are updated inside
    FMOD based on the positional information of the event and listener.

    **Horizontal angle** means the angle between vectors projected onto the
    listener's XZ plane (for the EVENT_ORIENTATION and DIRECTION parameters)
    or the global XZ plane (for the LISTENER_ORIENTATION parameter).

    [SEE_ALSO]
    FMOD_STUDIO_PARAMETER_DESCRIPTION
    Studio::ParameterInstance::setValue
    Studio::EventInstance::set3DAttributes
    Studio::System::setListenerAttributes
]
*/
typedef enum 
{
    FMOD_STUDIO_PARAMETER_GAME_CONTROLLED,                  /* Controlled via the API using Studio::ParameterInstance::setValue. */
    FMOD_STUDIO_PARAMETER_AUTOMATIC_DISTANCE,               /* Distance between the event and the listener. */
    FMOD_STUDIO_PARAMETER_AUTOMATIC_EVENT_CONE_ANGLE,       /* Angle between the event's forward vector and the vector pointing from the event to the listener (0 to 180 degrees). */
    FMOD_STUDIO_PARAMETER_AUTOMATIC_EVENT_ORIENTATION,      /* Horizontal angle between the event's forward vector and listener's forward vector (-180 to 180 degrees). */
    FMOD_STUDIO_PARAMETER_AUTOMATIC_DIRECTION,              /* Horizontal angle between the listener's forward vector and the vector pointing from the listener to the event (-180 to 180 degrees). */
    FMOD_STUDIO_PARAMETER_AUTOMATIC_ELEVATION,              /* Angle between the listener's XZ plane and the vector pointing from the listener to the event (-90 to 90 degrees). */
    FMOD_STUDIO_PARAMETER_AUTOMATIC_LISTENER_ORIENTATION,   /* Horizontal angle between the listener's forward vector and the global positive Z axis (-180 to 180 degrees). */

    FMOD_STUDIO_PARAMETER_MAX,                              /* Maximum number of parameter types supported. */
    FMOD_STUDIO_PARAMETER_FORCEINT = 65536                  /* Makes sure this enum is signed 32bit. */
} FMOD_STUDIO_PARAMETER_TYPE;

/*
[STRUCTURE]
[
    [DESCRIPTION]
    Information for loading a bank with Studio::System::loadBankCustom.

    [REMARKS]

    [SEE_ALSO]
    Studio::System::loadBankCustom
]
*/
typedef struct
{
    int   size;                                 /* The size of this struct (for binary compatibility) */
    void *userData;                             /* User data to be passed to the file callbacks */
    int   userDataLength;                       /* If this is non-zero, userData will be copied internally */
    FMOD_FILE_OPEN_CALLBACK  openCallback;      /* Callback for opening this file. */
    FMOD_FILE_CLOSE_CALLBACK closeCallback;     /* Callback for closing this file. */
    FMOD_FILE_READ_CALLBACK  readCallback;      /* Callback for reading from this file. */
    FMOD_FILE_SEEK_CALLBACK  seekCallback;      /* Callback for seeking within this file. */
} FMOD_STUDIO_BANK_INFO;

/*
[STRUCTURE]
[
    [DESCRIPTION]
    Structure describing an event parameter.

    [REMARKS]

    [SEE_ALSO]
    Studio::EventDescription::getParameter
    FMOD_STUDIO_PARAMETER_TYPE
]
*/
typedef struct
{
    const char *name;                           /* Name of the parameter. */
    float minimum;                              /* Minimum parameter value. */
    float maximum;                              /* Maximum parameter value. */
    FMOD_STUDIO_PARAMETER_TYPE type;            /* Type of the parameter */
} FMOD_STUDIO_PARAMETER_DESCRIPTION;

/*
[ENUM]
[
    [DESCRIPTION]
    These definitions describe a user property's type.

    [REMARKS]

    [SEE_ALSO]
    FMOD_STUDIO_USER_PROPERTY
]
*/
typedef enum
{
    FMOD_STUDIO_USER_PROPERTY_TYPE_INTEGER,         /* Integer property */
    FMOD_STUDIO_USER_PROPERTY_TYPE_BOOLEAN,         /* Boolean property */
    FMOD_STUDIO_USER_PROPERTY_TYPE_FLOAT,           /* Float property */
    FMOD_STUDIO_USER_PROPERTY_TYPE_STRING,          /* String property */

    FMOD_STUDIO_USER_PROPERTY_TYPE_FORCEINT = 65536 /* Makes sure this enum is signed 32bit. */
} FMOD_STUDIO_USER_PROPERTY_TYPE;

/*
[STRUCTURE]
[
    [DESCRIPTION]
    Structure describing a user property.

    [REMARKS]

    [SEE_ALSO]
    Studio::EventDescription::getUserProperty
]
*/
typedef struct
{
    const char *name;                           /* Name of the user property. */
    FMOD_STUDIO_USER_PROPERTY_TYPE type;        /* Type of the user property. Use this to select one of the following values. */

    union
    {
        int intValue;                           /* Value of the user property. Only valid when type is FMOD_STUDIO_USER_PROPERTY_TYPE_INTEGER. */
        bool boolValue;                         /* Value of the user property. Only valid when type is FMOD_STUDIO_USER_PROPERTY_TYPE_BOOLEAN. */
        float floatValue;                       /* Value of the user property. Only valid when type is FMOD_STUDIO_USER_PROPERTY_TYPE_FLOAT. */
        const char *stringValue;                /* Value of the user property. Only valid when type is FMOD_STUDIO_USER_PROPERTY_TYPE_STRING. */
    };
} FMOD_STUDIO_USER_PROPERTY;

/*
[ENUM]
[
    [DESCRIPTION]
    These callback types are used with Studio::EventInstance::setCallback.

    [REMARKS]
    The data passed to the event callback function in the *parameters* argument varies based on the callback type.

    [SEE_ALSO]
    Studio::EventDescription::setCallback
    Studio::EventInstance::setCallback
]
*/
typedef enum
{
    FMOD_STUDIO_EVENT_CALLBACK_STARTED,                     /* Called when an instance starts. Parameters = FMOD_STUDIO_EVENTINSTANCE, which can be cast to Studio::EventInstance* type. */
    FMOD_STUDIO_EVENT_CALLBACK_STOPPED,                     /* Called when an instance stops. Parameters = FMOD_STUDIO_EVENTINSTANCE, which can be cast to Studio::EventInstance* type. */
    FMOD_STUDIO_EVENT_CALLBACK_IDLE,                        /* Called when an instance enters the idle state. Parameters = FMOD_STUDIO_EVENTINSTANCE, which can be cast to Studio::EventInstance* type. */
    FMOD_STUDIO_EVENT_CALLBACK_CREATE_PROGRAMMER_SOUND,     /* Called when a programmer sound needs to be created in order to play a programmer instrument. Parameters = FMOD_STUDIO_PROGRAMMER_SOUND_PROPERTIES. */
    FMOD_STUDIO_EVENT_CALLBACK_DESTROY_PROGRAMMER_SOUND,    /* Called when a programmer sound needs to be destroyed. Parameters = FMOD_STUDIO_PROGRAMMER_SOUND_PROPERTIES. */

    FMOD_STUDIO_EVENT_CALLBACK_FORCEINT = 65536             /* Makes sure this enum is signed 32bit. */
} FMOD_STUDIO_EVENT_CALLBACK_TYPE;

/*
[STRUCTURE]
[
    [DESCRIPTION]
    This structure holds information about a programmer sound.

    [REMARKS]
    This data is passed to the event callback function when type is FMOD_STUDIO_EVENT_CALLBACK_CREATE_PROGRAMMER_SOUND or FMOD_STUDIO_EVENT_CALLBACK_DESTROY_PROGRAMMER_SOUND.

    [SEE_ALSO]
    FMOD_STUDIO_EVENT_CALLBACK
    Studio::EventDescription::setCallback
    Studio::EventInstance::setCallback
]
*/
typedef struct
{
    const char *name;                           /* The name of the programmer instrument (set in FMOD Studio). */
    FMOD_STUDIO_EVENTINSTANCE *event;           /* The event instance that needs to play the sound. Can be cast to Studio::EventInstance* type. */
    FMOD_SOUND *sound;                          /* The programmer-created sound. This should be filled in by the create callback, and cleaned up by the destroy callback. This can be cast to/from FMOD::Sound* type. */
} FMOD_STUDIO_PROGRAMMER_SOUND_PROPERTIES;

typedef FMOD_RESULT (F_CALLBACK *FMOD_STUDIO_EVENT_CALLBACK)(FMOD_STUDIO_EVENT_CALLBACK_TYPE type, void *parameters);

/*
[ENUM]
[
    [DESCRIPTION]
    These values describe the playback state of an event instance.

    [REMARKS]

    [SEE_ALSO]
    Studio::EventInstance::getPlaybackState
    Studio::EventInstance::start
    Studio::EventInstance::stop
    Studio::CueInstance::trigger
    Studio::ParameterInstance::setValue
]
*/
typedef enum
{
    FMOD_STUDIO_PLAYBACK_PLAYING,               /* Currently playing. */
    FMOD_STUDIO_PLAYBACK_IDLE,                  /* The timeline cursor has reached the end, but parameter value changes may still trigger sounds. */
    FMOD_STUDIO_PLAYBACK_SUSTAINING,            /* The timeline cursor is paused on a sustain point. */
    FMOD_STUDIO_PLAYBACK_STOPPED,               /* Not playing. */

    FMOD_STUDIO_PLAYBACK_FORCEINT = 65536       /* Makes sure this enum is signed 32bit. */
} FMOD_STUDIO_PLAYBACK_STATE;

/*
[ENUM]
[
    [DESCRIPTION]
    Controls how to stop playback of an event instance.

    [REMARKS]

    [SEE_ALSO]
    Studio::EventInstance::stop
    Studio::MixerStrip::stopAllEvents
]
*/
typedef enum
{
    FMOD_STUDIO_STOP_ALLOWFADEOUT,              /* Allows AHDSR modulators to complete their release, and DSP effect tails to play out. */
    FMOD_STUDIO_STOP_IMMEDIATE,                 /* Stops the event instance immediately. */

    FMOD_STUDIO_STOP_FORCEINT = 65536           /* Makes sure this enum is signed 32bit. */
} FMOD_STUDIO_STOP_MODE;

/*
[DEFINE]
[
    [NAME]
    FMOD_STUDIO_RECORD_COMMANDS_FLAGS

    [DESCRIPTION]
    Flags passed into Studio::System::startRecordCommands.

    [REMARKS]

    [SEE_ALSO]
    Studio::System::startRecordCommands
]
*/
#define FMOD_STUDIO_RECORD_COMMANDS_NORMAL          0x00000000       /* Standard behaviour. */
#define FMOD_STUDIO_RECORD_COMMANDS_FILEFLUSH       0x00000001       /* Call file flush on every command. */
/* [DEFINE_END] */

typedef unsigned int               FMOD_STUDIO_RECORD_COMMANDS_FLAGS;


/*
[DEFINE]
[
    [NAME]
    FMOD_STUDIO_LOAD_BANK_FLAGS

    [DESCRIPTION]
    Flags passed into Studio loadBank commands to control bank load behaviour.

    [REMARKS]

    [SEE_ALSO]
    Studio::System::loadBankFile
    Studio::System::loadBankMemory
    Studio::System::loadBankCustom
]
*/
#define FMOD_STUDIO_LOAD_BANK_NORMAL         0x00000000         /* Standard behaviour. */
#define FMOD_STUDIO_LOAD_BANK_NONBLOCKING    0x00000001         /* Bank loading occurs asynchronously rather than occurring immediately. */
/* [DEFINE_END] */

typedef unsigned int               FMOD_STUDIO_LOAD_BANK_FLAGS;

/*
[STRUCTURE] 
[
    [DESCRIPTION]
    Settings for advanced features like configuring memory and cpu usage.

    [REMARKS]
    Members marked with [r] mean the variable is modified by FMOD and is for reading purposes only.  Do not change this value.<br>
    Members marked with [w] mean the variable can be written to.  The user can set the value.<br>
    Members marked with [r/w] are either read or write depending on if you are using System::setAdvancedSettings (w) or System::getAdvancedSettings (r).

    [SEE_ALSO]
    Studio::System::setAdvancedSettings
    Studio::System::getAdvancedSettings
    FMOD_MODE
]
*/
typedef struct FMOD_STUDIO_ADVANCEDSETTINGS
{                       
    int                 cbSize;                     /* [w]   Size of this structure.  Use sizeof(FMOD_STUDIO_ADVANCEDSETTINGS)  NOTE: This must be set before calling System::getAdvancedSettings! */
    unsigned int        commandQueueSize;           /* [r/w] Optional. Specify 0 to ignore. Specify the command queue size for studio async processing.  Default 4096 (4kb) */
    unsigned int        handleInitialSize;          /* [r/w] Optional. Specify 0 to ignore. Specify the initial size to allocate for handles.  Memory for handles will grow as needed in pages. */
} FMOD_STUDIO_ADVANCEDSETTINGS;


/*
[STRUCTURE] 
[
    [DESCRIPTION]
    Performance information for FMOD Studio and low level systems.

    [REMARKS]

    [SEE_ALSO]
    Studio::System::getCPUUsage
    FMOD_STUDIO_CPU_USAGE_VERSION
]
*/
typedef struct FMOD_STUDIO_CPU_USAGE
{
    float               dspUsage;                           /* Returns the % CPU time taken by DSP processing on the low level mixer thread. */
    float               streamUsage;                        /* Returns the % CPU time taken by stream processing on the low level stream thread. */
    float               geometryUsage;                      /* Returns the % CPU time taken by geometry processing on the low level geometry thread. */
    float               updateUsage;                        /* Returns the % CPU time taken by low level update, called as part of the studio update. */
    float               studioUsage;                        /* Returns the % CPU time taken by studio update, called from the studio thread. Does not include low level update time. */
} FMOD_STUDIO_CPU_USAGE;

#endif // FMOD_STUDIO_COMMON_H
