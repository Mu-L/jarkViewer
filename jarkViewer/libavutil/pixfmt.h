/*
 * copyright (c) 2006 Michael Niedermayer <michaelni@gmx.at>
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef AVUTIL_PIXFMT_H
#define AVUTIL_PIXFMT_H

/**
 * @file
 * pixel format definitions
 *
 */

#include "libavutil/avconfig.h"
#include "version.h"

#define AVPALETTE_SIZE 1024
#define AVPALETTE_COUNT 256

/**
 * Pixel format.
 *
 * @note
 * AV_PIX_FMT_RGB32 is handled in an endian-specific manner. An RGBA
 * color is put together as:
 *  (A << 24) | (R << 16) | (G << 8) | B
 * This is stored as BGRA on little-endian CPU architectures and ARGB on
 * big-endian CPUs.
 *
 * @par
 * When the pixel format is palettized RGB (AV_PIX_FMT_PAL8), the palettized
 * image data is stored in AVFrame.data[0]. The palette is transported in
 * AVFrame.data[1], is 1024 bytes long (256 4-byte entries) and is
 * formatted the same as in AV_PIX_FMT_RGB32 described above (i.e., it is
 * also endian-specific). Note also that the individual RGB palette
 * components stored in AVFrame.data[1] should be in the range 0..255.
 * This is important as many custom PAL8 video codecs that were designed
 * to run on the IBM VGA graphics adapter use 6-bit palette components.
 *
 * @par
 * For all the 8bit per pixel formats, an RGB32 palette is in data[1] like
 * for pal8. This palette is filled in automatically by the function
 * allocating the picture.
 *
 * @note
 * Make sure that all newly added big-endian formats have (pix_fmt & 1) == 1
 * and that all newly added little-endian formats have (pix_fmt & 1) == 0.
 * This allows simpler detection of big vs little-endian.
 */
enum AVPixelFormat {
    AV_PIX_FMT_NONE = -1,
    AV_PIX_FMT_YUV420P,   ///< planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples)
    AV_PIX_FMT_YUYV422,   ///< packed YUV 4:2:2, 16bpp, Y0 Cb Y1 Cr
    AV_PIX_FMT_RGB24,     ///< packed RGB 8:8:8, 24bpp, RGBRGB...
    AV_PIX_FMT_BGR24,     ///< packed RGB 8:8:8, 24bpp, BGRBGR...
    AV_PIX_FMT_YUV422P,   ///< planar YUV 4:2:2, 16bpp, (1 Cr & Cb sample per 2x1 Y samples)
    AV_PIX_FMT_YUV444P,   ///< planar YUV 4:4:4, 24bpp, (1 Cr & Cb sample per 1x1 Y samples)
    AV_PIX_FMT_YUV410P,   ///< planar YUV 4:1:0,  9bpp, (1 Cr & Cb sample per 4x4 Y samples)
    AV_PIX_FMT_YUV411P,   ///< planar YUV 4:1:1, 12bpp, (1 Cr & Cb sample per 4x1 Y samples)
    AV_PIX_FMT_GRAY8,     ///<        Y        ,  8bpp
    AV_PIX_FMT_MONOWHITE, ///<        Y        ,  1bpp, 0 is white, 1 is black, in each byte pixels are ordered from the msb to the lsb
    AV_PIX_FMT_MONOBLACK, ///<        Y        ,  1bpp, 0 is black, 1 is white, in each byte pixels are ordered from the msb to the lsb
    AV_PIX_FMT_PAL8,      ///< 8 bit with PIX_FMT_RGB32 palette
    AV_PIX_FMT_YUVJ420P,  ///< planar YUV 4:2:0, 12bpp, full scale (JPEG), deprecated in favor of PIX_FMT_YUV420P and setting color_range
    AV_PIX_FMT_YUVJ422P,  ///< planar YUV 4:2:2, 16bpp, full scale (JPEG), deprecated in favor of PIX_FMT_YUV422P and setting color_range
    AV_PIX_FMT_YUVJ444P,  ///< planar YUV 4:4:4, 24bpp, full scale (JPEG), deprecated in favor of PIX_FMT_YUV444P and setting color_range
#if FF_API_XVMC
    AV_PIX_FMT_XVMC_MPEG2_MC,///< XVideo Motion Acceleration via common packet passing
    AV_PIX_FMT_XVMC_MPEG2_IDCT,
#define AV_PIX_FMT_XVMC AV_PIX_FMT_XVMC_MPEG2_IDCT
#endif /* FF_API_XVMC */
    AV_PIX_FMT_UYVY422,   ///< packed YUV 4:2:2, 16bpp, Cb Y0 Cr Y1
    AV_PIX_FMT_UYYVYY411, ///< packed YUV 4:1:1, 12bpp, Cb Y0 Y1 Cr Y2 Y3
    AV_PIX_FMT_BGR8,      ///< packed RGB 3:3:2,  8bpp, (msb)2B 3G 3R(lsb)
    AV_PIX_FMT_BGR4,      ///< packed RGB 1:2:1 bitstream,  4bpp, (msb)1B 2G 1R(lsb), a byte contains two pixels, the first pixel in the byte is the one composed by the 4 msb bits
    AV_PIX_FMT_BGR4_BYTE, ///< packed RGB 1:2:1,  8bpp, (msb)1B 2G 1R(lsb)
    AV_PIX_FMT_RGB8,      ///< packed RGB 3:3:2,  8bpp, (msb)2R 3G 3B(lsb)
    AV_PIX_FMT_RGB4,      ///< packed RGB 1:2:1 bitstream,  4bpp, (msb)1R 2G 1B(lsb), a byte contains two pixels, the first pixel in the byte is the one composed by the 4 msb bits
    AV_PIX_FMT_RGB4_BYTE, ///< packed RGB 1:2:1,  8bpp, (msb)1R 2G 1B(lsb)
    AV_PIX_FMT_NV12,      ///< planar YUV 4:2:0, 12bpp, 1 plane for Y and 1 plane for the UV components, which are interleaved (first byte U and the following byte V)
    AV_PIX_FMT_NV21,      ///< as above, but U and V bytes are swapped

