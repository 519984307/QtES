/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#ifndef APP_VERSION_H
#define APP_VERSION_H

namespace Core {
namespace Constants {

#define STRINGIFY_INTERNAL(x) #x
#define STRINGIFY(x) STRINGIFY_INTERNAL(x)

#define APP_VERSION 0.0.1
#define APP_VERSION_STR STRINGIFY(APP_VERSION)

#define APP_VERSION_MAJOR 0
#define APP_VERSION_MINOR 0
#define APP_VERSION_RELEASE 1

const char * const APP_VERSION_LONG      = APP_VERSION_STR;
const char * const APP_AUTHOR            = "Guo Bin";
const char * const APP_YEAR              = "2022";

#ifdef APP_VERSION_DESCRIPTION
const char * const APP_VERSION_DESCRIPTION_STR = STRINGIFY(APP_VERSION_DESCRIPTION);
#else
const char * const APP_VERSION_DESCRIPTION_STR = "";
#endif

#ifdef APP_REVISION
const char * const APP_REVISION_STR      = STRINGIFY(APP_REVISION);
#else
const char * const APP_REVISION_STR      = "";
#endif

// changes the path where the settings are saved to
#ifdef APP_SETTINGSVARIANT
const char * const APP_SETTINGSVARIANT_STR      = STRINGIFY(APP_SETTINGSVARIANT);
#else
const char * const APP_SETTINGSVARIANT_STR      = "PansimGUI";
#endif

#ifdef APP_COPY_SETTINGS_FROM_VARIANT
const char * const APP_COPY_SETTINGS_FROM_VARIANT_STR = STRINGIFY(APP_COPY_SETTINGS_FROM_VARIANT);
#else
const char * const APP_COPY_SETTINGS_FROM_VARIANT_STR = "DJEL";
#endif


#undef APP_VERSION
#undef APP_VERSION_STR
#undef STRINGIFY
#undef STRINGIFY_INTERNAL

} // Constants
} // Core

#endif //APP_VERSION_H
