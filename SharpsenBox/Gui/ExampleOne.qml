import QtQuick 2.12
import QtMultimedia 5.12
import QtWebEngine 1.8

Item {
    id: gamePresentation
    property int actualGameId: window.selectedGame
    property string youtubeLink: "https://www.youtube.com/embed/T5zxTI1gxOQ?&autohide=1&showinfo=0&amp;fs=0&amp;showinfo=0"
    property string descriptionString: "<h2>Sylio</h2> Simple multiplayer game, players controls snail and tries to survive as long as it is possible, using various powerups and collecting points. In game you can change music settings choose your nickname, controls and change number of rounds."
    property string platformString: "Platform:\tWindows/Linux\nSize:\t200MB"
    Image {
        id: background
        fillMode: Image.Pad
        anchors.fill: parent
        source: _Config.gameInfoDir(actualGameId) + "b4023bea919bff9e42c85f091bc95f8d.jpg"
        opacity: 0.5
    }
    Rectangle {
        id: content
        anchors{
            top: parent.top
            bottom: parent.bottom
        }
        width: parent.width
        property int destX: parent.x
        color: "transparent"

        Text {
            id: description
            text: gamePresentation.descriptionString
            anchors {
                right: parent.right
                rightMargin: 40
                verticalCenter: holder.verticalCenter
            }
            width: 200
            wrapMode: Text.WordWrap
            color: "white"
            font.family: latoFont.name
            font.pixelSize: 15
        }

        Text {
            id: gameInfo
            text: gamePresentation.platformString
            anchors {
                left: description.left
                bottom: holder.top
                bottomMargin: 10

            }
            width: 200
            color: "white"
            font.family: latoFont.name
            font.pixelSize: 12
        }

        Item {
            id: holder
            anchors {
                left: parent.left
                top: parent.top
                leftMargin: 30
                topMargin: 150
                right: description.left
                rightMargin: 30
                bottom: parent.bottom
                bottomMargin: 65
            }

            WebEngineView {
                backgroundColor: "transparent"
                id: webView
                anchors.fill: parent
                url: gamePresentation.youtubeLink
            }
        }

        Component.onCompleted: {
            animation.stop()
            animationOp.stop()
            animation.start()
            animationOp.start()
        }

        NumberAnimation {
            id: animation
            target: content
            property: "x"
            from: content.destX + parent.width
            to: content.destX
            duration: 300
            easing.type: Easing.OutQuart
        }

        NumberAnimation {
            id: animationOp
            target: content
            property: "opacity"
            from: 0
            to: 1
            duration: 300
            easing.type: Easing.OutCubic
        }
    }
}
