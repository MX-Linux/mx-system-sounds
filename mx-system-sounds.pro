# **********************************************************************
# * Copyright (C) 2016 MX Authors
# *
# * Authors: Adrian
# *          MX & MEPIS Community <http://forum.mepiscommunity.org>
# *
# * This file is part of mx-system-sounds.
# *
# * mx-system-sounds is free software: you can redistribute it and/or modify
# * it under the terms of the GNU General Public License as published by
# * the Free Software Foundation, either version 3 of the License, or
# * (at your option) any later version.
# *
# * mx-system-sounds is distributed in the hope that it will be useful,
# * but WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# * GNU General Public License for more details.
# *
# * You should have received a copy of the GNU General Public License
# * along with mx-system-sounds.  If not, see <http://www.gnu.org/licenses/>.
# **********************************************************************/

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mx-system-sounds
TEMPLATE = app


SOURCES += main.cpp\
        mxsystemsounds.cpp

HEADERS  += mxsystemsounds.h

FORMS    += mxsystemsounds.ui

TRANSLATIONS += translations/mx-system-sounds_ca.ts \
                translations/mx-system-sounds_de.ts \
                translations/mx-system-sounds_el.ts \
                translations/mx-system-sounds_es.ts \
                translations/mx-system-sounds_fr.ts \
                translations/mx-system-sounds_it.ts \
                translations/mx-system-sounds_ja.ts \
                translations/mx-system-sounds_nl.ts \
                translations/mx-system-sounds_ro.ts \
                translations/mx-system-sounds_sv.ts


