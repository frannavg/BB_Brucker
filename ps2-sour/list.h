/* ************************************************************************* */
/*                           Filename: List.h                                */
/*                                                                           */
/*  EXPORT: Procedure Insert:          Append an element at the end of a list*/
/*          Procedure InsertBefore:    Append an element at the beginning of */
/*                                     a list                                */
/*          Procedure Delete:          Delete an element from a list         */
/*          Procedure Makeempty:       Delete all elements from a list       */
/*          Procedure Member:          Check whether an element is in a list */
/*          Procedure PrintList:       Print list on screen                  */
/*          Procedure Update_DisjArcs: Updating of fixed disjunctive arcs    */
/*                                     during the backtracking               */
/* ************************************************************************* */

#ifndef _LIST_H
#define _LIST_H

#include "datastruct.h"

/* ************************************************************************* */
/*                          Procedure  Insert()                              */
/*                                                                           */
/*  INPUT : l          linked list of integers                               */ 
/*          Op         integer                                               */ 
/*                                                                           */
/*  FUNCTION: Op is appended at the end of l if member(l,Op) == false        */
/* ************************************************************************* */

struct List *Insert ();


/* ************************************************************************* */
/*                          Procedure  InsertBefore()                        */
/*                                                                           */
/*  INPUT : l          linked list of integers                               */
/*          Op         integer                                               */
/*                                                                           */
/*  FUNCTION: Op is appended at the begining of l                            */
/* ************************************************************************* */

struct List *InsertBefore ();


/* ************************************************************************* */
/*                          Procedure  Delete()                              */
/*                                                                           */
/*  INPUT : l          linked list of integers                               */
/*          Op         integer                                               */
/*                                                                           */
/*  FUNCTION: Op is deleted from l                                           */
/* ************************************************************************* */

struct List *Delete ();


/* ************************************************************************* */
/*                          Procedure  Makeempty()                           */
/*                                                                           */
/*  INPUT : l          linked list of integers                               */
/*                                                                           */
/*  FUNCTION: l is deleted                                                   */
/* ************************************************************************* */

struct List *Makeempty ();


/* ************************************************************************* */
/*                          Procedure  member()                              */
/*                                                                           */
/*  INPUT : l          linked list of integers                               */
/*          Op         integer                                               */
/*                                                                           */
/*  FUNCTION: Check whether Op is in l or not                                */
/* ************************************************************************* */

boolean Member ();


/* ************************************************************************* */
/*                        Procedure Update_DisjArcs()                        */
/*                                                                           */
/*  INPUT : -/-                                                              */
/*                                                                           */
/*  FUNCTION: Deletes all invalid disjunctive arcs in ActualNode during      */
/*            the backtracking.                                              */
/* ************************************************************************* */

void Update_DisjArcs ();

#endif
