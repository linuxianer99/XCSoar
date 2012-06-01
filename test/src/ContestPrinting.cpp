/* Copyright_License {

  XCSoar Glide Computer - http://www.xcsoar.org/
  Copyright (C) 2000-2012 The XCSoar Project
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
#include "Printing.hpp"
#include <fstream>

#include "Contest/ContestManager.hpp"
#include "Trace/Trace.hpp"

void
PrintHelper::contestmanager_print(const ContestManager& man)  
{
  {
    std::ofstream fs("results/res-olc-trace.txt");
    TracePointVector v;
    man.trace_full.GetPoints(v);

    for (auto it = v.begin(); it != v.end(); ++it)
      fs << it->get_location().longitude << " " << it->get_location().latitude
         << " " << it->GetAltitude() << " " << it->GetTime()
         << "\n";
  }

  {
    std::ofstream fs("results/res-olc-trace_sprint.txt");

    TracePointVector v;
    man.trace_sprint.GetPoints(v);

    for (auto it = v.begin(); it != v.end(); ++it)
      fs << it->get_location().longitude << " " << it->get_location().latitude
         << " " << it->GetAltitude() << " " << it->GetTime()
         << "\n";
  }

  std::ofstream fs("results/res-olc-solution.txt");

  if (man.stats.solution[0].empty()) {
    fs << "# no solution\n";
    return;
  }

  if (positive(man.stats.result[0].time)) {

    for (const TracePoint* it = man.stats.solution[0].begin();
         it != man.stats.solution[0].end(); ++it) {
      fs << it->get_location().longitude << " " << it->get_location().latitude
         << " " << it->GetAltitude() << " " << it->GetTime()
         << "\n";
    }
  }
}

void 
PrintHelper::print(const ContestResult& score)
{
  std::cout << "#   score " << score.score << "\n";
  std::cout << "#   distance " << score.distance/fixed(1000) << " (km)\n";
  std::cout << "#   speed " << score.speed*fixed(3.6) << " (kph)\n";
  std::cout << "#   time " << score.time << " (sec)\n";
}
