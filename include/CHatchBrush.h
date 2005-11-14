/*
 * CHatchBrush.h - Hatch brush header.
 *
 * Copyright (C) 2005  Free Software Foundation, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef _C_HATCHBRUSH_H_
#define _C_HATCHBRUSH_H_

#include "CBrush.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _tagCHatchBrush
{
	CBrush      _base;
	CHatchStyle style;
	CColor      foreground;
	CColor      background;
};

#define CHatchStyle_IsValid(style) \
	(((style) >= CHatchStyle_Min) && ((style) <= CHatchStyle_Max))

#define CHatchBrush_DataFormat   PIXMAN_FORMAT_NAME_ARGB32
#define CHatchBrush_StyleWidth   8
#define CHatchBrush_StyleHeight  8
#define CHatchBrush_StylesLength (sizeof(CHatchBrush_HatchInfo) / 8)

#define CHatchBrush_StyleToData_SetRow(src, dst, fg, bg)                      \
	do {                                                                       \
		/* get the current source row */                                       \
		const CByte row = *(src);                                             \
		                                                                       \
		/* set the current data row */                                         \
		*(dst)++ = ((row & 0x80) ? (fg) : (bg));                               \
		*(dst)++ = ((row & 0x40) ? (fg) : (bg));                               \
		*(dst)++ = ((row & 0x20) ? (fg) : (bg));                               \
		*(dst)++ = ((row & 0x10) ? (fg) : (bg));                               \
		*(dst)++ = ((row & 0x08) ? (fg) : (bg));                               \
		*(dst)++ = ((row & 0x04) ? (fg) : (bg));                               \
		*(dst)++ = ((row & 0x02) ? (fg) : (bg));                               \
		*(dst)++ = ((row & 0x01) ? (fg) : (bg));                               \
		                                                                       \
		/* move to the next row */                                             \
		++src;                                                                 \
	} while(0)

#define CHatchBrush_StyleToData(style, data, stride, foreground, background)  \
	do {                                                                       \
		/* declarations */                                                     \
		const CByte  *src;                                                    \
		CColor       *dst;                                                    \
		CColor        fg;                                                     \
		CColor        bg;                                                     \
		                                                                       \
		/* get the source pixel row pointer */                                 \
		src = CHatchBrush_Styles[(style)];                                    \
		                                                                       \
		/* NOTE: pixman's format is native endian */                           \
		                                                                       \
		/* get the destination pixel pointer */                                \
		dst = ((CColor *)(data));                                             \
		                                                                       \
		/* get the foreground color */                                         \
		fg = (foreground);                                                     \
		                                                                       \
		/* get the background color */                                         \
		bg = (background);                                                     \
		                                                                       \
		/* set the data, row by row */                                         \
		CHatchBrush_StyleToData_SetRow(src, dst, fg, bg);                     \
		(data) += (stride);                                                    \
		dst = ((CColor *)(data));                                             \
		CHatchBrush_StyleToData_SetRow(src, dst, fg, bg);                     \
		(data) += (stride);                                                    \
		dst = ((CColor *)(data));                                             \
		CHatchBrush_StyleToData_SetRow(src, dst, fg, bg);                     \
		(data) += (stride);                                                    \
		dst = ((CColor *)(data));                                             \
		CHatchBrush_StyleToData_SetRow(src, dst, fg, bg);                     \
		(data) += (stride);                                                    \
		dst = ((CColor *)(data));                                             \
		CHatchBrush_StyleToData_SetRow(src, dst, fg, bg);                     \
		(data) += (stride);                                                    \
		dst = ((CColor *)(data));                                             \
		CHatchBrush_StyleToData_SetRow(src, dst, fg, bg);                     \
		(data) += (stride);                                                    \
		dst = ((CColor *)(data));                                             \
		CHatchBrush_StyleToData_SetRow(src, dst, fg, bg);                     \
		(data) += (stride);                                                    \
		dst = ((CColor *)(data));                                             \
		CHatchBrush_StyleToData_SetRow(src, dst, fg, bg);                     \
	} while(0)

