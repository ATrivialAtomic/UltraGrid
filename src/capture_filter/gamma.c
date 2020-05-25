/**
 * @file   capture_filter/gamma.c
 * @author Martin Pulec     <pulec@cesnet.cz>
 */
/*
 * Copyright (c) 2020 CESNET, z. s. p. o.
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

#include "capture_filter.h"
#include "debug.h"
#include "lib_common.h"
#include "utils/color_out.h"
#include "video.h"
#include "video_codec.h"

#define MOD_NAME "[gamma cap. f.] "

struct state_capture_filter_gamma {
        unsigned char lut[256];
};

static int init(struct module *parent, const char *cfg, void **state)
{
        UNUSED(parent);

        if (!cfg || strcmp(cfg, "help") == 0) {
                printf("Performs gamma transformation.\n\n"
                       "usage:\n");
                color_out(COLOR_OUT_BOLD, "\t--capture-filter gamma:value\n");
                return 1;
        }
        double gamma = atof(cfg);

        if (gamma <= 0.0) {
                log_msg(LOG_LEVEL_WARNING, MOD_NAME "Using gamma value %lf\n", gamma);
        }

        struct state_capture_filter_gamma *s = calloc(1, sizeof(struct state_capture_filter_gamma));

        for (int i = 0; i < 256; ++i) {
                s->lut[i] = pow((double) i / 255, gamma) * 255;
        }

        *state = s;
        return 0;
}

static void done(void *state)
{
        free(state);
}

static struct video_frame *filter(void *state, struct video_frame *in)
{
        struct state_capture_filter_gamma *s = state;
        struct video_desc desc = video_desc_from_frame(in);
        if (get_bits_per_component(desc.color_spec) != 8) {
                log_msg(LOG_LEVEL_ERROR, MOD_NAME "Only 8-bit codecs are currently supported!\n");
                return NULL;
        }
        struct video_frame *out = vf_alloc_desc_data(desc);
        out->callbacks.dispose = vf_free;

        unsigned char *in_data = (unsigned char *) in->tiles[0].data;
        unsigned char *out_data = (unsigned char *) out->tiles[0].data;

        for (unsigned int i = 0; i < in->tiles[0].data_len; i += 1) {
                *out_data++ = s->lut[*in_data++];
        }

        VIDEO_FRAME_DISPOSE(in);

        return out;
}

static const struct capture_filter_info capture_filter_matrix = {
        .init = init,
        .done = done,
        .filter = filter,
};

REGISTER_MODULE(gamma, &capture_filter_matrix, LIBRARY_CLASS_CAPTURE_FILTER, CAPTURE_FILTER_ABI_VERSION);

/* vim: set expandtab sw=8: */
