#ifndef _lua_reference_h
#define _lua_reference_h

#include "../../luaC-api/lua.h"
#include "../../luaC-api/lualib.h"
#include "../../luaC-api/lauxlib.h"
#include "../lua_objects.h"	
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <git2.h>

static int lua_git_reference_create (lua_State *L) {
    luagit2_reference *lua_ref;
    const luagit2_repository *lua_repo = (luagit2_repository *)lua_touserdata(L, 1);
    const char *name = luaL_checkstring(L,2);
    const luagit2_oid *lua_oid = (luagit2_oid *)lua_touserdata(L,3);
    const int force = luaL_checkinteger(L,4);
    const char *log_message = luaL_checkstring(L,5);

    lua_ref = (luagit2_reference *)lua_newuserdata(L, sizeof(*lua_ref));
    lua_ref->reference  = NULL;
 
    luaL_getmetatable(L, "luagit2_reference");
    
    lua_setmetatable(L, -2);
    
    git_reference *local_ref;
    git_reference_create(&local_ref,lua_repo->repo,name,&(lua_oid->oid),force,log_message); 
    lua_ref->reference  = local_ref;
    return 1;
}

static int lua_git_reference_create_matching (lua_State *L) {
    luagit2_reference *lua_ref;
    const luagit2_repository *lua_repo = (luagit2_repository *)lua_touserdata(L, 1);
    const char *name = luaL_checkstring(L,2);
    const luagit2_oid *lua_oid = (luagit2_oid *)lua_touserdata(L,3);
    const int force = luaL_checkinteger(L,4);
    const luagit2_oid *current_oid = (luagit2_oid *)lua_touserdata(L,5);
    const char *log_message = luaL_checkstring(L,6);

    lua_ref = (luagit2_reference *)lua_newuserdata(L, sizeof(*lua_ref));
    lua_ref->reference  = NULL;
 
    luaL_getmetatable(L, "luagit2_reference");
    
    lua_setmetatable(L, -2);
    
    git_reference *local_ref;
    git_reference_create_matching(&local_ref,lua_repo->repo,name,&(lua_oid->oid),
    								force,&(current_oid->oid),log_message); 
    lua_ref->reference  = local_ref;
    return 1;
}

static int lua_git_reference_dup (lua_State *L) {
    luagit2_reference *lua_ref;
    const luagit2_reference *lua_ref_source = (luagit2_reference *)lua_touserdata(L, 1);

    lua_ref = (luagit2_reference *)lua_newuserdata(L, sizeof(*lua_ref));
    lua_ref->reference  = NULL;
 
    luaL_getmetatable(L, "luagit2_reference");
    
    lua_setmetatable(L, -2);
    
    git_reference *local_ref;
    git_reference_dup(&local_ref,lua_ref_source->reference); 
    lua_ref->reference  = local_ref;
    return 1;
}

static int lua_git_reference_dwim (lua_State *L) {
    luagit2_reference *lua_ref;
    const luagit2_repository *lua_repo = (luagit2_repository *)lua_touserdata(L, 1);
    const char *shorthand = luaL_checkstring(L,2);

    lua_ref = (luagit2_reference *)lua_newuserdata(L, sizeof(*lua_ref));
    lua_ref->reference  = NULL;
 
    luaL_getmetatable(L, "luagit2_reference");
    
    lua_setmetatable(L, -2);
    
    git_reference *local_ref;
    git_reference_dwim(&local_ref,lua_repo->repo,shorthand); 
    lua_ref->reference  = local_ref;
    return 1;
}

static int lua_git_reference_ensure_log (lua_State *L) {
    luagit2_reference *lua_ref;
    const luagit2_repository *lua_repo = (luagit2_repository *)lua_touserdata(L, 1);
    const char *refname = luaL_checkstring(L,2);

    int result = git_reference_ensure_log(lua_repo->repo,refname); 
    lua_pushinteger(L,result);
    return 1;
}

static int lua_git_reference_has_log (lua_State *L) {
    luagit2_reference *lua_ref;
    const luagit2_repository *lua_repo = (luagit2_repository *)lua_touserdata(L, 1);
    const char *refname = luaL_checkstring(L,2);

    int result = git_reference_has_log(lua_repo->repo,refname); 
    lua_pushinteger(L,result);
    return 1;
}

static int lua_git_reference_is_branch (lua_State *L) {
    const luagit2_reference *lua_ref = (luagit2_reference *)lua_touserdata(L, 1);

    int is_branch = git_reference_is_branch(lua_ref->reference); 
    lua_pushinteger(L,is_branch);
    return 1;
}

