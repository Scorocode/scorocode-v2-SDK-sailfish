import QtQuick 2.4
import Sailfish.Silica 1.0
import Sailfish.Pickers 1.0

Page {
    id: page

    property variant p

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

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
                title: qsTr("Websocket check")
            }

            TextField {
                id: socketMessage

                width: parent.width
                placeholderText: "Websocket message"
            }

            Row {
                width: parent.width
                spacing: Theme.paddingMedium
                Button {
                    id: sendMessage

                    width: parent.width * 0.3
                    enabled: socketMessage.text.length > 0
                    text: "Add"
                    onClicked: {
                        p.on(socketMessage.text)
                    }
                }
                Button {
                    id: removeMessage

                    width: parent.width * 0.3
                    enabled: socketMessage.text.length > 0
                    text: "Del"
                    onClicked: {
                        p.off(socketMessage.text)
                    }
                }
                Button {
                    id: sendMessageOnce

                    width: parent.width * 0.3
                    enabled: socketMessage.text.length > 0
                    text: "Once"
                    onClicked: {
                        p.once(socketMessage.text)
                    }
                }
            }

            TextArea {
                id: reponseMessage

                width: parent.width
                readOnly: true

                text: p.websocketMessage
            }
        }
    }
}
