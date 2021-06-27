/* ************************************************************************* */
/*                            Filename: Branch.h                             */
/*                                                                           */
/*  Export: Procedure Compute_Branchlist;                                    */
/*                    Calculation of Before- and After-Candidates of         */
/*                    the search tree node SonNode.                          */ 
/* ************************************************************************* */

#ifndef _BRANCH_H
#define _BRANCH_H

#include "datastruct.h"


/* ************************************************************************* */
/*                      Procedure Compute_Branchlist()                       */
/*                                                                           */
/*  INPUT: -/-                                                               */
/*                                                                           */
/*                                                                           */
/*  FUNCTION: Calculation of the Before- and After-Candidates. They are      */
/*            in the order of non-decreasing heads/tails in SonNode->order.  */
/* ************************************************************************* */

void Compute_BranchList ();

#endif

