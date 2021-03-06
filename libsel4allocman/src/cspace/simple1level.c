/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <allocman/cspace/simple1level.h>
#include <allocman/util.h>
#include <allocman/allocman.h>
#include <sel4/sel4.h>

void cspace_simple1level_create(cspace_simple1level_t *cspace, struct cspace_simple1level_config config)
{
    *cspace = (cspace_simple1level_t) {
        .config = config, .current_slot = config.first_slot
    };
}

int _cspace_simple1level_alloc(allocman_t *alloc, void *_cspace, cspacepath_t *slot)
{
    cspace_simple1level_t *cspace = (cspace_simple1level_t*)_cspace;

    if (cspace->current_slot == cspace->config.end_slot) {
        return 1;
    }

    *slot = _cspace_simple1level_make_path(cspace, cspace->current_slot++);
    return 0;
}

void _cspace_simple1level_free(allocman_t *alloc, void *_cspace, const cspacepath_t *slot)
{
    /* We happily ignore this */
}