    AV_PIX_FMT_ARGB,      ///< packed ARGB 8:8:8:8, 32bpp, ARGBARGB...
    AV_PIX_FMT_RGBA,      ///< packed RGBA 8:8:8:8, 32bpp, RGBARGBA...
    AV_PIX_FMT_ABGR,      ///< packed ABGR 8:8:8:8, 32bpp, ABGRABGR...
    AV_PIX_FMT_BGRA,      ///< packed BGRA 8:8:8:8, 32bpp, BGRABGRA...

    AV_PIX_FMT_GRAY16BE,  ///<        Y        , 16bpp, big-endian
    AV_PIX_FMT_GRAY16LE,  ///<        Y        , 16bpp, little-endian
    AV_PIX_FMT_YUV440P,   ///< planar YUV 4:4:0 (1 Cr & Cb sample per 1x2 Y samples)
    AV_PIX_FMT_YUVJ440P,  ///< planar YUV 4:4:0 full scale (JPEG), deprecated in favor of PIX_FMT_YUV440P and setting color_range
    AV_PIX_FMT_YUVA420P,  ///< planar YUV 4:2:0, 20bpp, (1 Cr & Cb sample per 2x2 Y & A samples)
#if FF_API_VDPAU
    AV_PIX_FMT_VDPAU_H264,///< H.264 HW decoding with VDPAU, data[0] contains a vdpau_render_state struct which contains the bitstream of the slices as well as various fields extracted from headers
    AV_PIX_FMT_VDPAU_MPEG1,///< MPEG-1 HW decoding with VDPAU, data[0] contains a vdpau_render_state struct which contains the bitstream of the slices as well as various fields extracted from headers
    AV_PIX_FMT_VDPAU_MPEG2,///< MPEG-2 HW decoding with VDPAU, data[0] contains a vdpau_render_state struct which contains the bitstream of the slices as well as various fields extracted from headers
    AV_PIX_FMT_VDPAU_WMV3,///< WMV3 HW decoding with VDPAU, data[0] contains a vdpau_render_state struct which contains the bitstream of the slices as well as various fields extracted from headers
    AV_PIX_FMT_VDPAU_VC1, ///< VC-1 HW decoding with VDPAU, data[0] contains a vdpau_render_state struct which contains the bitstream of the slices as well as various fields extracted from headers
#endif
    AV_PIX_FMT_RGB48BE,   ///< packed RGB 16:16:16, 48bpp, 16R, 16G, 16B, the 2-byte value for each R/G/B component is stored as big-endian
    AV_PIX_FMT_RGB48LE,   ///< packed RGB 16:16:16, 48bpp, 16R, 16G, 16B, the 2-byte value for each R/G/B component is stored as little-endian

    AV_PIX_FMT_RGB565BE,  ///< packed RGB 5:6:5, 16bpp, (msb)   5R 6G 5B(lsb), big-endian
    AV_PIX_FMT_RGB565LE,  ///< packed RGB 5:6:5, 16bpp, (msb)   5R 6G 5B(lsb), little-endian
    AV_PIX_FMT_RGB555BE,  ///< packed RGB 5:5:5, 16bpp, (msb)1A 5R 5G 5B(lsb), big-endian, most significant bit to 0
    AV_PIX_FMT_RGB555LE,  ///< packed RGB 5:5:5, 16bpp, (msb)1A 5R 5G 5B(lsb), little-endian, most significant bit to 0

    AV_PIX_FMT_BGR565BE,  ///< packed BGR 5:6:5, 16bpp, (msb)   5B 6G 5R(lsb), big-endian
    AV_PIX_FMT_BGR565LE,  ///< packed BGR 5:6:5, 16bpp, (msb)   5B 6G 5R(lsb), little-endian
    AV_PIX_FMT_BGR555BE,  ///< packed BGR 5:5:5, 16bpp, (msb)1A 5B 5G 5R(lsb), big-endian, most significant bit to 1
    AV_PIX_FMT_BGR555LE,  ///< packed BGR 5:5:5, 16bpp, (msb)1A 5B 5G 5R(lsb), little-endian, most significant bit to 1

    AV_PIX_FMT_VAAPI_MOCO, ///< HW acceleration through VA API at motion compensation entry-point, Picture.data[3] contains a vaapi_render_state struct which contains macroblocks as well as various fields extracted from headers
    AV_PIX_FMT_VAAPI_IDCT, ///< HW acceleration through VA API at IDCT entry-point, Picture.data[3] contains a vaapi_render_state struct which contains fields extracted from headers
    AV_PIX_FMT_VAAPI_VLD,  ///< HW decoding through VA API, Picture.data[3] contains a vaapi_render_state struct which contains the bitstream of the slices as well as various fields extracted from headers

    AV_PIX_FMT_YUV420P16LE,  ///< planar YUV 4:2:0, 24bpp, (1 Cr & Cb sample per 2x2 Y samples), little-endian
    AV_PIX_FMT_YUV420P16BE,  ///< planar YUV 4:2:0, 24bpp, (1 Cr & Cb sample per 2x2 Y samples), big-endian
    AV_PIX_FMT_YUV422P16LE,  ///< planar YUV 4:2:2, 32bpp, (1 Cr & Cb sample per 2x1 Y samples), little-endian
    AV_PIX_FMT_YUV422P16BE,  ///< planar YUV 4:2:2, 32bpp, (1 Cr & Cb sample per 2x1 Y samples), big-endian
    AV_PIX_FMT_YUV444P16LE,  ///< planar YUV 4:4:4, 48bpp, (1 Cr & Cb sample per 1x1 Y samples), little-endian
    AV_PIX_FMT_YUV444P16BE,  ///< planar YUV 4:4:4, 48bpp, (1 Cr & Cb sample per 1x1 Y samples), big-endian
#if FF_API_VDPAU
    AV_PIX_FMT_VDPAU_MPEG4,  ///< MPEG4 HW decoding with VDPAU, data[0] contains a vdpau_render_state struct which contains the bitstream of the slices as well as various fields extracted from headers
#endif
    AV_PIX_FMT_DXVA2_VLD,    ///< HW decoding through DXVA2, Picture.data[3] contains a LPDIRECT3DSURFACE9 pointer

