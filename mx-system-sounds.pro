# **********************************************************************
# * Copyright (C) 2016 MX Authors
# *
# * Authors: Adrian
# *          MX Linux <http://mxlinux.org>
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

TRANSLATIONS += translations/mx-system-sounds_am.ts \
                translations/mx-system-sounds_ca.ts \
                translations/mx-system-sounds_cs.ts \
                translations/mx-system-sounds_de.ts \
                translations/mx-system-sounds_el.ts \
                translations/mx-system-sounds_es.ts \
                translations/mx-system-sounds_fi.ts \
                translations/mx-system-sounds_fr.ts \
                translations/mx-system-sounds_hi.ts \
                translations/mx-system-sounds_hr.ts \
                translations/mx-system-sounds_hu.ts \
                translations/mx-system-sounds_it.ts \
                translations/mx-system-sounds_ja.ts \
                translations/mx-system-sounds_kk.ts \
                translations/mx-system-sounds_lt.ts \
                translations/mx-system-sounds_nl.ts \
                translations/mx-system-sounds_pl.ts \
                translations/mx-system-sounds_pt.ts \
                translations/mx-system-sounds_pt_BR.ts \
                translations/mx-system-sounds_ro.ts \
                translations/mx-system-sounds_ru.ts \
                translations/mx-system-sounds_sk.ts \
                translations/mx-system-sounds_sv.ts \
                translations/mx-system-sounds_tr.ts \
                translations/mx-system-sounds_uk.ts \
                translations/mx-system-sounds_zh_TW.ts

RESOURCES += \
    images.qrc


