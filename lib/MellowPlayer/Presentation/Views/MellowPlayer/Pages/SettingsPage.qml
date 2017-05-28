import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import MellowPlayer 3.0

Page {
    id: settingsPage

    header: ToolBar {
        id: toolBar

        Material.primary: style.primary
        Material.foreground: style.primaryForeground
        Material.theme: style.isDark(style.primary) ? Material.Dark : Material.Light

        RowLayout {
            anchors.fill: parent

            Item {
                Layout.fillWidth: true
            }

            ToolButton {
                id: btBack

                font { family: MaterialIcons.family; pixelSize: 24 }
                hoverEnabled: true
                text: MaterialIcons.icon_keyboard_arrow_right
                onClicked: back()

                function back() {
                    stackView.pop()
                }

                Tooltip {
                    y: toolBar.implicitHeight
                    text: qsTr("Back")
                }

                Shortcut {
                    sequence: "Escape"
                    onActivated: btBack.back()
                }
            }
        }

        Label {
            anchors.centerIn: parent
            text: "Settings"
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Pane {
            padding: 0

            Layout.fillHeight: true
            Layout.maximumWidth: 256
            Layout.minimumWidth: 256

            Material.background: style.secondary
            Material.foreground: style.secondaryForeground
            Material.elevation: 4
            Material.theme: style.isDark(style.secondary) ? Material.Dark : Material.Light

            ColumnLayout {
                anchors.fill: parent

                ListView {
                    id: settingsPageList

                    model: settings.categories
                    delegate: settingsCategoryDelegate

                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Component {
                        id: settingsCategoryDelegate

                        Rectangle {
                            property double colorFactor: style.getColorScaleFactor(style.secondary);

                            color: settingsPageList.currentIndex == index ||  mouseArea.containsMouse ? Qt.darker(style.secondary, colorFactor) : style.secondary
                            height: 60; width: parent.width


                            Rectangle {
                                anchors.top: parent.top
                                anchors.left: parent.left
                                anchors.bottom: parent.bottom

                                width: 3
                                color: settingsPageList.currentIndex == index ? style.accent : "transparent"
                            }

                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: 20
                                spacing: 10

                                Label {
                                    text: model.icon
                                    font.family: MaterialIcons.family
                                    font.pixelSize: 24
                                }

                                Label {
                                    verticalAlignment: "AlignVCenter"
                                    text: model.name
                                    font.pixelSize: 20
                                }

                                Item { Layout.fillWidth: true; }
                            }

                            MouseArea {
                                id: mouseArea
                                anchors.fill: parent
                                hoverEnabled: true
                                cursorShape: containsMouse && settingsPageList.currentIndex != index ? "PointingHandCursor" : "ArrowCursor"

                                onClicked: settingsPageList.currentIndex = index
                            }
                        }
                    }
                }

                Button {
                    id: btRestoreDefaults

                    flat: true
                    highlighted: true
                    hoverEnabled: true
                    text: "Restore all to defaults"
                    onClicked: messageBoxConfirmRestore.open()

                    Layout.fillWidth: true
                    Layout.leftMargin: 4
                    Layout.rightMargin: 4

                    Tooltip {
                        text: 'Restore all settings to their <b>default value</b>.'
                    }
                }
            }
        }

        StackLayout {
            clip: true
            currentIndex: settingsPageList.currentIndex

            Layout.fillHeight: true
            Layout.fillWidth: true

            Repeater {
                model: settings.categories

                Loader {
                    anchors.fill: parent
                    source: model.qmlComponent
                }
            }
        }
    }

    MessageBoxDialog {
        id: messageBoxConfirmRestore

        buttonTexts: [qsTr("Yes"), qsTr("No")]
        message: qsTr("Are you sure you want to restore all settings to their default values?")
        title: qsTr("Confirm restore defaults")
        x: settingsPage.width / 2 - width / 2
        y: settingsPage.height / 2 - height / 2

        onAccepted: settings.restoreDefaults()
    }
}
