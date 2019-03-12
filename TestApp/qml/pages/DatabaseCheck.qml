import QtQuick 2.4
import Sailfish.Silica 1.0
import Sailfish.Pickers 1.0

Page {
    id: page

    property variant p

    function isDataSet() {
        return dbType.text.length > 0 && dbName.text.length > 0 && dbSchema.text.length > 0 && tableName.text.length > 0
    }

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
                title: qsTr("Database check")
            }


            TextField {
                id: dbType
                width: parent.width
                placeholderText: "Type"
            }

            TextField {
                id: dbName
                width: parent.width
                placeholderText: "DB name"
            }

            TextField {
                id: dbSchema
                width: parent.width
                placeholderText: "DB schema"
            }

            TextField {
                id: tableName
                width: parent.width
                placeholderText: "table"
            }

            TextField {
                id: recordId
                width: parent.width
                placeholderText: "record Id"
            }

            TextField {
                id: recordPayload
                width: parent.width
                placeholderText: "table values"
            }
            Row {
                width: parent.width
                spacing: Theme.paddingMedium

                TextField {
                    id: additional
                    width: parent.width * 0.5
                    placeholderText: "fiters"
                }

                TextField {
                    id: additionalValue
                    width: parent.width * 0.5
                    placeholderText: "fiters"
                }
            }

            Button {
                enabled: additional.text.length > 0 && additionalValue.text.length > 0
                text: "Append params"
                onClicked: {
                    console.log("payload", recordPayload.text)
                    p.insertRecord(dbType.text, dbName.text, dbSchema.text, tableName.text, recordPayload.text)
                }
            }


            Row {
                width: parent.width
                spacing: Theme.paddingMedium
                Button {
                    enabled: recordPayload.text.length > 0 && isDataSet()
                    text: "Insert"
                    onClicked: {
                        console.log("payload", recordPayload.text)
                        p.insertRecord(dbType.text, dbName.text, dbSchema.text, tableName.text, recordPayload.text)
                    }
                }
                Button {
                    enabled: recordPayload.text.length > 0 && isDataSet()
                    text: "Get data 1"
                    onClicked: {
                        console.log("payload", recordPayload.text)
                        p.getRecordList(dbType.text, dbName.text, dbSchema.text, tableName.text, recordPayload.text)
                    }
                }
                Button {
                    enabled: recordPayload.text.length > 0 && isDataSet() && recordId.text.length > 0
                    text: "Update"
                    onClicked: {
                        console.log("payload", recordPayload.text)
                        var arr = recordPayload.text.split(';')
                        p.updateRecord(dbType.text, dbName.text, dbSchema.text, tableName.text, recordId.text, arr)
                    }
                }
            }
            Row {
                width: parent.width
                spacing: Theme.paddingSmall
                Button {
                    enabled: isDataSet()
                    text: "Get data"
                    onClicked: {
                        p.getRecordList(dbType.text, dbName.text, dbSchema.text, tableName.text, " ")
                    }
                }
                Button {
                    enabled: isDataSet() && recordId.text.length > 0
                    text: "Get data by Id"
                    onClicked: {
                        p.getRecordById(dbType.text, dbName.text, dbSchema.text, tableName.text, recordId.text)
                    }
                }
                Button {
                    enabled: isDataSet() && recordId.text.length > 0
                    text: "Delete"
                    onClicked: {
                        p.deleteRecord(dbType.text, dbName.text, dbSchema.text, tableName.text, recordId.text)
                    }
                }
            }
        }
    }

}
