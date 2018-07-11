import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.4
import QtWebChannel 1.0
import QtWebEngine 1.1

Window {
    visible: true
    width: 800
    minimumWidth: 600
    height: 500
    minimumHeight: 400
    title: qsTr("WebChannel example")

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5

        // an object with properties, signals and methods - just like any normal Qt object
        QtObject {
            id: someObject

            // ID, under which this object will be known at WebEngineView side
            WebChannel.id: "backend"

            property string someProperty: "Break on through to the other side"

            signal someSignal(string message);

            function changeText(newText) {
                console.log(newText);
                txt.text = newText;
                return "New text length: " + newText.length;
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 0.4
            border.width: 2
            border.color: "green"

            Text {
                id: txt
                anchors.centerIn: parent
                font.pixelSize: 40
                color: "green"
                text: "Some text"
                onTextChanged: {
                    // this signal will trigger a function at WebEngineView side (if connected)
                    someObject.someSignal(text)
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            border.width: 2
            border.color: "blue"

            WebEngineView {
                id: webView
                anchors.fill: parent
                anchors.margins: 5
                url: "qrc:/index.html"
                onLoadingChanged: {
                    if (loadRequest.errorString)
                        console.error(loadRequest.errorString);
                }
                webChannel: channel
            }
            WebChannel {
                id: channel
                registeredObjects: [someObject]
            }
        }
    }
}