    AV_PIX_FMT_RGB444LE,  ///< packed RGB 4:4:4, 16bpp, (msb)4A 4R 4G 4B(lsb), little-endian, most significant bits to 0
    AV_PIX_FMT_RGB444BE,  ///< packed RGB 4:4:4, 16bpp, (msb)4A 4R 4G 4B(lsb), big-endian, most significant bits to 0
    AV_PIX_FMT_BGR444LE,  ///< packed BGR 4:4:4, 16bpp, (msb)4A 4B 4G 4R(lsb), little-endian, most significant bits to 1
    AV_PIX_FMT_BGR444BE,  ///< packed BGR 4:4:4, 16bpp, (msb)4A 4B 4G 4R(lsb), big-endian, most significant bits to 1
    AV_PIX_FMT_YA8,       ///< 8bit gray, 8bit alpha

    AV_PIX_FMT_Y400A = AV_PIX_FMT_YA8, ///< alias for AV_PIX_FMT_YA8
    AV_PIX_FMT_GRAY8A= AV_PIX_FMT_YA8, ///< alias for AV_PIX_FMT_YA8

    AV_PIX_FMT_BGR48BE,   ///< packed RGB 16:16:16, 48bpp, 16B, 16G, 16R, the 2-byte value for each R/G/B component is stored as big-endian
    AV_PIX_FMT_BGR48LE,   ///< packed RGB 16:16:16, 48bpp, 16B, 16G, 16R, the 2-byte value for each R/G/B component is stored as little-endian

    /**
     * The following 12 formats have the disadvantage of needing 1 format for each bit depth.
     * Notice that each 9/10 bits sample is stored in 16 bits with extra padding.
     * If you want to support multiple bit depths, then using AV_PIX_FMT_YUV420P16* with the bpp stored separately is better.
     */
    AV_PIX_FMT_YUV420P9BE, ///< planar YUV 4:2:0, 13.5bpp, (1 Cr & Cb sample per 2x2 Y samples), big-endian
    AV_PIX_FMT_YUV420P9LE, ///< planar YUV 4:2:0, 13.5bpp, (1 Cr & Cb sample per 2x2 Y samples), little-endian
    AV_PIX_FMT_YUV420P10BE,///< planar YUV 4:2:0, 15bpp, (1 Cr & Cb sample per 2x2 Y samples), big-endian
    AV_PIX_FMT_YUV420P10LE,///< planar YUV 4:2:0, 15bpp, (1 Cr & Cb sample per 2x2 Y samples), little-endian
    AV_PIX_FMT_YUV422P10BE,///< planar YUV 4:2:2, 20bpp, (1 Cr & Cb sample per 2x1 Y samples), big-endian
    AV_PIX_FMT_YUV422P10LE,///< planar YUV 4:2:2, 20bpp, (1 Cr & Cb sample per 2x1 Y samples), little-endian
    AV_PIX_FMT_YUV444P9BE, ///< planar YUV 4:4:4, 27bpp, (1 Cr & Cb sample per 1x1 Y samples), big-endian
    AV_PIX_FMT_YUV444P9LE, ///< planar YUV 4:4:4, 27bpp, (1 Cr & Cb sample per 1x1 Y samples), little-endian
    AV_PIX_FMT_YUV444P10BE,///< planar YUV 4:4:4, 30bpp, (1 Cr & Cb sample per 1x1 Y samples), big-endian
    AV_PIX_FMT_YUV444P10LE,///< planar YUV 4:4:4, 30bpp, (1 Cr & Cb sample per 1x1 Y samples), little-endian
    AV_PIX_FMT_YUV422P9BE, ///< planar YUV 4:2:2, 18bpp, (1 Cr & Cb sample per 2x1 Y samples), big-endian
    AV_PIX_FMT_YUV422P9LE, ///< planar YUV 4:2:2, 18bpp, (1 Cr & Cb sample per 2x1 Y samples), little-endian
    AV_PIX_FMT_VDA_VLD,    ///< hardware decoding through VDA

#ifdef AV_PIX_FMT_ABI_GIT_MASTER
    AV_PIX_FMT_RGBA64BE,  ///< packed RGBA 16:16:16:16, 64bpp, 16R, 16G, 16B, 16A, the 2-byte value for each R/G/B/A component is stored as big-endian
    AV_PIX_FMT_RGBA64LE,  ///< packed RGBA 16:16:16:16, 64bpp, 16R, 16G, 16B, 16A, the 2-byte value for each R/G/B/A component is stored as little-endian
    AV_PIX_FMT_BGRA64BE,  ///< packed RGBA 16:16:16:16, 64bpp, 16B, 16G, 16R, 16A, the 2-byte value for each R/G/B/A component is stored as big-endian
    AV_PIX_FMT_BGRA64LE,  ///< packed RGBA 16:16:16:16, 64bpp, 16B, 16G, 16R, 16A, the 2-byte value for each R/G/B/A component is stored as little-endian
#endif
    AV_PIX_FMT_GBRP,      ///< planar GBR 4:4:4 24bpp
    AV_PIX_FMT_GBRP9BE,   ///< planar GBR 4:4:4 27bpp, big-endian
    AV_PIX_FMT_GBRP9LE,   ///< planar GBR 4:4:4 27bpp, little-endian
    AV_PIX_FMT_GBRP10BE,  ///< planar GBR 4:4:4 30bpp, big-endian
    AV_PIX_FMT_GBRP10LE,  ///< planar GBR 4:4:4 30bpp, little-endian
    AV_PIX_FMT_GBRP16BE,  ///< planar GBR 4:4:4 48bpp, big-endian
    AV_PIX_FMT_GBRP16LE,  ///< planar GBR 4:4:4 48bpp, little-endian

    /**
     * duplicated pixel formats for compatibility with libav.
     * FFmpeg supports these formats since May 8 2012 and Jan 28 2012 (commits f9ca1ac7 and 143a5c55)
     * Libav added them Oct 12 2012 with incompatible values (commit 6d5600e85)
     */
    AV_PIX_FMT_YUVA422P_LIBAV,  ///< planar YUV 4:2:2 24bpp, (1 Cr & Cb sample per 2x1 Y & A samples)
    AV_PIX_FMT_YUVA444P_LIBAV,  ///< planar YUV 4:4:4 32bpp, (1 Cr & Cb sample per 1x1 Y & A samples)

