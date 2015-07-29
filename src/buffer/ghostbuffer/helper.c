#include <Python.h>
#include <stdio.h>

#include <numpy/arrayobject.h>

#include "gstbuf.h"


/**
 * Assume gbuf has no ghost.
 */
void gstbuf_print_int32(gstbuf_t gbuf) {
    int *elem = (int *)gbuf.elem;
    size_t nelem=gbuf.shape[0];
    for (int it=1; it<gbuf.ndim; it++) {
        nelem *= gbuf.shape[it];
    }
    for (size_t jt=0; jt<nelem; jt++) {
        printf("%lu: %d\n", jt, elem[jt]);
    }
}

/**
 * Assume gbuf is valid and separable.
 */
void gstbuf_ranged_fill(gstbuf_t gbuf) {
    size_t nelem;
    int *elem = (int *)gbuf.elem;
    if (4 != gbuf.elemsize)
        return; // Do nothing.
    // Ghost part.
    nelem = gbuf.drange[0];
    for (int it=1; it<gbuf.ndim; it++)
        nelem *= gbuf.drange[it*2] + gbuf.drange[it*2+1];
    for (long it=-1; it>=-nelem; it--)
        elem[it] = it;
    // Body part.
    nelem = gbuf.drange[1];
    for (int it=1; it<gbuf.ndim; it++)
        nelem *= gbuf.drange[it*2] + gbuf.drange[it*2+1];
    for (long it=0; it<nelem; it++)
        elem[it] = it;
}

// vim: set ff=unix fenc=utf8 nobomb ai et sw=4 ts=4 tw=79:
