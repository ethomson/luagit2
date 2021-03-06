#ifndef _lua_blob_h
#define _lua_blob_h

#include "../../luaC-api/lua.h"
#include "../../luaC-api/lualib.h"
#include "../../luaC-api/lauxlib.h"
#include "../lua_objects.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <git2.h>

static int lua_git_blob_create_fromdisk (lua_State *L) {
	luagit2_oid *obj_id;
	const luagit2_repository *Repo = (luagit2_repository *)lua_touserdata(L, 1);
    const char *path = luaL_checkstring(L,2);

    obj_id = (luagit2_oid *)lua_newuserdata(L, sizeof(*obj_id));

    luaL_getmetatable(L, "luagit2_oid");
    lua_setmetatable(L, -2);

    git_oid local_id;
    git_blob_create_fromdisk(&local_id,Repo->repo,path);
   	obj_id->oid = local_id;

    return 1;
}

static int lua_git_blob_create_fromworkdir (lua_State *L) {
	luagit2_oid *obj_id;
	const luagit2_repository *Repo = (luagit2_repository *)lua_touserdata(L, 1);
    const char *relative_path = luaL_checkstring(L,2);

    obj_id = (luagit2_oid *)lua_newuserdata(L, sizeof(*obj_id));

    luaL_getmetatable(L, "luagit2_oid");
    lua_setmetatable(L, -2);

    git_oid local_id;
    git_blob_create_fromworkdir(&local_id,Repo->repo,relative_path);
   	obj_id->oid = local_id;

    return 1;
}

static int lua_git_blob_filtered_content (lua_State *L) {
	luagit2_blob *lua_blob = (luagit2_blob *)lua_touserdata(L, 1);
	const char *as_path = luaL_checkstring(L,2);
	int check_for_binary_data = luaL_checkinteger(L,3);

	luagit2_buf *lua_out_buf;

    lua_out_buf = (luagit2_buf *)lua_newuserdata(L, sizeof(*lua_out_buf));
    lua_out_buf->buf = NULL;

    luaL_getmetatable(L, "luagit2_buf");
    lua_setmetatable(L, -2);

    git_buf *local_buf;
    git_blob_filtered_content(local_buf,lua_blob->blob,as_path,check_for_binary_data);

   	lua_out_buf->buf  = local_buf;
    return 1;
}

static int lua_git_blob_id (lua_State *L) {
	luagit2_oid *obj_id;
	const luagit2_blob *lua_blob = (luagit2_blob *)lua_touserdata(L, 1);

    obj_id = (luagit2_oid *)lua_newuserdata(L, sizeof(*obj_id));

    luaL_getmetatable(L, "luagit2_oid");
    lua_setmetatable(L, -2);

   	obj_id->oid = *(git_blob_id(lua_blob->blob));

    return 1;
}

static int lua_git_blob_is_binary (lua_State *L) {
	const luagit2_blob *lua_blob = (luagit2_blob *)lua_touserdata(L, 1);

    int is_binary = git_blob_is_binary(lua_blob->blob);
    lua_pushinteger(L,is_binary);
    return 1;
}

static int lua_git_blob_lookup (lua_State *L) {
	luagit2_blob *lua_blob ;
	const luagit2_repository *Repo = (luagit2_repository *)lua_touserdata(L, 1);
	const luagit2_oid *lua_oid = (luagit2_oid *)lua_touserdata(L, 2);

    lua_blob = (luagit2_blob *)lua_newuserdata(L, sizeof(*lua_blob));
    lua_blob->blob = NULL;

    luaL_getmetatable(L, "luagit2_blob");
    lua_setmetatable(L, -2);

    git_blob *local_blob;
    git_blob_lookup(&local_blob,Repo->repo,&(lua_oid->oid));

   	lua_blob->blob  = local_blob;
    return 1;
}

static int lua_git_blob_lookup_prefix (lua_State *L) {
	luagit2_blob *lua_blob ;
	const luagit2_repository *Repo = (luagit2_repository *)lua_touserdata(L, 1);
	const luagit2_oid *lua_oid = (luagit2_oid *)lua_touserdata(L, 2);
 	size_t len = luaL_checkinteger(L,3);

    lua_blob = (luagit2_blob *)lua_newuserdata(L, sizeof(*lua_blob));
    lua_blob->blob = NULL;

    luaL_getmetatable(L, "luagit2_blob");
    lua_setmetatable(L, -2);

    git_blob *local_blob;
    git_blob_lookup_prefix(&local_blob,Repo->repo,&(lua_oid->oid),len);

   	lua_blob->blob  = local_blob;
    return 1;
}

static int lua_git_blob_owner(lua_State *L) {
    luagit2_repository *lua_repo;
    const luagit2_blob *lua_blob = (luagit2_blob *)lua_touserdata(L, 1);

    lua_repo = (luagit2_repository *)lua_newuserdata(L, sizeof(*lua_repo));
    lua_repo->repo  = NULL;

    luaL_getmetatable(L, "luagit2_repository");
    lua_setmetatable(L, -2);

    lua_repo->repo = git_blob_owner(lua_blob->blob);

    return 1;
}

static int lua_git_blob_rawsize(lua_State *L) {
    luagit2_off_t *lua_blob_size;
    const luagit2_blob *lua_blob = (luagit2_blob *)lua_touserdata(L, 1);

    lua_blob_size = (luagit2_off_t *)lua_newuserdata(L, sizeof(*lua_blob_size));

    luaL_getmetatable(L, "luagit2_off_t");
    lua_setmetatable(L, -2);

    lua_blob_size->size = git_blob_rawsize(lua_blob->blob);

    return 1;
}

#endif
