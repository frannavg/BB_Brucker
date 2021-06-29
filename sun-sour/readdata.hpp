/* ************************************************************************* */
/*                            Filename: ReadData.h                           */
/*                                                                           */
/*     EXPORT: Procedure Read_Data: Read data from file 'FileName'           */
/* ************************************************************************* */
#pragma once

#include "datastruct.hpp"

/* ************************************************************************* */
/*                           Procedure      Read_Data()                      */
/*                                                                           */
/*   INPUT:  FileName:    file which contains the data of the problem        */
/*                                                                           */
/*   FUNCTION: Reads data from file and stores it in global variables.       */
/*             If the file-read is correct Read_Data returns TRUE.           */
/* ************************************************************************* */
bool Read_Data(char *);
