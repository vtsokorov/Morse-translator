import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.2

ApplicationWindow  {
    width: 640
    height: 480
    visible: true
    title: qsTr("Morse translate")

    FileDialog {
        id: fileOpenDialog
        title: "Выберите файл..."
        folder: shortcuts.home
        nameFilters: [ "text files (*.txt)", "All files (*)" ]
        selectExisting: true
        visible: false
        onAccepted: {
            var path = fileOpenDialog.fileUrl.toString()
            path = decodeURIComponent(path.replace(/^(file:\/{2})/,""))
            backend.readFile(path)
            fileOpenDialog.close()
            statusBarLabel.text = "Read file"
            inputText.text = backend.content
        }
        onRejected: {
            fileOpenDialog.close()
        }
    }

    FileDialog {
        id: fileSaveDialog
        title: "Укажите путь и имя файла для сохранения"
        folder: shortcuts.home
        nameFilters: [ "text files (*.txt)", "All files (*)" ]
        selectExisting: false
        visible: false
        onAccepted: {
            var path = fileSaveDialog.fileUrl.toString()
            path = decodeURIComponent(path.replace(/^(file:\/{2})/,""))
            backend.result = resultText.text
            backend.saveFile(path)
            fileSaveDialog.close()
            statusBarLabel.text = "Save file"
        }
        onRejected: {
            fileSaveDialog.close()
        }
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("&Фаил")
            MenuItem {
                text: qsTr("&Новый...")
                shortcut: "Ctrl+N"
                objectName: "newAction"
                onTriggered: {
                    backend.createNew()
                    inputText.text = backend.content
                    resultText.text = backend.result
                    typeinput.text = "Input text"
                    statusBarLabel.text = "New document"
                }
            }
            MenuItem {
                text: qsTr("&Открыть...")
                shortcut: "Ctrl+O"
                objectName: "openAction"
                onTriggered: {
                    fileOpenDialog.open();
                }
            }
            MenuItem {
                text: qsTr("&Сохранить")
                shortcut: "Ctrl+S"
                objectName: "saveAction"
                onTriggered: {
                    fileSaveDialog.open();
                }
            }
            MenuItem {
                text: qsTr("&Выйти")
                shortcut: "Ctrl+X"
                objectName: "quitAction"
                onTriggered: Qt.quit();
            }
        }
    }
    ColumnLayout {
        anchors.fill: parent
        SplitView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            orientation: Qt.Vertical
            handleDelegate: Rectangle {
                height: 5
                color: "black"
            }
            Rectangle {
                height: 200
                TextEdit {
                    objectName: "inputText"
                    id: inputText
                    text: qsTr("")
                    wrapMode: Text.WordWrap
                    font.pixelSize: 20
                    anchors.fill: parent
                    font.capitalization: Font.AllLowercase
                    selectByMouse: true
                    //validator: RegExpValidator {regExp: RegExp("[a-z]+")}
                    property string placeholderText: "Введите текст..."
                    Text {
                        text: inputText.placeholderText
                        font.pixelSize: 20
                        color: "#aaa"
                        visible: !inputText.text && !inputText.activeFocus
                    }

                    function isMorse(text){
                        return text.trim().match(new RegExp("^(\\.|-)+(\\s{1,}(\\.|-)+)*$")) ? true : false
                    }

                    onTextChanged: {
                        let type = isMorse(inputText.text)
                        typeinput.text = type ? "Morse to Text" : "Text to Morce"
                        backend.inputContent(inputText.text, type)
                        resultText.text = backend.result
                        statusBarLabel.text = "Input data"
                    }
                }
            }
            Rectangle {
                height: 200
                TextEdit {
                    objectName: "showResult"
                    id: resultText
                    text: qsTr("")
                    wrapMode: Text.WordWrap
                    font.pixelSize: 20
                    readOnly: true
                    selectByMouse: true
                    anchors.fill: parent
                    font.capitalization: Font.AllLowercase
                    property string placeholderText: "Результат перевода"
                    Text {
                        text: resultText.placeholderText
                        font.pixelSize: 20
                        color: "#aaa"
                        visible: !resultText.text && !resultText.activeFocus
                    }
                }
            }
        }
    }
    statusBar: StatusBar {
        RowLayout {
            anchors.fill: parent
            Label {
                objectName: "statusBarLabel"
                id: statusBarLabel
                text: "Ready!"
            }
            Label {
                objectName: "typeinput"
                id: typeinput
                Layout.alignment: Qt.AlignRight
                text: "type input"
            }
        }
    }
}
