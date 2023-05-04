/*
 * container_template.h
 *
 * This file defines a bare-bones QTFF file. It is set up with a single track of uncompressed video
 * with the following parameters:
 *
 * Many of the fields in this template will need to be modified at run-time, for example the creation
 * time should be taken from the RTC.
 *
 * File
 *  ╷
 *  ├─ ftyp
 *  │
 *  ├─ moov
 *  │   ╷
 *  │   ├─ mvhd
 *  │   │
 *  │   ├─ mvex
 *  │   │   ╷
 *  │   │   ├─ mehd
 *  │   │   │
 *  │   │   └─ trex
 *  │   │
 *  │   └─ trak
 *  │       ╷
 *  │       ├─ tkhd
 *  │       │
 *  │       └─ mdia
 *  │           ╷
 *  │           ├─ mdhd
 *  │           │
 *  │           ├─ hdlr
 *  │           │
 *  │           └─ minf
 *  │               ╷
 *  │               ├─ vmhd
 *  │               │
 *  │               └─ hdlr
 *  └─ mdat
 *
 *
 *  Created on: 7 Feb 2023
 *      Author: Frank Plowman <post@frankplowman.com>
 */

#ifndef CONTAINER_TEMPLATE_H_
#define CONTAINER_TEMPLATE_H_

// stdlib includes
#include <stdbool.h>

// library includes
#define MuTFF_MAX_TRACK_ATOMS 1
#define MuTFF_MAX_USER_DATA_ITEMS 1
#include "mutff.h"
#include "mutff_default.h"

// project includes
#include "container.h"

const MuTFFVideoSampleDescription video_sample_desc_template = {
    0,                                 // version
    MuTFF_FOURCC('G', 'D', 'P', '4'),  // vendor
    0,                                 // temporal quality
    0,                                 // spatial quality
    0,                                 // width
    0,                                 // height
    {
        72, 0                          // horizontal resolution
    },
    {
        72, 0                          // vertical resolution
    },
    1,                                 // frame count
    {                                  // compressor name
        'O', 'V', '5', '6', '4', '0', ' ', 'J', 'P', 'E', 'G',
    },
    0,                                 // depth
    -1                                 // color table id
};

const MuTFFSampleDescription sample_desc_template = {
    MuTFF_FOURCC('j', 'p', 'e', 'g'),  // Data format
    1,                                 // Data reference index
    {video_sample_desc_template},
};

const MuTFFSampleDescriptionAtom stsd_template = {
    0,  // Version
    0,  // Flags
    1,  // Number of entries
    {   // Entries
        sample_desc_template
    }
};

const MuTFFTimeToSampleAtom stts_template = {
    0,                         // Version
    0,                         // Flags
    0,                         // Number of entries
    {}                         // Entries
};

const MuTFFSampleToChunkAtom stsc_template = {
    0,  // Version
    0,  // Flags
    0,  // Number of entries
    {}  // Entries
};

const MuTFFSampleSizeAtom stsz_template = {
    0,            // Version
    0,            // Flags,
    0,            // Sample size
    0,            // Number of entries
    {}            // Entries
};

const MuTFFChunkOffsetAtom stco_template = {
    0,  // Version
    0,  // Flags
    0,  // Number of entries
    {}  // Entries
};

const MuTFFSampleTableAtom stbl_template = {
    stsd_template,  // stsd
    stts_template,  // stts
    false,          // ctts present
    {},             // ctts
    false,          // cslg present
    {},             // cslg
    false,          // stss present
    {},             // stss
    false,          // stps present
    {},             // stps
    true,           // stsc present
    stsc_template,  // stsc
    true,           // stsz present
    stsz_template,  // stsz
    true,           // stco present
    stco_template,  // stco
    false,          // sdtp present
    {}              // sdtp
};

const MuTFFDataReference data_ref_template = {
    MuTFF_FOURCC('u', 'r', 'l', ' '),  // Type
    0,                                 // Version
    1,                                 // Flags
    0,                                 // Data size
    {}                                 // Data
};

const MuTFFDataReferenceAtom dref_template = {
    0,  // Version
    0,  // Flags
    1,  // Number of entries
    {   // Data references
        data_ref_template
    }
};

const MuTFFDataInformationAtom dinf_template = {
    dref_template,
};

const MuTFFHandlerReferenceAtom minf_hdlr_template = {
    0,                                 // Version
    0,                                 // Flags
    MuTFF_FOURCC('m', 'h', 'l', 'r'),  // Component type
    MuTFF_FOURCC('v', 'i', 'd', 'e'),  // Component subtype
    0,                                 // Component manufacturer
    0,                                 // Component flags
    0,                                 // Component flags mask
    ""                                 // Component name
};

