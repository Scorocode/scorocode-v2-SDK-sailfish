import QtQuick 2.0
import Sailfish.Silica 1.0

import scorocode.sdk 1.0

Page {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: qsTr("Websocket")
                onClicked: pageStack.push(Qt.resolvedUrl("WebSocket.qml"), {p: proxy})
            }
            MenuItem {
                text: qsTr("Database")
                onClicked: pageStack.push(Qt.resolvedUrl("DatabaseCheck.qml"), {p: proxy})
            }
            MenuItem {
                text: qsTr("Files/Folders")
                onClicked: pageStack.push(Qt.resolvedUrl("Files.qml"), {p: proxy})
            }
        }

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
            id: column

            width: page.width
            spacing: Theme.paddingLarge
            PageHeader {
                title: qsTr("UI Template")
            }
            Label {
                id: infoText
                x: Theme.horizontalPageMargin
                text: qsTr("Hello Sailors")
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeExtraLarge
            }
            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Singin"

                BusyIndicator {
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    size: BusyIndicatorSize.Small
                    running: proxy.singing
                }

                onClicked: {
                    proxy.singin()
                }
            }
            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Singup"

                BusyIndicator {
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    size: BusyIndicatorSize.Small
                    running: proxy.singing
                }

                onClicked: {
                    proxy.singup()
                }
            }
            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Get user info"

                onClicked: {
                    proxy.getUserInfo()
                }
            }
            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Singout"

                onClicked: {
                    proxy.singout()
                }
            }

            ProxySDK {
                id: proxy

                onTokenChanged: {
                    var d = JSON.parse(data)
                    console.log("Got info", data)
                    infoText.text = d.token.toString()
                }
            }
        }
    }
}