static int lua_git_reference_is_note (lua_State *L) {
    const luagit2_reference *lua_ref = (luagit2_reference *)lua_touserdata(L, 1);

    int is_note= git_reference_is_note(lua_ref->reference); 
    lua_pushinteger(L,is_note);
    return 1;
}

static int lua_git_reference_is_remote (lua_State *L) {
    const luagit2_reference *lua_ref = (luagit2_reference *)lua_touserdata(L, 1);

    int is_remote = git_reference_is_remote(lua_ref->reference); 
    lua_pushinteger(L,is_remote);
    return 1;
}

static int lua_git_reference_is_tag (lua_State *L) {
    const luagit2_reference *lua_ref = (luagit2_reference *)lua_touserdata(L, 1);

    int is_tag = git_reference_is_tag(lua_ref->reference); 
    lua_pushinteger(L,is_tag);
    return 1;
}

static int lua_git_reference_is_valid_name (lua_State *L) {
    const char *refname = luaL_checkstring(L,1);

    int is_valid_name = git_reference_is_valid_name(refname); 
    lua_pushinteger(L,is_valid_name);
    return 1;
}

static int lua_git_reference_iterator_glob_new (lua_State *L) {
    luagit2_reference_iterator *lua_ref_iterator;
    const luagit2_repository *lua_repo = (luagit2_repository *)lua_touserdata(L, 1);
    const char *glob = luaL_checkstring(L,2);

    lua_ref_iterator = (luagit2_reference_iterator *)lua_newuserdata(L, sizeof(*lua_ref_iterator));
    lua_ref_iterator->iterator = NULL;
 
    luaL_getmetatable(L, "luagit2_reference_iterator");
    
    lua_setmetatable(L, -2);
    
    git_reference_iterator *local_ref_iterator;
    git_reference_iterator_glob_new(&local_ref_iterator,lua_repo->repo,glob); 
    lua_ref_iterator->iterator  = local_ref_iterator;
    return 1;
}

static int lua_git_reference_iterator_new (lua_State *L) {
    luagit2_reference_iterator *lua_ref_iterator;
    const luagit2_repository *lua_repo = (luagit2_repository *)lua_touserdata(L, 1);
    
    lua_ref_iterator = (luagit2_reference_iterator *)lua_newuserdata(L, sizeof(*lua_ref_iterator));
    lua_ref_iterator->iterator = NULL;
 
    luaL_getmetatable(L, "luagit2_reference_iterator");
    
    lua_setmetatable(L, -2);
    
    git_reference_iterator *local_ref_iterator;
    git_reference_iterator_new(&local_ref_iterator,lua_repo->repo); 
    lua_ref_iterator->iterator  = local_ref_iterator;
    return 1;
}

static int lua_git_reference_list (lua_State *L) {
    luagit2_strarray *lua_array;
    const luagit2_repository *lua_repo = (luagit2_repository *)lua_touserdata(L, 1);
    
    lua_array = (luagit2_strarray *)lua_newuserdata(L, sizeof(*lua_array));
    luaL_getmetatable(L, "luagit2_strarray");
    
    lua_setmetatable(L, -2);
    
    git_strarray local_strarray;
    git_reference_list(&local_strarray,lua_repo->repo); 
    lua_array->array  = local_strarray;
    return 1;
}

static int lua_git_reference_lookup (lua_State *L) {
    luagit2_reference *lua_ref;
    const luagit2_repository *lua_repo = (luagit2_repository *)lua_touserdata(L, 1);
    const char *name = luaL_checkstring(L,2);

    lua_ref = (luagit2_reference *)lua_newuserdata(L, sizeof(*lua_ref));
    lua_ref->reference  = NULL;
 
    luaL_getmetatable(L, "luagit2_reference");
    
    lua_setmetatable(L, -2);
    
    git_reference *local_ref;
    git_reference_lookup(&local_ref,lua_repo->repo,name); 
    lua_ref->reference  = local_ref;
    return 1;
}

static int lua_git_reference_name (lua_State *L) {
	const luagit2_reference *lua_ref = (luagit2_reference *)lua_touserdata(L,1);
    const char *refname = git_reference_name(lua_ref->reference);
  
    lua_pushstring(L,refname);
    return 1;
}

static int lua_git_reference_name_to_id (lua_State *L) {
	luagit2_oid *obj_id;
	const luagit2_repository *lua_repo = (luagit2_repository *)lua_touserdata(L,1); 
    const char *name = luaL_checkstring(L,2);
	
    obj_id = (luagit2_oid *)lua_newuserdata(L, sizeof(*obj_id));

    luaL_getmetatable(L, "luagit2_oid");
    lua_setmetatable(L, -2);
    
    git_oid local_id;
    git_reference_name_to_id(&local_id,lua_repo->repo,name); 
   	obj_id->oid = local_id;
 
    return 1;
}

