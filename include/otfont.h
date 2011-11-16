/*****************************************************************************
 *
 *  otfont.h - OpenType "abstract" font objects.
 *
 *  Copyright (C) 2002 Monotype Imaging Inc. All rights reserved.
 *
 *  $Archive:   I:/BULL/DisplayImaging/archives/wtle/product/source/include/otfont.h_v  $ 
 *  $Date:   May 16 2005 15:18:26  $
 *  $Revision:   1.4  $
 *
 ****************************************************************************/

#ifndef OTFONT_H
#define OTFONT_H

#include "ts2d.h"
#include "tsfixed.h"
#include "tstypes.h"

TS_BEGIN_HEADER

/******************************************************************************
 *
 *  Summary:
 *      "Abstract" class providing limited font access ("virtual") functions
 *      to OpenType Layout Manager operations.
 *
 *  Description:
 *      This is an "abstract" class providing for an object which allows
 *      limited access to the client font for several OpenType Layout Manager
 *      operations.  The functions requiring such an object are:
 *          TsOtLayoutManager_findOtLayout()
 *          TsOtLayoutManager_deleteOtLayout()
 *          TsOtLayoutManager_deleteAllForFont()
 *
 *      This object will be managed by the user and must be initialized
 *      prior to calling the above-listed functions.
 *
 *      The members of the class are defined as follows:
 *          fontData -      pointer to a user-defined font object or handle
 *                          that will be passed as the first argument to all
 *                          of the user-defined "virtual" functions.
 *          holdHandle -    pointer to a function allowing user-defined
 *                          reference counting.  Called when a copy of
 *                          this object is stored for "long-term" access.
 *          releaseHandle - pointer to a function allowing user-defined
 *                          reference counting.  Called when a copy of
 *                          this object is removed from "long-term" storage.
 *          compare -       pointer to a function to compare two user-defined
 *                          font handles or objects.  Two font handles
 *                          will be passed to the function, and the function
 *                          should return TRUE if the fonts are considered
 *                          the same or equal, FALSE otherwise.
 *          getTable -      pointer to a function that will return a pointer
 *                          to the argument-specified OpenType table.  The
 *                          requested table will be identified by a standard
 *                          OpenType tag.  Currently used tags are "GDEF",
 *                          "GSUB", and "GPOS".  The user may implement
 *                          reference counting with this function, also.  A
 *                          single "long-term" reference to this table will
 *                          be stored until the "releaseTable" function is
 *                          called.  The OpenType table will be accessed as
 *                          a TsUInt8 array.  Byte swapping will be handled
 *                          by the library, if necessary.
 *          releaseTable -  pointer to a function that allows the release of
 *                          a table previously acquired with the "getTable"
 *                          function, allowing user-defined reference counting.
 *                          This function will be called with a pointer to
 *                          the table when the table is no longer needed in
 *                          "long-term" storage.
 *
 *      All members of this object are required to have valid, non-NULL
 *      pointers.
 *
 *  <GROUP opentype>
 */
typedef struct
{
    void  *fontData;
    void   (*holdHandle)(void *fontData);
    void   (*releaseHandle)(void *fontData);
    TsBool   (*compare)(void *fontData, void *fontDataOther);
    void  *(*getTable)(void *fontData, TsUInt32 tag /* GDEF,GSUB,GPOS */);
    TsResult (*releaseTable)(void *fontData, void *table);

} TsOtFont;

/* ------------------------------------------------------------------------- */

/******************************************************************************
 *
 *  Summary:
 *      "Abstract" class providing limited scaled font access ("virtual")
 *      functions to the OpenType Layout GPOS shaping/positioning operations.
 *
 *  Description:
 *      This is an "abstract" class providing for an object which allows
 *      limited access to the client scaled font for several OpenType Layout
 *      GPOS shaping/positioning operations.  The function requiring such an
 *      object is:
 *          TsOtLayout_shape
 *
 *      This object will be managed by the user and must be initialized
 *      prior to calling the above-listed function.
 *
 *      The members of the class are defined as follows:
 *          sclaedFontData -        pointer to a user-defined scaled font
 *                                  object or handle that will be passed as
 *                                  the first argument to all of the
 *                                  user-defined "virtual" functions.
 *          designUnits2Pixels -    pointer to a function that converts font
 *                                  design units to pixels.  The arguments are
 *                                  "x" and "y" coordinate values in design
 *                                  units and two pointers to TsFixed types
 *                                  which should contain the "x" and "y"
 *                                  coordinate values in pixels upon return.
 *                                  Note: TsFixed is a fixed-point floating
 *                                  type, 32 bits, with 16 bit whole and 16 bit
 *                                  fractional components.
 *          getXSize -              pointer to a function that is expected to
 *                                  return a TsFixed value for the "x" axis
 *                                  pixels per EM size of the scaled font.
 *          getYSize -              pointer to a function that is expected to
 *                                  return a TsFixed value for the "y" axis
 *                                  pixels per EM size of the scaled font.
 *          getGPOSpoint -          pointer to a function that may be set to
 *                                  NULL.  If a non-NULL, valid function
 *                                  pointer is provided, this will allow for
 *                                  more accurate positioning of some glyphs,
 *                                  as defined in the font GPOS tables.  The
 *                                  function takes as arguments a glyph ID and
 *                                  and an index to a point on the original
 *                                  glyph outline, as defined in the font.
 *                                  There are two pointers to TsCoord types
 *                                  which will be expected upon successful
 *                                  return from the function to
 *                                  contain the "x" and "y" pixel coordinate
 *                                  values of the specified glyph/point
 *                                  combination, post scaling/transformation.
 *                                  The "x" and "y" pixel coordinate values
 *                                  will be treated as fixed-point floating
 *                                  type, 32 bits, with 26 bit whole and 6 bit
 *                                  fractional components.
 *                                  The return value of the function is a
 *                                  TsBool where TRUE indicates success, FALSE
 *                                  otherwise.
 *
 *      All members of this object except the "getGPOSpoint" function pointer
 *      are required to have valid, non-NULL pointers.
 *
 *  <GROUP opentype>
 */
typedef struct
{
    void *scaledFontData;
    void  (*designUnits2Pixels)(void *scaledFontData,
                                  TsInt16 x_des_units, TsInt16 y_des_units,
                                  TsFixed *x_pixels, TsFixed *y_pixels);
    TsFixed (*getXSize)(void *scaledFontData);     /* return pixels per EM */
    TsFixed (*getYSize)(void *scaledFontData);     /* return pixels per EM */
    TsBool  (*getGPOSpoint)(void *scaledFontData,
                            TsUInt16 glyphIndex, TsUInt16 pointIndex,
                            TsCoord *x_pixels /* F26DOT6 */,
                            TsCoord *y_pixels /* F26DOT6 */); /* may be NULL */

} TsOtScaledFont;

TS_END_HEADER

#endif /* OTFONT_H */
