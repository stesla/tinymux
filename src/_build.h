// _build.h
//
// $Id: _build.h,v 1.64 2002-02-14 09:13:10 sdennis Exp $
//
// MUX 2.1
// Copyright (C) 1998 through 2002 Solid Vertical Domains, Ltd. All
// rights not explicitly given are reserved. Permission is given to
// use this code for building and hosting text-based game servers.
// Permission is given to use this code for other non-commercial
// purposes. To use this code for commercial purposes other than
// building/hosting text-based game servers, contact the author at
// Stephen Dennis <sdennis@svdltd.com> for another license.
//

#ifndef MUX_BUILD_NUM
extern char szBuildNum[];
#define MUX_BUILD_NUM szBuildNum
#endif // MUX_BUILD_NUM

#ifndef MUX_BUILD_DATE
extern char szBuildDate[];
#define MUX_BUILD_DATE szBuildDate
#endif // MUX_BUILD_DATE

#define MUX_VERSION       "2.1.12.35"    // Version number
#define MUX_RELEASE_DATE  "2002-FEB-14" // Source release date

#define BETA              1             // Define if a BETA release