static int lua_git_reference_next (lua_State *L) {
    luagit2_reference *lua_ref;
    const luagit2_reference_iterator *lua_ref_iterator = (luagit2_reference_iterator *)lua_touserdata(L, 1);

    lua_ref = (luagit2_reference *)lua_newuserdata(L, sizeof(*lua_ref));
    lua_ref->reference  = NULL;
 
    luaL_getmetatable(L, "luagit2_reference");
    
    lua_setmetatable(L, -2);
    
    git_reference *local_ref;
    git_reference_next(&local_ref,lua_ref_iterator->iterator); 
    lua_ref->reference  = local_ref;
    return 1;
}

static int lua_git_reference_next_name (lua_State *L) {
    const luagit2_reference_iterator *lua_ref_iterator = (luagit2_reference_iterator *)lua_touserdata(L, 1);

    const char *next_name ;
    git_reference_next_name(&next_name,lua_ref_iterator->iterator); 
    lua_pushstring(L,next_name);
    return 1;
}

static int lua_git_reference_owner (lua_State *L) {
    luagit2_repository *lua_repo;
    const luagit2_reference *lua_ref = (luagit2_reference *)lua_touserdata(L,1);

    lua_repo = (luagit2_repository *)lua_newuserdata(L, sizeof(*lua_repo));
    lua_repo->repo  = NULL;

    luaL_getmetatable(L, "luagit2_repository");
    lua_setmetatable(L, -2);

    lua_repo->repo = git_reference_owner(lua_ref->reference);
    return 1;
}

static int lua_git_reference_peel (lua_State *L) {
    luagit2_object *lua_git_obj;
    const luagit2_reference *lua_ref = (luagit2_reference *)lua_touserdata(L,1);
    const luagit2_otype *type = (luagit2_otype *)lua_touserdata(L,2);

    lua_git_obj = (luagit2_object *)lua_newuserdata(L, sizeof(*lua_git_obj));
    lua_git_obj->object  = NULL;

    luaL_getmetatable(L, "luagit2_object");
    lua_setmetatable(L, -2);

    git_object *local_git_obj;
    git_reference_peel(&local_git_obj,lua_ref->reference,type->otype);
    lua_git_obj->object = local_git_obj; 
    return 1;
}

static int lua_git_reference_remove (lua_State *L) {
	const luagit2_repository *lua_repo = (luagit2_repository *)lua_touserdata(L,1); 
    const char *name = luaL_checkstring(L,2);

    git_reference_remove(lua_repo->repo,name); 
    return 1;
}

static int lua_git_reference_rename (lua_State *L) {
    luagit2_reference *lua_ref;
    const luagit2_reference *lua_ref_old = (luagit2_reference *)lua_touserdata(L, 1);
    const char *new_name = luaL_checkstring(L,2);
    const int force = luaL_checkinteger(L,3);
    const char *log_message = luaL_checkstring(L,4);

    lua_ref = (luagit2_reference *)lua_newuserdata(L, sizeof(*lua_ref));
    lua_ref->reference  = NULL;
 
    luaL_getmetatable(L, "luagit2_reference");
    
    lua_setmetatable(L, -2);
    
    git_reference *local_ref;
    git_reference_rename(&local_ref,lua_ref_old->reference,new_name,force,log_message); 
    lua_ref->reference  = local_ref;
    return 1;
}

static int lua_git_reference_resolve (lua_State *L) {
    luagit2_reference *lua_ref;
    const luagit2_reference *lua_ref_old = (luagit2_reference *)lua_touserdata(L, 1);

    lua_ref = (luagit2_reference *)lua_newuserdata(L, sizeof(*lua_ref));
    lua_ref->reference  = NULL;
 
    luaL_getmetatable(L, "luagit2_reference");
    
    lua_setmetatable(L, -2);
    
    git_reference *local_ref;
    git_reference_resolve(&local_ref,lua_ref_old->reference); 
    lua_ref->reference  = local_ref;
    return 1;
}

static int lua_git_reference_set_target (lua_State *L) {
    luagit2_reference *lua_ref;
    const luagit2_reference *lua_ref_old = (luagit2_reference *)lua_touserdata(L, 1);
    const luagit2_oid *lua_oid = (luagit2_oid *)lua_touserdata(L,2);
    const char *log_message = luaL_checkstring(L,3);

    lua_ref = (luagit2_reference *)lua_newuserdata(L, sizeof(*lua_ref));
    lua_ref->reference  = NULL;
 
    luaL_getmetatable(L, "luagit2_reference");
    
    lua_setmetatable(L, -2);
    
    git_reference *local_ref;
    git_reference_set_target(&local_ref,lua_ref_old->reference,&(lua_oid->oid),log_message); 
    lua_ref->reference  = local_ref;
    return 1;
}

