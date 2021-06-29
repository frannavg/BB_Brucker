/* ************************************************************************* */
/*                       Filename: Datastruct.h                              */
/*                                                                           */
/*    Export: Global constants and datastructures                            */
/* ************************************************************************* */

#ifndef _DATASTRUCT_H
#define _DATASTRUCT_H
#define MaxNumOfOperations  310
#define MaxNumOfMachines     17
#define MaxNumOfJobs         32
#define MaxOpProMachine      32
#define true                  1
#define false                 0
#define NIL                   0
#define MaxInt            32000

typedef int boolean;        


struct List  {
                int          number;
                struct List  *next;
             };


struct Operation  {
                     int process_time;
                     int machine_nr;
                  };


struct ArcList  {
                  struct List  *pred[MaxNumOfOperations+1],
                               *succ[MaxNumOfOperations+1];
                };


struct BlockList  {
                    struct List       *elements;
                    struct BlockList  *next;
                    int               last_of_block;
                    char              fi_mi_la;     /* first - middle - last */
                  };


struct BranchList  {
                     int                branch_op;
                     char               before_or_after;
                     struct BranchList  *next;
                   };

struct NodeType  {
                    int                num_of_succ[MaxNumOfOperations+1],
				       num_of_pred[MaxNumOfOperations+1],
                                       lower_bound;
                    struct BlockList   *blocks;
                    struct BranchList  *order;
                 };


struct StackElement  {
                       struct NodeType       *node;
                       struct StackElement   *next;
                     };


#endif

