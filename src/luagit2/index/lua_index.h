#ifndef _lua_index_h
#define _lua_index_h

#include "../../luaC-api/lua.h"
#include "../../luaC-api/lualib.h"
#include "../../luaC-api/lauxlib.h"
#include "../lua_objects.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <git2.h>

static int lua_git_index_add(lua_State *L) {
    luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);
    const luagit2_index_entry *Index_entry = (luagit2_index_entry *)lua_touserdata(L,2);

    git_index_add(Index->index,Index_entry->index_entry);

    return 1;

}

static int lua_git_index_add_bypath(lua_State *L) {
    luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);
    const char *path = luaL_checkstring(L,2);

    git_index_add_bypath(Index->index,path);

    return 1;

}

static int lua_git_index_caps(lua_State *L) {
    luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);

    int values = git_index_caps(Index->index);
    lua_pushinteger(L,values);

    return 1;

}

static int lua_git_index_checksum(lua_State *L) {
    luagit2_oid *obj_id;
    const luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);

    obj_id = (luagit2_oid *)lua_newuserdata(L, sizeof(*obj_id));

    luaL_getmetatable(L, "luagit2_oid");
    lua_setmetatable(L, -2);

   	obj_id->oid = *(git_index_checksum(Index->index));

	return 1;

}

static int lua_git_index_conflict_add(lua_State *L) {
    luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);
    const luagit2_index_entry *Index_ancestor_entry = (luagit2_index_entry *)lua_touserdata(L, 2);
    const luagit2_index_entry *Index_our_entry = (luagit2_index_entry *)lua_touserdata(L, 3);
    const luagit2_index_entry *Index_their_entry = (luagit2_index_entry *)lua_touserdata(L, 4);

    git_index_conflict_add(Index->index,Index_ancestor_entry->index_entry
    						,Index_our_entry->index_entry,Index_their_entry->index_entry);

    return 1;

}

static int lua_git_index_conflict_cleanup(lua_State *L) {
    luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);

    git_index_conflict_cleanup(Index->index);

    return 1;

}

static int lua_git_index_entry_is_conflict(lua_State *L) {
    luagit2_index_entry *Index_entry = (luagit2_index_entry *)lua_touserdata(L, 1);

    int is_conflict = git_index_entry_is_conflict(Index_entry->index_entry);
    lua_pushinteger(L,is_conflict);

    return 1;

}

static int lua_git_index_entry_stage(lua_State *L) {
    luagit2_index_entry *Index_entry = (luagit2_index_entry *)lua_touserdata(L, 1);

    int stage_value = git_index_entry_stage(Index_entry->index_entry);
    lua_pushinteger(L,stage_value);

    return 1;

}

static int lua_git_index_entrycount(lua_State *L) {
    luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);

    int index_entry_count = git_index_entrycount(Index->index);
    lua_pushinteger(L,index_entry_count);

    return 1;

}

static int lua_git_index_find(lua_State *L) {
    luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);
    const char *path = luaL_checkstring(L,2);

	size_t at_pos;
    git_index_find(&at_pos,Index->index,path);
    lua_pushinteger(L,at_pos);

    return 1;

}

static int lua_git_index_find_prefix(lua_State *L) {
    luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);
    const char *prefix = luaL_checkstring(L,2);

	size_t at_pos;
    git_index_find_prefix(&at_pos,Index->index,prefix);
    lua_pushinteger(L,at_pos);

    return 1;

}

static int lua_git_index_get_byindex(lua_State *L) {
    luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);
	  size_t n = luaL_checkinteger(L,2);

   	luagit2_index_entry *Index_entry;
    Index_entry = (luagit2_index_entry *)lua_newuserdata(L, sizeof(*Index_entry));

    luaL_getmetatable(L, "luagit2_index_entry");
    lua_setmetatable(L, -2);


   	Index_entry->index_entry = git_index_get_byindex(Index->index,n);

    return 1;
}

static int lua_git_index_get_bypath(lua_State *L) {
    const luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);
    const char *path = luaL_checkstring(L,2);
	int stage = luaL_checkinteger(L,3);

   	luagit2_index_entry *Index_entry;
    Index_entry = (luagit2_index_entry *)lua_newuserdata(L, sizeof(*Index_entry));

    luaL_getmetatable(L, "luagit2_index_entry");
    lua_setmetatable(L, -2);


   	Index_entry->index_entry = git_index_get_bypath(Index->index,path,stage);

    return 1;
}