    AV_PIX_FMT_YUVA420P9BE,  ///< planar YUV 4:2:0 22.5bpp, (1 Cr & Cb sample per 2x2 Y & A samples), big-endian
    AV_PIX_FMT_YUVA420P9LE,  ///< planar YUV 4:2:0 22.5bpp, (1 Cr & Cb sample per 2x2 Y & A samples), little-endian
    AV_PIX_FMT_YUVA422P9BE,  ///< planar YUV 4:2:2 27bpp, (1 Cr & Cb sample per 2x1 Y & A samples), big-endian
    AV_PIX_FMT_YUVA422P9LE,  ///< planar YUV 4:2:2 27bpp, (1 Cr & Cb sample per 2x1 Y & A samples), little-endian
    AV_PIX_FMT_YUVA444P9BE,  ///< planar YUV 4:4:4 36bpp, (1 Cr & Cb sample per 1x1 Y & A samples), big-endian
    AV_PIX_FMT_YUVA444P9LE,  ///< planar YUV 4:4:4 36bpp, (1 Cr & Cb sample per 1x1 Y & A samples), little-endian
    AV_PIX_FMT_YUVA420P10BE, ///< planar YUV 4:2:0 25bpp, (1 Cr & Cb sample per 2x2 Y & A samples, big-endian)
    AV_PIX_FMT_YUVA420P10LE, ///< planar YUV 4:2:0 25bpp, (1 Cr & Cb sample per 2x2 Y & A samples, little-endian)
    AV_PIX_FMT_YUVA422P10BE, ///< planar YUV 4:2:2 30bpp, (1 Cr & Cb sample per 2x1 Y & A samples, big-endian)
    AV_PIX_FMT_YUVA422P10LE, ///< planar YUV 4:2:2 30bpp, (1 Cr & Cb sample per 2x1 Y & A samples, little-endian)
    AV_PIX_FMT_YUVA444P10BE, ///< planar YUV 4:4:4 40bpp, (1 Cr & Cb sample per 1x1 Y & A samples, big-endian)
    AV_PIX_FMT_YUVA444P10LE, ///< planar YUV 4:4:4 40bpp, (1 Cr & Cb sample per 1x1 Y & A samples, little-endian)
    AV_PIX_FMT_YUVA420P16BE, ///< planar YUV 4:2:0 40bpp, (1 Cr & Cb sample per 2x2 Y & A samples, big-endian)
    AV_PIX_FMT_YUVA420P16LE, ///< planar YUV 4:2:0 40bpp, (1 Cr & Cb sample per 2x2 Y & A samples, little-endian)
    AV_PIX_FMT_YUVA422P16BE, ///< planar YUV 4:2:2 48bpp, (1 Cr & Cb sample per 2x1 Y & A samples, big-endian)
    AV_PIX_FMT_YUVA422P16LE, ///< planar YUV 4:2:2 48bpp, (1 Cr & Cb sample per 2x1 Y & A samples, little-endian)
    AV_PIX_FMT_YUVA444P16BE, ///< planar YUV 4:4:4 64bpp, (1 Cr & Cb sample per 1x1 Y & A samples, big-endian)
    AV_PIX_FMT_YUVA444P16LE, ///< planar YUV 4:4:4 64bpp, (1 Cr & Cb sample per 1x1 Y & A samples, little-endian)

    AV_PIX_FMT_VDPAU,     ///< HW acceleration through VDPAU, Picture.data[3] contains a VdpVideoSurface

    AV_PIX_FMT_XYZ12LE,      ///< packed XYZ 4:4:4, 36 bpp, (msb) 12X, 12Y, 12Z (lsb), the 2-byte value for each X/Y/Z is stored as little-endian, the 4 lower bits are set to 0
    AV_PIX_FMT_XYZ12BE,      ///< packed XYZ 4:4:4, 36 bpp, (msb) 12X, 12Y, 12Z (lsb), the 2-byte value for each X/Y/Z is stored as big-endian, the 4 lower bits are set to 0
    AV_PIX_FMT_NV16,         ///< interleaved chroma YUV 4:2:2, 16bpp, (1 Cr & Cb sample per 2x1 Y samples)
    AV_PIX_FMT_NV20LE,       ///< interleaved chroma YUV 4:2:2, 20bpp, (1 Cr & Cb sample per 2x1 Y samples), little-endian
    AV_PIX_FMT_NV20BE,       ///< interleaved chroma YUV 4:2:2, 20bpp, (1 Cr & Cb sample per 2x1 Y samples), big-endian

    /**
     * duplicated pixel formats for compatibility with libav.
     * FFmpeg supports these formats since Sat Sep 24 06:01:45 2011 +0200 (commits 9569a3c9f41387a8c7d1ce97d8693520477a66c3)
     * also see Fri Nov 25 01:38:21 2011 +0100 92afb431621c79155fcb7171d26f137eb1bee028
     * Libav added them Sun Mar 16 23:05:47 2014 +0100 with incompatible values (commit 1481d24c3a0abf81e1d7a514547bd5305232be30)
     */
    AV_PIX_FMT_RGBA64BE_LIBAV,     ///< packed RGBA 16:16:16:16, 64bpp, 16R, 16G, 16B, 16A, the 2-byte value for each R/G/B/A component is stored as big-endian
    AV_PIX_FMT_RGBA64LE_LIBAV,     ///< packed RGBA 16:16:16:16, 64bpp, 16R, 16G, 16B, 16A, the 2-byte value for each R/G/B/A component is stored as little-endian
    AV_PIX_FMT_BGRA64BE_LIBAV,     ///< packed RGBA 16:16:16:16, 64bpp, 16B, 16G, 16R, 16A, the 2-byte value for each R/G/B/A component is stored as big-endian
    AV_PIX_FMT_BGRA64LE_LIBAV,     ///< packed RGBA 16:16:16:16, 64bpp, 16B, 16G, 16R, 16A, the 2-byte value for each R/G/B/A component is stored as little-endian

    AV_PIX_FMT_YVYU422,   ///< packed YUV 4:2:2, 16bpp, Y0 Cr Y1 Cb

    AV_PIX_FMT_VDA,          ///< HW acceleration through VDA, data[3] contains a CVPixelBufferRef

