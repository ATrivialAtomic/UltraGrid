/**
 * @file   discard.cpp
 * @author Martin Piatka     <piatka@cesnet.cz>
 */
/*
 * Copyright (c) 2022 CESNET, z. s. p. o.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, is permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of CESNET nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#include "config_unix.h"
#include "config_win32.h"
#endif /* HAVE_CONFIG_H */

#include <memory>
#include <string_view>

#include "debug.h"
#include "module.h"
#include "audio/audio_filter.h"
#include "audio/types.h"
#include "audio/utils.h"
#include "lib_common.h"

struct state_discard{
        state_discard(struct module *mod) : mod(MODULE_CLASS_DATA, mod, this)
        {
        }

        module_raii mod;

        int bps = 0;
        int ch_count = 0;
        int sample_rate = 0;
};

static void usage(){
        printf("discard:\n");
        printf("Discards all audio frames\n");
}

static af_result_code init(struct module *parent, const char *cfg, void **state){
        auto s = std::make_unique<state_discard>(parent);

        if(strcmp(cfg, ":help") == 0){
                usage();
                return AF_HELP_SHOWN;
        }

        *state = s.release();
        return AF_OK;
};

static af_result_code configure(void *state,
                        int in_bps, int in_ch_count, int in_sample_rate)
{
        auto s = static_cast<state_discard *>(state);

        s->bps = in_bps;
        s->ch_count = in_ch_count;
        s->sample_rate = in_sample_rate;

        return AF_OK;
}

static void done(void *state){
        auto s = static_cast<state_discard *>(state);

        delete s;
}

static void get_configured(void *state,
                        int *bps, int *ch_count, int *sample_rate)
{
        auto s = static_cast<state_discard *>(state);

        if(bps) *bps = s->bps;
        if(ch_count) *ch_count = s->ch_count;
        if(sample_rate) *sample_rate = s->sample_rate;
}

static af_result_code filter(void *state, struct audio_frame **frame){
        auto s = static_cast<state_discard *>(state);

        auto f = *frame;

        if(f->bps != s->bps || f->ch_count != s->ch_count){
                if(configure(state, f->bps, f->ch_count, f->sample_rate) != AF_OK){
                        return AF_MISCONFIGURED;
                }
        }

        *frame = nullptr;

        return AF_OK;
}

static const struct audio_filter_info audio_filter_discard = {
        .name = "discard",
        .init = init,
        .done = done,
        .configure = configure,
        .get_configured_in = get_configured,
        .get_configured_out = get_configured,
        .filter = filter,
};

REGISTER_HIDDEN_MODULE(discard, &audio_filter_discard, LIBRARY_CLASS_AUDIO_FILTER, AUDIO_FILTER_ABI_VERSION);