static int lua_git_index_has_conflicts(lua_State *L) {
    const luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);

    int has_conflicts = git_index_has_conflicts(Index->index);
    lua_pushinteger(L,has_conflicts);

    return 1;

}

static int lua_git_index_open(lua_State *L) {
    const char *path = luaL_checkstring(L,1);

   	luagit2_index *lua_index;
    lua_index = (luagit2_index *)lua_newuserdata(L, sizeof(*lua_index));
    lua_index->index = NULL;

    luaL_getmetatable(L, "luagit2_index");
    lua_setmetatable(L, -2);

    git_index *local_index;
   	git_index_open(&local_index,path);
   	lua_index->index = local_index;

    return 1;
}

static int lua_git_index_owner (lua_State *L) {
    luagit2_repository *lua_repo;
    const luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);

    lua_repo = (luagit2_repository *)lua_newuserdata(L, sizeof(*lua_repo));
    lua_repo->repo  = NULL;

    luaL_getmetatable(L, "luagit2_repository");
    lua_setmetatable(L, -2);

    lua_repo->repo = git_index_owner(Index->index);
    return 1;
}

static int lua_git_index_path(lua_State *L) {
      const luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);
    char *index_path = git_index_path(Index->index);
    lua_pushstring(L,index_path);

    return 1;

}

static int lua_git_index_read(lua_State *L) {
    const luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);
	int force = luaL_checkinteger(L,2);
    git_index_read(Index->index,force);

    return 1;

}

static int lua_git_index_read_tree(lua_State *L) {
    const luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);
	  const luagit2_tree *Tree = (luagit2_tree *)lua_touserdata(L, 2);
    git_index_read_tree(Index->index,Tree->tree);

    return 1;

}

static int lua_git_index_remove(lua_State *L) {
    const luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);
    const char *path = luaL_checkstring(L,2);
	int stage = luaL_checkinteger(L,3);

   	git_index_remove(Index->index,path,stage);

    return 1;
}

static int lua_git_index_remove_bypath(lua_State *L) {
    const luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);
    const char *path = luaL_checkstring(L,2);

   	git_index_remove_bypath(Index->index,path);

    return 1;
}

static int lua_git_index_remove_directory(lua_State *L) {
    const luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);
    const char *dir_path = luaL_checkstring(L,2);
	int stage = luaL_checkinteger(L,3);

   	git_index_remove_directory(Index->index,dir_path,stage);

    return 1;
}

static int lua_git_index_set_caps(lua_State *L) {
    const luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);
	int caps = luaL_checkinteger(L,2);

   	git_index_set_caps(Index->index,caps);

    return 1;
}


static int lua_git_index_set_version(lua_State *L) {
    const luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);
  	unsigned int version = luaL_checkinteger(L,2);

   	git_index_set_version(Index->index,version);

    return 1;
}

static int lua_git_index_version(lua_State *L) {
    const luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);

   	unsigned int version_number = git_index_version(Index->index);
   	lua_pushnumber(L,version_number);

    return 1;
}

static int lua_git_index_write(lua_State *L) {
    const luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);

	git_index_write(Index->index);

    return 1;
}

static int lua_git_index_write_tree(lua_State *L) {
    luagit2_oid *obj_id;
    const luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);

    obj_id = (luagit2_oid *)lua_newuserdata(L, sizeof(*obj_id));

    luaL_getmetatable(L, "luagit2_oid");
    lua_setmetatable(L, -2);

    git_oid local_id;
    git_index_write_tree(&local_id,Index->index);
   	obj_id->oid = local_id;

	return 1;

}

static int lua_git_index_write_tree_to(lua_State *L) {
    luagit2_oid *obj_id;
    const luagit2_index *Index = (luagit2_index *)lua_touserdata(L, 1);
    const luagit2_repository *Repo = (luagit2_repository *)lua_touserdata(L,2);

    obj_id = (luagit2_oid *)lua_newuserdata(L, sizeof(*obj_id));

    luaL_getmetatable(L, "luagit2_oid");
    lua_setmetatable(L, -2);

    git_oid local_id;
    git_index_write_tree_to(&local_id,Index->index,Repo->repo);
   	obj_id->oid = local_id;

	return 1;

}

#endif