    AV_PIX_FMT_YA16BE,       ///< 16bit gray, 16bit alpha (big-endian)
    AV_PIX_FMT_YA16LE,       ///< 16bit gray, 16bit alpha (little-endian)


#ifndef AV_PIX_FMT_ABI_GIT_MASTER
    AV_PIX_FMT_RGBA64BE=0x123,  ///< packed RGBA 16:16:16:16, 64bpp, 16R, 16G, 16B, 16A, the 2-byte value for each R/G/B/A component is stored as big-endian
    AV_PIX_FMT_RGBA64LE,  ///< packed RGBA 16:16:16:16, 64bpp, 16R, 16G, 16B, 16A, the 2-byte value for each R/G/B/A component is stored as little-endian
    AV_PIX_FMT_BGRA64BE,  ///< packed RGBA 16:16:16:16, 64bpp, 16B, 16G, 16R, 16A, the 2-byte value for each R/G/B/A component is stored as big-endian
    AV_PIX_FMT_BGRA64LE,  ///< packed RGBA 16:16:16:16, 64bpp, 16B, 16G, 16R, 16A, the 2-byte value for each R/G/B/A component is stored as little-endian
#endif
    AV_PIX_FMT_0RGB=0x123+4,      ///< packed RGB 8:8:8, 32bpp, 0RGB0RGB...
    AV_PIX_FMT_RGB0,      ///< packed RGB 8:8:8, 32bpp, RGB0RGB0...
    AV_PIX_FMT_0BGR,      ///< packed BGR 8:8:8, 32bpp, 0BGR0BGR...
    AV_PIX_FMT_BGR0,      ///< packed BGR 8:8:8, 32bpp, BGR0BGR0...
    AV_PIX_FMT_YUVA444P,  ///< planar YUV 4:4:4 32bpp, (1 Cr & Cb sample per 1x1 Y & A samples)
    AV_PIX_FMT_YUVA422P,  ///< planar YUV 4:2:2 24bpp, (1 Cr & Cb sample per 2x1 Y & A samples)

    AV_PIX_FMT_YUV420P12BE, ///< planar YUV 4:2:0,18bpp, (1 Cr & Cb sample per 2x2 Y samples), big-endian
    AV_PIX_FMT_YUV420P12LE, ///< planar YUV 4:2:0,18bpp, (1 Cr & Cb sample per 2x2 Y samples), little-endian
    AV_PIX_FMT_YUV420P14BE, ///< planar YUV 4:2:0,21bpp, (1 Cr & Cb sample per 2x2 Y samples), big-endian
    AV_PIX_FMT_YUV420P14LE, ///< planar YUV 4:2:0,21bpp, (1 Cr & Cb sample per 2x2 Y samples), little-endian
    AV_PIX_FMT_YUV422P12BE, ///< planar YUV 4:2:2,24bpp, (1 Cr & Cb sample per 2x1 Y samples), big-endian
    AV_PIX_FMT_YUV422P12LE, ///< planar YUV 4:2:2,24bpp, (1 Cr & Cb sample per 2x1 Y samples), little-endian
    AV_PIX_FMT_YUV422P14BE, ///< planar YUV 4:2:2,28bpp, (1 Cr & Cb sample per 2x1 Y samples), big-endian
    AV_PIX_FMT_YUV422P14LE, ///< planar YUV 4:2:2,28bpp, (1 Cr & Cb sample per 2x1 Y samples), little-endian
    AV_PIX_FMT_YUV444P12BE, ///< planar YUV 4:4:4,36bpp, (1 Cr & Cb sample per 1x1 Y samples), big-endian
    AV_PIX_FMT_YUV444P12LE, ///< planar YUV 4:4:4,36bpp, (1 Cr & Cb sample per 1x1 Y samples), little-endian
    AV_PIX_FMT_YUV444P14BE, ///< planar YUV 4:4:4,42bpp, (1 Cr & Cb sample per 1x1 Y samples), big-endian
    AV_PIX_FMT_YUV444P14LE, ///< planar YUV 4:4:4,42bpp, (1 Cr & Cb sample per 1x1 Y samples), little-endian
    AV_PIX_FMT_GBRP12BE,    ///< planar GBR 4:4:4 36bpp, big-endian
    AV_PIX_FMT_GBRP12LE,    ///< planar GBR 4:4:4 36bpp, little-endian
    AV_PIX_FMT_GBRP14BE,    ///< planar GBR 4:4:4 42bpp, big-endian
    AV_PIX_FMT_GBRP14LE,    ///< planar GBR 4:4:4 42bpp, little-endian
    AV_PIX_FMT_GBRAP,       ///< planar GBRA 4:4:4:4 32bpp
    AV_PIX_FMT_GBRAP16BE,   ///< planar GBRA 4:4:4:4 64bpp, big-endian
    AV_PIX_FMT_GBRAP16LE,   ///< planar GBRA 4:4:4:4 64bpp, little-endian
    AV_PIX_FMT_YUVJ411P,    ///< planar YUV 4:1:1, 12bpp, (1 Cr & Cb sample per 4x1 Y samples) full scale (JPEG), deprecated in favor of PIX_FMT_YUV411P and setting color_range

    AV_PIX_FMT_BAYER_BGGR8,    ///< bayer, BGBG..(odd line), GRGR..(even line), 8-bit samples */
    AV_PIX_FMT_BAYER_RGGB8,    ///< bayer, RGRG..(odd line), GBGB..(even line), 8-bit samples */
    AV_PIX_FMT_BAYER_GBRG8,    ///< bayer, GBGB..(odd line), RGRG..(even line), 8-bit samples */
    AV_PIX_FMT_BAYER_GRBG8,    ///< bayer, GRGR..(odd line), BGBG..(even line), 8-bit samples */
    AV_PIX_FMT_BAYER_BGGR16LE, ///< bayer, BGBG..(odd line), GRGR..(even line), 16-bit samples, little-endian */
    AV_PIX_FMT_BAYER_BGGR16BE, ///< bayer, BGBG..(odd line), GRGR..(even line), 16-bit samples, big-endian */
    AV_PIX_FMT_BAYER_RGGB16LE, ///< bayer, RGRG..(odd line), GBGB..(even line), 16-bit samples, little-endian */
    AV_PIX_FMT_BAYER_RGGB16BE, ///< bayer, RGRG..(odd line), GBGB..(even line), 16-bit samples, big-endian */
    AV_PIX_FMT_BAYER_GBRG16LE, ///< bayer, GBGB..(odd line), RGRG..(even line), 16-bit samples, little-endian */
    AV_PIX_FMT_BAYER_GBRG16BE, ///< bayer, GBGB..(odd line), RGRG..(even line), 16-bit samples, big-endian */
    AV_PIX_FMT_BAYER_GRBG16LE, ///< bayer, GRGR..(odd line), BGBG..(even line), 16-bit samples, little-endian */
    AV_PIX_FMT_BAYER_GRBG16BE, ///< bayer, GRGR..(odd line), BGBG..(even line), 16-bit samples, big-endian */
#if !FF_API_XVMC
    AV_PIX_FMT_XVMC,///< XVideo Motion Acceleration via common packet passing
#endif /* !FF_API_XVMC */

