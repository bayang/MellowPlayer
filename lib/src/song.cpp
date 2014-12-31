//---------------------------------------------------------
//
// This file is part of MellowPlayer.
//
// MellowPlayer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MellowPlayer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MellowPlayer.  If not, see <http://www.gnu.org/licenses/>.
//
//---------------------------------------------------------
#include "mellowplayer/song.h"


//---------------------------------------------------------
QString playbackStatusToString(PlaybackStatus status)
{
    switch (status) {
    case Loading:
        return "Loading";
    case Playing:
        return "Playing";
    case Paused:
        return "Paused";
    case Stopped:
        return "Stopped";
    }
    return "";
}


//---------------------------------------------------------
bool SongInfo::isValid()
{
    return songName != "";
}
