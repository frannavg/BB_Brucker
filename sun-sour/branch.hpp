/* ************************************************************************* */
/*                            Filename: Branch.hpp                           */
/*                                                                           */
/*  Export: Procedure Compute_Branchlist;                                    */
/*                    Calculation of Before- and After-Candidates of         */
/*                    the search tree node SonNode.                          */
/* ************************************************************************* */
#pragma once

#include "datastruct.hpp"

/* ************************************************************************* */
/*                      Procedure Compute_Branchlist()                       */
/*                                                                           */
/*  INPUT: -/-                                                               */
/*                                                                           */
/*                                                                           */
/*  FUNCTION: Calculation of the Before- and After-Candidates. They are      */
/*            in the order of non-decreasing heads/tails in SonNode->order.  */
/* ************************************************************************* */
void Compute_BranchList();
