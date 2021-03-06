#ifndef _lua_tree_h
#define _lua_tree_h

#include "../../luaC-api/lua.h"
#include "../../luaC-api/lualib.h"
#include "../../luaC-api/lauxlib.h"
#include "../lua_objects.h"	
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <git2.h>

static int lua_git_tree_entry_byid(lua_State *L) {
    const luagit2_tree *Tree = (luagit2_tree *)lua_touserdata(L, 1);
    const luagit2_oid *obj_id = (luagit2_oid *)lua_touserdata(L, 2);

    luagit2_tree_entry *lua_tree_entry;

    lua_tree_entry = (luagit2_tree_entry *)lua_newuserdata(L, sizeof(*lua_tree_entry));
    lua_tree_entry->tree_entry = NULL;
 
    luaL_getmetatable(L, "luagit2_tree_entry");
    lua_setmetatable(L, -2);

    lua_tree_entry->tree_entry = git_tree_entry_byid(Tree->tree,&(obj_id->oid));
    
    return 1;
}

static int lua_git_tree_entry_byindex(lua_State *L) {
    const luagit2_tree *Tree = (luagit2_tree *)lua_touserdata(L, 1);
    size_t index = luaL_checkinteger(L, 2);

    luagit2_tree_entry *lua_tree_entry;

    lua_tree_entry = (luagit2_tree_entry *)lua_newuserdata(L, sizeof(*lua_tree_entry));
    lua_tree_entry->tree_entry = NULL;
 
    luaL_getmetatable(L, "luagit2_tree_entry");
    lua_setmetatable(L, -2);

    lua_tree_entry->tree_entry = git_tree_entry_byindex(Tree->tree,index);
    
    return 1;
}

static int lua_git_tree_entry_byname(lua_State *L) {
    const luagit2_tree *Tree = (luagit2_tree *)lua_touserdata(L, 1);
    const char *filename = luaL_checkstring(L, 2);

    luagit2_tree_entry *lua_tree_entry;

    lua_tree_entry = (luagit2_tree_entry *)lua_newuserdata(L, sizeof(*lua_tree_entry));
    lua_tree_entry->tree_entry = NULL;
 
    luaL_getmetatable(L, "luagit2_tree_entry");
    lua_setmetatable(L, -2);

    lua_tree_entry->tree_entry = git_tree_entry_byname(Tree->tree,filename);
    
    return 1;
}

static int lua_git_tree_entry_bypath(lua_State *L) {
    const luagit2_tree *Tree = (luagit2_tree *)lua_touserdata(L, 1);
    const char *path = luaL_checkstring(L, 2);

    luagit2_tree_entry *lua_tree_entry;

    lua_tree_entry = (luagit2_tree_entry *)lua_newuserdata(L, sizeof(*lua_tree_entry));
    lua_tree_entry->tree_entry = NULL;
 
    luaL_getmetatable(L, "luagit2_tree_entry");
    lua_setmetatable(L, -2);

    git_tree_entry *local_tree_entry;
    git_tree_entry_bypath(&local_tree_entry,Tree->tree,path);
    lua_tree_entry->tree_entry = local_tree_entry;
    return 1;
}


static int lua_git_tree_entry_cmp(lua_State *L) {
    const luagit2_tree_entry *Tree_entry1 = (luagit2_tree_entry *)lua_touserdata(L, 1);
    const luagit2_tree_entry *Tree_entry2 = (luagit2_tree_entry *)lua_touserdata(L, 2);

    int result = git_tree_entry_cmp(Tree_entry1->tree_entry,Tree_entry2->tree_entry);
    lua_pushinteger(L,result);
    return 1;
}

static int lua_git_tree_entry_filemode(lua_State *L) {
	luagit2_filemode *File_Mode;
    const luagit2_tree_entry *Tree_entry = (luagit2_tree_entry *)lua_touserdata(L, 1);
	
    File_Mode = (luagit2_filemode *)lua_newuserdata(L, sizeof(*File_Mode));

    luaL_getmetatable(L, "luagit2_filemode");
    lua_setmetatable(L, -2);
	File_Mode->filemode = git_tree_entry_filemode(Tree_entry->tree_entry);

    return 1;
}

static int lua_git_tree_entry_filemode_raw(lua_State *L) {
	luagit2_filemode *File_Mode;
    const luagit2_tree_entry *Tree_entry = (luagit2_tree_entry *)lua_touserdata(L, 1);
	
    File_Mode = (luagit2_filemode *)lua_newuserdata(L, sizeof(*File_Mode));

    luaL_getmetatable(L, "luagit2_filemode");
    lua_setmetatable(L, -2);
	File_Mode->filemode = git_tree_entry_filemode_raw(Tree_entry->tree_entry);

    return 1;
}

