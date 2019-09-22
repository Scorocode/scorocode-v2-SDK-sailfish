import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Notifications 1.0

import "pages"

import scorocode.sdk 1.0

ApplicationWindow
{
    id: app

    property alias sdk: scorocode
    property alias notification: notificationItem

    initialPage: Component { StartPage { } }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: defaultAllowedOrientations

    //Create scorocode sdk item
    ScorocodeSDK {
        id: scorocode
    }

    Notification {
        id: notificationItem

        summary: "Scorocode notification"
        body: "Notification body"
        expireTimeout: 10000
    }
}
