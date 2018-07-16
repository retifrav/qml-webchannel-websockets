import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.4
import QtWebView 1.1

Window {
    visible: true
    width: 800
    minimumWidth: 600
    height: 500
    minimumHeight: 400
    title: qsTr("WebSockets example")

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5

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
                    // this signal will trigger a function at WebView side (if connected)
                    someObject.someSignal(text)
                }
                Component.onCompleted: {
                     someObject.textNeedsToBeChanged.connect(changeText)
                }
                function changeText(newText) {
                    txt.text = newText;
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            border.width: 2
            border.color: "blue"

            WebView {
                id: webView
                anchors.fill: parent
                anchors.margins: 5
                url: "qrc:/index.html"
                onLoadingChanged: {
                    if (loadRequest.errorString)
                        { console.error(loadRequest.errorString); }
                }
            }
        }
    }
}
