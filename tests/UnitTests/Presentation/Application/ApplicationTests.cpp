#include <catch.hpp>
#include <MellowPlayer/Domain/BuildConfig.hpp>
#include <MellowPlayer/Presentation/Application/Application.hpp>
#include <QtTest/QSignalSpy>
#include "FakeQtApplication.hpp"
#include <UnitTests/Presentation/Qml/FakeContextProperties.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;

SCENARIO("Application tests")
{
    GIVEN("An IQtApplication mock")
    {
        WHEN("Application is created")
        {
            FakeQtApplication qtApplication;
            FakeContextProperties contextProperties;

            Application application(qtApplication, contextProperties);

            THEN("applicationName is set")
            {
                REQUIRE(qtApplication.appName == "MellowPlayer");
            }

            AND_THEN("applicationDisplayName is set")
            {
                REQUIRE(qtApplication.appDisplayName == "MellowPlayer");
            }

            AND_THEN("applicationVersion is set")
            {
                REQUIRE(qtApplication.appVersion == BuildConfig::getVersion());
            }

            AND_THEN("organizationDomain is set")
            {
                REQUIRE(qtApplication.orgDomain == "org.mellowplayer");
            }

            AND_THEN("organizationName is set")
            {
                REQUIRE(qtApplication.orgName == "MellowPlayer");
            }

            AND_THEN("windowIcon is set")
            {
                REQUIRE(qtApplication.isIconSet);
            }

            AND_THEN("context property has been added")
            {
                contextProperties.contains(application);
            }
        }

        FakeQtApplication qtApplication;
        FakeContextProperties contextProperties;
        Application application(qtApplication, contextProperties);

        WHEN("qtApplication.commitDataRequest is emitted, application.commitDataRequest is emitted too")
        {
            QSignalSpy spy(&application, &IApplication::commitDataRequest);
            emit qtApplication.commitDataRequest();
            REQUIRE(spy.count() == 1);
        }

        WHEN("initializing the application")
        {
            QSignalSpy spy(&application, &IApplication::initialized);
            application.initialize();

            THEN("font is set")
            {
                REQUIRE(qtApplication.isFontSet);
            }

            AND_THEN("translator is set")
            {
                REQUIRE(qtApplication.translator != nullptr);
            }

            AND_THEN("initialized signal is emitted")
            {
                REQUIRE(spy.count() == 1);
            }
        }

        WHEN("running the application")
        {
            QSignalSpy spy(&application, &IApplication::started);
            application.run();

            THEN("Qt Application is running")
            {
                REQUIRE(qtApplication.isRunning);
            }

            THEN("started signal is emitted")
            {
                REQUIRE(spy.count() == 1);
            }
        }

        WHEN("quit the application")
        {
            application.quit();

            THEN("call exit on qtApplication with valid exit code 0")
            {
                REQUIRE(qtApplication.requestedExitCode == 0);
            }
        }

        WHEN("restart the application")
        {
            application.restart();

            THEN("call exit on qtApplication with valid exit code 0")
            {
                REQUIRE(qtApplication.requestedExitCode == 0);
            }
        }

        WHEN("restoreWindow is called")
        {
            QSignalSpy spy(&application, &IApplication::restoreWindowRequest);
            application.restoreWindow();

            THEN("restoreWindowRequest is emitted")
            {
                REQUIRE(spy.count() == 1);
            }
        }

        WHEN("requestQuit")
        {
            QSignalSpy spy(&application, &Application::quitRequest);
            application.requestQuit();

            THEN("quitRequest signal is emitted")
            {
                REQUIRE(spy.count() == 1);
            }
        }

        WHEN("name is called")
        {
            THEN("return value is _application")
            {
                REQUIRE(application.name() == "_application");
            }
        }

        WHEN("asQObject is called")
        {
            THEN("return value equals address of application")
            {
                REQUIRE(application.asQObject() == &application);
            }
        }
    }
}
