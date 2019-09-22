import QtQuick 2.4
import Sailfish.Silica 1.0

Page {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.Portrait

    Connections {
        target: app.sdk
        onSinginSuccefull: {
            if (status) {
                pageStack.replace(Qt.resolvedUrl("TasksListPage.qml"))
            }
        }        

        onSingupSuccefull: {
            if (status) {
                console.log(data)
            }
        }

        onSingingChanged: {
            busyIndicator.running = singing
        }

        onAuthError: {
            panel.show()
        }

    }

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("TasksListPage.qml"))
            }
            MenuItem {
                text: qsTr("Register")
                onClicked: pageStack.push(Qt.resolvedUrl("RegisterPage.qml"))
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
                title: qsTr("Sign in")
            }
            Label {
                x: Theme.horizontalPageMargin
                text: qsTr("Hello Sailors")
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
                text: qsTr("Sign in")

                onClicked: {
//                    scorocode.singin(emailId.text, passwordId.text)
                    app.sdk.singin(emailId.text, passwordId.text)
                    //pageStack.replace(Qt.resolvedUrl("TasksListPage.qml"))
                }
            }
        }
    }

    TouchBlocker {
        anchors.fill: parent
        enabled: busyIndicator.running
    }

    BusyIndicator {
        id: busyIndicator

        anchors.centerIn: parent
        size: BusyIndicatorSize.Large
        running: false
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
