import QtQuick 2.4
import Sailfish.Silica 1.0

Page {
    id: page

    Component.onCompleted: {
        busyIndicator.running = true
        var filter = "filter=originatorName:" + app.sdk.user + ";"
        app.sdk.getRecordList("pg", "scorocodetodo", "public", "tasks", filter)
    }

    Connections {
        target: app.sdk

        onTokenExpired: {
            app.sdk.singout()
            pageStack.replace(Qt.resolvedUrl("StartPage.qml"))
        }

        onGetRecordListDone: {
            if (tableName === "tasks") {
                busyIndicator.running = false
                var items = JSON.parse(data).items
                for (var i in items) {
                    tasksModel.append({"taskId": items[i].id,
                                          "task": items[i].taskTitle,
                                          "taskDate": items[i].deadline,
                                          "taskDesciption": items[i].taskDescription,
                                          "executor": items[i].userName,
                                          "status": items[i].taskStatus,
                                          "attachments": items[i].attachId
                                      })
                    var deadLine = new Date(items[i].deadline)
                    var currDate = new Date()
                    if(currDate > deadLine && items[i].taskStatus !== 4) {
                        app.notification.body = items[i].taskTitle + qsTr("Task is not finished")
                        app.notification.publish()
                    }
                }
            } else if (tableName === "attachments") {
                var attachmentsItems = JSON.parse(data).items
                for (var j in attachmentsItems) {
                    attachmentsModel.append({"fileName": attachmentsItems[j].name,
                                                "fileURL": attachmentsItems[j].fileURL,
                                                "id": attachmentsItems[j].attachId
                                            })
                }
            }
        }
    }

    Connections {
        target: app.notification

        onClicked: console.log("Task page Clicked")
    }

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.Portrait


    BusyIndicator {
        id: busyIndicator

        anchors.centerIn: parent
        size: BusyIndicatorSize.Large
        running: false
    }

    SilicaFlickable {
        anchors.fill: parent
        anchors.bottomMargin: panel.margin
        clip: panel.expanded

        QtObject {
            id: internal


            function rowEdit(rowIndex, rowData) {
                tasksModel.set(rowIndex, {"task": rowData.title,
                                   "taskDate": rowData.deadLine,
                                   "taskDesciption": rowData.description,
                                   "executor": rowData.executor,
                                   "status": rowData.status
                               })
                var deadLine = new Date(rowData.deadLine)
                var currDate = new Date()
                if((currDate > deadLine) === 1 && rowData.status !== 4) {
                    app.notification.body = rowData.title + qsTr("Task is not finished")
                    app.notification.publish()
                }
            }
        }

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: qsTr("Sign out")
                onClicked: {
                    app.sdk.singout()
                    pageStack.replace(Qt.resolvedUrl("StartPage.qml"))
                }
            }

            MenuItem {
                text: qsTr("Add task")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("AddTaskPage.qml"),
                                                {"name": header.title})
                    dialog.accepted.connect(function() {
                        if(dialog.taskItem){
                            var rowData = dialog.taskItem
                            var record = "{"
                                    + '"taskTitle":' + '"' + rowData.title
                                    + '", "taskDescription":"' + rowData.description
                                    + '", "originatorName":"' + app.sdk.user
                                    + '", "userName":"' + rowData.executor
                                    + '", "deadline":"' + rowData.deadLine
                                    + '", "attachId":"' + rowData.attachId
                                    + '", "taskStatus":"' + rowData.status + '"'
                                    + "}"
                            app.sdk.insertRecord("pg", "scorocodetodo", "public", "tasks", record.toString())
                            tasksModel.append({"task": rowData.title,
                                                  "taskDate": rowData.deadLine,
                                                  "taskDesciption": rowData.description,
                                                  "executor": rowData.executor,
                                                  "status": rowData.status,
                                                  "attachments": rowData.attachId
                                              })
                        }
                    })
                }
            }
        }

        PageHeader {
            id: header

            title: qsTr("Tasks list")
        }

        ListModel {
            id: tasksModel
        }

        ListModel {
            id: attachmentsModel
        }

        Component {
            id: taskDelegate

            ListItem {
                id: listItem

                anchors.margins: Theme.horizontalPageMargin
                menu: contextMenu
                width: parent.width
                ListView.onRemove: animateRemoval(listItem)
                state: "closed"


                function remove() {
                    remorseAction("Deleting", function() {
                        var item = tasksModel.get(index)
                        app.sdk.deleteRecord("pg", "scorocodetodo", "public", "tasks", item.taskId)
                        tasksModel.remove(index)
                    })
                }

                function rowEdit(rowIndex, rowData) {
                    var params = ({})
                    params.taskId = taskId
                    params.title = task
                    params.description = taskDesciption
                    params.deadLine = taskDate
                    params.executor = executor
                    params.attachId = attachments
                    var dialog = pageStack.push(Qt.resolvedUrl("AddTaskPage.qml"),
                                                {"taskItem": params, taskIndex: index})
                    dialog.accepted.connect(function() {
                        var rowData = dialog.taskItem
                        tasksModel.set(dialog.taskIndex, {"task": rowData.title,
                                           "taskDate": rowData.deadLine,
                                           "taskDesciption": rowData.description,
                                           "executor": rowData.executor,
                                           "status": rowData.status,
                                           "attachments": rowData.attachId})

                        var record = "{" + '"taskTitle":' + '"' + rowData.title
                                + '", "taskDescription":"' + rowData.description
                                + '", "userName":"' + rowData.executor
                                + '", "attachId":"' + rowData.attachId
                                + '", "deadline":"' + rowData.deadLine
                                + '", "taskStatus":"' + rowData.status + '"'  + "}"
                        app.sdk.updateRecord("pg", "scorocodetodo", "public", "tasks", rowData.taskId, record.toString())
                    })
                }

                function getColor(status) {
                    var statusColor = ["white", "green", "red", "gray", "gray"]
                    return statusColor[status]
                }

                Label {
                    id: label

                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.leftMargin: Theme.horizontalPageMargin
                    text: task
                    color: listItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                    font.bold: true
                }
                Label {
                    anchors.top: label.bottom
                    anchors.left: label.left
                    text: taskDate
                    font.pixelSize: Theme.fontSizeSmall
                    color: listItem.highlighted ? Theme.highlightColor : Theme.secondaryColor
                }
                Label {
                    id: executorName

                    anchors.top: label.bottom
                    anchors.right: taskStatusIndicator.left
                    anchors.rightMargin: Theme.horizontalPageMargin
                    text: executor
                    font.pixelSize: Theme.fontSizeSmall
                    color: listItem.highlighted ? Theme.highlightColor : Theme.secondaryColor
                }

                Rectangle {
                    id: taskStatusIndicator

                    anchors.right: parent.right
                    anchors.rightMargin: Theme.horizontalPageMargin
                    anchors.verticalCenter: parent.verticalCenter
                    height: parent.height * 0.9
                    width: 5 * Theme.pixelRatio

                    color: getColor(status)
                }

                Item {
                    id: additionalInfo

                    anchors.top: executorName.bottom
                    anchors.left: parent.left
                    anchors.leftMargin: Theme.horizontalPageMargin
                    anchors.right: taskStatusIndicator.left
                    anchors.rightMargin: Theme.horizontalPageMargin

                    height: 0


                    TextArea {
                        id: descriptionText

                        anchors.margins: Theme.horizontalPageMargin
                        height: Theme.itemSizeMedium
                        width: parent.width
                        readOnly: true
                        wrapMode: Text.WordWrap
                        horizontalAlignment: Text.AlignJustify
                        visible: additionalInfo.visible
                    }

                    ListView {
                        id: attachmnetsView

                        anchors.top: descriptionText.bottom
                        anchors.bottom: additionalInfo.bottom
                        anchors.left: additionalInfo.left
                        anchors.leftMargin: Theme.horizontalPageMargin
                        width: parent.width
                        height: Theme.itemSizeMedium
                        visible: additionalInfo.visible && attachmentsModel.count > 0
                        model: attachmentsModel
                        delegate: ListItem {
                            contentHeight: Theme.itemSizeExtraSmall
                            width: parent.width
                            Label {
                                anchors.left: parent.left
                                anchors.margins: Theme.horizontalPageMargin
                                width: parent.width
                                wrapMode: Text.WordWrap
                                horizontalAlignment: Text.AlignJustify
                                verticalAlignment: "AlignVCenter"
                                text: fileName
                            }
                            Separator {
                                anchors.bottom: parent.bottom
                                width: parent.width
                            }
                            menu: ContextMenu {
                                MenuItem {
                                    text:  qsTr("Download")

                                    onClicked: {
                                        app.sdk.downloadFile(fileURL)
                                    }
                                }
                            }
                        }
                    }
                }

                Separator {
                    anchors.bottom: parent.bottom
                    width: parent.width
                }

                Component {
                    id: contextMenu
                    ContextMenu {
                        MenuItem {
                            text: qsTr("Edit")
                            onClicked: {
                                attachmentsModel.clear()
                                rowEdit()
                            }
                        }
                        MenuItem {
                            text: qsTr("Remove")
                            onClicked: remove()
                        }
                    }
                }

                onClicked: {
                    listItem.state == 'expanded' ? listItem.state = 'closed' : listItem.state = 'expanded'

                    attachmentsModel.clear()
                    if(listItem.state == 'expanded') {
                        var filter = "filter=attachId:" + attachments + ";"
                        app.sdk.getRecordList("pg", "scorocodetodo", "public", "attachments", filter)
                        descriptionText.text = taskDesciption
                    }
                }

                states: [
                    State {
                        name: "expanded"
                        PropertyChanges {
                            target: additionalInfo
                            height: Theme.itemSizeMedium + Theme.itemSizeMedium
                            visible: true
                        }
                        PropertyChanges {
                            target: listItem
                            contentHeight: Theme.itemSizeHuge + Theme.itemSizeExtraLarge
                        }
                    },
                    State {
                        name: "closed"
                        PropertyChanges {
                            target: listItem
                            contentHeight: Theme.itemSizeLarge
                        }
                        PropertyChanges {
                            target: additionalInfo
                            height: 0
                            visible: false
                        }
                    }
                ]
            }
        }

        SilicaListView {
            anchors.top: header.bottom
            anchors.bottom: parent.bottom
            width: parent.width

            anchors.margins: Theme.horizontalPageMargin
            clip: true
            model: tasksModel
            delegate: taskDelegate


            ViewPlaceholder {
                enabled: tasksModel.count == 0 && !busyIndicator.running
                text: qsTr("No tasks")
                hintText: qsTr("Please, pull menu and add new task")
            }
        }
    }
}