static int lua_git_tree_entry_id(lua_State *L) {
	luagit2_oid *obj_id;
    const luagit2_tree_entry *Tree_entry = (luagit2_tree_entry *)lua_touserdata(L, 1);
	
    obj_id = (luagit2_oid *)lua_newuserdata(L, sizeof(*obj_id));

    luaL_getmetatable(L, "luagit2_oid");
    lua_setmetatable(L, -2);

    const git_oid *local_id = git_tree_entry_id(Tree_entry->tree_entry);
   	obj_id->oid = *local_id;
   	
    return 1;
}

static int lua_git_tree_entry_name (lua_State *L) {
	const luagit2_tree_entry *Tree_entry = (luagit2_tree_entry *)lua_touserdata(L, 1);

    const char *entry_name = git_tree_entry_name(Tree_entry->tree_entry);
    lua_pushstring(L,entry_name);
    return 1;
}

static int lua_git_tree_entry_to_object (lua_State *L) {
	luagit2_repository *Repo = (luagit2_repository *)lua_touserdata(L,1);
	const luagit2_tree_entry *Tree_entry = (luagit2_tree_entry *)lua_touserdata(L, 2);

	luagit2_object *lua_obj;

    lua_obj = (luagit2_object *)lua_newuserdata(L, sizeof(*lua_obj));
    lua_obj->object = NULL;
 
    luaL_getmetatable(L, "luagit2_object");
    lua_setmetatable(L, -2);
    
    git_object *local_obj;
    git_tree_entry_to_object(&local_obj,Repo->repo,Tree_entry->tree_entry);

   	lua_obj->object  = local_obj;
    return 1;
}


static int lua_git_tree_entry_type(lua_State *L)
{
	luagit2_otype *obj_type;
    const luagit2_tree_entry *Tree_entry = (luagit2_tree_entry *)lua_touserdata(L, 1);
    
    obj_type = (luagit2_otype *)lua_newuserdata(L, sizeof(*obj_type));

    luaL_getmetatable(L, "luagit2_otype");
    lua_setmetatable(L, -2);

    obj_type->otype = git_tree_entry_type(Tree_entry->tree_entry);

    return 1;
}

static int lua_git_tree_entrycount(lua_State *L)
{
	luagit2_oid *obj_id;
    const luagit2_tree *Tree = (luagit2_tree *)lua_touserdata(L, 1);
    
    size_t result = git_tree_entrycount(Tree->tree);
   	lua_pushinteger(L,result);
    return 1;
}

static int lua_git_tree_id(lua_State *L)
{
	luagit2_oid *obj_id;
    const luagit2_tree *Tree = (luagit2_tree *)lua_touserdata(L, 1);
	
    obj_id = (luagit2_oid *)lua_newuserdata(L, sizeof(*obj_id));

    luaL_getmetatable(L, "luagit2_oid");
    lua_setmetatable(L, -2);

    const git_oid *local_id = git_tree_id(Tree->tree);
   	obj_id->oid = *local_id;
    return 1;
}

static int lua_git_tree_lookup (lua_State *L) {
	luagit2_repository *Repo = (luagit2_repository *)lua_touserdata(L,1);
	const luagit2_oid *Tree_id = (luagit2_oid *)lua_touserdata(L, 2);

	luagit2_tree *lua_tree;
 
    lua_tree = (luagit2_tree *)lua_newuserdata(L, sizeof(*lua_tree));
    lua_tree->tree = NULL;
 
    luaL_getmetatable(L, "luagit2_tree");
    lua_setmetatable(L, -2);
    
    git_tree *local_tree_obj;
    git_tree_lookup(&local_tree_obj,Repo->repo,&(Tree_id->oid));

   	lua_tree->tree  = local_tree_obj;
    return 1;
}

static int lua_git_tree_lookup_prefix (lua_State *L) {
	luagit2_repository *Repo = (luagit2_repository *)lua_touserdata(L,1);
	const luagit2_oid *Tree_id = (luagit2_oid *)lua_touserdata(L, 2);
	size_t length = luaL_checkinteger(L,3);

	luagit2_tree *lua_tree;
 
    lua_tree = (luagit2_tree *)lua_newuserdata(L, sizeof(*lua_tree));
    lua_tree->tree = NULL;
 
    luaL_getmetatable(L, "luagit2_tree");
    lua_setmetatable(L, -2);
    
    git_tree *local_tree_obj;
    git_tree_lookup_prefix(&local_tree_obj,Repo->repo,&(Tree_id->oid),length);

   	lua_tree->tree  = local_tree_obj;
    return 1;
}

static int lua_git_tree_owner(lua_State *L)
{
    luagit2_repository *lua_repo;
    const luagit2_tree *Tree = (luagit2_tree *)lua_touserdata(L, 1);

    lua_repo = (luagit2_repository *)lua_newuserdata(L, sizeof(*lua_repo));
    lua_repo->repo  = NULL;

    luaL_getmetatable(L, "luagit2_repository");
    lua_setmetatable(L, -2);

    git_repository *Repository  = git_tree_owner(Tree->tree);
    lua_repo->repo = Repository ;
    return 1;
}


#endif
