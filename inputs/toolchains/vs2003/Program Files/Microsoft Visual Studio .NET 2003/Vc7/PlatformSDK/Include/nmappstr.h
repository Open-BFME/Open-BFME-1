//****************************************************************************
//  Module:     SDK
//  File:       NMAPPSTR.H
//  Content:    
//              
//
//  Copyright (c) Microsoft Corporation 1999-2002
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************

#ifndef _NM_APPLET_STRINGS_H_
#define _NM_APPLET_STRINGS_H_

//
// This is used to register applets such that the NetMeeting process knows
// how to launch the applet process.
//

//
// Registry folder for applets.
//

#define NM_APPLET_KEY TEXT("SOFTWARE\\Microsoft\\Conferencing\\T.120 Applets")

//
// Registry sub-folders for applets with standard keys.
//

#define NM_STD_KEY_TYPE     TEXT("Object Key")

//
// Registry sub-folders for applets with non-standard keys.
//

#define NM_NONSTD_KEY_TYPE  TEXT("NonStd Key")

//
// Registry keys for applets
//

#define NM_REGVAL_APP_PATH      TEXT("Path")            // required
#define NM_REGVAL_CMD_LINE      TEXT("CmdLine")         // optional
#define NM_REGVAL_CURR_DIR      TEXT("Directory")       // optional
#define NM_REGVAL_MANUFACTURER  TEXT("Manufacturer")    // optional
#define NM_REGVAL_PRODUCT_NAME  TEXT("ProductName")     // optional
#define NM_REGVAL_DESCRIPTION   TEXT("Description")     // optional

//
// Environment variables for invoke information
//

#define NM_ENV_NODE_ID          TEXT("_node_id")    // conference ID
#define NM_ENV_CONF_ID          TEXT("_conf_id")    // initiator's node ID


#endif // _NM_APPLET_STRINGS_H_

