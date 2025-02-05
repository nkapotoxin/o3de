/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <TestImpactFramework/TestImpactConsoleMain.h>
#include <TestImpactFramework/TestImpactSequenceReportException.h>
#include <TestImpactFramework/TestImpactTestSequence.h>
#include <TestImpactFramework/TestImpactUtils.h>

#include <TestImpactCommandLineOptions.h>

#include <AzCore/std/string/string.h>

#include <iostream>

namespace TestImpact::Console
{
    //! The set of available foreground colors.
    enum class Foreground
    {
        Black = 30,
        Red,
        Green,
        Yellow,
        Blue,
        Magenta,
        Cyan,
        White
    };

    //! The set of available background colors.
    enum class Background
    {
        Black = 40,
        Red,
        Green,
        Yellow,
        Blue,
        Magenta,
        Cyan,
        White
    };

    //! Returns a string to be used to set the specified foreground and background color.
    AZStd::string SetColor(Foreground foreground, Background background);

    //! Returns a string with the specified string set to the specified foreground and background color followed by a color reset.
    AZStd::string SetColorForString(Foreground foreground, Background background, const AZStd::string& str);

    //! Returns a string to be used to reset the color back to white foreground on black background. 
    AZStd::string ResetColor();

    //! Gets the appropriate console return code for the specified test sequence result.
    ReturnCode GetReturnCodeForTestSequenceResult(TestSequenceResult result);

    //! Wrapper around sequence reports to optionally serialize them and transform the result into a return code.
    template<typename SequenceReportType>
    ReturnCode ConsumeSequenceReportAndGetReturnCode(const SequenceReportType& sequenceReport, const CommandLineOptions& options)
    {
        if (options.HasSequenceReportFilePath())
        {
            std::cout << "Exporting sequence report '" << options.GetSequenceReportFilePath().value().c_str() << "'" << std::endl;
            const auto sequenceReportJson = SerializeSequenceReport(sequenceReport);
            WriteFileContents<SequenceReportException>(sequenceReportJson, options.GetSequenceReportFilePath().value());
        }

        return GetReturnCodeForTestSequenceResult(sequenceReport.GetResult());
    }
} // namespace TestImpact::Console
