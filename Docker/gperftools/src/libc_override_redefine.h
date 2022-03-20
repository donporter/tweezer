// -*- Mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
// Copyright (c) 2011, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// ---
// Author: Craig Silverstein <opensource@google.com>
//
// Used on systems that don't have their own definition of
// malloc/new/etc.  (Typically this will be a windows msvcrt.dll that
// has been edited to remove the definitions.)  We can just define our
// own as normal functions.
//
// This should also work on systems were all the malloc routines are
// defined as weak symbols, and there's no support for aliasing.

#ifndef TCMALLOC_LIBC_OVERRIDE_REDEFINE_H_
#define TCMALLOC_LIBC_OVERRIDE_REDEFINE_H_

void* operator new_NOT_USED(size_t size)                  { return tc_new(size);       }
void operator delete_NOT_USED(void* p) CPP_NOTHROW        { tc_delete(p);              }
void* operator new_NOT_USED[](size_t size)                { return tc_newarray(size);  }
void operator delete_NOT_USED[](void* p) CPP_NOTHROW      { tc_deletearray(p);         }
void* operator new_NOT_USED(size_t size, const std::nothrow_t& nt) CPP_NOTHROW {
  return tc_new_nothrow(size, nt);
}
void* operator new_NOT_USED[](size_t size, const std::nothrow_t& nt) CPP_NOTHROW {
  return tc_newarray_nothrow(size, nt);
}
void operator delete_NOT_USED(void* ptr, const std::nothrow_t& nt) CPP_NOTHROW {
  return tc_delete_nothrow(ptr, nt);
}
void operator delete_NOT_USED[](void* ptr, const std::nothrow_t& nt) CPP_NOTHROW {
  return tc_deletearray_nothrow(ptr, nt);
}

#ifdef ENABLE_SIZED_DELETE
void operator delete_NOT_USED(void* p, size_t s) CPP_NOTHROW  { tc_delete_sized(p, s);     }
void operator delete_NOT_USED[](void* p, size_t s) CPP_NOTHROW{ tc_deletearray_sized(p, s);}
#endif

#if defined(ENABLE_ALIGNED_NEW_DELETE)

void* operator new_NOT_USED(size_t size, std::align_val_t al) {
  return tc_new_aligned(size, al);
}
void operator delete_NOT_USED(void* p, std::align_val_t al) CPP_NOTHROW {
  tc_delete_aligned(p, al);
}
void* operator new_NOT_USED[](size_t size, std::align_val_t al) {
  return tc_newarray_aligned(size, al);
}
void operator delete_NOT_USED[](void* p, std::align_val_t al) CPP_NOTHROW {
  tc_deletearray_aligned(p, al);
}
void* operator new_NOT_USED(size_t size, std::align_val_t al, const std::nothrow_t& nt) CPP_NOTHROW {
  return tc_new_aligned_nothrow(size, al, nt);
}
void* operator new_NOT_USED[](size_t size, std::align_val_t al, const std::nothrow_t& nt) CPP_NOTHROW {
  return tc_newarray_aligned_nothrow(size, al, nt);
}
void operator delete_NOT_USED(void* ptr, std::align_val_t al, const std::nothrow_t& nt) CPP_NOTHROW {
  return tc_delete_aligned_nothrow(ptr, al, nt);
}
void operator delete_NOT_USED[](void* ptr, std::align_val_t al, const std::nothrow_t& nt) CPP_NOTHROW {
  return tc_deletearray_aligned_nothrow(ptr, al, nt);
}

#ifdef ENABLE_SIZED_DELETE
void operator delete_NOT_USED(void* p, size_t s, std::align_val_t al) CPP_NOTHROW {
  tc_delete_sized_aligned(p, s, al);
}
void operator delete_NOT_USED[](void* p, size_t s, std::align_val_t al) CPP_NOTHROW {
  tc_deletearray_sized_aligned(p, s, al);
}
#endif

#endif // defined(ENABLE_ALIGNED_NEW_DELETE)

extern "C" {
  void* malloc_NOT_USED(size_t s)                         { return tc_malloc(s);       }
  void  free_NOT_USED(void* p)                            { tc_free(p);                }
  void* realloc_NOT_USED(void* p, size_t s)               { return tc_realloc(p, s);   }
  void* calloc_NOT_USED(size_t n, size_t s)               { return tc_calloc(n, s);    }
  void  cfree_NOT_USED(void* p)                           { tc_cfree(p);               }
  void* memalign_NOT_USED(size_t a, size_t s)             { return tc_memalign(a, s);  }
  void* aligned_alloc_NOT_USED(size_t a, size_t s)        { return tc_memalign(a, s);  }
  void* valloc_NOT_USED(size_t s)                         { return tc_valloc(s);       }
  void* pvalloc_NOT_USED(size_t s)                        { return tc_pvalloc(s);      }
  int posix_memalign_NOT_USED(void** r, size_t a, size_t s)         {
    return tc_posix_memalign(r, a, s);
  }
  void malloc_stats_NOT_USED(void)                        { tc_malloc_stats();         }
  int mallopt_NOT_USED(int cmd, int v)                    { return tc_mallopt(cmd, v); }
#ifdef HAVE_STRUCT_MALLINFO
  struct mallinfo mallinfo_NOT_USED(void)                 { return tc_mallinfo();      }
#endif
  size_t malloc_size_NOT_USED(void* p)                    { return tc_malloc_size(p); }
  size_t malloc_usable_size_NOT_USED(void* p)             { return tc_malloc_size(p); }
}  // extern "C"

// No need to do anything at tcmalloc-registration time: we do it all
// via overriding weak symbols (at link time).
static void ReplaceSystemAlloc() { }

#endif  // TCMALLOC_LIBC_OVERRIDE_REDEFINE_H_
