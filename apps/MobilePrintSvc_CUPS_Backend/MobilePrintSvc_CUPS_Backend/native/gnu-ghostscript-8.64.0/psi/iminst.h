/* Copyright (C) 2001-2006 Artifex Software, Inc.
   All Rights Reserved.
  
  This file is part of GNU ghostscript

  GNU ghostscript is free software; you can redistribute it and/or
  modify it under the terms of the version 2 of the GNU General Public
  License as published by the Free Software Foundation.

  GNU ghostscript is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with
  ghostscript; see the file COPYING. If not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

*/

/* $Id: iminst.h,v 1.8 2007/09/11 15:24:37 Arabidopsis Exp $ */
/* Definition of interpreter instance */
/* Requires stdio_.h, gsmemory.h, iref.h, iapi.h */

#ifndef iminst_INCLUDED
#  define iminst_INCLUDED

#ifndef gs_main_instance_DEFINED
#  define gs_main_instance_DEFINED
typedef struct gs_main_instance_s gs_main_instance;
#endif

/*
 * Define the structure of a search path.  Currently there is only one,
 * but there might be more someday.
 *
 *      container - an array large enough to hold the specified maximum
 * number of directories.  Both the array and all the strings in it are
 * in the 'foreign' VM space.
 *      list - the initial interval of container that defines the actual
 * search list.
 *      env - the contents of an environment variable, implicitly added
 * at the end of the list; may be 0.
 *      final - the final set of directories specified in the makefile;
 * may be 0.
 *      count - the number of elements in the list, excluding a possible
 * initial '.', env, and final.
 */
typedef struct gs_file_path_s {
    ref container;
    ref list;
    const char *env;
    const char *final;
    uint count;
} gs_file_path;

/*
 * Here is where we actually define the structure of interpreter instances.
 * Clients should not reference any of the members.  Note that in order to
 * be able to initialize this structure statically, members including
 * unions must come last (and be initialized to 0 by default).
 */
struct gs_main_instance_s {
    /* The following are set during initialization. */
    gs_memory_t *heap;		/* (C) heap allocator */
    uint memory_chunk_size;	/* 'wholesale' allocation unit */
    ulong name_table_size;
    uint run_buffer_size;
    int init_done;		/* highest init done so far */
    int user_errors;		/* define what to do with errors */
    bool search_here_first;	/* if true, make '.' first lib dir */
    bool run_start;		/* if true, run 'start' after */
				/* processing command line */
    gs_file_path lib_path;	/* library search list (GS_LIB) */
    long base_time[2];		/* starting usertime */
    void *readline_data;	/* data for gp_readline */
    ref error_object;		/* Use by gsapi_*() */
#if 1
    /* needs to be removed */
    display_callback *display;	/* callback structure for display device */
#endif

    /* The following are updated dynamically. */
    i_ctx_t *i_ctx_p;		/* current interpreter context state */
};

/*
 * Note that any file that uses the following definition of default values
 * must include gconfig.h, because of SEARCH_HERE_FIRST.
 */
#define gs_main_instance_default_init_values\
  0, 20000, 0, 0, -1, 0, SEARCH_HERE_FIRST, 1
extern const gs_main_instance gs_main_instance_init_values;

#endif /* iminst_INCLUDED */
