/*
 * Copyright (c) 2005-2007 Rob Braun
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of Rob Braun nor the names of his contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * 03-Apr-2005
 * DRI: Rob Braun <bbraun@synack.net>
 */

#include <config.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <xar/xar.h>
#include <xar/archive.h>

void
xar_register_errhandler (xar_archive_t x, err_handler callback, void *usrctx)
{
  x->errctx.x = x;
  x->errctx.usrctx = usrctx;
  x->ercallback = callback;
  return;
}

xar_archive_t
xar_err_get_archive (xar_errctx_t ctx)
{
  return ctx->x;
}

xar_file_t
xar_err_get_file (xar_errctx_t ctx)
{
  return ctx->file;
}

void
xar_err_set_file (xar_archive_t x, xar_file_t f)
{
  x->errctx.file = f;
  return;
}

const char *
xar_err_get_string (xar_errctx_t ctx)
{
  return ctx->str;
}

void
xar_err_set_string (xar_archive_t x, const char *str)
{
  x->errctx.str = str;
  return;
}

int
xar_err_get_errno (xar_errctx_t ctx)
{
  return ctx->saved_errno;
}

void
xar_err_set_errno (xar_archive_t x, int e)
{
  x->errctx.saved_errno = e;
  return;
}

void
xar_err_new (xar_archive_t x)
{
  memset (&x->errctx, 0, sizeof (xar_errctx));
  x->errctx.saved_errno = errno;
  return;
}

int32_t
xar_err_callback (xar_archive_t x, int32_t sev, int32_t err)
{
  if (x->ercallback)
    return x->ercallback (sev, err, &x->errctx,
                                x->errctx.usrctx);
  return 0;
}
