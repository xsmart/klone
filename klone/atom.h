#ifndef _KLONE_ATOM_H_
#define _KLONE_ATOM_H_

#include <stdlib.h>
#include <u/libu.h>

/* global server-maintaned atom list */
typedef struct atom_s
{
    LIST_ENTRY(atom_s) np;  /* next & prev pointers         */
    char *id;               /* atom identifier              */
    char *data;             /* atom data block              */
    size_t size;            /* atom data block size         */
    void *arg;              /* opaque data                  */
} atom_t;

/* define atom list */
LIST_HEAD(atom_list_s, atom_s);
typedef struct atom_list_s atom_list_t;

struct atoms_s
{
    atom_list_t list;
    size_t size, count;
};

/* create an atom */
int atom_create(const char *id, const char *data, size_t size, void* arg, 
    atom_t**pa);
/* free an atom */
int atom_free(atom_t* atom);

/* atom_t list */
struct atoms_s;
typedef struct atoms_s atoms_t; 

/* create an atom list */
int atoms_create(atoms_t **);

/* free an atom list */
int atoms_free(atoms_t *);

/* sum of atoms size field */
size_t atoms_size(atoms_t *);

/* # of atoms */
size_t atoms_count(atoms_t *);

/* return the n-th atom */
int atoms_getn(atoms_t *, size_t n, atom_t**);

/* return the atom whose ID is id */
int atoms_get(atoms_t *, const char *id, atom_t**);

/* add an atom to the list */
int atoms_add(atoms_t *, atom_t*);

/* add an atom to the list */
int atoms_remove(atoms_t *, atom_t*);

#endif
