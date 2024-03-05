//**************************************************************************/
//                                                                        **/
//                         E X E I D E N T . H                            **/
//                                                                        **/
//**************************************************************************/
//                                                                        **/
//                  Copyrights(c) 2022 by KNORR-BREMSE,                   **/
//             Systeme fuer Schienenfahrzeuge GmbH, Muenchen              **/
//                                                                        **/
//! Project  :    ESRA-BSW3G55xx                                          **/
//! @date     :    27.06.2011                                             **/
//! @author   :    A. Tenkeu                                              **/
//! @aompiler :    DIAB                                                   **/
//                                                                        **/
//**************************************************************************/
// Content: Interface definition for corresponding source file            **/
//          ( file-include, constants, macros, types, global data,        **/
//            functions and their parameters)                             **/
//**************************************************************************/
// Date       Author      Changes:                                        **/
// 27.06.2011 A. Tenkeu   Start                                           **/
// 24.11.2022 J. Lulli    Coding guidelines alignment                     **/
//**************************************************************************/

#ifndef EXEIDENT_H
#define EXEIDENT_H

//************************* Header / include files **************************/
// #include */
#include "std_defs.h"
//#include "ccchws.h"                   /* Definitions of service ccc in fwr*/
//********************* Constant / macro definitions ************************/
// #define */

//*************************** Type definitions ******************************/
// typedef */

// Definition of programm identification -----------------------------------*/

// Access type to version information of LIB or ELF/BIN file */
typedef struct
{
        U8  au8Identification[32];
        U32 u32VersionIdentStruct;
        U8  au8Copyright[32];
        U8  au8ShortName[9];
        U8  au8Description[33];
        U16 u16SWType;
        U8  au8STN[16];
        U8  au8Version[13];
        U8  au8Date[11];
        U32 u32BuildID1;
        U32 u32DummyBuildID1;
        const U32* pu32CCCSegDef;
}C_SW_ID;

// Access to compatibility table of of LIB or ELF/BIN file */
typedef struct
{
        U8  au8STN[12];
        U16 u16SwType;
        U16 u16Versions;
        U16 u16Logic;
        U32 u32VersionDescriptor;
}C_COMPTAB;

// Access type to administration information of LIB or ELF/BIN file */
typedef struct
{
        const C_SW_ID cSWId;
        const U8** ppu8CompTab;
}C_EXE_IDENT;

//************************ Global data declarations *************************/
// extern */
extern const U8* pu8CompTabExe;
#endif
//* EndOfFile EXEIDENT.H ****************************************************/