static const CByte CHatchBrush_Styles[][8] =
{
	/* CHatchStyle_Horizontal */
	{ 0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },

	/* CHatchStyle_Vertical */
	{ 0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01 },

	/* CHatchStyle_ForwardDiagonal */
	{ 0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80 },

	/* CHatchStyle_BackwardDiagonal */
	{ 0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01 },

	/* CHatchStyle_Cross */
	{ 0xFF,0x01,0x01,0x01,0x01,0x01,0x01,0x01 },

	/* CHatchStyle_DiagonalCross */
	{ 0x81,0x42,0x24,0x18,0x18,0x24,0x42,0x81 },

	/* CHatchStyle_Percent05 */
	{ 0x01,0x00,0x00,0x00,0x10,0x00,0x00,0x00 },

	/* CHatchStyle_Percent10 */
	{ 0x01,0x00,0x10,0x00,0x01,0x00,0x10,0x00 },

	/* CHatchStyle_Percent20 */
	{ 0x11,0x00,0x44,0x00,0x11,0x00,0x44,0x00 },

	/* CHatchStyle_Percent25 */
	{ 0x11,0x44,0x11,0x44,0x11,0x44,0x11,0x44 },

	/* CHatchStyle_Percent30 */
	{ 0x55,0x22,0x55,0x88,0x55,0x22,0x55,0x88 },

	/* CHatchStyle_Percent40 */
	{ 0x55,0xAA,0x55,0x8A,0x55,0xAA,0x55,0xA8 },

	/* CHatchStyle_Percent50 */
	{ 0x55,0xAA,0x55,0xAA,0x55,0xAA,0x55,0xAA },

	/* CHatchStyle_Percent60 */
	{ 0x77,0xAA,0xDD,0xAA,0x77,0xAA,0xDD,0xAA },

	/* CHatchStyle_Percent70 */
	{ 0xEE,0xBB,0xEE,0xBB,0xEE,0xBB,0xEE,0xBB },

	/* CHatchStyle_Percent75 */
	{ 0xEE,0xFF,0xBB,0xFF,0xEE,0xFF,0xBB,0xFF },

	/* CHatchStyle_Percent80 */
	{ 0xF7,0xFF,0x7F,0xFF,0xF7,0xFF,0x7F,0xFF },

	/* CHatchStyle_Percent90 */
	{ 0xFF,0xFF,0xFF,0xEF,0xFF,0xFF,0xFF,0xFE },

	/* CHatchStyle_LightDownwardDiagonal */
	{ 0x11,0x22,0x44,0x88,0x11,0x22,0x44,0x88 },

	/* CHatchStyle_LightUpwardDiagonal */
	{ 0x88,0x44,0x22,0x11,0x88,0x44,0x22,0x11 },

	/* CHatchStyle_DarkDownwardDiagonal */
	{ 0x33,0x66,0xCC,0x99,0x33,0x66,0xCC,0x99 },

	/* CHatchStyle_DarkUpwardDiagonal */
	{ 0xCC,0x66,0x33,0x99,0xCC,0x66,0x33,0x99 },

	/* CHatchStyle_WideDownwardDiagonal */
	{ 0x83,0x07,0x0E,0x1C,0x38,0x70,0xE0,0xC1 },

	/* CHatchStyle_WideUpwardDiagonal */
	{ 0xC1,0xE0,0x70,0x38,0x1C,0x0E,0x07,0x83 },

	/* CHatchStyle_LightVertical */
	{ 0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11 },

	/* CHatchStyle_LightHorizontal */
	{ 0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00 },

	/* CHatchStyle_NarrowVertical */
	{ 0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA },

	/* CHatchStyle_NarrowHorizontal */
	{ 0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00 },

	/* CHatchStyle_DarkVertical */
	{ 0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33 },

	/* CHatchStyle_DarkHorizontal */
	{ 0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00 },

	/* CHatchStyle_DashedDownwardDiagonal */
	{ 0x00,0x00,0x11,0x22,0x44,0x88,0x00,0x00 },

	/* CHatchStyle_DashedUpwardDiagonal */
	{ 0x00,0x00,0x88,0x44,0x22,0x11,0x00,0x00 },

	/* CHatchStyle_DashedHorizontal */
	{ 0x0F,0x00,0x00,0x00,0xF0,0x00,0x00,0x00 },

	/* CHatchStyle_DashedVertical */
	{ 0x01,0x01,0x01,0x01,0x10,0x10,0x10,0x10 },

	/* CHatchStyle_SmallConfetti */
	{ 0x01,0x10,0x02,0x40,0x08,0x80,0x04,0x20 },

	/* CHatchStyle_LargeConfetti */
	{ 0x8D,0x0C,0xC0,0xD8,0x1B,0x03,0x30,0xB1 },

	/* CHatchStyle_ZigZag */
	{ 0x81,0x42,0x24,0x18,0x81,0x42,0x24,0x18 },

	/* CHatchStyle_Wave */
	{ 0x00,0x18,0xA4,0x03,0x00,0x18,0xA4,0x03 },

	/* CHatchStyle_DiagonalBrick */
	{ 0x80,0x40,0x20,0x10,0x18,0x24,0x42,0x81 },

	/* CHatchStyle_HorizontalBrick */
	{ 0xFF,0x01,0x01,0x01,0xFF,0x10,0x10,0x10 },

	/* CHatchStyle_Weave */
	{ 0x11,0x2A,0x44,0xA2,0x11,0x28,0x44,0x8A },

	/* CHatchStyle_Plaid */
	{ 0x55,0xAA,0x55,0xAA,0x0F,0x0F,0x0F,0x0F },

	/* CHatchStyle_Divot */
	{ 0x00,0x08,0x10,0x08,0x00,0x01,0x80,0x01 },

	/* CHatchStyle_DottedGrid */
	{ 0x55,0x00,0x01,0x00,0x01,0x00,0x01,0x00 },

	/* CHatchStyle_DottedDiamond */
	{ 0x01,0x00,0x44,0x00,0x10,0x00,0x44,0x00 },

	/* CHatchStyle_Shingle */
	{ 0xC0,0x21,0x12,0x0C,0x30,0x40,0x80,0x80 },

	/* CHatchStyle_Trellis */
	{ 0xFF,0x66,0xFF,0x99,0xFF,0x66,0xFF,0x99 },

	/* CHatchStyle_Sphere */
	{ 0xEE,0x91,0xF1,0xF1,0xEE,0x19,0x1F,0x1F },

	/* CHatchStyle_SmallGrid */
	{ 0xFF,0x11,0x11,0x11,0xFF,0x11,0x11,0x11 },

	/* CHatchStyle_SmallCheckerBoard */
	{ 0x99,0x66,0x66,0x99,0x99,0x66,0x66,0x99 },

	/* CHatchStyle_LargeCheckerBoard */
	{ 0x0F,0x0F,0x0F,0x0F,0xF0,0xF0,0xF0,0xF0 },

	/* CHatchStyle_OutlinedDiamond */
	{ 0x41,0x22,0x14,0x08,0x14,0x22,0x41,0x80 },

	/* CHatchStyle_SolidDiamond */
	{ 0x08,0x1C,0x3E,0x7F,0x3E,0x1C,0x08,0x00 }
};

static CStatus
CHatchBrush_Clone(CBrush  *_this,
                  CBrush **_clone);
static CStatus
CHatchBrush_CreatePattern(CBrush   *_this,
                          CPattern *pattern);
static void
CHatchBrush_Finalize(CBrush *_this);

static const CBrushClass CHatchBrush_Class =
{
	CBrushType_HatchFill,
	CHatchBrush_Clone,
	CHatchBrush_Finalize,
	CHatchBrush_CreatePattern,
	"sentinel"
};

#ifdef __cplusplus
};
#endif

#endif /* _C_HATCHBRUSH_H_ */