const MuTFFVideoMediaInformationHeaderAtom vmhd_template = {
    0,          // Version
    1,          // Flags
    0,          // Graphics mode
    {
        0,  // opcolor[0]
        0,  // opcolor[1]
        0   // opcolor[2]
    }
};

const MuTFFVideoMediaInformationAtom minf_template = {
    vmhd_template,       // vmhd
    minf_hdlr_template,  // hdlr
    true,                // dinf present
    dinf_template,       // dinf
    true,                // stbl present
    stbl_template        // stbl
};

const MuTFFHandlerReferenceAtom mdia_hdlr_template = {
    0,                                 // Version
    0,                                 // Flags
    MuTFF_FOURCC('m', 'h', 'l', 'r'),  // Component type
    MuTFF_FOURCC('v', 'i', 'd', 'e'),  // Component subtype
    0,                                 // Component manufacturer
    0,                                 // Component flags
    0,                                 // Component flags mask
    ""                                 // Component name
};

const MuTFFMediaHeaderAtom mdhd_template = {
    0,           // Version
    0,           // Flags
    0,           // Creation time
    0,           // Modification time
    0,           // Time scale
    0,           // Duration
    0,           // Language
    0,           // Quality
};

const MuTFFMediaAtom mdia_template = {
    mdhd_template,       // mdhd
    false,               // elng present
    {},
    true,                // hdlr present
    mdia_hdlr_template,
    true,                // minf present
    minf_template,
    {},
    {},
    false,               // udta present
    {}
};

const MuTFFTrackHeaderAtom tkhd_template = {
    0,                          // Version
    0,                          // Flags
    0,                          // Creation time
    0,                          // Modification time
    1,                          // Track ID
    0,                          // Duration
    0,                          // Layer
    0,                          // Alternate group
    {1, 0},                     // Volume
    {                           // Matrix structure
        {1, 0}, {0, 0}, {0, 0},
        {0, 0}, {1, 0}, {0, 0},
        {0, 0}, {0, 0}, {1, 0}
    },
    {0, 0},                     // Track width
    {0, 0}                      // Track height
};

const MuTFFTrackAtom trak_template = {
    tkhd_template,
    mdia_template,
    false,          // tapt present
    {},
    false,          // clip present
    {},
    false,          // matt present
    {},
    false,          // edts present
    {},
    false,          // tref present
    {},
    false,          // txas present
    {},
    false,          // load present
    {},
    false,          // imap present
    {},
    false,          // udta present
    {}
};

const MuTFFMovieHeaderAtom mvhd_template = {
    0,                           // Version
    0,                           // Flags
    0,                           // Creation time
    0,                           // Modification time
    0,                           // Frames per second
    0,                           // Duration
    {1, 0},                      // Preferred rate
    {1, 0},                      // Preferred volume
    {                            // Matrix structure
        {1, 0}, {0, 0}, {0, 0},
        {0, 0}, {1, 0}, {0, 0},
        {0, 0}, {0, 0}, {1, 0}
    },
    0,                           // Preview time
    0,                           // Preview duration
    0,                           // Poster time
    0,                           // Selection time
    0,                           // Selection duration
    0,                           // Current time
    0                            // Next track ID
};

const MuTFFTrackExtendsAtom trex_template = {
    0,  // version
    0,  // flags
    1,  // track ID
    1,  // default sample description index
    1,  // default sample duration
    0,  // default sample size
    0,  // default sample flags
};

const MuTFFMovieExtendsAtom mvex_template = {
    false,
    (MuTFFMovieExtendsHeaderAtom) {1, 0, 0},
    1,
    {
        trex_template,
    }
};

const MuTFFMovieAtom moov_template = {
    mvhd_template,          // mvhd
    1,                      // trak count
    {                       // trak
        trak_template,  // trak[0]
    },
    false,                  // clip present
    {},                     // clip
    false,                  // ctab present
    {},                     // ctab
    false,                  // udta present
    {},                      // udta
    true,
    mvex_template,
};

const MuTFFFileTypeAtom ftyp_template = {
    MuTFF_FOURCC('m', 'p', '4', '1'),          // Major brand
    MuTFF_FOURCC(20, 16, 9, 0),                // Minor version
    0,                                         // Compatible brands count
    {                           // Compatible brands
    }
};

const MuTFFMovieFile file_template = {
    true,           // ftyp present
    ftyp_template,  // ftyp
    moov_template,  // moov
    0,              // mdat count
    {},             // mdat
    0,              // moof count
    {},             // moof
    0,              // free count
    {},             // free
    0,              // skip count
    {},             // skip
    0,              // wide count
    {},             // wide
    false,          // preview present
    {}              // preview
};

#endif  // CONTAINER_TEMPLATE_H_
