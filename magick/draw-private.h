/*
  Copyright 1999 ImageMagick Studio LLC, a non-profit organization
  dedicated to making software imaging solutions freely available.
  
  You may not use this file except in compliance with the License.  You may
  obtain a copy of the License at
  
    https://imagemagick.org/script/license.php
  
  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  MagickCore private image drawing methods.
*/
#ifndef MAGICKCORE_DRAW_PRIVATE_H
#define MAGICKCORE_DRAW_PRIVATE_H

#include "magick/cache.h"
#include "magick/image.h"
#include "magick/memory_.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

static inline MagickBooleanType GetFillColor(const DrawInfo *draw_info,
  const ssize_t x,const ssize_t y,PixelPacket *fill)
{
  Image
    *pattern;

  MagickBooleanType
    status;

  pattern=draw_info->fill_pattern;
  if (pattern == (Image *) NULL)
    {
      *fill=draw_info->fill;
      return(MagickTrue);
    }
  status=GetOneVirtualMethodPixel(pattern,TileVirtualPixelMethod,
    x+pattern->tile_offset.x,y+pattern->tile_offset.y,fill,&pattern->exception);
  if (pattern->matte == MagickFalse)
    fill->opacity=OpaqueOpacity;
  if (fabs(draw_info->fill_opacity-TransparentOpacity) >= MagickEpsilon)
    fill->opacity=(Quantum) (QuantumRange-(QuantumRange-fill->opacity)*
      QuantumScale*(QuantumRange-draw_info->fill_opacity));
  return(status);
}

static inline MagickBooleanType GetStrokeColor(const DrawInfo *draw_info,
  const ssize_t x,const ssize_t y,PixelPacket *stroke)
{
  Image
    *pattern;

  MagickBooleanType
    status;

  pattern=draw_info->stroke_pattern;
  if (pattern == (Image *) NULL)
    {
      *stroke=draw_info->stroke;
      return(MagickTrue);
    }
  status=GetOneVirtualMethodPixel(pattern,TileVirtualPixelMethod,
    x+pattern->tile_offset.x,y+pattern->tile_offset.y,stroke,
    &pattern->exception);
  if (pattern->matte == MagickFalse)
    stroke->opacity=OpaqueOpacity;
  if (fabs(draw_info->stroke_opacity-TransparentOpacity) >= MagickEpsilon)
    stroke->opacity=(Quantum) (QuantumRange-(QuantumRange-stroke->opacity)*
      QuantumScale*(QuantumRange-draw_info->stroke_opacity));
  return(status);
}

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
