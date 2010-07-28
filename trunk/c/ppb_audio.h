// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_C_PPB_AUDIO_H_
#define PPAPI_C_PPB_AUDIO_H_

#include "ppapi/c/pp_instance.h"
#include "ppapi/c/pp_module.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/c/pp_stdint.h"

#define PPB_AUDIO_INTERFACE "PPB_Audio;1"

// Callback function type for SetCallback.
typedef void (*PPB_Audio_Callback)(void* sample_buffer, void* user_data);

// Callback-based audio interface. User of audio must set the callback that will
// be called each time that the buffer needs to be filled.
//
// A C++ example:
//
// void audio_callback(void* sample_buffer, void* user_data) {
//   ... fill in the buffer with samples ...
// }
//
// Audio audio(AudioConfig(44100, 0), audio_callback, NULL);
// audio.StartPlayback();
//
typedef struct _ppb_Audio {
  // Creates a paused audio interface. No sound will be heard until
  // StartPlayback() is called. The callback is called with the buffer address
  // and given user data whenever the buffer needs to be filled. From within the
  // callback, you should not call PPB_Audio functions.  The callback will be
  // called on a different thread than the one which created the interface. For
  // performance-critical applications (i.e. low-latency audio), the callback
  // should avoid blocking or calling functions that can obtain locks, such as
  // malloc. The layout and the size of the buffer passed to the audio callback
  // will be determined by the device configuration and is specified in the
  // AudioConfig documentation. If the configuration cannot be honored, or the
  // callback is null, the function returns 0.
  PP_Resource (*Create)(PP_Instance instance, PP_Resource config,
                        PPB_Audio_Callback audio_callback, void* user_data);

  // Get the current configuration.
  PP_Resource (*GetCurrentConfig)(PP_Resource audio);

  // Start the playback. Begin periodically calling the callback. If called
  // while playback is already in progress, will return true and be a no-op.
  // On error, return false.
  bool (*StartPlayback)(PP_Resource audio);

  // Stop the playback. If playback is already stopped, this is a no-op and
  // returns true. On error, returns false. If a callback is in progress,
  // StopPlayback will block until callback completes.
  bool (*StopPlayback)(PP_Resource audio);
} PPB_Audio;

#endif  // PPAPI_C_PPB_DEVICE_CONTEXT_AUDIO_H_

