/*

Copyright_License {

  XCSoar Glide Computer - http://www.xcsoar.org/
  Copyright (C) 2000-2010 The XCSoar Project
  A detailed list of copyright holders can be found in the file "AUTHORS".

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
}
*/

#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include "shapelib/mapshape.h"
#include "Geo/GeoBounds.hpp"
#include "Screen/Pen.hpp"
#include "Screen/Brush.hpp"
#include "Screen/Icon.hpp"
#include "Util/NonCopyable.hpp"
#include "Util/AllocatedArray.hpp"
#include "Math/fixed.hpp"

struct GeoPoint;
class Canvas;
class WindowProjection;
struct GeoBounds;
class LabelBlock;
struct SETTINGS_MAP;
class XShape;

class TopologyFile : private NonCopyable {
  AllocatedArray<XShape *> shpCache;

  int label_field;

public:
  /**
   * The constructor opens the given shapefile and clears the cache
   * @param shpname The shapefile to open (*.shp)
   * @param thecolor The color to use for drawing
   * @param label_field The field in which the labels should be searched
   * @return
   */
  TopologyFile(const char* shpname, const Color thecolor, int label_field);

  /**
   * The destructor clears the cache and closes the shapefile
   */
  ~TopologyFile();

  void updateCache(const WindowProjection &map_projection);

  /**
   * Paints the polygons, lines and points/icons in the TopologyFile
   * @param canvas The canvas to paint on
   * @param bitmap_canvas Temporary canvas for the icon
   * @param projection
   */
  void Paint(Canvas &canvas, BitmapCanvas &bitmap_canvas,
             const WindowProjection &projection) const;

  /**
   * Paints a topology label if the space is available in the LabelBlock
   * @param canvas The canvas to paint on
   * @param projection
   * @param label_block The LabelBlock class to use for decluttering
   * @param settings_map
   */
  void PaintLabels(Canvas &canvas,
                   const WindowProjection &projection, LabelBlock &label_block,
                   const SETTINGS_MAP &settings_map) const;

  /**
   * The threshold value for the visibility check. If the current scale
   * is below this value the contents of this TopologyFile will be drawn.
   */
  fixed scaleThreshold;

  /**
   * This function loads an icon from the resource file that
   * will be drawn at each MS_SHAPE_POINT of the TopologyFile
   * @param
   */
  void loadIcon(const int);

private:
  /**
   * The current scope of the shape cache.  If the screen exceeds this
   * rectangle, then we need to update the cache.
   */
  GeoBounds cache_bounds;

  unsigned GetSkipSteps(fixed map_scale) const;
  static rectObj ConvertRect(const GeoBounds &br);

protected:
  void ClearCache();

  Pen hPen;
  Brush hbBrush;
  MaskedIcon icon;
  shapefileObj shpfile;
  bool shapefileopen;
};

#endif
