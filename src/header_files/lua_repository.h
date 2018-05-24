#ifndef _lua_repository_h
#define _lua_repository_h

#include "../luaC-api/lua.h"
#include "../luaC-api/lualib.h"
#include "../luaC-api/lauxlib.h"
#include "lua_objects.h"	
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <git2.h>

static int lua_git_repository_open(lua_State *L)
{
    luagit2_repository *lua_repo;
    const char *path;

    path  = luaL_checkstring(L, 1);
    if (path == NULL)
        luaL_error(L, "path cannot be empty");

    lua_repo = (luagit2_repository *)lua_newuserdata(L, sizeof(*lua_repo));
    lua_repo->repo  = NULL;

    luaL_getmetatable(L, "luagit2_repository");
    lua_setmetatable(L, -2);

    git_repository *Repository  = NULL;
    git_repository_open(&Repository,path);

    lua_repo->repo = Repository ;
    return 1;
}

#endif