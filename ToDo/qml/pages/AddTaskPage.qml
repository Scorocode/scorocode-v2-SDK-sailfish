import QtQuick 2.4
import Sailfish.Silica 1.0
import Sailfish.Pickers 1.0

Dialog {
    property var taskItem: ({})

    property int taskIndex: 0

    QtObject {
        id: internal

        property string fileName
        property string filePath
        property string attachId: new Date().getTime()
    }


    ListModel {
        id: usersModel
    }

    ListModel {
        id: attachmentsModel
    }

    Component.onCompleted: {
        console.log("get list of users")
        app.sdk.getRecordList("pg", "scorocodetodo", "public", "users")
        if (!taskItem.attachId){
            taskItem.attachId = internal.attachId
        }
    }

    Component.onDestruction: {
        usersModel.clear()
    }

    Connections {
        target: app.sdk

        onGetRecordListDone: {
            console.log(data, JSON.stringify(data))
            if(tableName === "users") {
                var items = JSON.parse(data).items

                for (var i in items) {
                    console.log("name", items[i].userName, "email", items[i].email)
                    usersModel.append({"name": items[i].email})
                }
                var filter = "filter=attachId:" + taskItem.attachId+ ";"
                app.sdk.getRecordList("pg", "scorocodetodo", "public", "attachments", filter)
            }  else if (tableName === "attachments") {
                var attachmentsItems = JSON.parse(data).items
                for (var j in attachmentsItems) {
                    attachmentsModel.append({"fileName": attachmentsItems[j].name,
                                                "fileURL": attachmentsItems[j].fileURL,
                                                "id": attachmentsItems[j].id,
                                                "attachId": attachmentsItems[j].attachId
                                            })
                }
            }
        }
    }


    Component {
        id: downloadPickerPage
        ContentPickerPage {
            title: qsTr("Select file")
            onSelectedContentPropertiesChanged: {
                internal.fileName = selectedContentProperties.fileName
                internal.filePath = selectedContentProperties.filePath
                app.sdk.uploadFile(internal.filePath, internal.fileName)
                var record = "{" + '"attachId":"' + taskItem.attachId  + '", "name":"' + internal.fileName + '", "fileURL":"' + internal.fileName + '"' + "}"
                app.sdk.insertRecord("pg", "scorocodetodo", "public", "attachments", record)
            }
        }
    }

    Column {
        width: parent.width

        DialogHeader { }

        TextField {
            id: taskTitle

            width: parent.width
            placeholderText:  qsTr("Task title")
            label:  qsTr("Title")
            text: taskItem.title

            onTextChanged: {
                taskItem.title = text
            }
        }

        TextArea {
            id: taskDescription

            width: parent.width
            placeholderText:  qsTr("Task description")
            label:  qsTr("Description")
            text: taskItem.description

            onTextChanged: {
                taskItem.description = text
            }
        }

        ValueButton {
            id: deadLineButton

            label:  qsTr("Date")
            value:  taskItem.deadLine ? taskItem.deadLine : qsTr("Select")

            onClicked: {
                var dialog = taskItem.deadLine ? pageStack.push("Sailfish.Silica.DatePickerDialog", {
                                                                    date: new Date(taskItem.deadLine)
                                                                }) : pageStack.push("Sailfish.Silica.DatePickerDialog", {
                                                                                        date: new Date()
                                                                                    })


                dialog.accepted.connect(function() {
                    value = dialog.dateText
                    taskItem.deadLine = dialog.dateText
                })
            }
        }

        TextField {
            id: executorName

            width: parent.width
            placeholderText:  qsTr("Executor's name")
            label:  qsTr("Name")
            text: taskItem.executor
            readOnly: true

            onClicked: {
                panel.show()
            }

            onTextChanged: {
                taskItem.executor = text
            }
        }

        ComboBox {
            id: taskStatus

            label: "Task status"

            menu: ContextMenu {
                MenuItem { text:  qsTr("Open") }
                MenuItem { text:  qsTr("In progress") }
                MenuItem { text:  qsTr("Suspended") }
                MenuItem { text:  qsTr("Finished") }
                MenuItem { text:  qsTr("Closed") }
            }

            onCurrentIndexChanged: {
                taskItem.status = currentIndex
            }

            Component.onCompleted: {
                taskItem.status = currentIndex
            }
        }

        ValueButton {
            enabled: taskTitle.text.length > 0
            label: qsTr("Attach file")
            value: internal.fileName ? internal.fileName : qsTr("None")
            onClicked: pageStack.push(downloadPickerPage)
        }

        ListView {
            anchors.left: parent.left
            anchors.leftMargin: Theme.horizontalPageMargin
            height: Theme.itemSizeHuge * 3
            width: parent.width
            visible: attachmentsModel.count > 0
            model: attachmentsModel
            delegate: ListItem {
                id: listItem

                height: Theme.itemSizeSmall
                width: parent.width
                anchors.left: parent.left
                anchors.leftMargin: Theme.horizontalPageMargin
                ListView.onRemove: animateRemoval(listItem)

                function remove() {
                    remorseAction("Deleting", function() {
                        var item = attachmentsModel.get(index)
                        app.sdk.deleteRecord("pg", "scorocodetodo", "public", "attachments", item.id)
                        attachmentsModel.remove(index)
                    })
                }

                menu: ContextMenu {
                    MenuItem {
                        text: qsTr("Remove")
                        onClicked: remove()
                    }
                }

                Label {
                    text: fileName
                    anchors.margins: Theme.horizontalPageMargin
                    width: parent.width
                    wrapMode: Text.WordWrap
                    horizontalAlignment: Text.AlignJustify
                }
            }
        }
    }

    onDone: {
        if (result != DialogResult.Accepted) {
            taskItem = null
        }
    }


    DockedPanel {
        id: panel

        width: parent.width
        height: Theme.itemSizeExtraLarge * 2

        dock: Dock.Bottom

        SilicaListView {
            id: usersList

            anchors.fill: parent
            anchors.leftMargin: Theme.horizontalPageMargin
            clip: true
            model: usersModel
            delegate: ListItem {
                Label {
                    anchors.left: parent.left
                    anchors.leftMargin: Theme.horizontalPageMargin
                    text: name
                }

                onClicked: {
                    executorName.text = usersModel.get(index).name
                    panel.open = false
                }

            }
        }
    }
}
