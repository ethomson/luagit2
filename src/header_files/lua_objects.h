#ifndef _lua_objects_h
#define _lua_objects_h

#include "../luaC-api/lua.h"
#include "../luaC-api/lualib.h"
#include "../luaC-api/lauxlib.h"	
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <git2.h> 

typedef struct {
   int major;
   int minor;
   int rev;
} libgit_version_data;

typedef struct {
   git_cred *git_cred_object;
} luagit2_cred_object;

typedef struct {
	git_buf *buf;
} luagit2_buf;

typedef struct {
	git_config *cfg;
} luagit2_config;


#endif