    AV_PIX_FMT_NB,        ///< number of pixel formats, DO NOT USE THIS if you want to link with shared libav* because the number of formats might differ between versions

#if FF_API_PIX_FMT
#include "old_pix_fmts.h"
#endif
};

#if AV_HAVE_INCOMPATIBLE_LIBAV_ABI
#define AV_PIX_FMT_YUVA422P AV_PIX_FMT_YUVA422P_LIBAV
#define AV_PIX_FMT_YUVA444P AV_PIX_FMT_YUVA444P_LIBAV
#define AV_PIX_FMT_RGBA64BE AV_PIX_FMT_RGBA64BE_LIBAV
#define AV_PIX_FMT_RGBA64LE AV_PIX_FMT_RGBA64LE_LIBAV
#define AV_PIX_FMT_BGRA64BE AV_PIX_FMT_BGRA64BE_LIBAV
#define AV_PIX_FMT_BGRA64LE AV_PIX_FMT_BGRA64LE_LIBAV
#endif


#define AV_PIX_FMT_Y400A AV_PIX_FMT_GRAY8A
#define AV_PIX_FMT_GBR24P AV_PIX_FMT_GBRP

#if AV_HAVE_BIGENDIAN
#   define AV_PIX_FMT_NE(be, le) AV_PIX_FMT_##be
#else
#   define AV_PIX_FMT_NE(be, le) AV_PIX_FMT_##le
#endif

#define AV_PIX_FMT_RGB32   AV_PIX_FMT_NE(ARGB, BGRA)
#define AV_PIX_FMT_RGB32_1 AV_PIX_FMT_NE(RGBA, ABGR)
#define AV_PIX_FMT_BGR32   AV_PIX_FMT_NE(ABGR, RGBA)
#define AV_PIX_FMT_BGR32_1 AV_PIX_FMT_NE(BGRA, ARGB)
#define AV_PIX_FMT_0RGB32  AV_PIX_FMT_NE(0RGB, BGR0)
#define AV_PIX_FMT_0BGR32  AV_PIX_FMT_NE(0BGR, RGB0)

#define AV_PIX_FMT_GRAY16 AV_PIX_FMT_NE(GRAY16BE, GRAY16LE)
#define AV_PIX_FMT_YA16   AV_PIX_FMT_NE(YA16BE,   YA16LE)
#define AV_PIX_FMT_RGB48  AV_PIX_FMT_NE(RGB48BE,  RGB48LE)
#define AV_PIX_FMT_RGB565 AV_PIX_FMT_NE(RGB565BE, RGB565LE)
#define AV_PIX_FMT_RGB555 AV_PIX_FMT_NE(RGB555BE, RGB555LE)
#define AV_PIX_FMT_RGB444 AV_PIX_FMT_NE(RGB444BE, RGB444LE)
#define AV_PIX_FMT_RGBA64 AV_PIX_FMT_NE(RGBA64BE, RGBA64LE)
#define AV_PIX_FMT_BGR48  AV_PIX_FMT_NE(BGR48BE,  BGR48LE)
#define AV_PIX_FMT_BGR565 AV_PIX_FMT_NE(BGR565BE, BGR565LE)
#define AV_PIX_FMT_BGR555 AV_PIX_FMT_NE(BGR555BE, BGR555LE)
#define AV_PIX_FMT_BGR444 AV_PIX_FMT_NE(BGR444BE, BGR444LE)
#define AV_PIX_FMT_BGRA64 AV_PIX_FMT_NE(BGRA64BE, BGRA64LE)

#define AV_PIX_FMT_YUV420P9  AV_PIX_FMT_NE(YUV420P9BE , YUV420P9LE)
#define AV_PIX_FMT_YUV422P9  AV_PIX_FMT_NE(YUV422P9BE , YUV422P9LE)
#define AV_PIX_FMT_YUV444P9  AV_PIX_FMT_NE(YUV444P9BE , YUV444P9LE)
#define AV_PIX_FMT_YUV420P10 AV_PIX_FMT_NE(YUV420P10BE, YUV420P10LE)
#define AV_PIX_FMT_YUV422P10 AV_PIX_FMT_NE(YUV422P10BE, YUV422P10LE)
#define AV_PIX_FMT_YUV444P10 AV_PIX_FMT_NE(YUV444P10BE, YUV444P10LE)
#define AV_PIX_FMT_YUV420P12 AV_PIX_FMT_NE(YUV420P12BE, YUV420P12LE)
#define AV_PIX_FMT_YUV422P12 AV_PIX_FMT_NE(YUV422P12BE, YUV422P12LE)
#define AV_PIX_FMT_YUV444P12 AV_PIX_FMT_NE(YUV444P12BE, YUV444P12LE)
#define AV_PIX_FMT_YUV420P14 AV_PIX_FMT_NE(YUV420P14BE, YUV420P14LE)
#define AV_PIX_FMT_YUV422P14 AV_PIX_FMT_NE(YUV422P14BE, YUV422P14LE)
#define AV_PIX_FMT_YUV444P14 AV_PIX_FMT_NE(YUV444P14BE, YUV444P14LE)
#define AV_PIX_FMT_YUV420P16 AV_PIX_FMT_NE(YUV420P16BE, YUV420P16LE)
#define AV_PIX_FMT_YUV422P16 AV_PIX_FMT_NE(YUV422P16BE, YUV422P16LE)
#define AV_PIX_FMT_YUV444P16 AV_PIX_FMT_NE(YUV444P16BE, YUV444P16LE)

