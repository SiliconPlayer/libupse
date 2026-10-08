/*
 * UPSE: the unix playstation sound emulator.
 *
 * Filename: upse-scope-tap.h
 * Purpose: libupse: per-voice channel-scope tap for visualizers
 *
 * UPSE is free software, released under the GNU General Public License,
 * version 2.
 */

#ifndef _UPSE__LIBUPSE__UPSE_SCOPE_TAP_H__GUARD
#define _UPSE__LIBUPSE__UPSE_SCOPE_TAP_H__GUARD

#ifdef __cplusplus
extern "C" {
#endif

/* Per-voice scope tap: the SPU reports each voice's post-volume mono
** contribution through the callback. Silence arrives as zeroes, never
** as a null pointer; frames is always positive. Only core 0 is tapped. */
typedef void (*upse_spu_scope_cb_t)(int voice, const short *samples, int frames, void *user);
void upse_ps1_spu_set_scope_callback(void *spuState, upse_spu_scope_cb_t callback, void *user);
/* Channel mutes for scope isolation; muted voices tap silence. */
void upse_ps1_spu_set_voice_mute(void *spuState, int voice, int muted);
void upse_ps1_spu_clear_voice_mutes(void *spuState);

#ifdef __cplusplus
}
#endif

#endif
