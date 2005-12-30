/*
 * Copyright (c) 2005 by KoanLogic s.r.l. <http://www.koanlogic.com>
 * All rights reserved.
 *
 * This file is part of KLone, and as such it is subject to the license stated
 * in the LICENSE file which you have received as part of this distribution.
 *
 * $Id: io.h,v 1.11 2005/12/30 17:21:53 tat Exp $
 */

#ifndef _KLONE_IO_H_ 
#define _KLONE_IO_H_

#include "klone_conf.h"
#include <sys/types.h>
#include <stdio.h>
#ifdef HAVE_LIBOPENSSL
#include <openssl/ssl.h>
#include <openssl/err.h>
#endif /* HAVE_LIBOPENSSL */
#include <klone/codec.h>

#ifdef __cplusplus
extern "C" {
#endif 

struct io_s;
typedef struct io_s io_t;

enum io_fd_flags {
    IO_FD_NO_FLAGS,
    IO_FD_CLOSE /* close(2) fd on io_free           */
};

enum io_mem_flags {
    IO_MEM_NO_FLAGS,
    IO_MEM_FREE_BUF     /* free(3) io mem buf on io_free    */
};

int io_fd_create(int fd, int flags, io_t **pio);
int io_mem_create(char *buf, size_t size, int flags, io_t **pio);

#ifdef HAVE_LIBOPENSSL
int io_ssl_create(int fd, int flags, SSL_CTX *ssl_tx, io_t **pio);
#endif

int io_dup(io_t *io, io_t **pio);

int io_free(io_t *io);

int io_name_set(io_t *io, const char* name);
int io_name_get(io_t *io, char* name, size_t sz);

int io_codec_add_head(io_t *io, codec_t* codec);
int io_codec_add_tail(io_t *io, codec_t* codec);

int io_codecs_remove(io_t *io);

ssize_t io_read(io_t *io, char* buf, size_t size);
ssize_t io_write(io_t *io, const char* buf, size_t size);
ssize_t io_flush(io_t *io);
ssize_t io_seek(io_t *io, size_t off);
ssize_t io_tell(io_t *io);
ssize_t io_copy(io_t *out, io_t *in, size_t size);
ssize_t io_pipe(io_t *out, io_t *in);

ssize_t io_gets(io_t *io, char *buf, size_t size);
ssize_t io_getc(io_t *io, char *c);

ssize_t io_printf(io_t *io, const char* fmt, ...);
ssize_t io_putc(io_t *io, char c);

#ifdef __cplusplus
}
#endif 

#endif