#define AV_PIX_FMT_GBRP9     AV_PIX_FMT_NE(GBRP9BE ,    GBRP9LE)
#define AV_PIX_FMT_GBRP10    AV_PIX_FMT_NE(GBRP10BE,    GBRP10LE)
#define AV_PIX_FMT_GBRP12    AV_PIX_FMT_NE(GBRP12BE,    GBRP12LE)
#define AV_PIX_FMT_GBRP14    AV_PIX_FMT_NE(GBRP14BE,    GBRP14LE)
#define AV_PIX_FMT_GBRP16    AV_PIX_FMT_NE(GBRP16BE,    GBRP16LE)
#define AV_PIX_FMT_GBRAP16   AV_PIX_FMT_NE(GBRAP16BE,   GBRAP16LE)

#define AV_PIX_FMT_BAYER_BGGR16 AV_PIX_FMT_NE(BAYER_BGGR16BE,    BAYER_BGGR16LE)
#define AV_PIX_FMT_BAYER_RGGB16 AV_PIX_FMT_NE(BAYER_RGGB16BE,    BAYER_RGGB16LE)
#define AV_PIX_FMT_BAYER_GBRG16 AV_PIX_FMT_NE(BAYER_GBRG16BE,    BAYER_GBRG16LE)
#define AV_PIX_FMT_BAYER_GRBG16 AV_PIX_FMT_NE(BAYER_GRBG16BE,    BAYER_GRBG16LE)


#define AV_PIX_FMT_YUVA420P9  AV_PIX_FMT_NE(YUVA420P9BE , YUVA420P9LE)
#define AV_PIX_FMT_YUVA422P9  AV_PIX_FMT_NE(YUVA422P9BE , YUVA422P9LE)
#define AV_PIX_FMT_YUVA444P9  AV_PIX_FMT_NE(YUVA444P9BE , YUVA444P9LE)
#define AV_PIX_FMT_YUVA420P10 AV_PIX_FMT_NE(YUVA420P10BE, YUVA420P10LE)
#define AV_PIX_FMT_YUVA422P10 AV_PIX_FMT_NE(YUVA422P10BE, YUVA422P10LE)
#define AV_PIX_FMT_YUVA444P10 AV_PIX_FMT_NE(YUVA444P10BE, YUVA444P10LE)
#define AV_PIX_FMT_YUVA420P16 AV_PIX_FMT_NE(YUVA420P16BE, YUVA420P16LE)
#define AV_PIX_FMT_YUVA422P16 AV_PIX_FMT_NE(YUVA422P16BE, YUVA422P16LE)
#define AV_PIX_FMT_YUVA444P16 AV_PIX_FMT_NE(YUVA444P16BE, YUVA444P16LE)

#define AV_PIX_FMT_XYZ12      AV_PIX_FMT_NE(XYZ12BE, XYZ12LE)
#define AV_PIX_FMT_NV20       AV_PIX_FMT_NE(NV20BE,  NV20LE)


#if FF_API_PIX_FMT
//#define PixelFormat AVPixelFormat

#define PIX_FMT_Y400A AV_PIX_FMT_Y400A
#define PIX_FMT_GBR24P AV_PIX_FMT_GBR24P

#define PIX_FMT_NE(be, le) AV_PIX_FMT_NE(be, le)

#define PIX_FMT_RGB32   AV_PIX_FMT_RGB32
#define PIX_FMT_RGB32_1 AV_PIX_FMT_RGB32_1
#define PIX_FMT_BGR32   AV_PIX_FMT_BGR32
#define PIX_FMT_BGR32_1 AV_PIX_FMT_BGR32_1
#define PIX_FMT_0RGB32  AV_PIX_FMT_0RGB32
#define PIX_FMT_0BGR32  AV_PIX_FMT_0BGR32

#define PIX_FMT_GRAY16 AV_PIX_FMT_GRAY16
#define PIX_FMT_RGB48  AV_PIX_FMT_RGB48
#define PIX_FMT_RGB565 AV_PIX_FMT_RGB565
#define PIX_FMT_RGB555 AV_PIX_FMT_RGB555
#define PIX_FMT_RGB444 AV_PIX_FMT_RGB444
#define PIX_FMT_BGR48  AV_PIX_FMT_BGR48
#define PIX_FMT_BGR565 AV_PIX_FMT_BGR565
#define PIX_FMT_BGR555 AV_PIX_FMT_BGR555
#define PIX_FMT_BGR444 AV_PIX_FMT_BGR444

#define PIX_FMT_YUV420P9  AV_PIX_FMT_YUV420P9
#define PIX_FMT_YUV422P9  AV_PIX_FMT_YUV422P9
#define PIX_FMT_YUV444P9  AV_PIX_FMT_YUV444P9
#define PIX_FMT_YUV420P10 AV_PIX_FMT_YUV420P10
#define PIX_FMT_YUV422P10 AV_PIX_FMT_YUV422P10
#define PIX_FMT_YUV444P10 AV_PIX_FMT_YUV444P10
#define PIX_FMT_YUV420P12 AV_PIX_FMT_YUV420P12
#define PIX_FMT_YUV422P12 AV_PIX_FMT_YUV422P12
#define PIX_FMT_YUV444P12 AV_PIX_FMT_YUV444P12
#define PIX_FMT_YUV420P14 AV_PIX_FMT_YUV420P14
#define PIX_FMT_YUV422P14 AV_PIX_FMT_YUV422P14
#define PIX_FMT_YUV444P14 AV_PIX_FMT_YUV444P14
#define PIX_FMT_YUV420P16 AV_PIX_FMT_YUV420P16
#define PIX_FMT_YUV422P16 AV_PIX_FMT_YUV422P16
#define PIX_FMT_YUV444P16 AV_PIX_FMT_YUV444P16

#define PIX_FMT_RGBA64 AV_PIX_FMT_RGBA64
#define PIX_FMT_BGRA64 AV_PIX_FMT_BGRA64
#define PIX_FMT_GBRP9  AV_PIX_FMT_GBRP9
#define PIX_FMT_GBRP10 AV_PIX_FMT_GBRP10
#define PIX_FMT_GBRP12 AV_PIX_FMT_GBRP12
#define PIX_FMT_GBRP14 AV_PIX_FMT_GBRP14
#define PIX_FMT_GBRP16 AV_PIX_FMT_GBRP16
#endif

