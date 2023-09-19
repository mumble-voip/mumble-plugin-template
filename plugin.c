#include "MumblePlugin_v_1_0_x.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MumbleAPI_v_1_0_x mumbleAPI;
mumble_plugin_id_t ownID;

mumble_error_t mumble_init(mumble_plugin_id_t pluginID)
{
	ownID = pluginID;

	if (mumbleAPI.log(ownID, "Hello Mumble") != MUMBLE_STATUS_OK)
	{
		// Logging failed -> usually you'd probably want to log things like this in your plugin's
		// logging system (if there is any)
	}

	return MUMBLE_STATUS_OK;
}

void mumble_shutdown()
{
	if (mumbleAPI.log(ownID, "Goodbye Mumble") != MUMBLE_STATUS_OK)
	{
		// Logging failed -> usually you'd probably want to log things like this in your plugin's
		// logging system (if there is any)
	}
}

struct MumbleStringWrapper mumble_getName()
{
	static const char *name = "Factorio";

	struct MumbleStringWrapper wrapper;
	wrapper.data = name;
	wrapper.size = strlen(name);
	wrapper.needsReleasing = false;

	return wrapper;
}

mumble_version_t mumble_getAPIVersion()
{
	// This constant will always hold the API version  that fits the included header files
	return MUMBLE_PLUGIN_API_VERSION;
}

void mumble_registerAPIFunctions(void *apiStruct)
{
	// Provided mumble_getAPIVersion returns MUMBLE_PLUGIN_API_VERSION, this cast will make sure
	// that the passed pointer will be cast to the proper type
	mumbleAPI = MUMBLE_API_CAST(apiStruct);
}

void mumble_releaseResource(const void *pointer)
{
	// As we never pass a resource to Mumble that needs releasing, this function should never
	// get called
	printf("Called mumble_releaseResource but expected that this never gets called -> Aborting");
	abort();
}

// Below functions are not strictly necessary but every halfway serious plugin should implement them nonetheless

mumble_version_t mumble_getVersion()
{
	mumble_version_t version;
	version.major = 0;
	version.minor = 1;
	version.patch = 0;

	return version;
}

struct MumbleStringWrapper mumble_getAuthor()
{
	static const char *author = "alifeee";

	struct MumbleStringWrapper wrapper;
	wrapper.data = author;
	wrapper.size = strlen(author);
	wrapper.needsReleasing = false;

	return wrapper;
}

struct MumbleStringWrapper mumble_getDescription()
{
	static const char *description = "Factorio plugin for Mumble's Positional Audio API. Requires Factorio positional audio mod.";

	struct MumbleStringWrapper wrapper;
	wrapper.data = description;
	wrapper.size = strlen(description);
	wrapper.needsReleasing = false;

	return wrapper;
}

// positional audio functions

uint32_t mumble_getFeatures()
{
	return MUMBLE_FEATURE_POSITIONAL;
}

uint8_t mumble_initPositionalData(const char *const *programNames, const uint64_t *programPIDs, size_t programCount)
{
	// Check if the supported game is in the list of programs and if yes
	// check if the position can be obtained from the program

	// If everything went well
	return MUMBLE_PDEC_OK;
	// Other potential return values are:
	// MUMBLE_PDEC_ERROR_TEMP -> The plugin can temporarily not deliver positional data
	// MUMBLE_PDEC_PERM -> Permanenet error. The plugin will never be able to deliver positional data
}

bool mumble_fetchPositionalData(float *avatarPos, float *avatarDir, float *avatarAxis, float *cameraPos, float *cameraDir,
								float *cameraAxis, const char **context, const char **identity)
{
	// fetch positional data and store it in the respective variables. All fields that can't be filled properly
	// have to be set to 0 or the empty String ""

	// If positional data could be fetched successfully
	return true;
	// otherwise return false
}

void mumble_shutdownPositionalData()
{
	// Unlink the connection to the supported game
	// Perform potential clean-up code
}