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
#pragma once

#include "datastruct.hpp"

/* ************************************************************************* */
/*                          Procedure  Insert()                              */
/*                                                                           */
/*  INPUT : l          linked list of integers                               */
/*          Op         integer                                               */
/*                                                                           */
/*  FUNCTION: Op is appended at the end of l if member(l,Op) == false        */
/* ************************************************************************* */
List *Insert(List *, int);

/* ************************************************************************* */
/*                          Procedure  InsertBefore()                        */
/*                                                                           */
/*  INPUT : l          linked list of integers                               */
/*          Op         integer                                               */
/*                                                                           */
/*  FUNCTION: Op is appended at the begining of l                            */
/* ************************************************************************* */
List *InsertBefore(List *, int);

/* ************************************************************************* */
/*                          Procedure  Delete()                              */
/*                                                                           */
/*  INPUT : l          linked list of integers                               */
/*          Op         integer                                               */
/*                                                                           */
/*  FUNCTION: Op is deleted from l                                           */
/* ************************************************************************* */
List *Delete(List *, int);

/* ************************************************************************* */
/*                          Procedure  Makeempty()                           */
/*                                                                           */
/*  INPUT : l          linked list of integers                               */
/*                                                                           */
/*  FUNCTION: l is deleted                                                   */
/* ************************************************************************* */
List *Makeempty(List *);

/* ************************************************************************* */
/*                          Procedure  member()                              */
/*                                                                           */
/*  INPUT : l          linked list of integers                               */
/*          Op         integer                                               */
/*                                                                           */
/*  FUNCTION: Check whether Op is in l or not                                */
/* ************************************************************************* */
bool Member(List *, int);
 
/* ************************************************************************* */
/*                        Procedure Update_DisjArcs()                        */
/*                                                                           */
/*  INPUT : -/-                                                              */
/*                                                                           */
/*  FUNCTION: Deletes all invalid disjunctive arcs in ActualNode during      */
/*            the backtracking.                                              */
/* ************************************************************************* */
void Update_DisjArcs();