/**
  * Chromaticity coordinates of the source primaries.
  */
enum AVColorPrimaries {
    AVCOL_PRI_RESERVED0   = 0,
    AVCOL_PRI_BT709       = 1, ///< also ITU-R BT1361 / IEC 61966-2-4 / SMPTE RP177 Annex B
    AVCOL_PRI_UNSPECIFIED = 2,
    AVCOL_PRI_RESERVED    = 3,
    AVCOL_PRI_BT470M      = 4, ///< also FCC Title 47 Code of Federal Regulations 73.682 (a)(20)

    AVCOL_PRI_BT470BG     = 5, ///< also ITU-R BT601-6 625 / ITU-R BT1358 625 / ITU-R BT1700 625 PAL & SECAM
    AVCOL_PRI_SMPTE170M   = 6, ///< also ITU-R BT601-6 525 / ITU-R BT1358 525 / ITU-R BT1700 NTSC
    AVCOL_PRI_SMPTE240M   = 7, ///< functionally identical to above
    AVCOL_PRI_FILM        = 8, ///< colour filters using Illuminant C
    AVCOL_PRI_BT2020      = 9, ///< ITU-R BT2020
    AVCOL_PRI_NB,              ///< Not part of ABI
};

/**
 * Color Transfer Characteristic.
 */
enum AVColorTransferCharacteristic {
    AVCOL_TRC_RESERVED0    = 0,
    AVCOL_TRC_BT709        = 1,  ///< also ITU-R BT1361
    AVCOL_TRC_UNSPECIFIED  = 2,
    AVCOL_TRC_RESERVED     = 3,
    AVCOL_TRC_GAMMA22      = 4,  ///< also ITU-R BT470M / ITU-R BT1700 625 PAL & SECAM
    AVCOL_TRC_GAMMA28      = 5,  ///< also ITU-R BT470BG
    AVCOL_TRC_SMPTE170M    = 6,  ///< also ITU-R BT601-6 525 or 625 / ITU-R BT1358 525 or 625 / ITU-R BT1700 NTSC
    AVCOL_TRC_SMPTE240M    = 7,
    AVCOL_TRC_LINEAR       = 8,  ///< "Linear transfer characteristics"
    AVCOL_TRC_LOG          = 9,  ///< "Logarithmic transfer characteristic (100:1 range)"
    AVCOL_TRC_LOG_SQRT     = 10, ///< "Logarithmic transfer characteristic (100 * Sqrt(10) : 1 range)"
    AVCOL_TRC_IEC61966_2_4 = 11, ///< IEC 61966-2-4
    AVCOL_TRC_BT1361_ECG   = 12, ///< ITU-R BT1361 Extended Colour Gamut
    AVCOL_TRC_IEC61966_2_1 = 13, ///< IEC 61966-2-1 (sRGB or sYCC)
    AVCOL_TRC_BT2020_10    = 14, ///< ITU-R BT2020 for 10 bit system
    AVCOL_TRC_BT2020_12    = 15, ///< ITU-R BT2020 for 12 bit system
    AVCOL_TRC_NB,                ///< Not part of ABI
};

/**
 * YUV colorspace type.
 */
enum AVColorSpace {
    AVCOL_SPC_RGB         = 0,  ///< order of coefficients is actually GBR, also IEC 61966-2-1 (sRGB)
    AVCOL_SPC_BT709       = 1,  ///< also ITU-R BT1361 / IEC 61966-2-4 xvYCC709 / SMPTE RP177 Annex B
    AVCOL_SPC_UNSPECIFIED = 2,
    AVCOL_SPC_RESERVED    = 3,
    AVCOL_SPC_FCC         = 4,  ///< FCC Title 47 Code of Federal Regulations 73.682 (a)(20)
    AVCOL_SPC_BT470BG     = 5,  ///< also ITU-R BT601-6 625 / ITU-R BT1358 625 / ITU-R BT1700 625 PAL & SECAM / IEC 61966-2-4 xvYCC601
    AVCOL_SPC_SMPTE170M   = 6,  ///< also ITU-R BT601-6 525 / ITU-R BT1358 525 / ITU-R BT1700 NTSC / functionally identical to above
    AVCOL_SPC_SMPTE240M   = 7,
    AVCOL_SPC_YCOCG       = 8,  ///< Used by Dirac / VC-2 and H.264 FRext, see ITU-T SG16
    AVCOL_SPC_BT2020_NCL  = 9,  ///< ITU-R BT2020 non-constant luminance system
    AVCOL_SPC_BT2020_CL   = 10, ///< ITU-R BT2020 constant luminance system
    AVCOL_SPC_NB,               ///< Not part of ABI
};
#define AVCOL_SPC_YCGCO AVCOL_SPC_YCOCG


/**
 * MPEG vs JPEG YUV range.
 */
enum AVColorRange {
    AVCOL_RANGE_UNSPECIFIED = 0,
    AVCOL_RANGE_MPEG        = 1, ///< the normal 219*2^(n-8) "MPEG" YUV ranges
    AVCOL_RANGE_JPEG        = 2, ///< the normal     2^n-1   "JPEG" YUV ranges
    AVCOL_RANGE_NB,              ///< Not part of ABI
};

/**
 * Location of chroma samples.
 *
 *  X   X      3 4 X      X are luma samples,
 *             1 2        1-6 are possible chroma positions
 *  X   X      5 6 X      0 is undefined/unknown position
 */
enum AVChromaLocation {
    AVCHROMA_LOC_UNSPECIFIED = 0,
    AVCHROMA_LOC_LEFT        = 1, ///< mpeg2/4, h264 default
    AVCHROMA_LOC_CENTER      = 2, ///< mpeg1, jpeg, h263
    AVCHROMA_LOC_TOPLEFT     = 3, ///< DV
    AVCHROMA_LOC_TOP         = 4,
    AVCHROMA_LOC_BOTTOMLEFT  = 5,
    AVCHROMA_LOC_BOTTOM      = 6,
    AVCHROMA_LOC_NB,              ///< Not part of ABI
};

#endif /* AVUTIL_PIXFMT_H */
