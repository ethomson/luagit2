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

typedef struct {
	git_oid oid;
} luagit2_oid;

typedef struct {
	git_commit *commit;
} luagit2_commit;

typedef struct {
	git_signature *sign;
} luagit2_signature;

typedef struct {
	git_tree *tree;
} luagit2_tree;

typedef struct {
	git_repository *repo;
} luagit2_repository;

typedef struct {
	git_index *index;
} luagit2_index;

typedef struct {
	git_tree_entry *tree_entry;
} luagit2_tree_entry;

typedef struct {
	git_tree_update *tree_update;
} luagit2_tree_update;

typedef struct {
	git_object *object;
} luagit2_object;

typedef struct {
	git_otype otype;
} luagit2_otype;

typedef struct {
	git_filemode_t filemode;
} luagit2_filemode;

typedef struct {
	git_time_t time;
} luagit2_time;

typedef struct {
	git_reference *reference;
} luagit2_reference;

typedef struct {
	git_odb *odb;
} luagit2_odb;

typedef struct {
	git_worktree *worktree;
} luagit2_worktree;

typedef struct {
	git_refdb *refdb;
} luagit2_refdb;

typedef struct {
	git_reference_iterator *iterator;
} luagit2_reference_iterator;

typedef struct {
	git_strarray array;
} luagit2_strarray;

typedef struct {
	git_ref_t ref_type;
} luagit2_ref_type;

typedef struct {
	git_annotated_commit *annotated_commit;
} luagit2_annotated_commit;

typedef struct {
	git_branch_t branch_type;
} luagit2_branch_type;

typedef struct {
	git_branch_iterator *branch_iterator;
} luagit2_branch_iterator;

typedef struct {
	git_blame *blame;
} luagit2_blame;

typedef struct {
	git_blame_hunk *blame_hunk;
} luagit2_blame_hunk;

typedef struct {
	git_blob *blob;
} luagit2_blob;

typedef struct {
	git_off_t size;
} luagit2_off_t;

typedef struct {
	git_index_entry *index_entry;
} luagit2_index_entry;

typedef struct {
	git_index_conflict_iterator *index_conflict_iterator;
} luagit2_index_conflict_iterator;

#endif
