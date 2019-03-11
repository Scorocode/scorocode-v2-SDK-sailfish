import QtQuick 2.4
import Sailfish.Silica 1.0
import Sailfish.Pickers 1.0

Page {
    id: page

    property variant p

    QtObject {
        id: internal

        property string selectedFile
    }



    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: qsTr("Upload file")
                onClicked: {
                    console.log(internal.selectedFile)
                    p.uploadFile(internal.selectedFile)
                }
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
                title: qsTr("Files/Folders")
            }
            ValueButton {
                id: files
                label: "File"
                value: internal.selectedFile ? internal.selectedFile : "None"
                onClicked: pageStack.push(filePickerPage)
            }

            ListItem {
                TextInput {
                    id: fileName
                    width: parent.width
                }

                menu: ContextMenu {
                    MenuItem {
                        text: "Download file"
                        enabled: fileName.text.length > 1
                        onClicked: {
                            p.downloadFile(fileName.text)
//                            Q_INVOKABLE void uploadFile(const QString filePath, const QString fileName);
//                            Q_INVOKABLE void downloadFile(const QString fileName);
//                            Q_INVOKABLE void renameFile(const QString fileName, const QString newFileName);
//                            Q_INVOKABLE void deleteFile(const QString fileName);
                        }
                    }
                    MenuItem {
                        enabled: internal.selectedFile && fileName.text.length > 1
                        text: "Send file"
                        onClicked: {
                            p.uploadFile(internal.selectedFile, fileName.text)
                        }
                    }
                    MenuItem {
                        text: "Delete file"
                        enabled: fileName.text.length > 1
                        onClicked: {
                            p.deleteFile(fileName.text)
                        }
                    }
                }
            }

            Row {
                width: parent.width
                TextInput {
                    id: newFileName
                    width: parent.width * 0.5
                }
                Button {
                    text: "Rename"
                    enabled: fileName.text.length > 1 && newFileName.text.length > 1
                    onClicked: {
                        p.renameFile(fileName.text, newFileName.text)
                    }
                }
            }

            ListItem {
                width: parent.width
//                height: Theme.itemSizeLarge

                TextField {
                    id: folderName
                    width: parent.width * 0.5
                    placeholderText: "Folder name"
                }

                menu: ContextMenu {
                    MenuItem {
                        text: "Get"
                        onClicked: {
                            if (folderName.text.length > 0) {
                                p.getFolderInfo(folderName.text)
                            } else {
                                p.getFolderInfo()
                            }
                        }
                    }
                    MenuItem {
                        text: "Create"
                        enabled: folderName.text.length > 1
                        onClicked: p.setDirectoryPath(folderName.text)
                    }
                    MenuItem {
                        text: "Remove"
                        enabled: folderName.text.length > 1
                        onClicked: {
                            p.deleteDirectory(folderName.text)
                        }
                    }
                }
            }

            Row {
                width: parent.width
                TextField {
                    id: newFolderName
                    width: parent.width * 0.5
                    placeholderText: "New folder name"
                }
                Button {
                    text: "Rename"
                    enabled: folderName.text.length > 1 && newFolderName.text.length > 1
                    onClicked: {
                        p.renameDirectoryPath(folderName.text, newFolderName.text)
                    }
                }
            }

        }

        Component {
            id: filePickerPage
            FilePickerPage {
                nameFilters: [ '*.*' ]
                onSelectedContentPropertiesChanged: {
                    internal.selectedFile = selectedContentProperties.filePath
                }
            }
        }
    }
}