static int lua_git_reference_symbolic_create (lua_State *L) {
    luagit2_reference *lua_ref;
    const luagit2_repository *lua_repo = (luagit2_repository *)lua_touserdata(L, 1);
    const char *name = luaL_checkstring(L,2);
    const char *target = luaL_checkstring(L,3);
    const int force = luaL_checkinteger(L,4);
    const char *log_message = luaL_checkstring(L,5);

    lua_ref = (luagit2_reference *)lua_newuserdata(L, sizeof(*lua_ref));
    lua_ref->reference  = NULL;
 
    luaL_getmetatable(L, "luagit2_reference");
    
    lua_setmetatable(L, -2);
    
    git_reference *local_ref;
    git_reference_symbolic_create(&local_ref,lua_repo->repo,name,target,force,log_message); 
    lua_ref->reference  = local_ref;
    return 1;
}

static int lua_git_reference_symbolic_create_matching (lua_State *L) {
    luagit2_reference *lua_ref;
    const luagit2_repository *lua_repo = (luagit2_repository *)lua_touserdata(L, 1);
    const char *name = luaL_checkstring(L,2);
    const char *target = luaL_checkstring(L,3);
    const int force = luaL_checkinteger(L,4);
    const char *current_value = luaL_checkstring(L,5);
    const char *log_message = luaL_checkstring(L,6);

    lua_ref = (luagit2_reference *)lua_newuserdata(L, sizeof(*lua_ref));
    lua_ref->reference  = NULL;
 
    luaL_getmetatable(L, "luagit2_reference");
    
    lua_setmetatable(L, -2);
    
    git_reference *local_ref;
    git_reference_symbolic_create_matching(&local_ref,lua_repo->repo,name,target,
    								force,current_value,log_message); 
    lua_ref->reference  = local_ref;
    return 1;
}

static int lua_git_reference_symbolic_set_target (lua_State *L) {
    luagit2_reference *lua_ref;
    const luagit2_reference *lua_ref_old = (luagit2_reference *)lua_touserdata(L, 1);
    const char *target = luaL_checkstring(L,2);
    const char *log_message = luaL_checkstring(L,3);

    lua_ref = (luagit2_reference *)lua_newuserdata(L, sizeof(*lua_ref));
    lua_ref->reference  = NULL;
 
    luaL_getmetatable(L, "luagit2_reference");
    
    lua_setmetatable(L, -2);
    
    git_reference *local_ref;
    git_reference_symbolic_set_target(&local_ref,lua_ref_old->reference,target,log_message); 
    lua_ref->reference  = local_ref;
    return 1;
}

static int lua_git_reference_symbolic_target (lua_State *L) {
    const luagit2_reference *lua_ref = (luagit2_reference *)lua_touserdata(L, 1);
    const char *target_symbolic = git_reference_symbolic_target(lua_ref->reference); 
    lua_pushstring(L,target_symbolic);
    return 1;
}

static int lua_git_reference_target (lua_State *L) {
    const luagit2_reference *lua_ref = (luagit2_reference *)lua_touserdata(L, 1);
    luagit2_oid *target_oid ;
	target_oid = (luagit2_oid *)lua_newuserdata(L, sizeof(*target_oid));

    luaL_getmetatable(L, "luagit2_oid");
    lua_setmetatable(L, -2);
    target_oid->oid = *(git_reference_target(lua_ref->reference)); 
    
    return 1;
}

static int lua_git_reference_target_peel (lua_State *L) {
    const luagit2_reference *lua_ref = (luagit2_reference *)lua_touserdata(L, 1);
    luagit2_oid *target_oid ;
    target_oid = (luagit2_oid *)lua_newuserdata(L, sizeof(*target_oid));

    luaL_getmetatable(L, "luagit2_oid");
    lua_setmetatable(L, -2);
    target_oid->oid = *(git_reference_target_peel(lua_ref->reference)); 

    return 1;
}

static int lua_git_reference_type (lua_State *L) {
    const luagit2_reference *lua_ref = (luagit2_reference *)lua_touserdata(L, 1);
    luagit2_ref_type *lua_ref_type ;
    lua_ref_type = (luagit2_ref_type *)lua_newuserdata(L, sizeof(*lua_ref_type));

    luaL_getmetatable(L, "luagit2_oid");
    lua_setmetatable(L, -2);
    lua_ref_type->ref_type = git_reference_type(lua_ref->reference); 

    return 1;
}

#endif
