import QtQuick 2.4
import Sailfish.Silica 1.0

Page {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    Connections {
        target: app.sdk
        onAuthError: {
            console.log("Authentication error")
            panel.show()
        }

    }

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
            id: column

            width: page.width
            spacing: Theme.paddingLarge
            PageHeader {
                title: qsTr("Register page")
            }
            Label {
                x: Theme.horizontalPageMargin
                text: qsTr("Please, register in service")
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeExtraLarge
            }
            TextField {
                id: emailId

                anchors.horizontalCenter: parent.horizontalCenter
                x: Theme.horizontalPageMargin
                width: parent.width
                placeholderText: qsTr("Email")
            }
            TextField {
                id: passwordId

                anchors.horizontalCenter: parent.horizontalCenter
                x: Theme.horizontalPageMargin
                width: parent.width
                placeholderText: qsTr("Password")
                echoMode: TextInput.PasswordEchoOnEdit
            }
            Button {
                id: loginButton

                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Register")

                onClicked: {
                    app.sdk.singup(emailId.text, passwordId.text)
                }
            }
        }
    }

    DockedPanel {
        id: panel

        width: parent.width
        height: page.height

        dock: Dock.Bottom

        ViewPlaceholder {
            enabled: panel.open
            text: qsTr("Incorrect user name or password")
            hintText: qsTr("Please, check your credentials")
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                panel.hide()
            }
        }
    }
}
